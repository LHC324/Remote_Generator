/********************************************************************
 **--------------文件信息---------------------------------------------
 **文   件   名：Adc.h
 **创 建  日 期：2020年1月4日
 **最后修改日期：
 **版 权 信  息: 云南兆富科技有限公司
 **程   序   员：
 **版   本   号：
 **描        述：
 **修 改 日  志:
 *********************************************************************/

#include "LTE.h"
#include "Modbus.h"
#include "tmr0.h"

uint8_t index = 0; //AT指令索引
uint8_t SendTime; //AT指令重发次数

//extern uint8_t Send2_Buff[SendBuffSize];           //串口2缓冲
//extern uint8_t Receive2_Buff[ReceiveBuffSize];
//extern ADC_VALUE CurrentAdcValue;         //当前通道电压值

typedef struct {
    float VBAT_DetectionValue;
    float Power_Off1Value;
    float Power_Off2Value;
} ADC_STRUCT;

//ADC_STRUCT AdcValue_ABCD;


AT_COMMAND atCmdLteInit[] = // LTE初始化为网络透传模式
{
    // AT命令， 模块应答， 超时时间
    {"+++", "a", T_2S}, // 串口发送‘+++’给模块，模块回应‘a’
    {"a", "+ok", T_2S}, // 收到‘a’后三秒内发送‘a’给模块，模块回应‘OK’，则模块进入临时指令模式
    {"AT+E=OFF\r\n", "OK", T_500MS}, // 关闭回显，模块应答：OK

    // 设置心跳数据：www.ynpax.com
    {"AT+HEARTDT=7777772E796E7061782E636F6D\r\n", "OK", T_500MS},

    //4G时只用一个socket通道时把不需要的通道屏蔽，两个socket都使用时，IP端口填写正确，同为长或同为短连接，不可一长一短

    // SOCKET A参数设置
    {"AT+WKMOD=NET\r\n", "OK", T_500MS}, // 模块设置为NET（网络透传模式）
    {"AT+SOCKAEN=ON\r\n", "OK", T_500MS}, // SOCKET A使能
    {"AT+SOCKASL=LONG\r\n", "OK", T_500MS}, // SOCKET A设置为长连接
    {"AT+SOCKA=TCP,clouddata.usr.cn,15000\r\n", "OK", T_500MS}, // 设置SOCKET A远程IP和端口，使用有人透传云

    // 设置透传云功能
    {"AT+REGEN=ON\r\n", "OK", T_500MS}, // 开启注册包功能
    {"AT+REGTP=CLOUD\r\n", "OK", T_500MS}, // 设置注册包类型为CLOUD
    //  {&userPassword, "OK", T_500MS},            //
    // {"AT+CLOUD=00043518000000000002,SkdGAzyl\r\n","OK",T_500MS},      
    {"AT+CLOUD=00019639000000000002,SkdGAzyl\r\n", "OK", T_500MS}, // 设置透传云用户名和密码
    // SOCKET B参数设置
    //    {"AT+SOCKBEN=ON\r\n", "OK", T_500MS},     // SOCKET B使能
    //    {"AT+SOCKBSL=LONG\r\n", "OK", T_500MS},   // SOCKET B设置为长连接
    //    {"AT+SOCKB=TCP,103.46.128.43,21711\r\n", "OK", T_500MS},// SOCKET B设置为TCP client
    //   {"AT+UART=9600,8,1,NONE,NFC\r\n","OK",T_500MS},

    // 重启模块，参数生效
    {"AT+Z\r\n", "OK", T_500MS}, // 重启模块，参数生效
};
#define atCmdLteInitSize sizeof(atCmdLteInit) / sizeof(AT_COMMAND)

AT_COMMAND *pAtCmdList = atCmdLteInit; // AT命令指针

void WireLessModule(void) //无线模块
{
    switch (LinkStage) {
        case AT_INIT:
        {
            ConnectNet();
            break;
        }
        case WAIT_ANSWER:
        {
            WaitAnwer();
            break;
        }
        case AT_CONNECTED:
        {
            Communication();
            break;
        }
        default:break;
    }
}


