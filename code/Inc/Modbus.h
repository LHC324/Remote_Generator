/********************************************************************
 **--------------文件信息---------------------------------------------
 **文   件   名：Modbus.h
 **创 建  日 期：2020年3月20日
 **最后修改日期：
 **版 权 信  息: 云南兆富科技有限公司
 **程   序   员：
 **版   本   号：
 **描        述：
 **修 改 日  志:
 *********************************************************************/

#ifndef MODBUS_H
#define	MODBUS_H

#include"config.h"

#ifdef	__cplusplus
extern "C" {
#endif

#define  MODBUS_CMD_01  0x01        //读单线圈状态(PLC的I存储区)
#define  MODBUS_CMD_02  0x02        //读离散输入状态(PLC的Q存储区)
#define  MODBUS_CMD_03  0x03        //读保持寄存器(PLC的V存储区)
#define  MODBUS_CMD_04  0x04        //读模拟量输入寄存器(PLC的AI存储区)
#define  MODBUS_CMD_05  0x05        //强制写单线圈状态(PLC的Q存储区)
#define  MODBUS_CMD_06  0x06        //强制写单寄存器(PLC的V存储区)
#define  MODBUS_CMD_15  0x0F        //强制写多线圈(PLC的Q存储区)
#define  MODBUS_CMD_16  0x10        //强制写多寄存器(PLC的V存储区)    

#define  MODBUS_CMD_42  0x42      //上报多个离散寄存器(数字输出)
#define  MODBUS_CMD_44  0x44      //上报多个模拟输入寄存器
#define  MODBUS_CMD_45  0x45      //上报多个线圈寄存器(数字输入)
#define  MODBUS_CMD_46  0x46      //上报多个保持寄存器

    //    uint8_t CmdBuff[] = {MODBUS_CMD_45, MODBUS_CMD_46};

    //*******************自定义地址******************************//    
#define SLAVE_ADDR      0x02       //单片机从站地址

#define GEN_VOLTAGE_ADDR     0x0000      //自定义发电机数字输出地址
#define GEN_FAULT_CODE_ADDR  0x0006      //发电机故障码地址
#define GEN_CONTROL_ADDR1    0x0000      //发电机控制线圈1地址
#define GEN_CONTROL_ADDR2    0x0001      //自定义发电机控制模式地址

#define ELEMENT_SIZE 32U

    uint8_t report_buffer[ELEMENT_SIZE];

    uint8_t Set_ModbusFrame(uint8_t* data, uint8_t data_len, uint8_t regs, uint8_t cmd, uint16_t addr);
    uint16_t Modbus_05(uint8_t* dat); //05指令，写单线圈

    typedef struct {
        uint8_t Cmd; //功能码
        uint16_t (*pCallBack)(uint8_t* Data); //函数指针
    } MASTER_FUNC_MAP;

#ifdef	__cplusplus
}
#endif

#endif	/* MODBUS_H */

