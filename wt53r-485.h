#ifndef WT53R485_H
#define WT53R485_H


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
#define uart_1 1    //uart1  使用串口1
#define uart_2 2    //uart2  使用串口2
#define uart_3 3    //uart3  使用串口3


class wt53r{
  public :
    int uart_init(int uart, unsigned char add,unsigned char cmd,int reg, int len);  //串口初始化函数
    int read_data(int id);                                                          //距离读取函数
    int set_com_config(int fd,int baud_rate, int data_bits, char parity, int stop_bits);//内部无关函数
    int crc_algorithm(unsigned char* dat);                                              //内部无关函数
  private:  
};



#endif // WT53R485_H
