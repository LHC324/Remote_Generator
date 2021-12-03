/********************************************************************
 **--------------文件信息---------------------------------------------
 **文   件   名：Event.c
 **创 建  日 期：2020年1月4日
 **最后修改日期：
 **版 权 信  息: 云南兆富科技有限公司
 **程   序   员：
 **版   本   号：
 **描        述：
 **修 改 日  志:
 *********************************************************************/

#include "Event.h"
#include "multi_timer.h"
#include "eusart1.h"
#include "eusart2.h"
#include "adc.h"
#include "pFunc.h"
#include "Modbus.h"

/*发电机启动模式*/
uint8_t gAlternator = AUTO_MODE;
/*当前状态编码*/
uint16_t gCurrent_code = 0x0000;
/*远程操作发电机打开互斥信号量:市电和发电机电压存在时为false,否则为true*/
bool gStart_mutex = false;
/*远程操作发电机关闭互斥信号量:市电和发电机存在时为true,否则为false*/
bool gStop_mutex = false;
/*软件计数器*/
//uint32_t gTimes = 0;
/*记录发电机启动次数*/
//uint8_t start_counter = 0;


void Event1(void *arg);
void Event2(void *arg);
void Event3(void *arg);
void Event4(void *arg);
void Event5(void *arg);
void Event6(void *arg);
void Event7(void *arg);
void Event8(void *arg);

Event_Handle_t Events_Group[] = {
    {"ALL_VOLTAGE_LOW",
        {false, false, false}, .error_code.record = 0x01FF, true, false, .pFunc = &Event1},
    { "GEN_VOLTAGE_FIRST_HIGE",
        {false, false, true}, .error_code.record = 0x02FF, false, false, .pFunc = &Event2},
    { "CITY_VOLTAGE_FIRST_HIGE",
        {false, true, false}, .error_code.record = 0x03FF, false, false, .pFunc = &Event3},
    { "CITY_VOLTAGE_CMP_HIGH",
        {false, true, true}, .error_code.record = 0x04FF, false, true, .pFunc = &Event4},
    { "VBAT_VOLTAGE_FIRST_HIGH",
        {true, false, false}, .error_code.record = 0x05FF, true, false, .pFunc = &Event5},
    { "GEN_VOLTAGE_CMP_HIGE",
        {true, false, true}, .error_code.record = 0x06FF, false, false, .pFunc = &Event6},
    { "CITY_VOLTAGE_CMP_HIGH",
        {true, true, false}, .error_code.record = 0x07FF, false, false, .pFunc = &Event7},
    { "ALL_VOLTAGE_HIGH",
        {true, true, true}, .error_code.record = 0x08FF, false, true, .pFunc = &Event8}
};

#define EVENTS_SIZE (sizeof(Events_Group) / sizeof(Event_Handle_t))

/*PC与MCU协议*/
MASTER_FUNC_MAP SlaveFuncMapbuff[] = {/*设置PLC参数*/
    {.Cmd = MODBUS_CMD_05, .pCallBack = Modbus_05}
};

#define SlaveFuncMapbuffSize  sizeof(SlaveFuncMapbuff)/sizeof(MASTER_FUNC_MAP)

/*设置运行时编码*/
__inline void Set_Code(Event_Handle_t *handle, uint8_t code) {
    handle->error_code.r.code = code;
}

/*清除运行时编码*/
__inline void Reset_Code(Event_Handle_t *handle) {
    handle->error_code.r.code = 0xFF;
}

/*获得软件计数器下次目标时间*/
//uint32_t Get_SoftwareTime(uint8_t size){
//    return (gTimes % size);
//}

/*变频器启动*/
bool Inverter_Start(uint8_t delay_times) {
    static uint8_t counter;
    if (++counter >= delay_times) {
        counter = 0;
        return true;
    }
    return false;
}

/*发电机关闭*/
//void Gen_Stop(void) {
//  /*打开发电机停止继电器*/
//   MOTOR_STOP_RELAY_ON;
////   RELAY1_ON;
//}

