#include "gpio.h"
#include "qdebug.h"


/*
    GPIO引脚初始化函数
    输入:
        @gpio_id  选择初始化的引脚号
        @state  配置引脚输入/输出模式
    输出：
        @无

    示例：
        gpio::init(62, gpio_input_mode)  初始化62号IO口并配置为输入模式
        gpio::init(62, gpio_output_mode)  初始化62号IO口并配置为输出模式
*/


int gpio::init(int gpio_id, unsigned char state)
{
    int fd;
    char commad[10];
    int len;
    memset(commad,0,10);
    switch(gpio_id)
    {
    case gpio_63:
    {
        if(access("/sys/class/gpio/gpio63",F_OK)!=0)
            {
                fd=open("/sys/class/gpio/export",O_WRONLY);
                if(fd<0)
                {
                    perror("open1\n");
                    close(fd);
                    exit(1);
                }
                sprintf(commad,"63",2);
                len=strlen(commad);
                if(write(fd,commad,len)<0)
                        {
                            perror("write4\n");
                            close(fd);
                            exit(1);
                        }
            }
            memset(commad,0,10);
    }break;
    case gpio_62:
    {
        if(access("/sys/class/gpio/gpio62",F_OK)!=0)
            {
                fd=open("/sys/class/gpio/export",O_WRONLY);
                if(fd<0)
                {
                    perror("open1\n");
                    close(fd);
                    exit(1);
                }
                sprintf(commad,"62",2);
                len=strlen(commad);
                if(write(fd,commad,len)<0)
                        {
                            perror("write4\n");
                            close(fd);
                            exit(1);
                        }
            }
            memset(commad,0,10);
    }break;
    case gpio_61:
    {
        if(access("/sys/class/gpio/gpio61",F_OK)!=0)
            {
                fd=open("/sys/class/gpio/export",O_WRONLY);
                if(fd<0)
                {
                    perror("open1\n");
                    close(fd);
                    exit(1);
                }
                sprintf(commad,"61",2);
                len=strlen(commad);
                if(write(fd,commad,len)<0)
                        {
                            perror("write4\n");
                            close(fd);
                            exit(1);
                        }
            }
            memset(commad,0,10);
    }break;
    case gpio_60:
    {
        if(access("/sys/class/gpio/gpio60",F_OK)!=0)
            {
                fd=open("/sys/class/gpio/export",O_WRONLY);
                if(fd<0)
                {
                    perror("open1\n");
                    close(fd);
                    exit(1);
                }
                sprintf(commad,"60",2);
                len=strlen(commad);
                if(write(fd,commad,len)<0)
                        {
                            perror("write4\n");
                            close(fd);
                            exit(1);
                        }
            }
            memset(commad,0,10);
    }break;
    }
    switch(state)
    {
        case gpio_input_mode:
    {
        switch(gpio_id)
        {
        case gpio_63:
        {
            fd=open("/sys/class/gpio/gpio63/direction",O_WRONLY);
                if(fd<0)
                {
                    qDebug()<<"open1\n";
                    close(fd);
                    exit(1);
                }
                sprintf(commad,"%s","in");
                len=strlen(commad);
                if(write(fd,&commad,len)<0)
                {
                    qDebug()<<"write1\n";
                    close(fd);
                    exit(1);
                }
        }break;
        case gpio_62:
        {
            fd=open("/sys/class/gpio/gpio62/direction",O_WRONLY);
                if(fd<0)
                {
                    qDebug()<<"open1\n";
                    close(fd);
                    exit(1);
                }
                sprintf(commad,"%s","in");
                len=strlen(commad);
                if(write(fd,&commad,len)<0)
                {
                    qDebug()<<"write1\n";
                    close(fd);
                    exit(1);
                }
        }break;
        case gpio_61:
        {
            fd=open("/sys/class/gpio/gpio61/direction",O_WRONLY);
                if(fd<0)
                {
                    qDebug()<<"open1\n";
                    close(fd);
                    exit(1);
                }
                sprintf(commad,"%s","in");
                len=strlen(commad);
                if(write(fd,&commad,len)<0)
                {
                    qDebug()<<"write1\n";
                    close(fd);
                    exit(1);
                }
        }break;
        case gpio_60:
        {
            fd=open("/sys/class/gpio/gpio60/direction",O_WRONLY);
                if(fd<0)
                {
                    qDebug()<<"open1\n";
                    close(fd);
                    exit(1);
                }
                sprintf(commad,"%s","in");
                len=strlen(commad);
                if(write(fd,&commad,len)<0)
                {
                    qDebug()<<"write1\n";
                    close(fd);
                    exit(1);
                }
        }break;
        }
    }break;
        case gpio_output_mode:
    {
        switch (gpio_id)
        {
        case gpio_63:
        {
            fd=open("/sys/class/gpio/gpio63/direction",O_WRONLY);
                if(fd<0)
                {
                    qDebug()<<"open1\n";
                    close(fd);
                    exit(1);
                }
                sprintf(commad,"%s","out");
                len=strlen(commad);
                if(write(fd,&commad,len)<0)
                {
                    qDebug()<<"write1\n";
                    close(fd);
                    exit(1);
                }
        }break;
        case gpio_62:
        {
            fd=open("/sys/class/gpio/gpio62/direction",O_WRONLY);
                if(fd<0)
                {
                    qDebug()<<"open1\n";
                    close(fd);
                    exit(1);
                }
                sprintf(commad,"%s","out");
                len=strlen(commad);
                if(write(fd,&commad,len)<0)
                {
                    qDebug()<<"write1\n";
                    close(fd);
                    exit(1);
                }
        }break;
        case gpio_61:
        {
            fd=open("/sys/class/gpio/gpio61/direction",O_WRONLY);
                if(fd<0)
                {
                    qDebug()<<"open1\n";
                    close(fd);
                    exit(1);
                }
                sprintf(commad,"%s","out");
                len=strlen(commad);
                if(write(fd,&commad,len)<0)
                {
                    qDebug()<<"write1\n";
                    close(fd);
                    exit(1);
                }
        }break;
        case gpio_60:
        {
            fd=open("/sys/class/gpio/gpio60/direction",O_WRONLY);
                if(fd<0)
                {
                    qDebug()<<"open1\n";
                    close(fd);
                    exit(1);
                }
                sprintf(commad,"%s","out");
                len=strlen(commad);
                if(write(fd,&commad,len)<0)
                {
                    qDebug()<<"write1\n";
                    close(fd);
                    exit(1);
                }
        }break;
        }

    }break;
    }

    return fd;
}

