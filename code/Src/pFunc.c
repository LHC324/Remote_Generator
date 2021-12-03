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

#include "pFunc.h"


#if (USING_QUEUE)  
FILTER_QUEUE gFliterQueue[3]; //滤波缓冲区队列,包括电池电压检测,掉电检测1，掉电检测2

/*********************************************************************
 * Function:    uint16_t Calibrated_Current(struct SAVE * gSaveParamter ,uint8_t AdcChannel)
 * Overview:    标定校正,进行拟合运算
 * Input:      
 * Output:      
 * Note:        None
 ********************************************************************/
uint16_t CalibratedFunc(uint16_t FirVoltage, uint16_t FirAdcVoltage, uint16_t CurrentAdc, float SaveSlope) {
    float Current;
    Current = SaveSlope * ((int16_t) CurrentAdc - (int16_t) FirAdcVoltage) + (float) FirVoltage;
    //    Current += 0.5;            //四舍五入计算
    //
    if (Current < 0) //防止在0到10A之间偏差过大计算出负数值
    {
        Current = 0;
    }
    return (uint16_t) (Current * 100);
}

/*********************************************************************
 * Function:    float SlopeFunc(uint8_t x1,uint8_t x2,uint8_t y1,uint8_t y2)
 * Overview:    计算斜率(K=(x1-x2)/(y1-y2))
 * Input:       x1,x2,y1,y2
 * Output:      K
 * Note:        None
 ********************************************************************/
float SlopeFunc(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2) {
    return ((float) x1 - (float) x2) / ((float) y1 - (float) y2);
}

/*********************************************************************
 * Function:    bool EnQueue(struct QUEUE * Fliter_Queue,uint16_t Data)
 * Overview:    进行入队操作
 * Input:       队列结构体指针,入队数据
 * Output:      bool值
 * Note:        None
 ********************************************************************/
bool EnQueue(struct QUEUE * Fliter_Queue, uint16_t Data) {
    if (isFull(Fliter_Queue)) {
        return false;
    }
    if (isEmpty(Fliter_Queue)) {
        Fliter_Queue->FliterBuf[Fliter_Queue->Front] = Data;
    }
    Fliter_Queue->FliterBuf[Fliter_Queue->Rear] = Data;
    Fliter_Queue->Rear = (Fliter_Queue->Rear + 1) % FILTER_N;

    return true;
}

/*********************************************************************
 * Function:    uint16_t DeQueue(struct QUEUE * Fliter_Queue)
 * Overview:    进行出队操作
 * Input:       队列结构体指针
 * Output:      出队数据
 * Note:        None
 ********************************************************************/
uint16_t DeQueue(struct QUEUE * Fliter_Queue) {
    if (isEmpty(Fliter_Queue)) {
        return false;
    }
    uint16_t temp = Fliter_Queue->FliterBuf[Fliter_Queue->Front];
    Fliter_Queue->Front = (Fliter_Queue->Front + 1) % FILTER_N;
    return temp;

}

/*********************************************************************
 * Function:    bool isEmpty( struct QUEUE * Fliter_Queue)
 * Overview:    判断队列是否为空
 * Input:       队列结构体指针
 * Output:      bool值
 * Note:        None
 ********************************************************************/
bool isEmpty(struct QUEUE * Fliter_Queue) {
    if (Fliter_Queue->Front == Fliter_Queue->Rear) {
        return true;
    }
    return false;
}

/*********************************************************************
 * Function:    bool isFull(struct QUEUE * Fliter_Queue)
 * Overview:    判断队列是否为满
 * Input:       队列结构体指针
 * Output:      bool值
 * Note:        None
 ********************************************************************/
bool isFull(struct QUEUE * Fliter_Queue) {
    if ((Fliter_Queue->Rear + 1) % FILTER_N == Fliter_Queue->Front) {
        return true;
    }
    return false;
}

/*********************************************************************
 * Function:    uint16_t Rear_Value(struct QUEUE * Fliter_Queue)
 * Overview:    取队尾值
 * Input:       队列结构体指针
 * Output:      bool值
 * Note:        None
 ********************************************************************/
uint16_t Rear_Value(struct QUEUE * Fliter_Queue) {
    return Fliter_Queue->FliterBuf[Fliter_Queue->Rear];
}

/*********************************************************************
 * Function:    uint16_t FilterFunc(uint16_t Value,uint8_t index)
 * Overview:    获取滤波后的值
 * Input:       滤波前的值,队列索引
 * Output:      滤波后的值
 * Note:        None
 ********************************************************************/