/*发电机启动*/
void Gen_Start(bool changing_flag, Event_Handle_t *handle) {
    /*记录发电机启动次数*/
    static uint8_t start_counter = 0;
    static bool gen_state = false;

    if (gAlternator == AUTO_MODE) {
//        /*首次直接启动*/
//        if (start_counter == 0) {
//            MOTOR_START_ON;
//        }
//        /*记录启动次数*/
//        start_counter++;
        /*6S启动一次，三次不成功，不再自动启动*/
        if (((start_counter++) % GEN_START_TIMES) == 0U) {
            /*cpu对发电机启动电机供电,状态切换*/
            gen_state ^= true;
            MOTOR_START = gen_state;
        }
        /*超过最大启动次数，启动模式切换到手动*/
        if (start_counter > MAX_START_TIMES) {
            gen_state = false;
            start_counter = 0;
            /*切换到手动模式*/
            gAlternator = MANU_MODE;
            /*断开cpu对发电机启动电机供电*/
            MOTOR_START_OFF;
            Set_Code(handle, CODE2);
#if (USING_DEBUG)
            DEBUG("ERROR : The generator failed to start and exceeded the maximum number of times ! Switch to manual mode !!\r\n");
#endif
            /*记录完故障后直接返回*/
            return;
        }
    } else {
        /*清空启动次数*/
        gen_state = false;
        start_counter = 0;
    }
    /*等待供电稳定*/
    if (GET_GEN_VOLTAGE() >= POWEROFF2_THR) {
        /*发电机启动成功，清除启动记录*/
        if (start_counter) {
            gen_state = false;
            start_counter = 0;
        }
        /*线路切换继电器闭合，线路切换到发电机供电线路*/
        POWER_CHARGE_RELAY_ON;
        /*断开cpu对发电机启动电机供电*/
        MOTOR_START_OFF;
        /*等待变频器电源稳定: 15s*/
        if (Inverter_Start(SETTLE_TIMES)) {
            /*打开变频器端子继电器*/
            POST_ON;
#if(USING_DEBUG)
            DEBUG("NOTE : Inverter start .\r\n");
#endif         
        }
        /*电池需要充电*/
        if (changing_flag) {
            /*打开电池充电开关*/
        }
        Set_Code(handle, CODE0);
#if(USING_DEBUG)
        DEBUG("SUCCESS : Generator start .\r\n");
#endif   
    } else { /*报警:发电机故障/线路故障*/
        Set_Code(handle, CODE1);
#if (USING_DEBUG)
        DEBUG("WARNING : Open Generator fault / line fault ! The current counts %d.\r\n", start_counter);
#endif        
    }
}

/*持续检测市电电压*/
void City_VoltageCheck(bool changing_flag, Event_Handle_t *handle) {
    /*持续检测市电电压*/
    if (GET_CITY_VOLTAGE() >= POWEROFF1_THR) {
        Set_Code(handle, CODE5);
        /*等待变频器电源稳定: 15s*/
        if (Inverter_Start(SETTLE_TIMES)) {
            /*打开变频器端子继电器*/
            POST_ON;
#if(USING_DEBUG)
            DEBUG("NOTE : Inverter start .\r\n");
#endif         
        }

        /*电池需要充电*/
        if (changing_flag) {
            /*打开电池充电开关*/
        }
#if(USING_DEBUG)
        DEBUG("NOTE : The mains power supply is normal .\r\n");
#endif
    } else { /*市电供电不稳定/检测不稳定*/
        Set_Code(handle, CODE6);
#if (USING_DEBUG)
        DEBUG("WARNING : Unstable mains power supply !\r\n");
#endif
    }
}

