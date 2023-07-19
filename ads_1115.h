#ifndef ADS_1115_H
#define ADS_1115_H


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


/*int init_ADS1115(void);
int read_ADS_1115(void);*/
class ads1115 {
  public :
    int init(unsigned char address,unsigned char device);
    float rd(unsigned char address,unsigned char device);
    int value;

};

/*#define write_address 0x90
#define reg_config 0x01
#define reg_convertion 0x00
#define msb 0xc0
#define lsb 0x83*/
#define volt_device 1
#define current_device 2


#endif // ADS_1115_H
