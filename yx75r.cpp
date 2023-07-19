#include "yx75r.h"
#include <QDebug>

static unsigned char device_address;
static int register_address;
static int data_length;
static unsigned char CMD;
static int crc16;
static unsigned char crc16_low;
static unsigned char crc16_high;
//static int fd;


/*
串口初始化函数
输入：
    @uart--串口号
输出:
    @-1--串口打开失败
    @-2--串口阻塞设置失败
    @-3--串口终端设备测试失败
    @-4--波特率设置失败
    @fd--串口对应的文件描述符

使用示例：
    fd=yx.uart_init(uart_3);
    使用串口3初始化准备485通信
*/

int yx75r::uart_init(int uart)
{
    int fd;

    switch(uart)
    {
        case uart_1:

    {
        fd = open("/dev/ttyS1", O_RDWR|O_NOCTTY|O_NDELAY);

            if (fd < 0)
            {
                perror("open serial port");
                return -1;
            }

            /*恢复串口为阻塞状态*/
            if (fcntl(fd, F_SETFL, 0) < 0)
            {
                perror("fcntl F_SETFL\n");
                ::close(fd);
                return -2;
            }

            /*测试是否为终端设备*/
            if (isatty(STDIN_FILENO) == 0)
            {
                perror("standard input is not a terminal device");
                ::close(fd);
                return -3;
            }
    }break;
        case uart_2:
    {
        fd = open("/dev/ttyS2", O_RDWR|O_NOCTTY|O_NDELAY);

            if (fd < 0)
            {
                perror("open serial port");
                return(-1);
            }

            /*恢复串口为阻塞状态*/
            if (fcntl(fd, F_SETFL, 0) < 0)
            {
                perror("fcntl F_SETFL\n");
                ::close(fd);
                return -2;
            }

            /*测试是否为终端设备*/
            if (isatty(STDIN_FILENO) == 0)
            {
                perror("standard input is not a terminal device");
                ::close(fd);
                return -3;
            }
    }break;
        case uart_3:
    {

        fd = open("/dev/ttyS3", O_RDWR|O_NOCTTY|O_NDELAY);

            if (fd < 0)
            {
                perror("open serial port");
                return(-1);
            }

            /*恢复串口为阻塞状态*/
            if (fcntl(fd, F_SETFL, 0) < 0)
            {
                perror("fcntl F_SETFL\n");
                ::close(fd);
                return -2;
            }

            /*测试是否为终端设备*/
            if (isatty(STDIN_FILENO) == 0)
            {
                perror("standard input is not a terminal device");
                ::close(fd);
                return -3;
            }
    }break;
    }

    if(set_com_config(fd, 9600, 8, 'N', 1) < 0) /* 配置串口 */
        {
            perror("set_com_config");
            ::close(fd);
            return -4;
        }
    return fd;
}

/*
声光报警器命令写入函数
输入:
    @id--串口对应的文件描述符
    @cmd--命令类型
输出：
    @1--操作成功
    @0--操作失败

使用示例:
    temp=yx.write_commad(fd,commad_steadyon);
    命令YX75R指示灯处于常亮状态
*/

int yx75r::write_commad(int id,unsigned char cmd,unsigned char add)
{
    int fd=id;
    unsigned char buff[10];
    unsigned char rx[10];
    unsigned char data_high;
    unsigned char data_low;
    int temp;
    switch(cmd)
    {
        case commad_fastflash:
        {
    device_address=add;
    register_address=0x00c2;
    data_length=0x0003;
    CMD=0x06;
    }break;
    case commad_slowflash:
    {
        device_address=add;
        register_address=0x00c2;
        data_length=0x0004;
        CMD=0x06;
    }break;
    case commad_steadyon:
    {
        device_address=add;
        register_address=0x00c2;
        data_length=0x0005;
        CMD=0x06;
    }break;
    case commad_close:
    {
        device_address=add;
        register_address=0x00c2;
        data_length=0x0006;
        CMD=0x06;
    }break;
    }
    memset(buff,0,10);
    memset(rx,0,10);
    buff[0]=device_address;
    buff[1]=CMD;
    buff[2]=register_address>>8;
    buff[3]=register_address&0x00ff;
    buff[4]=data_length>>8;
    buff[5]=data_length&0x00ff;
    crc16=crc_algorithm(buff);
    crc16_high=crc16>>8;
    buff[7]=crc16_high;
    crc16_low=crc16&0x00ff;
    buff[6]=crc16_low;
    if(!write(fd, &buff, 8))
    {
        ::close(fd);
        return -1;
    }
    /*
    qDebug()<<"write\n";
    qDebug()<<"buff0"<<buff[0];
    qDebug()<<"buff1"<<buff[1];
    qDebug()<<"buff2"<<buff[2];
    qDebug()<<"buff3"<<buff[3];
    qDebug()<<"buff4"<<buff[4];
    qDebug()<<"buff5"<<buff[5];
    qDebug()<<"buff6"<<buff[6];
    qDebug()<<"buff7"<<buff[7];*/
    memset(rx, 0, 10);
   /* if (read(fd, &rx, 10) > 0)
    {
        data_high=rx[3];
        data_low=rx[4];
        if((rx[3]==buff[3])&&(rx[4]==buff[4]))
            temp=1;
        else
            temp=0;
    }
    else
    {
        ::close(fd);
        return -2;
    }
    */
    ::close(fd);
    return temp;
}


