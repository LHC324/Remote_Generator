/********************************************************************
 **--------------文件信息---------------------------------------------
 **文   件   名：config.h
 **创 建  日 期：
 **最后修改日期：
 **版 权 信  息:
 **程   序   员：
 **版   本   号：
 **描        述：
 **修 改 日  志:
 *********************************************************************/

#ifndef _CONFIG_H
#define	_CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

//根据使用的编译器环境定义相应的头文件
#if defined(__XC)
    #include <xc.h>        //XC8 编译器包含头文件
#elif defined(HI_TECH_C)
    #include <htc.h>       //HiTech 编译器包含头文件
#elif defined(__18CXX)
    #include <p18cxxx.h>   //C18 编译器包含头文件
#endif

#if defined(__XC) || defined(HI_TECH_C)
    #include <stdint.h>        /* For uint8_t definition */
    #include <stdbool.h>       /* For true/false definition */
#endif

//#include <GenericTypeDefs.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "math.h"  
//#include "pFunc.h"
//#include "Event.h"
//#include "LTE.h"
//#include "Modbus.h"
    
#define USING_DEBUG  0
#define MAX_CHANNEL  3U
    
#define SYS_STATUS_LED         (LATCbits.LATC0)       //系统状态指示灯
#define SYS_STATUS_LED_ON      (LATCbits.LATC0 = 0)
#define SYS_STATUS_LED_OFF     (LATCbits.LATC0 = 1)
    
#define MOTOR_START            (LATBbits.LATB0)       //电机PWM控制
#define MOTOR_START_ON         (LATBbits.LATB0 = 1)
#define MOTOR_START_OFF        (LATBbits.LATB0 = 0)
    
#define CHARGE_EN              (LATCbits.LATC4)       //充电使能
#define CHARGE_EN_ON           (LATCbits.LATC4 = 1)
#define CHARGE_EN_OFF          (LATCbits.LATC4 = 0)
 
#define POST                  (LATAbits.LATA1)        //变频器端子启动继电器
#define POST_ON               (LATAbits.LATA1 = 1)    //端子启动开
#define POST_OFF              (LATAbits.LATA1 = 0)    //端子启动关
#define MOTOR_STOP_RELAY       (LATAbits.LATA2)       //发电机停止继电器
#define MOTOR_STOP_RELAY_ON    (LATAbits.LATA2 = 1)   //发电机停止继电器启动
#define MOTOR_STOP_RELAY_OFF   (LATAbits.LATA2 = 0)   //发电机停止继电器停止    
#define POWER_CHARGE_RELAY     (LATAbits.LATA3)       //电源切换继电器
#define POWER_CHARGE_RELAY_ON  (LATAbits.LATA3 = 1)   //继电器开  电池供电
#define POWER_CHARGE_RELAY_OFF (LATAbits.LATA3 = 0)   //继电器关  220V供电
    
//#define TRUE 1
//#define FALSE 0

#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_H */


