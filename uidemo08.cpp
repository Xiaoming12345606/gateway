#pragma execution_character_set("utf-8")

#include "uidemo08.h"
#include "ui_uidemo08.h"
#include "iconhelper.h"

UIDemo08::UIDemo08(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UIDemo08)
{
    ui->setupUi(this);
    this->initForm();
    this->initLeftMain();
    this->initLeftConfig();
    // 初始化下拉框，激活下拉框样式
    QList<QComboBox*> comboList = {ui->methodComboBox1, ui->methodComboBox2,
                                   ui->uartComboBox, ui->zigbeeComboBox1, ui->gpioComboBox,
                                   ui->gpioComboBox2, ui->interfaceComboBox};
    for (int i = 0; i < comboList.size(); i++) {
        comboList[i]->setView(new QListView());
    }
    // 添加阴影效果
    QList<QWidget*> shadowList = {ui->widget_11, ui->widget_16, ui->widget_17, ui->widget_20,
                            ui->widget_26, ui->widget_2, ui->widget_4,
                            ui->widget_46, ui->widget_35, ui->widget_32,
                            ui->widget_37, ui->widget_41, ui->widget_44,ui->widget_52
                           };
    for (int i = 0; i < shadowList.size(); i++) {
        QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(shadowList[i]);
        shadow_effect->setOffset(0, 0);              //阴影的偏移量
        shadow_effect->setColor(QColor(180, 180, 180)); //阴影的颜色
        shadow_effect->setBlurRadius(15);             // 阴影圆角的大小
        shadowList[i]->setGraphicsEffect(shadow_effect);//给那个控件设置阴影，这里需要注意的是所有此控件的子控件，也都继承这个阴影。
    }
    // 拓扑图
    networkWidget = new NetWorkWidget();
    ui->network->layout()->addWidget(networkWidget);


    qDebug() << "widget:"<<QThread::currentThreadId();
      startDeviceThread();
      qDebug() << "WXThread";
      startFourgThread();
      qDebug() << "FourgThread";

      startDistanceThread();
      qDebug() << "DistanceThread";
      startTemperatureThread();
      qDebug() << "TemperatureThread";
      startADCThread();
      qDebug() << "ADCThread";
      startGPIOThread();
      qDebug() << "GPIOThread";

      startZigbeeThread();
      qDebug() << "ZigbeeThread";
      startSTMThread();
      qDebug() << "STMThread";

      isDistanceThreadRunning=false;
      QTimer* checkThreadTimer = new QTimer(this);
      connect(checkThreadTimer, &QTimer::timeout, this, &UIDemo08::checkDistanceThread);
      checkThreadTimer->start(2000);
      qDebug() << "checkThreadTimer connected";

      isTemperatureThreadRunning=false;
      QTimer* checkThreadTimer_t = new QTimer(this);
      connect(checkThreadTimer_t, &QTimer::timeout, this, &UIDemo08::checkTemperatureThread);
      checkThreadTimer_t->start(2000);
      qDebug() << "checkThreadTimer_t connected";

     serial=new Serial();//串口 STM32

      QTimer* updateRealDataTimer = new QTimer(this);
      connect(updateRealDataTimer, &QTimer::timeout, this, &UIDemo08::updateRealtimeData);
      updateRealDataTimer->start(1500);

      QTimer* showTemperatureTimer = new QTimer(this);
      connect(showTemperatureTimer, &QTimer::timeout, this, &UIDemo08::showTemperature);
      showTemperatureTimer->start(1000);

      QTimer* showDistanceTimer = new QTimer(this);
      connect(showDistanceTimer, &QTimer::timeout, this, &UIDemo08::showDistance);
      showDistanceTimer->start(1000);

      QTimer* updateNetworkTimer = new QTimer(this);
      connect(updateNetworkTimer, &QTimer::timeout, this, &UIDemo08::updateNetwork);
      updateNetworkTimer->start(1000);

      QTimer* stopMachineTimer = new QTimer(this);
      connect(stopMachineTimer, &QTimer::timeout, this, &UIDemo08::stopMachine);
      stopMachineTimer->start(1000);
}

UIDemo08::~UIDemo08()
{
    delete ui;
}