/*
CRC16校验码计算函数
*/

int yx75r::crc_algorithm(unsigned char* dat)
{
    int i,j;
    int temp=0xffff;
    unsigned char *p;
    unsigned char data_crc[6];
    p=dat;
    for(i=0;i<6;i++)
    {data_crc[i]=*p; p++;}
    for(i=0;i<6;i++)
    {
        temp=temp^data_crc[i];
        for(j=0;j<8;j++)
        {
            if(temp&0x0001)
            {
                temp=temp>>1;
                temp=temp&0x7fff;
                temp=temp^0xa001;
            }
            else
            {
                temp=temp>>1; temp=temp&0x7fff;
            }
        }
    }
    return temp;
}


/*
串口配置函数

*/
int yx75r::set_com_config(int fd,int baud_rate, int data_bits, char parity, int stop_bits)
{
    struct termios new_cfg,old_cfg;
    int speed;

    /*保存测试现有串口参数设置，在这里如果串口号等出错，会有相关的出错信息*/
    if  (tcgetattr(fd, &old_cfg)  !=  0)
    {
        perror("tcgetattr");
        return -1;
    }

    /*设置字符大小*/
    new_cfg = old_cfg;
    cfmakeraw(&new_cfg);
    new_cfg.c_cflag &= ~CSIZE;

    /*设置波特率*/
    switch (baud_rate)
    {
        case 2400:
        {
            speed = B2400;
        }
        break;

        case 4800:
        {
            speed = B4800;
        }
        break;

        case 9600:
        {
            speed = B9600;
        }
        break;

        case 19200:
        {
            speed = B19200;
        }
        break;

        case 38400:
        {
            speed = B38400;
        }
        break;

        default:
        case 115200:
        {
            speed = B115200;
        }
        break;
    }
    cfsetispeed(&new_cfg, speed);
    cfsetospeed(&new_cfg, speed);

    /*设置停止位*/
    switch (data_bits)
    {
        case 7:
        {
            new_cfg.c_cflag |= CS7;
        }
        break;

        default:
        case 8:
        {
            new_cfg.c_cflag |= CS8;
        }
        break;
    }

    /*设置奇偶校验位*/
    switch (parity)
    {
        default:
        case 'n':
        case 'N':
        {
            new_cfg.c_cflag &= ~PARENB;
            new_cfg.c_iflag &= ~INPCK;
        }
        break;

        case 'o':
        case 'O':
        {
            new_cfg.c_cflag |= (PARODD | PARENB);
            new_cfg.c_iflag |= INPCK;
        }
        break;

        case 'e':
        case 'E':
        {
            new_cfg.c_cflag |= PARENB;
            new_cfg.c_cflag &= ~PARODD;
            new_cfg.c_iflag |= INPCK;
        }
        break;

        case 's':  /*as no parity*/
        case 'S':
        {
            new_cfg.c_cflag &= ~PARENB;
            new_cfg.c_cflag &= ~CSTOPB;
        }
        break;
    }

    /*设置停止位*/
    switch (stop_bits)
    {
        default:
        case 1:
        {
            new_cfg.c_cflag &=  ~CSTOPB;
        }
        break;

        case 2:
        {
            new_cfg.c_cflag |= CSTOPB;
        }
    }

    /*设置等待时间和最小接收字符*/
    new_cfg.c_cc[VTIME]  = 0;
    new_cfg.c_cc[VMIN] = 1;

    /*处理未接收字符*/
    tcflush(fd, TCIFLUSH);

    /*激活新配置*/
    if((tcsetattr(fd, TCSANOW, &new_cfg)) != 0)
    {
        perror("tcsetattr");
        return -1;
    }

    return 0;
}