/*持续检测发电机电压*/
void Gen_VoltageCheck(bool changing_flag, Event_Handle_t *handle) {
    /*持续检测发电机电压*/
    if (GET_GEN_VOLTAGE() >= POWEROFF2_THR) {
        /*等待变频器电源稳定: 15s*/
        if (Inverter_Start(SETTLE_TIMES)) {
            /*打开变频器端子继电器*/
            POST_ON;
#if(USING_DEBUG)
            DEBUG("NOTE : Inverter start .\r\n");
#endif         
        }
        //        /*打开变频器端子继电器*/
        //        POST_ON; //////////////////////////////此处为了满足远程启动发电机时
        Set_Code(handle, CODE3);
        /*电池需要充电*/
        if (changing_flag) {
            /*打开电池充电开关*/
        }
#if(USING_DEBUG)
        DEBUG("NOTE : The generator is working .\r\n");
#endif
    } else { /*报警:发电机故障/供电不稳定/检测不稳定*/
        Set_Code(handle, CODE4);
#if (USING_DEBUG)
        DEBUG("WARNING : Generator fault / Unstable power supply !\r\n");
#endif
    }
}

/*@event: 事件1发生，检测电池、市电、发电机电压均比较低
 *@action: 电池需要充电、关闭所有动作继电器、电压输出控制，发出报警
 * @note: 发生线路切换
 */
void Event1(void *arg) {
    if (arg == NULL) {
        return;
    }
    /*关闭变频器端子继电器*/
    POST_OFF;
    /*先关闭发电机停止继电器*/
    MOTOR_STOP_RELAY_OFF;
    /*断开电池充电线路*/
    CHARGE_EN_OFF;
    //    /*cpu对发电机启动电机供电*/
    //    MOTOR_START_ON;
    Gen_Start(true, (Event_Handle_t *) arg);
}

/*@event: 事件2发生，检测电池、市电比较低、发电机电压比较高
 *@action: 电池需要充电、市电供电线路断开
 */
void Event2(void *arg) {
    if (arg == NULL) {
        return;
    }
    /*切断发电机起动机供电*/
    MOTOR_START_OFF;
    /*关闭发电机停止继电器*/
    MOTOR_STOP_RELAY_OFF;
    /*线路切换继电器打开，线路切换到发电机供电线路*/
    POWER_CHARGE_RELAY_ON;
    /*持续检测发电机电压*/
    Gen_VoltageCheck(true, (Event_Handle_t *) arg);
}

/*@event: 事件3发生，检测电池、发电机电压比较低、市电比较高
 *@action: 电池需要充电、发电机供电线路断开
 */
void Event3(void *arg) {
    if (arg == NULL) {
        return;
    }
    /*切断发电机起动机供电*/
    MOTOR_START_OFF;
    /*打开发电机停止继电器*/
    MOTOR_STOP_RELAY_ON;
    /*线路切换继电器断开，线路切换到市电220v供电线路*/
    POWER_CHARGE_RELAY_OFF;
    /*持续检测市电电压*/
    City_VoltageCheck(true, (Event_Handle_t *) arg);
}

/*@event: 事件4发生，检测电池比较低、市电、发电机电压比较高
 *@action: 电池需要充电、发电机供电线路断开，切换到市电220v
 * @note: 发生线路切换
 */
void Event4(void *arg) {
    if (arg == NULL) {
        return;
    }
    /*关闭变频器端子继电器*/
    POST_OFF;
    /*切断发电机起动机供电*/
    MOTOR_START_OFF;
    /*打开发电机停止继电器*/
    MOTOR_STOP_RELAY_ON;
    /*持续检测发电机电压,供电完全断开后，再切换到市电220v*/
    if (GET_GEN_VOLTAGE() < ERROR_VOLTAGE) {
        /*线路切换继电器断开，线路切换到市电220v供电线路*/
        POWER_CHARGE_RELAY_OFF;
        Set_Code((Event_Handle_t *) arg, CODE7);
        /*等待变频器电源稳定: 15s*/
        if (Inverter_Start(SETTLE_TIMES)) {
            /*打开变频器端子继电器*/
            POST_ON;
#if(USING_DEBUG)
            DEBUG("NOTE : Inverter start .\r\n");
#endif         
        }
#if(USING_DEBUG)
        DEBUG("NOTE : Switch to mains power supply .\r\n");
#endif
    } else { /*发电机关闭失败：发电机故障/线路故障*/
        Set_Code((Event_Handle_t *) arg, CODE8);
#if(USING_DEBUG)
        DEBUG("ERROR : Generator shutdown failed !\r\n");
#endif        
    }
    /*持续检测市电电压*/
    City_VoltageCheck(true, (Event_Handle_t *) arg);
}

