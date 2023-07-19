#include "ads_1115.h"
#include <QDebug>
extern "C"
{
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/types.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
}


/*
ADS1115初始化函数
只需要开机时初始化一次，往后只需要执行读取函数
输入:
    @address ADS1115的IIC地址
输出：
    -1:IIC打开失败
    -2:IIC写入失败
    0:成功
*/
int ads1115::init(unsigned char address,unsigned char device)
{
    int fd;
    unsigned char buff[3]={0x01,0xc0,0x83};
    if(device ==volt_device)
    {
        fd=open("/dev/i2c-0",O_RDWR);
        if(fd<0)
        {
            ::close(fd);
            return -1;
         }
    }
    else if(device ==current_device)
    {
        fd=open("/dev/i2c-1",O_RDWR);
        if(fd<0)
        {
            ::close(fd);
            return -1;
         }
    }
    ioctl(fd,I2C_SLAVE,address);
    ioctl(fd,I2C_TIMEOUT,1);
    ioctl(fd,I2C_RETRIES,1);
    if(!write(fd,&buff[0],3))
    {
        ::close(fd);
        qDebug()<<"votlage -2";
        return -2;
    }
    ::close(fd);
    return 0;
}

/*
ADS1115读取函数
读取ADS1115采集的电压值
输入:
    @address ADS1115的IIC地址
输出:
    -1:IIC打开失败
    -2:IIC写入失败
    -4:IIC写入失败
    -5:IIC写入失败
    @temp 读取到的电压值
*/
float ads1115::rd(unsigned char address,unsigned char device)
{
    int fd;
    float temp;
    unsigned char add[3]={0x48,0x00,0x00};
    unsigned char buff[2];
    add[0]=address;

    if(device ==volt_device)
    {
        fd=open("/dev/i2c-0",O_RDWR);
        if(fd<0)
        {
            ::close(fd);
            return -1;
         }
    }
    else if(device ==current_device)
    {
        fd=open("/dev/i2c-1",O_RDWR);
        if(fd<0)
        {
            ::close(fd);
            return -1;
         }
    }
    ioctl(fd,I2C_SLAVE,address);
    ioctl(fd,I2C_TIMEOUT,1);
    ioctl(fd,I2C_RETRIES,1);
    if(!write(fd,&add[0],2))
    {
        ::close(fd);
        qDebug()<<" rd votlage -2";
        return -2;
    }
    if(!write(fd,&add[2],1))
    {
        ::close(fd);
        return -4;
    }
    if(!read(fd,&buff[0],2))
    {
        ::close(fd);
        return -5;
    }
    temp=(buff[0]*256)+buff[1];
    if(temp>0x7fff) temp=0;
    else
    {temp=(float)temp*6.144/32768;}
    value=temp;
    ::close(fd);
    return temp;
    qDebug()<<"temp"<<temp;
}
