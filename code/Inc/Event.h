/********************************************************************
 **--------------文件信息---------------------------------------------
 **文   件   名：pFunc.h
 **创 建  日 期：2020年1月4日
 **最后修改日期：
 **版 权 信  息: 云南兆富科技有限公司
 **程   序   员：
 **版   本   号：
 **描        述：
 **修 改 日  志:
 *********************************************************************/

#ifndef EVENT_H
#define	EVENT_H

#include "config.h"

#ifdef	__cplusplus
extern "C" {
#endif

#define UNUSED(x)              (x = x)
#define POWEROFF1_THR           200.0f  //市电检测电压阈值
#define POWEROFF2_THR           200.0f  //发电机检测电压阈值
#define VBAT_NOFULL_THR         11.0f   //蓄电池充电电压阈值
#define VBAT_FULL_THR           13.2f   //蓄电池充满电阈值
#define ERROR_VOLTAGE           2.0f    //检测误差电压
#define GET_BAT_VOLTAGE() (adc[0].adcValue)
#define GET_CITY_VOLTAGE() (adc[1].adcValue)
#define GET_GEN_VOLTAGE() (adc[2].adcValue)    
#define AUTO_MODE                 0x00       //自动模式
#define MANU_MODE                 0xFF       //手动模式

#define GEN_START_TIMES         2U       //间隔时间(GEN_START_TIMES * 时间调度时间) 
#define GEN_DURATION            5U       //0-1-2-3-4-5(开-关：总计3次)
#define MAX_START_TIMES         (GEN_START_TIMES * GEN_DURATION)       //最大启动次数(3次)

#define CYCLE_TIME_MAX          15      //连续检测次数,例：连续检测市电电压低于1V 5次判定为市电电压过低
#define CYCLE_TRANSIT           6       //给一定的缓冲,AD电压值由高到低需要一定的时间以及发电机的启动停止等需要一定的时间 
#define SETTLE_TIMES            5       //等待变频器电源稳定时间
    //      市电             发电机              蓄电池
    //      >THR             >THR               >THR            发电机停止
    //      >THR             >THR               <THR          发电机停止,蓄电池充电    
    //      >THR             <THR             <THR          蓄电池充电
    //      >THR             <THR             >THR            正常状态
    //      <THR           <THR             <THR          尝试启动发电机
    //      <THR           >THR               >THR            准备由发电机供电或发电机已供电
    //      <THR           >THR               <THR          准备由发电机供电或发电机已供电,准备蓄电池充电
    //      <THR           <THR             >THR            启动发电机，不充电池    

    typedef enum {
        ALL_VOLTAGE_LOW, //所有电压低
        GEN_VOLTAGE_CMP_HIGE, //相较下发电机电压高
        CITY_VOLTAGE_CMP_HIGE, //相较下市电电压高
        VBAT_VOLTAGE_CMP_HIGH, //相较下蓄电池电压高
        VBAT_VOLTAGE_CMP_LOW, //相较下蓄电池电压低
        CITY_VOLTAGE_CMP_LOW, //相较下市电电压低
        GEN_VOLTAGE_CMP_LOW, //相较下发电机电压低
        ALL_VOLTAGE_HIGH, //所有电压高
    } Voltage_State_t;

    /*错误代码*/
#define CODE0 0x00 //发电机启动成功
#define CODE1 0x01 //发电机启动失败
#define CODE2 0x02 //3次启动发电机失败，切换到手动模式
#define CODE3 0x03 //发电机工作正常
#define CODE4 0x04 //发电机供电不稳定
#define CODE5 0x05 //市电供应正常
#define CODE6 0x06 //市电供应不稳定
#define CODE7 0x07 //市电切换成功
#define CODE8 0x08 //市电切换失败（发电机关闭失败）
    //VOLTAGE_STATE  VoltageStage;        //电压状态

    typedef union {

        struct {
            uint8_t code;
            uint8_t id;
        } r;
        uint16_t record;
    } Error_Record;

    typedef struct events {
        //	Voltage_State_t state;
        //    uint8_t event_id;
        char *state;
        bool compose[MAX_CHANNEL];
        Error_Record error_code;
        bool start_mutex;
        bool stop_mutex;
        void (*pFunc)(void *arg);
    } Event_Handle_t; //__attribute__((packed))

    extern uint8_t gAlternator;
    extern bool gStart_mutex;
    extern bool gStop_mutex;
    // /*发电机启动*/
    //extern void Gen_Start(void *arg);
    // /*发电机关闭*/
    //extern void Gen_Stop(void *arg);
    /*当前工作系统状态检测*/
    extern void Status_Check(void *arg);
    /*当前工作系统状态检测*/
    extern void Status_Check(void *arg);
    /*电压检测*/
    extern void Voltage_Check(void *arg);
    /*定时上报任务*/
    extern void Timing_Report(void *arg);
    /*运行状态指示*/
    extern void Run_Stutas(void *arg);
    /*串口1接收数据处理*/
    extern void Uart1_Handle(void *arg);
    /*串口2接收数据处理*/
    extern void Uart2_Handle(void *arg);

#ifdef	__cplusplus
}
#endif

#endif	/* EVENT_H */