/*
    GPIO引脚电平读取函数
    输入:
        @gpio_id  选择读取的引脚号
    输出:
        @电平值(二进制)
         1--代表高电平
         0--代表低电平
    示例
        gpio63.rd(gpio_63);     读取63号引脚的电平值
*/


int gpio::rd(int gpio_id)
{
    int fd;
    int dat[5];
    memset(dat,0,5);
    switch(gpio_id)
    {
    case gpio_63:
    {
        fd=open("/sys/class/gpio/gpio63/value",O_RDONLY);
            if(fd<0)
            {
                qDebug()<<"open2\n";
                close(fd);
                exit(1);
            }
    }break;
    case gpio_62:
    {
        fd=open("/sys/class/gpio/gpio62/value",O_RDONLY);
            if(fd<0)
            {
                qDebug()<<"open2\n";
                close(fd);
                exit(1);
            }
    }break;
    case gpio_61:
    {
        fd=open("/sys/class/gpio/gpio61/value",O_RDONLY);
            if(fd<0)
            {
                qDebug()<<"open2\n";
                close(fd);
                exit(1);
            }
    }break;
    case gpio_60:
    {
        fd=open("/sys/class/gpio/gpio60/value",O_RDONLY);
            if(fd<0)
            {
                qDebug()<<"open2\n";
                close(fd);
                exit(1);
            }
    }break;
    }
    if(!read(fd,&dat,1))
    {
        qDebug()<<"read\n";
        return -1;
    }
    fd=dat[0];
    if(fd==48)
        fd=0;
    else if(fd==49)
        fd=1;
    //qDebug()<<fd;
    return fd;
}

/*
    GPIO引脚电平输出函数
    输入:
        @gpio_id 选择输出的引脚号
    输出:
        @dat 选择输出的电平状态(二进制)
        1--代表输出高电平
        0--代表输出低电平
    示例
        gpio63.wr(gpio_63,gpio_low);    控制63号引脚输出低电平
*/


int gpio::wr(int gpio_id, unsigned char dat)
{
    int fd;
    int len;
    char buff[5];
    memset(buff,0,5);
    switch(gpio_id)
    {
    case gpio_63:
    {
        fd=open("/sys/class/gpio/gpio63/value",O_WRONLY);
            if(fd<0)
            {
                qDebug()<<"open3\n";
                close(fd);
                exit(1);
            }
    }break;
    case gpio_62:
    {
        fd=open("/sys/class/gpio/gpio62/value",O_WRONLY);
            if(fd<0)
            {
                perror("open3\n");
                close(fd);
                exit(1);
            }
    }break;
    case gpio_61:
    {
       fd=open("/sys/class/gpio/gpio61/value",O_WRONLY);
            if(fd<0)
            {
                qDebug()<<"open3\n";
                close(fd);
                exit(1);
            }
    }break;
    case gpio_60:
    {
        fd=open("/sys/class/gpio/gpio60/value",O_WRONLY);
            if(fd<0)
            {
                qDebug()<<"open3\n";
                close(fd);
                exit(1);
            }
    }break;
    }
    switch(dat)
    {
        case gpio_high:
    {
        sprintf(buff,"1",1);
        len=strlen(buff);
        if(write(fd,buff,len)<0)
                {
                    qDebug()<<"write2\n";
                    close(fd);
                    return -1;
                }
    }break;
    case gpio_low:
    {
        sprintf(buff,"0",1);
        len=strlen(buff);
        if(write(fd,buff,len)<0)
                {
                    qDebug()<<"write2\n";
                    close(fd);
                    return -2;
                }
    }break;
    }
    return fd;
}
