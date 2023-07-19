#include "ec600n.h"
#include "QDebug"


/*
4G模块初始化函数
打开0号串口并尝试与服务器建立连接
建立连接大概需要三到五秒
输入:
    无
输出:
    无
*/
int ec600n::connect()
{
    int len;
    int fd;
    char rx[data_length];
    int i;
    memset(tx,0,data_length);
    sprintf(tx,str_MQTTFLAG,data_length);
    len=strlen(tx);
    fd=uart_init(1);
    if(!write(fd,&tx,len))
    {
        qDebug()<<"mqtt_flag\n";
        close(fd);
        return -1;
    }
    qDebug()<<"write1\n";
    read(fd,rx,data_length);
    sleep(1);
    qDebug("a%s",rx);
    memset(rx,0,data_length);
    sleep(1);
    close(fd);

    memset(tx,0,data_length);
    sprintf(tx,str_MQTTOPEN,data_length);
    len=strlen(tx);
    fd=uart_init(10);
    if(!write(fd,&tx,len))
    {
        qDebug()<<"mqtt_open\n";
        close(fd);
        return -1;
    }
     qDebug()<<"write2\n";
    //read(fd,rx,data_length);
    //qDebug("%s",rx);
    //memset(rx,0,data_length);
    read(fd,rx,data_length);
    sleep(1);
    qDebug("b%s",rx);
    memset(rx,0,data_length);
    close(fd);
    //read(fd,rx,data_length);
    //qDebug("%s",rx);
    //memset(rx,0,data_length);
    sleep(2);

    memset(tx,0,data_length);
    sprintf(tx,str_MQTTCONNECT,data_length);
    len=strlen(tx);
    fd=uart_init(10);
    if(!write(fd,&tx,len))
    {
        qDebug()<<"mqtt_connect\n";
        close(fd);
        return -1;
    }
     qDebug()<<"write3\n";
    read(fd,rx,data_length);
    qDebug("%s",rx);
    memset(rx,0,data_length);
    memset(tx,0,data_length);
    read(fd,rx,data_length);
    qDebug("%s",rx);
    memset(rx,0,data_length);
    //memset(tx,0,data_length);



    close(fd);
    return 0;
}

/*
IIC数据发送函数
发送数据包括：温度值，大气压强，电压量接口电压值，电流量接口电压值，电流量接口配置状态
发送由int update_data_iic(float volt,float current,float pressure,float temp,bool current_state); 更新的数值  
发送需要4S左右
输入:
    无
输出:
    无
*/
int ec600n::send_iic()
{
    int fd;
    char temp_str[data_length];
    char rx[data_length];
    char str[data_length];
    int len;
    memset(temp_str,0,data_length);
    memset(tx,0,data_length);
    sprintf(temp_str,str_MQTTPUB,strlen(str_MQTTPUB));

    //sprintf(str,"\"{params:{Temperature:%.2f,Pressure:%.2f,Current_port:%.2f,Volt_in:%.2f,Current_port_state:%2d}}\"\r\n",(float)Temperature,(float)Pressure,(float)Current_port,(float)Volt_in,(int)Current_port_state);
    //sprintf(str,"\"{params:{Temperature:%.2f,Pressure:%.2f,Current_port:%.2f,Volt_in:%.2f}}\"\r\n",(float)Temperature,(float)Pressure,(float)Current_port,(float)Volt_in);
    sprintf(str,"\"{params:{Temperature:%.2f,Pressure:%.2f}}\"\r\n",(float)Temperature,(float)Pressure);
    sprintf(tx,"%s,%s",temp_str,str);
    len=strlen(tx);
    fd=uart_init(1);
    if(!write(fd,&tx,len))
    {
        qDebug()<<"write1\n";
        close(fd);
        return -2;
    }
    //sleep(1);
    read(fd,rx,data_length);
    sleep(1);
    qDebug("4%s",rx);
    memset(rx,0,data_length);

    memset(temp_str,0,data_length);
    memset(tx,0,data_length);
    sprintf(temp_str,str_MQTTPUB,strlen(str_MQTTPUB));
    sprintf(str,"\"{params:{Volt_in:%.2f,Current_port_state:%d}}\"\r\n",(float)Volt_in,(int)Current_port_state);
    sprintf(tx,"%s,%s",temp_str,str);
    len=strlen(tx);
    fd=uart_init(1);
    if(!write(fd,&tx,len))
    {
        qDebug()<<"write1\n";
        close(fd);
        return -2;
    }
    //sleep(1);
    read(fd,rx,data_length);
    sleep(1);
    qDebug("5%s",rx);
    memset(rx,0,data_length);

    memset(temp_str,0,data_length);
    memset(tx,0,data_length);
    sprintf(temp_str,str_MQTTPUB,strlen(str_MQTTPUB));
    sprintf(str,"\"{params:{Current_port:%.2f}}\"\r\n",(float)Current_port);
    sprintf(tx,"%s,%s",temp_str,str);
    len=strlen(tx);
    fd=uart_init(1);
    if(!write(fd,&tx,len))
    {
        qDebug()<<"write1\n";
        close(fd);
        return -2;
    }
    //sleep(1);
    read(fd,rx,data_length);
    sleep(1);
    qDebug("6%s",rx);
    memset(rx,0,data_length);

    close(fd);
    return fd;
}

