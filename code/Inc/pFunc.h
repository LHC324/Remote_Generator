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

#ifndef PFUNC_H
#define	PFUNC_H

#include "config.h"

#ifdef	__cplusplus
extern "C" {
#endif

#define USING_QUEUE 0
    
#if (USING_QUEUE)    
#define FILTER_N  10
    
typedef struct QUEUE                    //通用队列结构，其它扩展程序用到队列可重命名，防止误解
{
    uint16_t FliterBuf[FILTER_N];
    uint8_t  Front;
    uint8_t  Rear;
}FILTER_QUEUE;
#else

#define FILTER_SHIFT 3
typedef uint16_t sideparm_t;

typedef struct
{
	bool firstflag;
	sideparm_t sidebuff[1U << FILTER_SHIFT];
    sideparm_t *head;
    sideparm_t sum;
}sideparm;

typedef struct
{
    float Last_Covariance;			//上次估算协方差 初始化值为0.02
    float Now_Covariance;			//当前估算协方差 初始化值为0
    float Output;					//卡尔曼滤波器输出 初始化值为0
    float Kg;						//卡尔曼增益 初始化值为0
    float Q;						//过程噪声协方差 初始化值为0.001
    float R;						//观测噪声协方差 初始化值为0.543
}KFP;
#endif

typedef union    //float转换大小端用
{
    float f;
    uint8_t temp[4];
}FLOAT_CONV;

#if (USING_QUEUE)    
bool EnQueue(struct QUEUE * Fliter_Queue,uint16_t Data);   //入队
uint16_t DeQueue(struct QUEUE * Fliter_Queue);             //出队
bool isEmpty( struct QUEUE * Fliter_Queue);                //判断队空
bool isFull(struct QUEUE * Fliter_Queue);                  //判断队满
uint16_t Rear_Value(struct QUEUE * Fliter_Queue);         //取队尾值
float SlopeFunc(uint16_t x1,uint16_t x2,uint16_t y1,uint16_t y2);  //斜率计算公式
uint16_t CalibratedFunc(uint16_t FirVoltage,uint16_t FirAdcVoltage,uint16_t CurrentAdc,float SaveSlope);//线性变化公式
uint16_t FilterFunc(uint16_t Value,uint8_t index);  //滤波函数
#else
extern uint16_t sidefilter(sideparm *side, uint16_t input);
extern float kalmanFilter(KFP *kfp, uint32_t input);
#endif

uint16_t getCrc16(uint8_t *ptr, uint8_t length, uint16_t IniDat);    //获取CRC16值
bool checkCrc16(uint8_t *ptr, uint8_t length);      //检查CRC16值
float FloatChange(float Parm);    //float数转换 DCBA 转化为 ABCD型
void Endian_Swap(uint8_t *pData, uint8_t start, uint8_t length);
void ShellSort(uint8_t* array,uint8_t Length);  //希尔排序

#ifdef	__cplusplus
}
#endif

#endif	/* PFUNC_H */