void UIDemo08::initForm()
{   
    this->setProperty("form", true);
    this->setProperty("canMove", true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);

    IconHelper::Instance()->setIcon(ui->labIco, QChar(0xf073), 30);
    IconHelper::Instance()->setIcon(ui->btnMenu_Min, QChar(0xf068));
    IconHelper::Instance()->setIcon(ui->btnMenu_Max, QChar(0xf067));
    IconHelper::Instance()->setIcon(ui->btnMenu_Close, QChar(0xf00d));

    QSize icoSize(32, 32);
    int icoWidth = 85;

    // 设置顶部导航按钮
    QList<QToolButton *> tbtns = ui->widgetTop->findChildren<QToolButton *>();
    foreach (QToolButton *btn, tbtns) {
        btn->setIconSize(icoSize);
        btn->setMinimumWidth(icoWidth);
        btn->setCheckable(true);
        connect(btn, SIGNAL(clicked()), this, SLOT(buttonClick()));
    }

    ui->btnMain->click();

    ui->widgetLeftMain->setProperty("flag", "left");
    ui->widgetLeftConfig->setProperty("flag", "left");
}

void UIDemo08::buttonClick()
{
    QToolButton *b = (QToolButton *)sender();
    QString name = b->text();

    QList<QToolButton *> tbtns = ui->widgetTop->findChildren<QToolButton *>();
    foreach (QToolButton *btn, tbtns) {
        if (btn == b) {
            btn->setChecked(true);
        } else {
            btn->setChecked(false);
        }
    }
    if (name == "主 页") {
        ui->stackedWidget->setCurrentIndex(0);
    } else if (name == "设 置") {
        ui->stackedWidget->setCurrentIndex(1);
    }
    else if (name == "退 出") {
        exit(0);
    }
}

void UIDemo08::initLeftMain()
{
    pixCharMain << 0xf030 << 0xf03e ;
                //<< 0xf247;
    btnsMain << ui->tbtnMain1 << ui->tbtnMain2;
            //<< ui->tbtnMain3;
    int count = btnsMain.count();
    for (int i = 0; i < count; i++) {
        btnsMain.at(i)->setCheckable(true);
        connect(btnsMain.at(i), SIGNAL(clicked(bool)), this, SLOT(leftMainClick()));
    }
    // 用于设置左侧导航栏的样式和图标。
    ui->tbtnMain1->click();
}

void UIDemo08::initLeftConfig()
{
    pixCharConfig << 0xf031 << 0xf036 << 0xf249 << 0xf055 << 0xf05a << 0xf249;
    btnsConfig << ui->tbtnConfig1 << ui->tbtnConfig2 << ui->tbtnConfig3 << ui->tbtnConfig4 << ui->tbtnConfig5;
               //<< ui->tbtnConfig6;
    int count = btnsConfig.count();
    for (int i = 0; i < count; i++) {
        btnsConfig.at(i)->setFont(QFont("Arial", 6));
        btnsConfig.at(i)->setCheckable(true);
        connect(btnsConfig.at(i), SIGNAL(clicked(bool)), this, SLOT(leftConfigClick()));
    }
    ui->tbtnConfig1->click();
}

void UIDemo08::leftMainClick()
{
    QToolButton *b = (QToolButton *)sender();
    QString name = b->text();

    int count = btnsMain.count();
    for (int i = 0; i < count; i++) {
        if (btnsMain.at(i) == b) {
            // 跳转到相应实时数据或网络拓扑界面
            ui->mainStackedWidget->setCurrentIndex(i);
            btnsMain.at(i)->setChecked(true);
        } else {
            btnsMain.at(i)->setChecked(false);
        }
    }
}

void UIDemo08::leftConfigClick()
{
    QToolButton *b = (QToolButton *)sender();
    QString name = b->text();

    int count = btnsConfig.count();
    for (int i = 0; i < count; i++) {
        if (btnsConfig.at(i) == b) {
            // 跳转到相应的配置界面
            ui->configStackedWidget->setCurrentIndex(i);
            btnsConfig.at(i)->setChecked(true);
        } else {
            btnsConfig.at(i)->setChecked(false);
        }
    }

    //ui->lab2->setText(name);
}

void UIDemo08::on_btnMenu_Min_clicked()
{
    showMinimized();
}

