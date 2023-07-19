#ifndef EN600_H
#define EN600_H

extern "C"
{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <linux/types.h>
#include <sys/ioctl.h>
}
#define data_length 512
#define str_MQTTFLAG "AT+QMTCFG=\"ALIAUTH\",0,\"izyjShDGwe8\",\"gateway\",\"ee5380af013d5a343f96aac044cd21d2\"\r\n"
#define str_MQTTOPEN "AT+QMTOPEN=0,\"izyjShDGwe8.iot-as-mqtt.cn-shanghai.aliyuncs.com\",1883\r\n"
#define str_MQTTCONNECT "AT+QMTCONN=0,\"CAT\"\r\n"
#define str_MQTTPUB "AT+QMTPUB=0,1,1,0,\"/sys/izyjShDGwe8/gateway/thing/event/property/post\""

#define EndDevice_1_State_Online 1        //Zigbee终端一在线
#define EndDevice_1_State_Offline 0       //Zigbee终端一离线
#define EndDevice_2_State_Online 1        //Zigbee终端二在线
#define EndDevice_2_State_Offline 0       //Zigbee终端二离线
#define Current_port_state_normal 0       //电流量接口采集常规模拟电流值
#define Current_port_state_sensor 1       //电流量接口采集传感器数据
#define GPIO_1_state_input 0              //IO口一输入模式
#define GPIO_1_state_output 1             //IO口一输出模式
#define GPIO_2_state_input 0              //IO口二输入模式
#define GPIO_2_state_output 1             //IO口二输出模式
#define GPIO_3_state_input 0              //IO口三输入模式
#define GPIO_3_state_output 1             //IO口三输出模式
#define GPIO_1_value_high 1               //IO口一高电平
#define GPIO_1_value_low 0                //IO口一低电平
#define GPIO_2_value_high 1               //IO口二高电平
#define GPIO_2_value_low 0                //IO口二低电平
#define GPIO_3_value_high 1               //IO口三高电平
#define GPIO_3_value_low 0                //IO口三低电平


class ec600n{
public:
   int connect();  //初始化函数
   int send_iic(void);         //向服务器发送IIC采集到的相关数据
   int send_port(void);        //向服务器发送IO口采集到的相关数据
   int send_uart(void);        //向服务器发送串口采集到的相关数据
   int send_rs485(void);      //向服务器发送RS485总线采集到的相关数据
   int uart_init(int vmin);   //类内部串口初始化函数
   int set_com_config(int fd,int baud_rate, int data_bits, char parity, int stop_bits,int vmin);  //类内部串口配置函数
   char tx[data_length];      //AT指令字符串数组
   int update_data_iic(float volt,float current,float pressure,float temp,bool current_state);     //更新IIC相关数据
   int update_data_port(bool state_1,bool value_1,bool state_2,bool value_2,bool state_3,bool value_3);     //更新IO口相关数据
   int update_data_uart(bool device_1_state,float temp_1,bool device_2_state,float temp_2);        //更新串口相关数据
   int update_rs485(int distance);                                                                 //更新RS485总线相关数据

   /*
   私有成员变量
   使用相关的update函数更新数值，使用相关的send函数会自动发送保存的值
   */
private:                //不能执行就把私有变量改为公共变量
   float EndDevice_1_temp;       //Zigbee终端一温度
   float EndDevice_2_temp;       //Zigbee终端二温度
   float Volt_in;                //电压量接口电压值
   float Current_port;           //电流量接口电流值
   float Pressure;               //大气压强值
   float Temperature;            //温度值
   int Distance;                 //距离值
   bool EndDevice_1_State;       //Zigbee终端一在线状态
   bool EndDevice_2_State;       //Zigbee终端二在线状态
   bool Current_port_state;      //电流量接口配置状态
   bool GPIO_1_state;            //IO口一输入输出状态
   bool GPIO_2_state;            //IO口二输入输出状态
   bool GPIO_3_state;            //IO口三输入输出状态
   bool GPIO_1_value;            //IO口一电平状态
   bool GPIO_2_value;            //IO口二电平状态
   bool GPIO_3_value;            //IO口三电平状态
};


#endif // EN600_H
