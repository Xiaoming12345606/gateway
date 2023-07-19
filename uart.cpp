#include "uart.h"
#include "QDebug"

/*
串口初始化函数
    输入:
    @uart_id   初始化串口号
    @baud_rate      波特率设置
*/
int uart::init_uart(unsigned char uart_id,int baud_rate)
{
    int fd;
    switch(uart_id)
    {
        case uart1:
    {
        fd = open("/dev/ttyS1", O_RDWR|O_NOCTTY|O_NDELAY);

        if (fd < 0)
        {
            perror("open serial port");
            return(-1);
        }

        /*恢复串口为阻塞状态*/
        if (fcntl(fd, F_SETFL, 0) < 0)
        {
            perror("fcntl F_SETFL\n");
        }

        /*测试是否为终端设备*/
        if (isatty(STDIN_FILENO) == 0)
        {
            perror("standard input is not a terminal device");
        }
        if(set_com_config(fd, baud_rate, 8, 'N', 1) < 0) /* 配置串口*/
        {
                qDebug()<<"set\n";
                close(fd);
                return -2;
        }
    }break;
    case uart2:
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
        }

        /*测试是否为终端设备*/
        if (isatty(STDIN_FILENO) == 0)
        {
            perror("standard input is not a terminal device");
        }
        if(set_com_config(fd, baud_rate, 8, 'N', 1) < 0) /* 配置串口*/
        {
                qDebug()<<"set\n";
                close(fd);
                return -2;
        }
    }break;
    case uart3:
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
        }

        /*测试是否为终端设备*/
        if (isatty(STDIN_FILENO) == 0)
        {
            perror("standard input is not a terminal device");
        }
        if(set_com_config(fd, baud_rate, 8, 'N', 1) < 0) /* 配置串口*/
        {
                qDebug()<<"set\n";
                close(fd);
                return -2;
        }
    }break;
    }
    qDebug()<<"temperature end"<<fd;
    return fd;
}

/*
串口读取函数
    输入:
    @uart_id 初始化串口号
    @baud_rate 波特率设置
    输出：
    @无
*/
int uart::read_uart(unsigned char uart_id,int baud_rate)
{
    int fd;
    fd=init_uart(uart_id,baud_rate);
    //qDebug()<<fd;
    memset(rx,0,32);
    read(fd,rx,30);
    close(fd);
    return fd;
}


/*
串口打开函数
*/
int uart::open_port(unsigned char uart_id)
{
    int fd;

    switch(uart_id)
    {
    case uart1:
    {
        fd = open("/dev/ttyS1", O_RDWR|O_NOCTTY|O_NDELAY);

        if (fd < 0)
        {
            perror("open serial port");
            return(-1);
        }

        /*恢复串口为阻塞状态*/
        if (fcntl(fd, F_SETFL, 0) < 0)
        {
            perror("fcntl F_SETFL\n");
        }

        /*测试是否为终端设备*/
        if (isatty(STDIN_FILENO) == 0)
        {
            perror("standard input is not a terminal device");
        }
    }break;
    case uart2:
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
        }

        /*测试是否为终端设备*/
        if (isatty(STDIN_FILENO) == 0)
        {
            perror("standard input is not a terminal device");
        }
    }break;
    case uart3:
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
        }

        /*测试是否为终端设备*/
        if (isatty(STDIN_FILENO) == 0)
        {
            perror("standard input is not a terminal device");
        }
    }break;
    }
    return fd;
}

/*
波特率设置函数
*/
int uart::set_com_config(int fd,int baud_rate, int data_bits, char parity, int stop_bits)
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
