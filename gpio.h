#ifndef GPIO_H
#define GPIO_H


extern "C"{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
}
#define gpio_input_mode 1     //配置引脚为输出模式
#define gpio_output_mode 2      //配置引脚为输入模式
#define gpio_63 63              //选择63号引脚
#define gpio_62 62              //选择62号引脚
#define gpio_61 61              //选择61号引脚
#define gpio_60 60              //选择60号引脚
#define gpio_high 1             //高电平输出
#define gpio_low 0              //低电平输出


class gpio{
    public:
    int init(int gpio_id,unsigned char state);  //引脚初始化函数
    int rd(int gpio_id);                        //读取引脚电平
    int wr(int gpio_id,unsigned char dat);      //改变引脚电平
};
#endif // GPIO_H