void UIDemo08::on_btnMenu_Max_clicked()
{
    static bool max = false;
    static QRect location = this->geometry();

    if (max) {
        this->setGeometry(location);
    } else {
        location = this->geometry();
        this->setGeometry(qApp->desktop()->availableGeometry());
    }

    this->setProperty("canMove", max);
    max = !max;
}
void UIDemo08::on_btnMenu_Close_clicked()
{
    close();
}

void UIDemo08::startDeviceThread()
{
    // 创建新线程对象
     deviceThread = new QThread(this);
    // 创建设备对象
    deviceWorker = new DeviceWorker();

    deviceWorker->moveToThread(deviceThread);
    // 连接线程启动信号与设备对象的槽函数
    connect(deviceThread, &QThread::started, deviceWorker, &DeviceWorker::runDeviceTemplate);
    // 启动线程
    deviceThread->start();
}
void UIDemo08::startFourgThread()
{
    // 创建新线程对象
     fourgThread = new QThread(this);
    // 创建设备对象
    fourg = new FourG();
    fourg->moveToThread(fourgThread);
    // 连接线程启动信号与设备对象的槽函数
    connect(fourgThread, &QThread::started, fourg, &FourG::upload);
    // 启动线程
    fourgThread->start();
}
void UIDemo08::startADCThread(){
    ADCThread= new QThread(this);
    adc=new ADC();
    adc->moveToThread(ADCThread);
    connect(ADCThread, &QThread::started, adc, &ADC::readADCdata);
    ADCThread->start();
}
void UIDemo08::startGPIOThread(){
    GPIOThread = new QThread(this);
    gpio= new GPIO();
    gpio->moveToThread(GPIOThread);
    connect(GPIOThread, &QThread::started, gpio, &GPIO::readGPIOdata);
    GPIOThread->start();
}
void UIDemo08::startDistanceThread(){
    distanceThread=new QThread(this);
    distance =new Distance();
    //distance->setSharedData(sharedData);
    distance->moveToThread(distanceThread);
    connect(distanceThread, &QThread::started, distance,&Distance::readDistance);
    connect(distance, &Distance::threadBlocked, this, &UIDemo08::killDistanceThread);
    // 启动线程
    distanceThread->start();
    isDistanceThreadRunning = true;
}

void UIDemo08::checkDistanceThread()
{
    if (!distanceThread->isRunning())
    {
        QTimer::singleShot(10000, this, &UIDemo08::restartDistanceThread); // 10秒后重新启动线程
    }
}
void UIDemo08::killDistanceThread()
{
    qDebug() << "Killing distance thread...";
    if (distanceThread->isRunning())
    {
        distanceThread->quit();
        distanceThread->wait();
        delete distanceThread;
        distanceThread = nullptr;
        delete distance;
        distance = nullptr;
        isDistanceThreadRunning = false;
    }
}
void UIDemo08::restartDistanceThread()
{
    if (!distanceThread && !isDistanceThreadRunning)
    {
        qDebug() << "Restarting distance thread...";
        startDistanceThread();
    }
}

void UIDemo08::startTemperatureThread(){
    qDebug()<<"startTemperatureThread";
    temperatureThread=new QThread(this);
    qDebug()<<"NEW Thread";
    temperature_T=new Temperature();
    qDebug()<<"NEW Temperature";
    temperature_T->moveToThread(temperatureThread);
    qDebug()<<"moveToThread";
    connect(temperatureThread, &QThread::started, temperature_T,&Temperature::readTemperature);
    qDebug()<<"connect start";
    //connect(temperature_T, &Temperature::threadBlocked, this, &UIDemo08::killTemperatureThread);
    // 启动线程
    qDebug()<<"connect kill";
    temperatureThread->start();
    qDebug()<<"Thread start";
    isTemperatureThreadRunning=true;
}

