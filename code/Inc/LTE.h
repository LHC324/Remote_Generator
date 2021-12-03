/* 
 * File:   4G.h
 * Author: Administrator
 *
 * Created on 2020年3月17日, 上午10:31
 */

#ifndef _4G_H
#define	_4G_H

#include"config.h"


#ifdef	__cplusplus
extern "C" {
#endif
    
#define LTE_RELOAD       (LATBbits.LATB1)
#define LTE_RELOAD_ON    (LATBbits.LATB1 = 0)
#define LTE_RELOAD_OFF   (LATBbits.LATB1 = 1)
    
#define LTE_RESET        (LATBbits.LATB2)
#define LTE_RESET_ON     (LATBbits.LATB2 = 0)
#define LTE_RESET_OFF    (LATBbits.LATB2 = 1)
    
#define _4G_SOCKETB_LINK  (PORTBbits.RB4)
    
  //LINK LED管脚
  #define LINK_LED            (LATCbits.LATC3)
  #define LINK_LED_ON         (LATCbits.LATC3 = 0)
  #define LINK_LED_OFF        (LATCbits.LATC3 = 1)
    
#define ATCmdMaxTime   4
    
typedef struct
{
    char *pAtCmd;                    // AT命令
    char *pAck;                      // 此AT命令的正确应答
    uint16_t timeOut;                   // 应答超时时间
}AT_COMMAND;

typedef enum
{
    AT_CONNECTED,
    AT_INIT,
    WAIT_ANSWER,        
}LINKSTAGE;

LINKSTAGE LinkStage ;

void WireLessModule(void);     //无线模块
void LTEReload(void);           //重置模块
void ConnectNet(void);          //连接 
void WaitAnwer(void);           //等待
void Communication(void);      //通讯
void LTELinkCheck(void);       //断线检查

#ifdef	__cplusplus
}
#endif

#endif	/* 4G_H */

