#ifndef DEV_MANAGE_H
#define DEV_MANAGE_H

#include <QMainWindow>
#include "mainwindow.h"

class Dev_Manage : public QObject
{
    Q_OBJECT
public:
    Dev_Manage(MainWindow *p_mw);

public:
    MainWindow *m_p_mw;
    //数据结构
public:
    struct struct_progress_flag{
        int p1;            //表示现在进行到第几级的snesor调整 ， 暂时只支持3级sensor
#define SENSOR_1   1
#define SENSOR_2   2
#define SENSOR_3   3
        int p2_num;        //表示该级别的sensor 一共有几组
        int p2;            //现在调整到第几组
        int p3;            //这个变量仅仅用来表示，当前有没有正在调整的设备，没有就调用找设备的函数
    }m_progress_flag;

    int m_sensor_num;         //选出来的sensor个数
    unsigned int m_sensor_id[64];                    //等待调整的sensor ID
    unsigned int m_sensor_adjust_flag[64];
    int m_rp_num;            //选出来的rp个数
    unsigned int m_father_rp_id[6];                  //sensor的父rp id 可能包含多级 越往后越是靠近AP的RP
    int m_rp_default_channel;  //默认rp通道
    int m_sensor_default_channel;   //默认的sensor通道
    int m_timeout;  //用来标定超时

    int adjust_one_level_rp_times;
    int adjust_one_level_sensor_times;
    int adjust_more_level_rp_times;

    QStringList m_dev_adjust_p_level;

    struct _sensor_slot_id{
        unsigned int sensor_id;
        int slot;
    }sensor_slot_id[128];

    typedef struct {
        unsigned int rp_id;
        int level_1_dev_count;
        int level_2_dev_count;
        int dev_count;
    }rp_list;

    //方法
public:
    int get_sensor_index(int sensor_id);
    int get_rp_index(int rp_id);
    void get_need_set_sensor(void);  //搜寻需要配置的sensor
    void poll(void);
    void adjust_channel(void);
    void auto_adjust_slot(void);
    int find_nearest_sec_sensor(void);
    int find_nearest_sec_rp(int *flag);
    int set_ap_channel(int channel);
    int set_one_leve_rp_channel();
    int check_one_leve_rp_online();
    int set_one_leve_sensor_channel();
    int check_sensor_online();
    void set_sensor_rp_timeout(void);
    int set_rp_channel(int rp_id,int channel);
    int adjust_father_rp_channel();
    QString Dev_Manage::make_string(unsigned int*data,int num);
    void set_count_down(int count_down);
    void flag_adjust_fail_rp(unsigned int rpid);
    int check_sensor_adjust_flag();
    void set_sensor_adjust_flag();
    void clear_sensor_adjust_flag();
    void set_rp_slot(void);
    int find_rp_nouse_slot(int rp_type ,int rp_level);
    void set_sensor_slot(void);
    int get_sensor_canuse_slot(unsigned int sensor_id);
    int judge_slot_if_enough(void);
    static bool compareBarData(const rp_list &barAmount1, const rp_list &barAmount2);
    int find_sec_dev_send_to_ap(void);
    void band_dev(void);
    int check_sensor_timeout();
    int find_nearest_sec_sensor_all(void);
    int set_sensor_channel_to_back();
    void adjust_channel_to_back();


signals:
    void signal_set_ap_channel(int channel);
    void signal_get_ap_channel(void);
    void signal_get_ap_id(void);

    void signal_band_sensor_rp(int id,int apid,int sec);

    void signal_set_sensor_rp_channel(int id,int channel,int sec);
    void signal_set_sensor_rp_slot(int id,int slot,int sec);
    void signal_re_connect_n1();
    void signal_settext_text_rp_list(QString str);
    void signal_settext_text_sensor_list(QString str);
    void signal_settext_text_dev_p1(QString str);
    void signal_settext_text_dev_p2(QString str);
    void signal_addtext_text_dev_p3(QString str);

public slots:



};

#endif // DEV_MANAGE_H