/*@event: 事件5发生，检测电池比较高、市电、发电机电压比较低
 *@action: 关闭电池充电开关、闭合发电机供电线路，切换到发电机供电
 * @note : 发生线路切换
 */
void Event5(void *arg) {
    if (arg == NULL) {
        return;
    }
    /*关闭变频器端子继电器*/
    POST_OFF;
    /*关闭发电机停止继电器*/
    MOTOR_STOP_RELAY_OFF;
    /*断开电池充电线路*/
    CHARGE_EN_OFF;
    /*启动发电机*/
    Gen_Start(false, (Event_Handle_t *) arg);
}

/*@event: 事件6发生，检测电池比较高、市电低、发电机电压高
 *@action: 关闭电池充电开关、维持发电机供电
 */
void Event6(void *arg) {
    if (arg == NULL) {
        return;
    }
    /*切断发电机起动机供电*/
    MOTOR_START_OFF;
    /*关闭发电机停止继电器*/
    MOTOR_STOP_RELAY_OFF;
    /*断开电池充电线路*/
    CHARGE_EN_OFF;
    /*线路切换继电器打开，线路切换到发电机供电线路*/
    POWER_CHARGE_RELAY_ON;
    /*持续检测发电机电压*/
    Gen_VoltageCheck(false, (Event_Handle_t *) arg);
}

/*@event: 事件7发生，检测电池电压高、市电高、发电机电压低
 *@action: 关闭电池充电开关、维持市电供电
 */
void Event7(void *arg) {
    if (arg == NULL) {
        return;
    }
    /*切断发电机起动机供电*/
    MOTOR_START_OFF;
    /*打开发电机停止继电器*/
    MOTOR_STOP_RELAY_ON;
    /*断开电池充电线路*/
    CHARGE_EN_OFF;
    /*线路切换继电器断开，线路切换到市电220v供电线路*/
    POWER_CHARGE_RELAY_OFF;
    /*持续检测市电电压*/
    City_VoltageCheck(false, (Event_Handle_t *) arg);
}

/*@event: 事件8发生，检测电池电压高、市电高、发电机电压高
 *@action: 关闭电池充电开关、维持市电供电
 *@note : 发生线路切换
 */
void Event8(void *arg) {
    if (arg == NULL) {
        return;
    }
    /*关闭变频器端子继电器*/
    POST_OFF;
    /*切断发电机起动机供电*/
    MOTOR_START_OFF;
    /*打开发电机停止继电器*/
    MOTOR_STOP_RELAY_ON;
    /*断开电池充电线路*/
    CHARGE_EN_OFF;
    /*持续检测发电机电压,供电完全断开后，再切换到市电220v*/
    if (GET_GEN_VOLTAGE() < ERROR_VOLTAGE) {
        /*线路切换继电器断开，线路切换到市电220v供电线路*/
        POWER_CHARGE_RELAY_OFF;
        Set_Code((Event_Handle_t *) arg, CODE7);
#if(USING_DEBUG)
        DEBUG("NOTE : Switch to mains power supply .\r\n");
#endif
    } else { /*发电机关闭失败：发电机故障/线路故障*/
        Set_Code((Event_Handle_t *) arg, CODE8);
#if(USING_DEBUG)
        DEBUG("ERROR : Generator shutdown failed !\r\n");
#endif        
    }
    /*持续检测市电电压*/
    City_VoltageCheck(false, (Event_Handle_t *) arg);
}

/*取得当前工作模式*/
void Get_CurrentSate(adc_handle_t *adc_obj, bool *arry) {
    /*Quantify the voltage of each channel*/
    for (uint8_t i = 0; i < MAX_CHANNEL; i++)
        if (adc_obj[i].counts < CYCLE_TRANSIT) {
            arry[i] = true;
        } else {
            arry[i] = false;
        }
}

//#pragma OPTIMIZE(0)
//#pragma switch speed

