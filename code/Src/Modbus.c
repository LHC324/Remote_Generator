
/********************************************************************
 **--------------文件信息---------------------------------------------
 **文   件   名：Modbus.c
 **创 建  日 期：2020年3月20日
 **最后修改日期：
 **版 权 信  息: 云南兆富科技有限公司
 **程   序   员：
 **版   本   号：
 **描        述：
 **修 改 日  志:
 *********************************************************************/
#include "Modbus.h"
#include "pFunc.h"
#include "eusart1.h"
#include "Event.h"

uint8_t Set_ModbusFrame(uint8_t* data, uint8_t data_len, uint8_t regs, uint8_t cmd, uint16_t addr) {
    uint8_t temp_len = 0;
    uint16_t temp_crc = 0;

    report_buffer[0] = SLAVE_ADDR;
    report_buffer[1] = cmd;
    report_buffer[2] = (uint8_t) (addr >> 8U);
    report_buffer[3] = (uint8_t) addr;
    if ((cmd == 0x01) || (cmd == 0x05)) {
        memcpy(&report_buffer[4], data, data_len);
        temp_len = 4U + data_len;
    } else {
        report_buffer[4] = 0x00;
        report_buffer[5] = regs;
        report_buffer[6] = data_len;
        memcpy(&report_buffer[7], data, data_len);
        temp_len = 7U + data_len;
    }
    temp_crc = getCrc16(report_buffer, temp_len, 0xFFFF);
    report_buffer[temp_len++] = (uint8_t) temp_crc;
    report_buffer[temp_len++] = (uint8_t) (temp_crc >> 8U);
    return temp_len;
}

/*强制写单线圈*/
uint16_t Modbus_05(uint8_t* dat) {
    uint16_t addr = ((uint16_t) dat[2]) << 8U | dat[3];
    uint8_t option = dat[4];

    switch (addr) {
        case GEN_CONTROL_ADDR1:
        {
            /*必须在手动模式下*/
            if (gAlternator == MANU_MODE) {
                if (option == 0xFF) {
                    /*启动发电机*/
                    if (gStart_mutex) { /*考虑发电机启动成功后进入的事件为2，6*/
                        /*关闭发电机停止继电器*/
                        MOTOR_STOP_RELAY_OFF;
                        /*cpu对发电机启动电机供电*/
                        MOTOR_START_ON;
                    } else { /*市电和发电机电压不为0，不允许打开发电机*/
                        dat[4] = 0x00;
                    }
                } else {
                    /*停止发电机*/
                    if (gStop_mutex) {
                        /*打开发电机停止继电器*/
                        MOTOR_STOP_RELAY_ON;
                    } else { /*没有市电或者发电机已经关闭情况下，不允许关闭发电机*/
                        dat[4] = 0xFF;
                    }
                }
            } else {
                dat[4] = 0x00;
            }
        }
            break;
        case GEN_CONTROL_ADDR2:
        {
            if (option == 0xFF) {
                gAlternator = MANU_MODE; //手动模式
#if (USING_DEBUG)
                DEBUG("NOTE : The generator switches to manual start mode.\r\n");
#endif
            } else {
                gAlternator = AUTO_MODE; //自动模式
#if (USING_DEBUG)              
                DEBUG("NOTE : The generator switches to automatic start mode.\r\n");
#endif               
            }
        }
            break;
        default: break;
    }
    return (0x00FF & dat[4]);
}