/*
IO口数据发送函数
发送数据包括：IO口一状态；IO口一电平值；IO口二状态；IO口二电平值；IO口三状态；IO口三电平值
发送由update_data_port(bool state_1,bool value_1,bool state_2,bool value_2,bool state_3,bool value_3); 更新的数值  
发送需要4S左右
输入:
    无
输出:
    无
*/
int ec600n::send_port()
{
    int fd;
    char temp_str[data_length];
    char rx[data_length];
    char str[data_length];
    int len;
    memset(temp_str,0,data_length);
    memset(tx,0,data_length);
    sprintf(temp_str,str_MQTTPUB,data_length);
    sprintf(str,"\"{params:{GPIO_1_state:%d,GPIO_1_value:%d}}\"\r\n",(int) GPIO_1_state,(int) GPIO_1_value);
    sprintf(tx,"%s,%s",temp_str,str);
    fd=uart_init(1);
    len=strlen(tx);
    if(!write(fd,&tx,len))
    {
        qDebug()<<"write1\n";
        close(fd);
        return -2;
    }
    //sleep(1);
    read(fd,rx,data_length);
    sleep(1);
    qDebug("1%s",rx);
    memset(rx,0,data_length);

    memset(temp_str,0,data_length);
    memset(tx,0,data_length);
    sprintf(temp_str,str_MQTTPUB,data_length);
    sprintf(str,"\"{params:{GPIO_2_state:%d,GPIO_2_value:%d}}\"\r\n",(int) GPIO_2_state,(int) GPIO_2_value);
    sprintf(tx,"%s,%s",temp_str,str);
    fd=uart_init(1);
    len=strlen(tx);
    if(!write(fd,&tx,len))
    {
        qDebug()<<"write1\n";
        close(fd);
        return -2;
    }
    //sleep(1);
    read(fd,rx,data_length);
    sleep(1);
    qDebug("2%s",rx);
    memset(rx,0,data_length);

    memset(temp_str,0,data_length);
    memset(tx,0,data_length);
    sprintf(temp_str,str_MQTTPUB,data_length);
    sprintf(str,"\"{params:{GPIO_3_state:%d,GPIO_3_value:%d}}\"\r\n",(int) GPIO_3_state,(int) GPIO_3_value);
    sprintf(tx,"%s,%s",temp_str,str);
    fd=uart_init(1);
    len=strlen(tx);
    if(!write(fd,&tx,len))
    {
        qDebug()<<"write1\n";
        close(fd);
        return -2;
    }
    //sleep(1);
    read(fd,rx,data_length);
    sleep(1);
    qDebug("3%s",rx);
    memset(rx,0,data_length);


    return 0;
}

/*
串口数据发送函数
发送数据包括：Zigbee终端一在线状态；Zigbee终端一温度值；Zigbee终端二在线状态；Zigbee终端二温度值。
发送由update_data_uart(bool device_1_state,float temp_1,bool device_2_state,float temp_2); 更新的数值  
送需要3S左右
输入:
    无
输出:
    无
*/

int ec600n::send_uart()
{
    int fd;
    char temp_str[data_length];
    char rx[data_length];
    char str[data_length];
    int len;
    memset(temp_str,0,data_length);
    memset(tx,0,data_length);
    sprintf(temp_str,str_MQTTPUB,data_length);
    //qDebug()<<EndDevice_1_State;
    sprintf(str,"\"{params:{EndDevice_1_temp:%.2f,EndDevice_1_state:%d}}\"\r\n",(float)EndDevice_1_temp,(int)EndDevice_1_State);
    //qDebug()<<EndDevice_1_State;
    sprintf(tx,"%s,%s",temp_str,str);
    fd=uart_init(1);
    len=strlen(tx);
    if(!write(fd,&tx,len))
    {
        qDebug()<<"write1\n";
        close(fd);
        return -2;
    }
    //sleep(1);
    read(fd,rx,data_length);
    sleep(1);
    qDebug("7%s",rx);
    memset(rx,0,data_length);


    memset(temp_str,0,data_length);
    memset(tx,0,data_length);
    sprintf(temp_str,str_MQTTPUB,data_length);
    sprintf(str,"\"{params:{EndDevice_2_temp:%.2f,EndDevice_2_state:%d}}\"\r\n",(float)EndDevice_2_temp,(int)EndDevice_2_State);
    sprintf(tx,"%s,%s",temp_str,str);
    fd=uart_init(1);
    len=strlen(tx);
    if(!write(fd,&tx,len))
    {
        qDebug()<<"write1\n";
        close(fd);
        return -2;
    }
    //sleep(1);
    read(fd,rx,data_length);
    sleep(1);
    qDebug("8%s",rx);
    memset(rx,0,data_length);
    return 0;
}