void UIDemo08::checkTemperatureThread()
{
    if (!temperatureThread->isRunning())
    {
        QTimer::singleShot(10000, this, &UIDemo08::restartTemperatureThread); // 10秒后重新启动线程
    }
}
void UIDemo08::killTemperatureThread()
{
    qDebug() << "Killing temperature thread...";
    if (temperatureThread->isRunning())
    {
        temperatureThread->quit();
        temperatureThread->wait();
        delete distanceThread;
        temperatureThread = nullptr;
        delete distance;
        temperature_T = nullptr;
        isTemperatureThreadRunning = false;
    }
}
void UIDemo08::restartTemperatureThread()
{
    if (!temperatureThread && !isTemperatureThreadRunning)
    {
        qDebug() << "Restarting temperature thread...";
        startTemperatureThread();
    }
}


void UIDemo08::startZigbeeThread(){
    zigbeeThread=new QThread(this);
    bjZigbee=new BJ();
    bjZigbee->moveToThread(zigbeeThread);
    connect(zigbeeThread, &QThread::started,bjZigbee ,&BJ::bj_zigbee);
    zigbeeThread->start();
}
void UIDemo08::startSTMThread(){
    stmThread=new QThread(this);
    bjStm=new BJ();
    bjStm->moveToThread(stmThread);
    connect(stmThread, &QThread::started,bjStm ,&BJ::bj_stm);
    stmThread->start();
}
void UIDemo08::on_zigbeeConfirmButton_clicked()
{
    selectedOption_zigbee=ui->zigbeeComboBox1->currentText();
    if(selectedOption_zigbee=="串口接口一"){

       SharedData::zigbee=2;
    }else{
      SharedData::zigbee=3;
    }
}

void UIDemo08::on_gpioConfirmButton_clicked()
{
    selectedOption_GPIO=ui->gpioComboBox->currentText();
    //gpio_up, gpio
    qDebug()<<"GPIO61"<<selectedOption_GPIO;
    if(selectedOption_GPIO=="输入模式"){
        //G_61.init(gpio_61,gpio_input_mode);
        qDebug()<<"INPUT";
        SharedData::mode=2;
    }else if(selectedOption_GPIO=="输出模式（低电平）"){
       // G_61.init(gpio_61,gpio_output_mode);
       // G_61.wr(gpio_61,gpio_low);
        qDebug()<<"output_low";
        SharedData::mode=1;
        SharedData::dat=0;
    }else{
       // G_61.init(gpio_61,gpio_output_mode);
        //G_61.wr(gpio_61,gpio_high);
        qDebug()<<"output_high";
        SharedData::mode=1;
        SharedData::dat=1;
    }
}

void UIDemo08::on_interfaceConfirmButton_clicked()
{
    selectedOption_current=ui->interfaceComboBox->currentText();
    if(selectedOption_current=="常规模拟电流值"){
        SharedData::current_state=0;
    }else if(selectedOption_current=="大气压强传感器"){
        SharedData::current_state=1;
    }else{
        SharedData::current_state=2;
    }
}


void UIDemo08::on_openAlarmButton2_clicked()
{
    qDebug()<<"temperature BJ button";
    bj_zigbee_add_string=ui->addLineEdit->text();

    SharedData::bj_zigbee_add=bj_zigbee_add_string.toInt();
 qDebug()<<"zigbee_add"<<SharedData::bj_zigbee_add;
    QByteArray tmp=bj_zigbee_add_string.toLatin1();
    //bj_zigbee_add=tmp.data();
    SharedData::bj_zigbee_limit=ui->limitLineEdit->text().toFloat();
qDebug()<<"zigbee_limit"<<SharedData::bj_zigbee_limit;
    selectedOption_bj_zigbee_method=ui->methodComboBox2->currentText();
    if(selectedOption_bj_zigbee_method=="常亮"){
        SharedData::bj_zigbee_method=commad_steadyon;
    }else  if(selectedOption_bj_zigbee_method=="爆闪"){
        SharedData::bj_zigbee_method=commad_fastflash;
    }else if(selectedOption_bj_zigbee_method=="慢闪"){
        SharedData::bj_zigbee_method=commad_slowflash;
    }
    /*if(SharedData::flag_zigbee==0){
        SharedData::flag_zigbee=1;
    }else{
        SharedData::flag_zigbee=0;
    }*/
    SharedData::flag_zigbee=1;
    qDebug()<<"SharedData::flag_zigbee"<<SharedData::flag_zigbee;
}


