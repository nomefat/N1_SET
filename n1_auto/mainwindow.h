#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTDebug>
#include <QTreeWidgetItem>
#include <QTcpSocket>
#include <QThread>
#include "mythread.h"
#include "handlethread.h"
#include <QBuffer.h>
#include <QQueue>
#include <QMutex>
#include "n1_data_typedef.h"
#include "n1_devicetable.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_BTN_MODIFY_clicked();

    void on_BTN_ADD_AP_clicked();

    void on_BTN_ADD_RP_clicked();

    void on_BTN_ADD_Sensor_clicked();

    void on_BTN_DEL_clicked();

    void on_saveconfig_clicked();

    void on_openconfig_clicked();

    void on_BTN_Connect_clicked();

    void on_socket_connected();

    void on_socket_disconnected();

    void on_socket_receive();

    void on_CLBtn_openDeviceTable_clicked();

    void on_BTN_GetAPparam_clicked();

    void on_BTN_Adjust_clicked();

    void on_BTN_Adjust_pause_clicked();

    void on_BTN_Adjust_stop_clicked();

    void on_BTN_Adjust_slot_begin_clicked();

    void on_BTN_Adjust_slot_stop_clicked();

    void on_BTN_band_clicked();

    void on_BTN_band_false_clicked();

    void on_BTN_band_ap_clicked();

    void on_BTN_band_false_AP_clicked();

    void on_BTN_save_ap_pram_clicked();

    void on_BTN_Adjust_to_back_clicked();

public:
    QTreeWidgetItem * ap_item;

private:


    QTcpSocket *client_socket;

    MyThread *n1_data_process_thread;

    HandleThread *handle_thread;

public:
    Ui::MainWindow *ui;

    QQueue<char> n1_data_queue;

    QMutex n1_data_lock;   
    QMutex m_count_down_lock;

    int ap_syn_second;
    int m_sec_go;             //一个随着ap同步包一直累加的时间
    int ap_slot_num;
    unsigned short m_ap_id;

    int m_dev_adjust_count;             //每次点击调整按钮 此变量+1
    int m_dev_adjust_slot_flag;             //每次点击调整按钮 此变量+1
    int m_dev_band;               //绑定标志，空闲是0  需要绑定置为1
    struct _n1_device_list n1_device_list;

    N1_DeviceTable *p_n1_device_table;

    int m_count_down;   //倒计时 显示

public:
    int find_no_using_channel(void);     //遍历所有的设备，找到未使用的通道
    void n1_data_process(QByteArray n1_data);  //处理socekt收到的n1的数据
    void get_n1_config_param(void);           //获取设备配置表，在打开配置文件和保存配置文件是调用，更新设备配置表到内存中
    int find_rp_index(unsigned int rp_id);
    int find_sensor_index(unsigned int sensor_id);
    int find_rp_index_zero(unsigned int rp_id);
    int find_sensor_index_zero(unsigned int sensor_id);
    void add_sensor_level(void);         //
    void add_rp_level(void);
    void add_rp_sec(void);
    static int reversebytes_uint32t(int value);
    static int reversebytes_uint16t(int value);

    void dev_param_poll_set();
    void add_rp_own_sensor_count(void);


public slots:
    void socket_set_ap_channel(int channel);
    void socket_get_ap_channel();
    void socket_set_sensor_rp_channel(int id, int channel,int sec);
    void socket_set_sensor_rp_slot(int id, int slot,int sec);
    void socket_get_ap_id();
    void settext_text_rp_list(QString str);
    void settext_text_sensor_list(QString str);
    void settext_text_dev_p1(QString str);
    void settext_text_dev_p2(QString str);
    void socket_band_sensor_rp(int id, int apid,int sec);
    void addtext_text_dev_p3(QString str);
    void socket_band_ap_(unsigned char yes_or_no);
    void socket_save_ap_param(void);
};

#endif // MAINWINDOW_H