/*
RS485总线数据发送函数
发送数据包括：测距模块返回的距离值。
发送由update_rs485(int distance);  更新的数值  
送需要1.5S左右
输入:
    无
输出:
    无
*/
int ec600n::send_rs485()
{
    int fd;
    char temp_str[data_length];
    char rx[data_length];
    char str[data_length];
    int len;
    memset(temp_str,0,data_length);
    memset(tx,0,data_length);
    sprintf(temp_str,str_MQTTPUB,data_length);
    sprintf(str,"\"{params:{Distance:%d}}\"\r\n",(int)Distance);
    sprintf(tx,"%s,%s",temp_str,str);
    fd=uart_init(1);
    len=strlen(tx);
    if(!write(fd,&tx,len))
    {
        qDebug()<<"write1\n";
        close(fd);
        return -2;
    }
    //sleep(1);
    read(fd,rx,data_length);
    sleep(1);
    qDebug("9%s",rx);
    memset(rx,0,data_length);

    return 0;
}


/*
IIC采集相关变量更新函数
只负责更新相关的变量值，不负责上传
输入:
    @volt--电压量接口电压值
    @current--电流量接口电流值
    @pressure--大气压强值
    @temp--温度值
    @current_state--电流量接口状态
输出:
    无
注：
    当电流量接口状态为Current_port_state_normal时，Pressure和Temperature会自动变为0，只更新Current_port
    反之只更新Pressure和Temperature，Current_port变为0
示例:
    ec600.update_data_iic(1.33,1.22,1.23,12.6,Current_port_state_normal);
*/
int ec600n::update_data_iic(float volt, float current, float pressure, float temp, bool current_state)
{
    Volt_in=volt;
    Current_port=current;
    Pressure=pressure;
    Temperature=temp;
    Current_port_state=current_state;
    if(Current_port_state==Current_port_state_normal)
    {Temperature=0; Pressure=0;}
    else if(Current_port_state==Current_port_state_sensor)
    {Current_port=0;}
    return 0;
}

/*
IO口相关变量更新函数
只负责更新相关的变量值，不负责上传
输入:
    @state_1--IO口一状态
    @value_1--IO口一电平值
    @state_2--IO口二状态
    @value_2--IO口二电平值
    @state_3--IO口三状态
    @value_3--IO口三电平值
输出:
    无
示例:
    ec600.update_data_port(GPIO_1_state_input,GPIO_1_value_low,GPIO_2_state_output,GPIO_2_value_low,GPIO_3_state_input,GPIO_3_value_high);
*/
int ec600n::update_data_port(bool state_1, bool value_1, bool state_2, bool value_2, bool state_3, bool value_3)
{
    GPIO_1_state=state_1;
    GPIO_1_value=value_1;

    GPIO_2_state=state_2;
    GPIO_2_value=value_2;

    GPIO_3_state=state_3;
    GPIO_3_value=value_3;

    return 0;
}


/*
串口相关变量更新函数
只负责更新相关的变量值，不负责上传
输入:
    @device_1_state--Zigee终端一在线状态
    @temp_1--Zigbee终端一温度值
    @device_2_state--Zigbee终端二在线状态
    @temp_2--Zigbee终端二温度值
输出:
    无
注：
    当终端的状态为离线状态时其采集的对应温度值会自动变为0，无法设置
示例:
    ec600.update_data_uart(EndDevice_1_State_Online,24.5,EndDevice_2_State_Offline,25.7);
*/
int ec600n::update_data_uart(bool device_1_state, float temp_1, bool device_2_state, float temp_2)
{
    EndDevice_1_State=device_1_state;
    if(EndDevice_1_State==EndDevice_1_State_Online)
        EndDevice_1_temp=temp_1;
    else if(EndDevice_1_State==EndDevice_1_State_Offline)
        EndDevice_1_temp=0;
    EndDevice_2_State=device_2_state;
    if(EndDevice_2_State==EndDevice_2_State_Online)
        EndDevice_2_temp=temp_2;
    else if(EndDevice_2_State==EndDevice_2_State_Offline)
        EndDevice_2_temp=0;

    return 0;
}

/*
RS485总线相关变量更新函数
只负责更新相关的变量值，不负责上传
输入:
    @distance--测距模块距离值
输出:
    无
示例:
    ec600.update_rs485(1223);
*/
int ec600n::update_rs485(int distance)
{
    Distance=distance;
    return 0;
}


/*
无关函数
*/
int ec600n::uart_init(int vmin)
{
    int fd;

        fd = open("/dev/ttyS0", O_RDWR|O_NOCTTY|O_NDELAY);

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

    if(set_com_config(fd, 9600, 8, 'N', 1,vmin) < 0) /* 配置串口 */
        {
            perror("set_com_config");
            ::close(fd);
            return -4;
        }
    return fd;
}
/*
无关函数
*/
int ec600n::set_com_config(int fd, int baud_rate, int data_bits, char parity, int stop_bits,int vmin)
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
    new_cfg.c_cc[VMIN] = vmin;
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