void UIDemo08::on_closeAlarmButton2_clicked()
{
     qDebug()<<"close";
    SharedData::flag_zigbee=0;
     qDebug()<<"SharedData::flag_zigbee"<<SharedData::flag_zigbee;
}

void UIDemo08::on_openAlarmButton1_clicked()
{
    bj_stm_add_string=ui->addLineEdit1->text();
    SharedData::bj_stm_add=bj_stm_add_string.toInt();
    qDebug()<<"SharedData::bj_stm_add"<<SharedData::bj_stm_add;
    SharedData::bj_stm_limit=ui->limitLineEdit1->text().toFloat();
    qDebug()<<"SharedData::bj_stm_limit"<<SharedData::bj_stm_limit;

    selectedOption_bj_stm_io=ui->gpioComboBox2->currentText();
   // if(selectedOption_bj_stm_io.toInt()==62){
    if(selectedOption_bj_stm_io=="开关量接口一"){
        SharedData::bj_GPIO=62;
    //}else  if(selectedOption_bj_stm_io.toInt()==63){
    }else{
        SharedData::bj_GPIO=63;
    }
    selectedOption_bj_stm_method=ui->methodComboBox1->currentText();
    if(selectedOption_bj_stm_method=="常亮"){
        SharedData::bj_stm_method=commad_steadyon;
    }else  if(selectedOption_bj_stm_method=="爆闪"){
        SharedData::bj_stm_method=commad_fastflash;
    }else if(selectedOption_bj_stm_method=="慢闪"){
        SharedData::bj_stm_method=commad_slowflash;
    }
/*
   if(SharedData::flag_stm==0){
       SharedData::flag_stm=1;
    }else{
        SharedData::flag_stm=0;
    }
    */
     SharedData::flag_stm=1;
      qDebug()<<"SharedData::flag_stm"<<SharedData::flag_stm;
}



void UIDemo08::on_closeAlarmButton1_clicked()
{
    qDebug()<<"flag_stm close";
    SharedData::flag_stm=0;
    qDebug()<<"SharedData::flag_stm"<<SharedData::flag_stm;
}

void UIDemo08::on_openUartButton_clicked()
{
    selectedOption_stm32=ui->uartComboBox->currentText();
    if(selectedOption_stm32=="串口接口一"){
       serial->openSerialPort("/dev/ttyS2");
       qDebug()<<"uart_2";
    }else{
       serial->openSerialPort("/dev/ttyS3");
       qDebug()<<"uart_3";
    }
}


void UIDemo08::on_closeUartButton_clicked()
{
    serial->close();
    qDebug()<<"close";
}


void UIDemo08::on_leftButton_clicked()
{
   // if(SharedData::flag_stm==1){
        qDebug()<<"move0";
        if(serial->isOpen() && serial->isWritable()) {
                qDebug() << "send data!";
                QByteArray data = "MOVE0\n";
                serial->write(data);
                serial->waitForBytesWritten(100); // 等待发送完成
                qDebug()<<"DATA:"<< data;
            } else {
                qDebug() << "Cannot send data, serial port is not open or not writable!";
            }
   // }
}


void UIDemo08::on_rightButton_clicked()
{
    //if(SharedData::flag_stm==1){
        qDebug()<<"move1";
        if(serial->isOpen() && serial->isWritable()) {
                qDebug() << "send data!";
                QByteArray data = "MOVE1\n";
                serial->write(data);
                serial->waitForBytesWritten(100); // 等待发送完成
                qDebug()<<"DATA:"<< data;
            } else {
                qDebug() << "Cannot send data, serial port is not open or not writable!";
            }
   // }
}

