#ifndef UART_H
#define UART_H

extern"C"{
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
#define uart1 1     //串口1
#define uart2 2     //串口2
#define uart3 3     //串口3

class uart{
    public:
    char rx[32];            //存储串口信息的数组
    int init_uart(unsigned char uart_id,int baud_rate);     //内部函数不用理会
    int read_uart(unsigned char uart_id,int baud_rate);     //串口读取函数
    int open_port(unsigned char uart_id);                   //内部函数不用理会
    int set_com_config(int fd,int baud_rate, int data_bits, char parity, int stop_bits);        //内部函数不用理会
};

/*
示例；
    u3.read_uart(uart3,9600);
    以9600的波特率读取串口3的数据信息
    读取到的内容存储在rx数组中
*/

#endif // UART_H
