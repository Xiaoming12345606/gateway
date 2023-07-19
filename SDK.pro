#-------------------------------------------------
#
# Project created by QtCreator 2023-06-17T04:07:04
#
#-------------------------------------------------
INCLUDEPATH += ../qcloud_iot_c_sdk/include
INCLUDEPATH += ../qcloud_iot_c_sdk/include/exports
INCLUDEPATH += ../qcloud_iot_c_sdk/sdk_src/internal_inc
QT       += core gui
QT       +=serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = SDK
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
    qcloud_iot_c_sdk/platform/HAL_Device_linux.c \
    qcloud_iot_c_sdk/platform/HAL_File_linux.c \
    qcloud_iot_c_sdk/platform/HAL_Log_linux.c \
    qcloud_iot_c_sdk/platform/HAL_OS_linux.c \
    qcloud_iot_c_sdk/platform/HAL_TCP_linux.c \
    qcloud_iot_c_sdk/platform/HAL_Timer_linux.c \
    qcloud_iot_c_sdk/platform/HAL_UDP_linux.c \
    qcloud_iot_c_sdk/sdk_src/data_template_action.c \
    qcloud_iot_c_sdk/sdk_src/data_template_client.c \
    qcloud_iot_c_sdk/sdk_src/data_template_client_common.c \
    qcloud_iot_c_sdk/sdk_src/data_template_client_json.c \
    qcloud_iot_c_sdk/sdk_src/data_template_client_manager.c \
    qcloud_iot_c_sdk/sdk_src/data_template_event.c \
    qcloud_iot_c_sdk/sdk_src/device_bind.c \
    qcloud_iot_c_sdk/sdk_src/dynreg.c \
    qcloud_iot_c_sdk/sdk_src/file_manage_client.c \
    qcloud_iot_c_sdk/sdk_src/gateway_api.c \
    qcloud_iot_c_sdk/sdk_src/gateway_common.c \
    qcloud_iot_c_sdk/sdk_src/json_parser.c \
    qcloud_iot_c_sdk/sdk_src/json_token.c \
    qcloud_iot_c_sdk/sdk_src/kgmusic_client.c \
    qcloud_iot_c_sdk/sdk_src/location.c \
    qcloud_iot_c_sdk/sdk_src/mqtt_client.c \
    qcloud_iot_c_sdk/sdk_src/mqtt_client_common.c \
    qcloud_iot_c_sdk/sdk_src/mqtt_client_connect.c \
    qcloud_iot_c_sdk/sdk_src/mqtt_client_net.c \
    qcloud_iot_c_sdk/sdk_src/mqtt_client_publish.c \
    qcloud_iot_c_sdk/sdk_src/mqtt_client_subscribe.c \
    qcloud_iot_c_sdk/sdk_src/mqtt_client_unsubscribe.c \
    qcloud_iot_c_sdk/sdk_src/mqtt_client_yield.c \
    qcloud_iot_c_sdk/sdk_src/network_interface.c \
    qcloud_iot_c_sdk/sdk_src/network_socket.c \
    qcloud_iot_c_sdk/sdk_src/ota_client.c \
    qcloud_iot_c_sdk/sdk_src/ota_fetch.c \
    qcloud_iot_c_sdk/sdk_src/ota_lib.c \
    qcloud_iot_c_sdk/sdk_src/ota_mqtt.c \
    qcloud_iot_c_sdk/sdk_src/qcloud_iot_ca.c \
    qcloud_iot_c_sdk/sdk_src/qcloud_iot_device.c \
    qcloud_iot_c_sdk/sdk_src/qcloud_iot_log.c \
    qcloud_iot_c_sdk/sdk_src/resource_client.c \
    qcloud_iot_c_sdk/sdk_src/resource_lib.c \
    qcloud_iot_c_sdk/sdk_src/resource_mqtt.c \
    qcloud_iot_c_sdk/sdk_src/resource_upload.c \
    qcloud_iot_c_sdk/sdk_src/service_mqtt.c \
    qcloud_iot_c_sdk/sdk_src/string_utils.c \
    qcloud_iot_c_sdk/sdk_src/utils_aes.c \
    qcloud_iot_c_sdk/sdk_src/utils_base64.c \
    qcloud_iot_c_sdk/sdk_src/utils_getopt.c \
    qcloud_iot_c_sdk/sdk_src/utils_hmac.c \
    qcloud_iot_c_sdk/sdk_src/utils_httpc.c \
    qcloud_iot_c_sdk/sdk_src/utils_list.c \
    qcloud_iot_c_sdk/sdk_src/utils_md5.c \
    qcloud_iot_c_sdk/sdk_src/utils_ringbuff.c \
    qcloud_iot_c_sdk/sdk_src/utils_sha1.c \
    qcloud_iot_c_sdk/sdk_src/utils_timer.c \
    qcloud_iot_c_sdk/sdk_src/utils_url_download.c \
    qcloud_iot_c_sdk/sdk_src/utils_url_upload.c \
    ads_1115.cpp \
    serial.cpp \
    wt53r-485.cpp \
    yx75r.cpp \
    deviceworker.cpp \
    gpio.cpp \
    uart.cpp \
    temperature.cpp \
    gpio_up.cpp \
    ec600n.cpp \
    shareddara.cpp \
    adc.cpp \
    distance.cpp \
    fourg.cpp \
    bj.cpp \
    uidemo08.cpp \
    appinit.cpp \
    iconhelper.cpp \
    networkwidget.cpp \