uint16_t FilterFunc(uint16_t Value, uint8_t index) {
    uint16_t FilterValue;
    uint16_t filter_sum = 0;
    uint8_t i;

    EnQueue(&gFliterQueue[index], Value); //对AD采样值进行入队操作

    if (isFull(&gFliterQueue[index])) //判断队列是否为满
    {
        for (i = 0; i < FILTER_N; i++) //队列为满进行递推平均滤波
        {
            filter_sum += gFliterQueue[index].FliterBuf[i];
            FilterValue = (uint16_t) filter_sum / FILTER_N;
        }
        DeQueue(&gFliterQueue[index]);
    } else //队列不满则进行算数平均滤波
    {
        for (i = 0; i < gFliterQueue[index].Rear; i++) {
            filter_sum += gFliterQueue[index].FliterBuf[i];
            FilterValue = (uint16_t) filter_sum / (gFliterQueue[index].Rear);
        }
    }
    return FilterValue;
}
#else
sideparm_t sidefilter(sideparm *side, sideparm_t input) {

    if (side->firstflag) { //第一次滤波

        for (int i = 0; i < sizeof (side->sidebuff) / sizeof (sideparm_t); i++) {
            side->sidebuff[i] = input;
        }

        side->firstflag = false;
        side->head = &side->sidebuff[0];
        side->sum = input * (sizeof (side->sidebuff) / sizeof (sideparm_t));
    } else {
        side->sum = side->sum - *side->head + input;
        *side->head = input;

        if (++side->head > &side->sidebuff[sizeof (side->sidebuff) / sizeof (sideparm_t) - 1]) {
            side->head = &side->sidebuff[0];
        }

        input = side->sum >> FILTER_SHIFT;
    }

    return input;
}

/**
 *卡尔曼滤波器
 *@param KFP *kfp 卡尔曼结构体参数
 *   float input 需要滤波的参数的测量值（即传感器的采集值）
 *@return 滤波后的参数（最优值）
 */
float kalmanFilter(KFP *kfp, uint32_t input) {
    //预测协方差方程：k时刻系统估算协方差 = k-1时刻的系统协方差 + 过程噪声协方差
    kfp->Now_Covariance = kfp->Last_Covariance + kfp->Q;
    //卡尔曼增益方程：卡尔曼增益 = k时刻系统估算协方差 / （k时刻系统估算协方差 + 观测噪声协方差）
    kfp->Kg = kfp->Now_Covariance / (kfp->Now_Covariance + kfp->R);
    //更新最优值方程：k时刻状态变量的最优值 = 状态变量的预测值 + 卡尔曼增益 * （测量值 - 状态变量的预测值）
    kfp->Output = kfp->Output + kfp->Kg * (input - kfp->Output); //因为这一次的预测值就是上一次的输出值
    //更新协方差方程: 本次的系统协方差付给 kfp->Last_Covariance 为下一次运算准备。
    kfp->Last_Covariance = (1 - kfp->Kg) * kfp->Now_Covariance;
    return kfp->Output;
}
#endif


/*计算modBus的crc16码，带初值的16位CRC计算*/
uint16_t getCrc16(uint8_t *ptr, uint8_t length, uint16_t IniDat) {
    uint8_t iix;
    uint16_t iiy;
    uint16_t crc16 = IniDat;

    for (iix = 0; iix < length; iix++) {
        crc16 ^= *ptr++;

        for (iiy = 0; iiy < 8; iiy++) {
            if (crc16 & 0x0001) {
                crc16 = (crc16 >> 1) ^ 0xa001;
            } else {
                crc16 = crc16 >> 1;
            }
        }
    }
    return (crc16);
}
// ptr：数据指针，length：数据总长度（含CRC）

bool checkCrc16(uint8_t *ptr, uint8_t length) {
    uint16_t crc1;
    uint16_t crc2;

    crc1 = getCrc16(ptr, length - 2U, 0xFFFF);

    crc2 = (uint16_t)*(ptr + length - 1U) << 8U; // CRC MSB
    crc2 += (uint16_t)*(ptr + length - 2U); // CRC LSB

    // 如果数据校验和位置为0xCCCC或0xcccc则说明不校验CRC
    if ((crc1 == crc2) || (crc2 == 0xCCCC) || (crc2 == 0xcccc))
        return true;
    return false;
}

//float FloatChange(float Parm) //float数转换 DCBA 转化为 ABCD型
//{
//    FLOAT_CONV d1, d2;
//    d1.f = Parm;
//    d2.temp[0] = d1.temp[3];
//    d2.temp[1] = d1.temp[2];
//    d2.temp[2] = d1.temp[1];
//    d2.temp[3] = d1.temp[0];
//
//    return d2.f;
//}

/**
 * @brief  大小端数据类型交换
 * @note   对于一个单精度浮点数的交换仅仅需要2次
 * @param  pData 数据
 * @param  start 开始位置
 * @param  length  数据长度
 * @retval None
 */
void Endian_Swap(uint8_t *pData, uint8_t start, uint8_t length)
{
	uint8_t i = 0;
	uint8_t tmp = 0;
	uint8_t count = length / 2U;
	uint8_t end = start + length - 1U;

	for (; i < count; i++)
	{
		tmp = pData[start + i];
		pData[start + i] = pData[end - i];
		pData[end - i] = tmp;
	}
}

//void ShellSort(uint8_t* array, uint8_t Length) //希尔排序
//{
//    uint8_t cur; //当前数
//    uint8_t i, j;
//    uint8_t incre = Length / 2; //增量
//
//    while (incre >= 1) {
//        for (i = incre; i < Length; i++) {
//            cur = array[i]; //待排序元素
//            for (j = i - incre; j >= 0 && array[j] > cur; j = j - incre) {
//                array[j + incre] = array[j]; //元素向后移动
//            }
//            array[j + incre] = cur; //插入待排序元素
//        }
//        incre = incre / 2; //增量减半
//    }
//}