void UIDemo08::on_stopButton_clicked()
{
    //if(SharedData::flag_stm==1){
    if(serial->isOpen() && serial->isWritable()) {
            qDebug() << "send data!";
            QByteArray data = "STOP!\n";
            serial->write(data);
            serial->waitForBytesWritten(100); // 等待发送完成
            qDebug()<<"DATA:"<< data;
        } else {
            qDebug() << "Cannot send data, serial port is not open or not writable!";
        }
    qDebug()<<"stop";
    //}
}
void UIDemo08::updateRealtimeData(){
    //ui->current->setText(QString::number(SharedData::share_current));
    //ui->pressure->setText(QString::number(SharedData::share_atmosphere_pressure));
    //ui->temperature->setText(QString::number(SharedData::share_temperature));
    if(SharedData::current_state==0){
       qDebug()<<"常规模拟电流值";
       ui->current->setText(QString::number(SharedData::share_current));
       ui->pressure->setText("--");
       ui->temperature->setText("--");
       ui->current_in_state->setText("常规模拟电流值");
    }else if(SharedData::current_state==1){
        qDebug()<<"大气压强传感器";
        ui->pressure->setText(QString::number(SharedData::share_atmosphere_pressure));
        ui->current->setText("--");
        ui->temperature->setText("--");
        ui->current_in_state->setText("大气压强传感器");
    }else if(SharedData::current_state==2){
        qDebug()<<"温度传感器";
        ui->temperature->setText(QString::number(SharedData::share_temperature));
        ui->pressure->setText("--");
        ui->current->setText("--");
        ui->current_in_state->setText("温度传感器");
    }

    ui->voltage->setText(QString::number(SharedData::share_voltage));

    if(SharedData::share_temperature1_state){
        ui->temperature_1->setText(QString::number(SharedData::share_temperature1));
        //ui->temperature_2->setText(QString::number(SharedData::share_temperature2));
    }else{
       ui->temperature_1->setText("--");
    }
    if(SharedData::share_temperature2_state){
        //ui->temperature_1->setText(QString::number(SharedData::share_temperature1));
        ui->temperature_2->setText(QString::number(SharedData::share_temperature2));
    }else{
       ui->temperature_2->setText("--");
    }
    qDebug()<<"ui->distance"<<SharedData::share_distance;
    ui->distance->setText(QString::number(SharedData::share_distance));

    if(SharedData::share_GPIO1_state){
        ui->gpio1_state->setText("输出模式");
    }else{
        ui->gpio1_state->setText("输入模式");
    }
    if(SharedData::share_GPIO1_value){
        ui->gpio1->setText("高电平");
    }else{
        ui->gpio1->setText("低电平");
    }
    if(SharedData::share_GPIO2_value){
        ui->gpio2->setText("高电平");
    }else{
        ui->gpio2->setText("低电平");
    }
    if(SharedData::share_GPIO3_value){
        ui->gpio3->setText("高电平");
    }else{
        ui->gpio3->setText("低电平");
    }

}
void UIDemo08::showTemperature(){
   // qDebug()<<"showTemperature";
    if(SharedData::flag_zigbee==1){
        //qDebug()<<"curTemperature"<<SharedData::share_temperature2;
        ui->curTemperature->setText(QString::number(SharedData::share_temperature2));
    }else{
        //qDebug()<<"curTemperature --";
        ui->curTemperature->setText("--");
    }
}
void UIDemo08::showDistance(){
    if(SharedData::flag_stm==1){
        ui->curDistance->setText(QString::number(SharedData::share_distance));
    }else{
        ui->curDistance->setText("--");
    }

}
void UIDemo08::updateNetwork(){
    if(SharedData::share_mainTemperature_state){
        qDebug()<<"share_mainTemperature_state";
        node[0]=1;
    }
    if(SharedData::share_temperature1_state){
        node[1]=1;
        line[0]=1;
    }else{
        node[1]=0;
        line[0]=0;
    }
    if(SharedData::share_temperature2_state){
        node[2]=1;
        line[1]=1;
    }else{
        node[2]=0;
        line[1]=0;
    }
   // qDebug()<<"node[0]"<<node[0];
   // qDebug()<<"node[1]"<<node[1];
  //  qDebug()<<"node[2]"<<node[2];
    networkWidget->setNodeAndLineState(node,line);
}
void UIDemo08::stopMachine(){
        if((SharedData::flag_stm==1)&&(!SharedData::tmp)&&(SharedData::share_distance<=SharedData::bj_stm_limit)){
            if(serial->isOpen() && serial->isWritable()) {
                    qDebug() << "send data!";
                    QByteArray data = "STOP!\n";
                    serial->write(data);
                    serial->waitForBytesWritten(100); // 等待发送完成
                    qDebug()<<"DATA:"<< data;
                } else {
                    qDebug() << "Cannot send data, serial port is not open or not writable!";
                }
}
}