HEADERS += \
    qcloud_iot_c_sdk/include/exports/qcloud_iot_export_asr.h \
    qcloud_iot_c_sdk/include/exports/qcloud_iot_export_data_template.h \
    qcloud_iot_c_sdk/include/exports/qcloud_iot_export_device_bind.h \
    qcloud_iot_c_sdk/include/exports/qcloud_iot_export_dynreg.h \
    qcloud_iot_c_sdk/include/exports/qcloud_iot_export_error.h \
    qcloud_iot_c_sdk/include/exports/qcloud_iot_export_file_manage.h \
    qcloud_iot_c_sdk/include/exports/qcloud_iot_export_gateway.h \
    qcloud_iot_c_sdk/include/exports/qcloud_iot_export_kgmusic.h \
    qcloud_iot_c_sdk/include/exports/qcloud_iot_export_location.h \
    qcloud_iot_c_sdk/include/exports/qcloud_iot_export_log.h \
    qcloud_iot_c_sdk/include/exports/qcloud_iot_export_method.h \
    qcloud_iot_c_sdk/include/exports/qcloud_iot_export_mqtt.h \
    qcloud_iot_c_sdk/include/exports/qcloud_iot_export_ota.h \
    qcloud_iot_c_sdk/include/exports/qcloud_iot_export_resource.h \
    qcloud_iot_c_sdk/include/exports/qcloud_iot_export_system.h \
    qcloud_iot_c_sdk/include/config.h \
    qcloud_iot_c_sdk/include/gitinfo.h \
    qcloud_iot_c_sdk/include/lite-list.h \
    qcloud_iot_c_sdk/include/lite-utils.h \
    qcloud_iot_c_sdk/include/platform.h \
    qcloud_iot_c_sdk/include/qcloud_iot_export.h \
    qcloud_iot_c_sdk/include/qcloud_iot_export_variables.h \
    qcloud_iot_c_sdk/include/qcloud_iot_import.h \
    qcloud_iot_c_sdk/include/utils_getopt.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/asr_client.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/at_client.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/at_socket_inf.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/at_uart_hal.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/at_utils.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/data_template_action.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/data_template_client.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/data_template_client_common.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/data_template_client_json.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/data_template_event.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/file_manage_client.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/gateway_common.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/json_parser.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/log_upload.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/mqtt_client.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/mqtt_client_net.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/network_interface.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/ota_client.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/ota_fetch.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/ota_lib.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/qcloud_iot_ca.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/qcloud_iot_common.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/qcloud_iot_device.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/qcloud_wifi_config.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/qcloud_wifi_config_internal.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/resource_client.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/resource_lib.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/resource_upload.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/service_mqtt.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/utils_aes.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/utils_base64.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/utils_hmac.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/utils_httpc.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/utils_list.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/utils_md5.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/utils_param_check.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/utils_ringbuff.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/utils_sha1.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/utils_timer.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/utils_url_download.h \
    qcloud_iot_c_sdk/sdk_src/internal_inc/utils_url_upload.h \
    adc.h \
    ads_1115.h \
    appinit.h \
    bj.h \
    deviceworker.h \
    distance.h \
    ec600n.h \
    fourg.h \
    gpio.h \
    gpio_up.h \
    iconhelper.h \
    networkwidget.h \
    serial.h \
    shareddata.h \
    temperature.h \
    uart.h \
    uidemo08.h \
    wt53r-485.h \
    yx75r.h
LIBS += -lQt5SerialPort
FORMS += \
    uidemo08.ui

    uidemo08.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qss.qrc \
    main.qrc \
    main.qrc \
    qss.qrc \
    resources.qrc

DISTFILES += \
    image/fontawesome-webfont.ttf \
    image/down-arrow.png \
    image/down.png \
    image/kongzhi.png \
    image/line.png \
    image/logo.png \
    image/main_about.png \
    image/main_company.png \
    image/main_config.png \
    image/main_data.png \
    image/main_exit.png \
    image/main_help.png \
    image/main_main.png \
    image/main_person.png \
    image/online.png \
    image/online1.png \
    qss/psblack/add_bottom.png \
    qss/psblack/add_left.png \
    qss/psblack/add_right.png \
    qss/psblack/add_top.png \
    qss/psblack/branch_close.png \
    qss/psblack/branch_open.png \
    qss/psblack/calendar_nextmonth.png \
    qss/psblack/calendar_prevmonth.png \
    qss/psblack/checkbox_checked.png \
    qss/psblack/checkbox_checked_disable.png \
    qss/psblack/checkbox_parcial.png \
    qss/psblack/checkbox_parcial_disable.png \
    qss/psblack/checkbox_unchecked.png \
    qss/psblack/checkbox_unchecked_disable.png \
    qss/psblack/radiobutton_checked.png \
    qss/psblack/radiobutton_checked_disable.png \
    qss/psblack/radiobutton_unchecked.png \
    qss/psblack/radiobutton_unchecked_disable.png \
    qss/psblack.css