//void ConnectNet(void)        //连接 
//{
//    if(gPublicTimer8.ATcmdDly.TimeOutFg)
//    {      
//        gPublicTimer8.ATcmdDly.TimeOutFg = FALSE;
//        if(index < atCmdLteInitSize)   //最大指令条数
//        {
//            uart1Send(atCmdLteInit[index].pAtCmd, strlen(atCmdLteInit[index].pAtCmd));  //发送AT指令
//            uart2Send(atCmdLteInit[index].pAtCmd, strlen(atCmdLteInit[index].pAtCmd));  //发送AT指令
//           // LinkStage = WAIT_ANSWER; //进入等待应答状态
//            index++;
//        }       
//        else
//        {
//          //  SPBRG2 = (uint16_t)(SYS_FREQ / BAUD9600 / 16 - 1); //115200bps
//            Debug("AT_CONNECTED\r\n");
//            LinkStage = AT_CONNECTED;
//          
//        }
//        gPublicTimer8.ATcmdDly.TimerCounter = T_500MS;
//    }
//}
//void Communication(void)     //通讯
//{
//    //LTELinkCheck();    // 断线检测
//     TimingReport();     // 定时上报数据   
//}
//void WaitAnwer(void)
//{
//    if(gPublicTimer8.ATcmdDly.TimeOutFg)
//    {
//        gPublicTimer8.ATcmdDly.TimeOutFg = FALSE;
//        if(strstr(Receive2_Buff,pAtCmdList[index].pAck)!= NULL)    //判断接收字符串中是否有指定字符串,该句最为重要,用于判断是否模块进行回复
//        {
//            
//            index++;       //指令进入下一条索引
//            LinkStage = AT_INIT; //回到初始化AT指令发送阶段
//            if(index == atCmdLteInitSize) //如果进行到最后一条AT指令的话，进入连接状态
//            {
//                index = 0; //索引清零,如果下次不断电需要重新初始化时用到
//            //    SPBRG2 = (uint16_t)(SYS_FREQ / BAUD9600 / 16 - 1); //115200bps
//                LinkStage = AT_CONNECTED;
//                gPublicTimer16.ModbulLinkLOD1.TimerCounter = T_10S; // 开启断线重连定时器
//            }
//        }
//        else        //如果接收字符串中没有指定字符，进行重发，规定上限
//        {
//            SendTime++;           
//            if(SendTime == ATCmdMaxTime)
//            {
//                SendTime = 0; //归0重发次数               
//                index++;  //重发次数等于最大重发次数时发送下一条
//            }
//            LinkStage = AT_INIT; //回到初始化AT指令发送阶段
//        }
//        gPublicTimer8.ATcmdDly.TimerCounter = T_200MS;
//    }
//}

void LTEReload() //模块重置
{
    uint16_t ii;
    LTE_RELOAD_ON;
    for (ii = 0; ii < 100; ii++) {
//        __delaywdt_ms(50);
    }
    LTE_RELOAD_OFF;

    for (ii = 0; ii < 300; ii++) {
//        __delaywdt_ms(50);
    }
}

void LinkCheck() //断线检查
{
    if (!_4G_SOCKETB_LINK) { //判断模块是否处于连接状态,wifi高电平连接上了，4g低电平连接上了
        LINK_LED_OFF;
    } else {
        LINK_LED_ON;
    }
    //    if(gPublicTimer16.ModbulLinkLOD1.TimeOutFg)     
    //    {
    //        gPublicTimer16.ModbulLinkLOD1.TimeOutFg = FALSE;
    //       
    //        if(_4G_SOCKETB_LINK)
    //        {
    //            LTE_RESET_ON;
    //            gPublicTimer16.ModbulLinkLOD2.TimerCounter = T_1S;
    //        }
    //        else
    //        {
    //            gPublicTimer16.ModbulLinkLOD1.TimerCounter = T_5S;
    //        }               
    //       
    //    }
    //    if(gPublicTimer16.ModbulLinkLOD2.TimeOutFg)
    //    {
    //        gPublicTimer16.ModbulLinkLOD2.TimeOutFg = FALSE;
    //        LTE_RESET_OFF;
    //        gPublicTimer16.ModbulLinkLOD1.TimerCounter = T_60S;
    //    }     
}