/*事件轮询*/
void Events_Poll(void) {
    Event_Handle_t *pHandle = NULL; //volatile 
    bool current_state[MAX_CHANNEL] = {false};
    //	DEBUG("ok\r\n");
    Get_CurrentSate(adc, current_state);
    //    for(uint8_t i = 0; i < 3; i++)
    //    DEBUG("%d\r\n",current_state[i]);
    for (uint8_t i = 0; i < EVENTS_SIZE; i++) {
        if ((current_state[0] == Events_Group[i].compose[0]) &&
                (current_state[1] == Events_Group[i].compose[1]) &&
                (current_state[2] == Events_Group[i].compose[2])) {
            pHandle = &Events_Group[i];
            Reset_Code(pHandle);
            if (pHandle) {
                pHandle->pFunc(pHandle);
            }
            gCurrent_code = pHandle->error_code.record;
            gStart_mutex = pHandle->start_mutex;
            gStop_mutex = pHandle->stop_mutex;
#if (USING_DEBUG)
            DEBUG("%s\r\nError code is :0x%X\r\n", Events_Group[i].state, gCurrent_code);
#endif
            break;
        }
    }
}

/*当前工作系统状态检测*/
void Status_Check(void *arg) {
    UNUSED(arg);
    static uint8_t cycle;

    for (uint8_t i = 0; i < EVENTS_SIZE; i++)
        /*Battery voltage / Mains / generator is lower than the lower limit of voltage*/
        if (adc[i].adcValue < VBAT_NOFULL_THR) {
            adc[i].counts++;
        }
    /*Execute actions after a certain detection period is met*/
    if (++cycle >= CYCLE_TIME_MAX) {
        cycle = 0;
        /*The current generator mode is automatic mode*/
        //		 if (){
        /*Software counter: increment once in 3S*/
        //        gTimes++;
        Events_Poll();
        //		 }
        for (uint8_t i = 0; i < EVENTS_SIZE; i++) {
            adc[i].counts = 0;
        }
    }
}

/*电压检测*/
void Voltage_Check(void *arg) {
    UNUSED(arg);
    uint8_t i = 0;
    sideparm_t adcValue = 0;

    for (i = 0; i < MAX_CHANNEL; i++) {
        //        adc[i].adc_done_flag = false;
        adcValue = sidefilter(adc[i].sideObj, ADC_GetConversion(adc[i].channel));
#if(USING_DEBUG)
        //        adcValue = ADC_GetConversion(adc[i].channel);
        //        DEBUG("channel %d, value is %d\r\n", i, adcValue);
#endif
        switch (adc[i].channel) {
            case ADC_VBAT: adc[i].adcValue = GET_ADCVALUE(VBAT_MAX, adcValue); //(VBAT_MAX * (float) adcValue) / 1024.0f;
                break;
            case ADC_CITY_POWER:
            case ADC_GEN_POWER:
            {
                adc[i].adcValue = GET_ADCVALUE(VCHECK_MAX, adcValue) * RATIO(); //1.4f + (3.3f * 6.0f * (float) adcValue) / 1024.0f;
                if (adc[i].adcValue < ERROR_VOLTAGE) {
                    adc[i].adcValue = 0.0f;
                }
            }
                break;
        }
#if(USING_DEBUG)       
        //    DEBUG("channel %d, value is %f\r\n", i, adc[i].adcValue);
#endif
    }
}

#define CMP_LEN(_L) (_L >= 2U ? _L / 2U : 0x01)

__inline void Data_Report(uint8_t cmd, uint16_t start_addr, uint8_t *pdata, uint8_t len) {
    uint8_t temp_len = 0;
    /*The pointer is not null and the data length is not zero*/
    if (pdata && len) {
        /*Organize Modbus protocol package*/
        temp_len = Set_ModbusFrame(pdata, len, CMP_LEN(len), cmd, start_addr);
        /*Data reporting to the middle end of the Internet of things*/
        Uart2_Send(report_buffer, temp_len);
    }
}

