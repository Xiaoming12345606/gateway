#ifndef YX75R_H
#define YX75R_H

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
#define uart_1 1    //uart1     串口1
#define uart_2 2    //uart2     串口2    
#define uart_3 3    //uart3     串口3
#define commad_fastflash 3      //指示灯爆闪指令
#define commad_slowflash 4      //指示灯慢闪指令
#define commad_steadyon 5       //指示灯常亮指令
#define commad_close 6          //指示灯关闭


class yx75r{
public:
    int uart_init(int uart);  //串口初始化函数
    int write_commad(int fd,unsigned char cmd,unsigned char add); //命令写入函数
    int set_com_config(int fd,int baud_rate, int data_bits, char parity, int stop_bits);  //内部无关函数
    int crc_algorithm(unsigned char* dat);                                                 //CRC16校验函数
private:
};

#endif // YX75R_H