/*实时上报*/
void Timing_Report(void *arg) {
    UNUSED(arg);
    static uint8_t change_counts;
    float temp_arry[MAX_CHANNEL] = {0};
    uint16_t temp_value = gCurrent_code;

    switch (++change_counts) {
        case 1:
        {
            for (uint8_t i = 0; i < MAX_CHANNEL; i++) {
                temp_arry[i] = adc[i].adcValue;
                /*Report one after the exchange is completed*/
                Endian_Swap((uint8_t *) & temp_arry[i], 0U, sizeof (float));
            }
            /*Report three channel voltage values*/
            Data_Report(MODBUS_CMD_46, GEN_VOLTAGE_ADDR, (uint8_t *) temp_arry, sizeof (temp_arry));
        }
            break;
        case 2:
        {
            /*Report generator status*/
            Data_Report(MODBUS_CMD_45, GEN_CONTROL_ADDR2, &gAlternator, sizeof (gAlternator));
        }
            break;
        case 3:
        {
            change_counts = 0;
            /*Report current controller status*/
            Endian_Swap((uint8_t *) & temp_value, 0U, sizeof (temp_value));
            Data_Report(MODBUS_CMD_46, GEN_FAULT_CODE_ADDR, (uint8_t *) & temp_value, sizeof (temp_value));
        }
            break;
        default: change_counts = 0;
            break;
    }
}

/*运行状态指示*/
void Run_Stutas(void *arg) {
    //    UNUSED(arg);
    Timer *pTimer = (Timer *) arg;
    uint8_t current_code = (uint8_t) (gCurrent_code & 0x00FF);
#if(USING_DEBUG)
    DEBUG("Led code is %d.\r\n", current_code);
#endif
    //    for (uint8_t i = 0; i < EVENTS_SIZE; i++) {
    if ((current_code == CODE1) || (current_code == CODE2) || \
           (current_code == CODE4) || (current_code == CODE6) || \
           (current_code == CODE8)) {
        /*100ms,Flash once*/
        pTimer->repeat = 10U;
    } else { /*1000ms*/
        pTimer->repeat = 100U;
    }

    SYS_STATUS_LED ^= 1;
}

/*串口1接收数据处理*/
void Uart1_Handle(void *arg) {
    UNUSED(arg);
    /*uart1 receive ready*/
    if (EUSART1_DataReady) {
        //        PIE1bits.RC1IE = 0;
        //        RCSTA1bits.CREN = 0;
#if(!USING_DEBUG)
        Uart1_Send((uint8_t *)Uart1Rx.eusart1RxBuffer, (uint8_t)Uart1Rx.eusart1RxCount);
        Uart1Rx.eusart1RxCount = 0;
#endif
        //        printf("%s", Uart1Rx.eusart1RxBuffer);
        //        Uart1_Send("\x5A\xA5\x0B\x82\x03\x10", 6);

        //        PIE1bits.RC1IE = 1; 
        //        RCSTA1bits.CREN = 1;

        //        Uart1_Send(EUSART1_Read(), 0x01);
    }
}

/*串口2接收数据处理*/
void Uart2_Handle(void *arg) {
    UNUSED(arg);
    uint8_t slave_addr = Uart2Rx.eusart2RxBuffer[0];
    uint8_t cmd = Uart2Rx.eusart2RxBuffer[1];
    uint16_t register_addr = (((uint16_t) Uart2Rx.eusart2RxBuffer[2]) << 8U | Uart2Rx.eusart2RxBuffer[3]);
    uint16_t register_data = 0x0000;

    /*uart2 receive ready*/
    if (EUSART2_DataReady) {
        if (slave_addr == SLAVE_ADDR) {
            for (uint8_t i = 0; i < SlaveFuncMapbuffSize; i++) {
                if (cmd == SlaveFuncMapbuff[i].Cmd) {
                    /*返回的数据已经处理为小端*/
                    register_data = SlaveFuncMapbuff[i].pCallBack((uint8_t *) Uart2Rx.eusart2RxBuffer);
                    /*从站响应:去掉2byte校验码*/
                    Data_Report(cmd, register_addr, (uint8_t *) & register_data, sizeof (register_data));
                    break;
                }
            }
        }

        //                                Uart2_Send((uint8_t *)Uart2Rx.eusart2RxBuffer, (uint8_t)Uart2Rx.eusart2RxCount);
        Uart2Rx.eusart2RxCount = 0;
    }
}
