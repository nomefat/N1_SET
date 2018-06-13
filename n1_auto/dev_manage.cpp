#include "dev_manage.h"
#include "mainwindow.h"
#include <windows.h>
#include <QMessageBox>
#include <QDateTime>
#include "ui_mainwindow.h"
#include <stdio.h>


namespace Ui {
class MainWindow;
}

#pragma execution_character_set("utf-8")

Dev_Manage::Dev_Manage(MainWindow *p_mw)
{
    m_p_mw = p_mw;
    m_progress_flag.p1 = 0;
    m_progress_flag.p2 = 0;
    m_progress_flag.p2_num = 0;
    m_progress_flag.p3 = 0;

    m_rp_default_channel = 9;
    m_sensor_default_channel = 2;

    m_timeout=0;

    QObject::connect ( this, SIGNAL(signal_set_ap_channel(int)),
            p_mw, SLOT(socket_set_ap_channel(int)) );

    QObject::connect ( this, SIGNAL(signal_get_ap_channel()),
            p_mw, SLOT(socket_get_ap_channel()) );

    QObject::connect ( this, SIGNAL(signal_get_ap_id()),
            p_mw, SLOT(socket_get_ap_id()) );

    QObject::connect ( this, SIGNAL(signal_set_sensor_rp_channel(int, int,int)),
            p_mw, SLOT(socket_set_sensor_rp_channel(int, int,int)) );

    QObject::connect ( this, SIGNAL(signal_set_sensor_rp_slot(int, int,int)),
            p_mw, SLOT(socket_set_sensor_rp_slot(int, int,int)) );

    QObject::connect ( this, SIGNAL(signal_re_connect_n1()),
            p_mw, SLOT(on_socket_disconnected()) );

    QObject::connect ( this, SIGNAL(signal_settext_text_rp_list(QString)),
            p_mw, SLOT(settext_text_rp_list(QString )) );
    QObject::connect ( this, SIGNAL(signal_settext_text_sensor_list(QString)),
            p_mw, SLOT(settext_text_sensor_list(QString )) );

    QObject::connect ( this, SIGNAL(signal_settext_text_dev_p1(QString)),
            p_mw, SLOT(settext_text_dev_p1(QString )) );


    QObject::connect ( this, SIGNAL(signal_settext_text_dev_p2(QString)),
            p_mw, SLOT(settext_text_dev_p2(QString )) );

    QObject::connect ( this, SIGNAL(signal_addtext_text_dev_p3(QString)),
            p_mw, SLOT(addtext_text_dev_p3(QString )) );


    QObject::connect ( this, SIGNAL(signal_band_sensor_rp(int, int,int)),
            p_mw, SLOT(socket_band_sensor_rp(int, int,int)) );




    m_dev_adjust_p_level<<"第一步：设置1级RP的通道"<<"第二步：设置1级sensor的通道"<<"第三步：设置2级sensor的通道"<<"第四步：设置3级sensor的通道";

    adjust_one_level_rp_times = 2;
    adjust_one_level_sensor_times = 2;
    adjust_more_level_rp_times = 4;


//     unsigned char ap_slot[] = {33,34,35,36,63,64,65,68,69,70,98,99,100,127};   //APÊ¹ÓÃµÄÊ±¼ä²Û£¬¼ì²âÆ÷ºÍrp²»¿ÉÒÔÊ¹ÓÃ   ¼ÓÉÏ0-6



}


int Dev_Manage::get_sensor_index(int sensor_id)
{
   for(int i=0;i<m_p_mw->n1_device_list.sensor_num_cfg;i++)
   {
       if(sensor_id == m_p_mw->n1_device_list.sensor[i].sensor_id)
           return i;
   }
   return -1;

}

int Dev_Manage::get_rp_index(int rp_id)
{
   for(int i=0;i<m_p_mw->n1_device_list.rp_num_cfg;i++)
   {
       if(rp_id == m_p_mw->n1_device_list.rp[i].rp_id)
           return i;
   }
   return -1;

}




void Dev_Manage::get_need_set_sensor(void)  //搜寻需要配置的sensor
{
    m_sensor_num = 0;
    m_rp_num = 0;
    if(m_progress_flag.p1 == 0)      //1级rp,只有一组
    {
        for(int i=0;i<m_p_mw->n1_device_list.rp_num_cfg;i++)
        {
            if(1 == m_p_mw->n1_device_list.rp[i].level && (m_p_mw->n1_device_list.rp[i].up_channel!=m_p_mw->n1_device_list.rp[i].up_channel_cfg || m_p_mw->n1_device_list.rp[i].down_channel!=m_p_mw->n1_device_list.rp[i].down_channel_cfg))
                m_father_rp_id[m_rp_num++] = m_p_mw->n1_device_list.rp[i].rp_id;
        }
    }
    else if(m_progress_flag.p1 == 1)       //1级sensor,只有一组
    {
        for(int i=0;i<m_p_mw->n1_device_list.sensor_num_cfg;i++)
        {
            if(1 == m_p_mw->n1_device_list.sensor[i].level && m_p_mw->n1_device_list.sensor[i].channel!=m_p_mw->n1_device_list.sensor[i].channel_cfg)
                m_sensor_id[m_sensor_num++] = m_p_mw->n1_device_list.sensor[i].sensor_id;
        }

    }
    else  //找多级sensor
    {
        for(int i=0;i<m_p_mw->n1_device_list.sensor_num_cfg;i++)           //先随机找一个实际通道和配置通道不一样的，以此判断该sensor没有被配置过
        {
            if(m_p_mw->n1_device_list.sensor[i].channel_cfg != m_p_mw->n1_device_list.sensor[i].channel &&  //sensor实际通道和配置通道不同
                    m_p_mw->n1_device_list.sensor[i].level == m_progress_flag.p1 &&                    //级别相符
                    m_rp_num == 0 &&                                  //找到了第一个sensor
                    m_p_mw->n1_device_list.sensor[i].adjust_fail == 0)        //没有调整失败的标志
            {
                m_sensor_id[m_sensor_num++] = m_p_mw->n1_device_list.sensor[i].sensor_id;             //先存这个sensor ，然后找到他的所有父rp
                m_father_rp_id[m_rp_num++] = m_p_mw->n1_device_list.sensor[i].father_id_cfg;         //(m_progress_flag.p1 - 1)级RP
                int i1 = get_rp_index(m_p_mw->n1_device_list.sensor[i].father_id_cfg);
                if(i1>=0 && m_p_mw->n1_device_list.rp[i1].father_id_cfg != -1)
                {
                    m_father_rp_id[m_rp_num++] = m_p_mw->n1_device_list.rp[i1].father_id_cfg;        //(m_progress_flag.p1 - 2)级RP
                    int i2 = get_rp_index(m_p_mw->n1_device_list.rp[i1].father_id_cfg);
                    if(i2>=0 && m_p_mw->n1_device_list.rp[i2].father_id_cfg != -1)
                    {
                        m_father_rp_id[m_rp_num++] = m_p_mw->n1_device_list.rp[i2].father_id_cfg;    //(m_progress_flag.p1 - 3)级RP
                    }
                }
            }
            else if(m_rp_num!=0)          //已经找到了第一个sensor  现在只需要找到和他同一个父rp的其他sensor
            {
                if(m_p_mw->n1_device_list.sensor[i].father_id_cfg == m_father_rp_id[0] && m_p_mw->n1_device_list.sensor[i].channel != m_p_mw->n1_device_list.sensor[i].channel_cfg)
                {
                    m_sensor_id[m_sensor_num++] = m_p_mw->n1_device_list.sensor[i].sensor_id;
                }
            }
        }
    }

}



/*
 * 设置AP通道为指定值，并且读取ap实际通道
 *
 * 设置成功返回 0
 * 设置失败返回 -1
 *
 *
 */
int Dev_Manage::set_ap_channel(int channel)
{
    int timeout = 0;
    m_p_mw->n1_device_list.ap_channel = -1;
    emit signal_set_ap_channel(channel);
    Sleep(10);
    emit signal_get_ap_channel();

    set_sensor_rp_timeout(); //每次更改ap通道的时候都会将所有rp和sensor的超时时间设置成31 默认已经掉线
    while(timeout++<20)
    {
        Sleep(100);
        if(m_p_mw->n1_device_list.ap_channel == channel)
        {
            qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<QString::asprintf("更改AP通道为%d",channel);
            return 0;
        }
    }
    emit signal_re_connect_n1();
    return -1;
}

/*
 * 每次更改AP通道时 把直连得rp和sensor 设置成超时模式
 *
 *
 *
 *
 *
 */
void Dev_Manage::set_sensor_rp_timeout(void)
{

    for(int i=0;i<m_p_mw->n1_device_list.sensor_num_cfg ;i++)
    {
        m_p_mw->n1_device_list.sensor[i].timeout = 31;
    }
    for(int i=0;i<m_p_mw->n1_device_list.rp_num_cfg ;i++)
    {
        m_p_mw->n1_device_list.rp[i].timeout = 31;
    }
}



/*
 * 从已经找出的rp列表中找到与当前秒点最接近的那个
 *
 *
 *
 *
 *
 */
int Dev_Manage::find_nearest_sec_rp(int *flag)
{
    int dev_sec = 0;
    for(int i=0;i<m_rp_num;i++)
    {
        dev_sec = m_p_mw->n1_device_list.rp[get_rp_index(m_father_rp_id[i])].sec_dot-1;
        if(dev_sec<0)
            dev_sec += 30;
        if(dev_sec == m_p_mw->ap_syn_second  && flag[i]==0)  //rp秒点=现在秒点-1 而且这个rp超时小于40 表示上线过
        {
            return i;
        }
    }
    return -1;
}

void Dev_Manage::set_count_down(int count_down)
{
    m_p_mw->m_count_down_lock.lock();

    m_p_mw->m_count_down = count_down;
    m_p_mw->m_count_down_lock.unlock();
}

/*
 * 从已经找出的rp列表中找到与当前秒点最接近的那个
 *
 *
 *
 *
 *
 */
int Dev_Manage::find_nearest_sec_sensor(void)
{
    int dev_sec = 0;
    for(int i=0;i<m_sensor_num;i++)
    {
        dev_sec = m_p_mw->n1_device_list.sensor[get_sensor_index(m_sensor_id[i])].sec_dot-1;
        if(dev_sec<0)
            dev_sec += 30;
        if(dev_sec == m_p_mw->ap_syn_second && m_p_mw->n1_device_list.sensor[get_sensor_index(m_sensor_id[i])].timeout<30)  //sensor秒点=现在秒点-1 而且这个rp超时小于40 表示上线过
        {
            return i;
        }
    }
    return -1;
}


int Dev_Manage::set_one_leve_rp_channel()
{
    int index = 0;

    int rp_level = 1;

    int flag[10];
    int i = 0;

    memset(flag,0,40);


    set_count_down(60);
    m_timeout= m_p_mw->m_sec_go;
    while(1)
    {
        index = find_nearest_sec_rp(flag);  //找到秒点相同 和 没有设置过的rp
        Sleep(100);
        if(index!=-1)
        {
            flag[index] = 1;        //设置过之后 标志为1
            index = get_rp_index(m_father_rp_id[index]);
            if(index%2)
                rp_level = 1;
            else
                rp_level = 3;
            emit signal_set_sensor_rp_channel(m_p_mw->n1_device_list.rp[index].rp_id,m_p_mw->n1_device_list.rp[index].up_channel_cfg | (m_p_mw->n1_device_list.rp[index].down_channel_cfg<<4) | (rp_level<<8),m_p_mw->n1_device_list.rp[index].sec_dot);

            m_p_mw->n1_device_list.rp[index].timeout = 31;
            emit signal_addtext_text_dev_p3(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + QString::asprintf("设置RP%04X channel=%x",m_p_mw->reversebytes_uint16t(m_p_mw->n1_device_list.rp[index].rp_id),m_p_mw->n1_device_list.rp[index].up_channel_cfg | (m_p_mw->n1_device_list.rp[index].down_channel_cfg<<4)));
            qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<QString::asprintf("p1=0调整1级RP,步骤：2,设置rpid=%04X 通道=%x",m_p_mw->n1_device_list.rp[index].rp_id,m_p_mw->n1_device_list.rp[index].up_channel_cfg | (m_p_mw->n1_device_list.rp[index].down_channel_cfg<<4));
            Sleep(1000);
        }

        for(i=0; i<m_rp_num;i++) //判断是不是都设置过了
        {
            if(flag[i]==0)
                break;
        }

        if((m_p_mw->m_sec_go-m_timeout)>60 || i>=m_rp_num || m_p_mw->m_dev_adjust_count != 2)   //超过60秒 或者设置参数次数大于等于需要调整的rp个数后 退出
        {
            set_count_down(0);
            m_timeout = 0;  //用完之后清零
            return 0;
        }

    }
}

void Dev_Manage::set_sensor_adjust_flag()
{
    for(int i=0;i<m_sensor_num;i++)
    {
        m_sensor_adjust_flag[i] = 1;

    }

}

void Dev_Manage::clear_sensor_adjust_flag()
{
    for(int i=0;i<m_sensor_num;i++)
    {
        m_sensor_adjust_flag[i] = 0;

    }

}

int Dev_Manage::check_sensor_adjust_flag()
{
    for(int i=0;i<m_sensor_num;i++)
    {
        if(m_sensor_adjust_flag[i] !=0)
            return -1;
    }
    return 0;
}

int Dev_Manage::set_one_leve_sensor_channel()
{
    int index = 0;
    int time_ = 90;

    if(m_timeout==0)   //函数调用的起始时间，用来标定是否超时
        m_timeout= m_p_mw->m_sec_go;

    index = find_nearest_sec_sensor();  //找到秒点和已经上线的sensor

    if(index!=-1)
    {
        index = get_sensor_index(m_sensor_id[index]);
        emit signal_set_sensor_rp_channel(m_p_mw->n1_device_list.sensor[index].sensor_id,m_p_mw->n1_device_list.sensor[index].channel_cfg,m_p_mw->n1_device_list.sensor[index].sec_dot);
        m_p_mw->n1_device_list.sensor[index].timeout = 31;
        m_sensor_adjust_flag[index] = 0;
        emit signal_addtext_text_dev_p3(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + QString::asprintf("设置Sensor%04X channel=%x",m_p_mw->reversebytes_uint16t(m_p_mw->n1_device_list.sensor[index].sensor_id),m_p_mw->n1_device_list.sensor[index].channel_cfg));
        qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<QString::asprintf("p1=%d调整1级sensor,步骤：2,设置sensor_id=%04X 通道=%x",m_progress_flag.p1,m_p_mw->n1_device_list.sensor[index].sensor_id,m_p_mw->n1_device_list.sensor[index].channel_cfg);
        Sleep(1000);
    }
    else
       Sleep(100);

    if((m_p_mw->m_sec_go-m_timeout)>(m_sensor_num*10>time_ ? (60+m_sensor_num*30) : time_)  )   //超过60秒 或者设置参数次数大于等于需要调整的rp个数后 退出 （此处可能不太严谨）
    {
        clear_sensor_adjust_flag();
        m_timeout = 0;  //用完之后清零
        return 0;
    }
    else if(check_sensor_adjust_flag()==0)
    {
        m_timeout = 0;  //用完之后清零
        return 0;
    }
    else
        return -1;


}

int Dev_Manage::check_one_leve_rp_online()
{

    if(m_timeout==0)   //函数调用的起始时间，用来标定是否超时
        m_timeout= m_p_mw->m_sec_go;


    for(int i=0;i<m_rp_num;i++)
    {
        if(m_p_mw->n1_device_list.rp[get_rp_index(m_father_rp_id[i])].timeout>30)
        {
            if((m_p_mw->m_sec_go-m_timeout)>30)  //30秒之内RP没有上线 认为失败
            {
                m_timeout = 0;  //用完之后清零
                return -2;    //已经失败 没有时间了
            }
            return -1;    //已经失败  还有时间 继续等待
        }
    }
    m_timeout = 0;  //用完之后清零
    return 0;    //成功了
}

QString Dev_Manage::make_string(unsigned int*data,int num)
{
    QString str_data = "";
    for(int i=0;i<num;i++)
    {
        str_data += QString::asprintf("%02X%02X\r\n",data[i]&0xff,(data[i]>>8)&0xff);

    }
    return str_data;
}


/*
 * 用来确认所选出来得sensor是否上线，超时没有全部上线 返回失败 并且会把上线得sensor T出队列
 *
 *
 *
 *
 *
 */
int Dev_Manage::check_sensor_online()
{

   //函数调用的起始时间，用来标定是否超时
    m_timeout= m_p_mw->m_sec_go;
    set_count_down(90);
    while(1)
        {
            for(int i=0;i<m_sensor_num;i++)
            {
                if(m_p_mw->n1_device_list.sensor[get_sensor_index(m_sensor_id[i])].timeout<30 && m_p_mw->n1_device_list.sensor[get_sensor_index(m_sensor_id[i])].channel == m_p_mw->n1_device_list.sensor[get_sensor_index(m_sensor_id[i])].channel_cfg)
                {
                   m_sensor_id[i] = m_sensor_id[m_sensor_num-1];
                   m_sensor_num--;
                   signal_settext_text_sensor_list( make_string(m_sensor_id,m_sensor_num));
                   if(m_sensor_num == 0)
                   {
                       m_timeout = 0;  //用完之后清零
                       return 0;    //成功了
                   }
                }
            }
            Sleep(100);
            if((m_p_mw->m_sec_go-m_timeout)>90 || m_p_mw->m_dev_adjust_count != 2)  //90秒之内RP没有上线 认为失败
            {
                m_timeout = 0;  //用完之后清零
                return -2;    //已经失败 没有时间了
            }

    }
}
/*
 * 设置一次指定id的rp的通道
 *
 *
 *
 *
 *
 */
int Dev_Manage::set_rp_channel(int rp_id,int channel)
{
    int dev_sec;
    dev_sec = m_p_mw->n1_device_list.rp[get_rp_index(rp_id)].sec_dot-1;
    if(dev_sec<0)
        dev_sec += 30;
    int my_timeout= m_p_mw->m_sec_go;
    set_count_down(60);
    while(1)
    {
        if(dev_sec == m_p_mw->ap_syn_second)  //rp秒点=现在秒点-1
        {
            emit signal_set_sensor_rp_channel(rp_id,channel,m_p_mw->n1_device_list.rp[get_rp_index(rp_id)].sec_dot);
            emit signal_addtext_text_dev_p3(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+QString::asprintf("设置RP%04X channel=%x",m_p_mw->reversebytes_uint16t(rp_id),channel));
            qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<QString::asprintf("set rp%04X channel %x",rp_id,channel);
            m_p_mw->n1_device_list.rp[get_rp_index(rp_id)].timeout = 31;
            Sleep(1000);
            m_timeout = 0;
            return 0;
        }
        if(m_p_mw->m_sec_go-my_timeout>60 || m_p_mw->m_dev_adjust_count != 2)  //超时 设置失败  只有m_p_mw->ap_syn_second停止之时才会满足该条件
        {
            my_timeout = 0;
            return -1;
        }
    }
}

/*
 * 用来标记rp设置失败 同时将会标记带的sensor调试失败
 *
 * 此函数只往上找2级RP
 *
 *
 *
 */
void Dev_Manage::flag_adjust_fail_rp(unsigned int rpid)
{

    m_p_mw->n1_device_list.rp[get_rp_index(rpid)].adjust_fail = 1;   //表示自己无法设置
    for(int i=0;i<m_p_mw->n1_device_list.sensor_num_cfg;i++)
    {
        if(m_p_mw->n1_device_list.sensor[i].father_id_cfg == rpid)
        {
            m_p_mw->n1_device_list.sensor[i].adjust_fail = 2;  //表示上级rp 无法设置
        }
        else if(m_p_mw->n1_device_list.rp[get_rp_index(m_p_mw->n1_device_list.sensor[i].father_id_cfg)].father_id_cfg == rpid)
        {
            m_p_mw->n1_device_list.sensor[i].adjust_fail = 3;  //表示上上级rp 无法设置
        }
    }

}



/*
 * 用来调整和确认m_father_rp_id[]中的所有rp都上线
 *
 *
 *
 *
 *
 */
int Dev_Manage::adjust_father_rp_channel()
{
    static int adjust_step = -1;  //用来标定 调整RP进行到那一级了
    static int ajust_timeout = 0;   //调整3次不上线认为失败。
    static int adjust_online_timeout = 0; //能一直上线但是改不了通道的超时计数
    int dead_while = 1;


    if(adjust_step == -1)  //为初始化的值 此时将他置为RP_num-1
        adjust_step = m_rp_num -1;

    if(adjust_step == m_rp_num -1) //此时是修改1级rp 所以需要修改AP的通道
    {
        if(set_ap_channel(m_p_mw->n1_device_list.ap_channel_cfg)==-1) //更改AP通道到配置通道，准备搜索1级RP，因为之前已经调整过1级RP的通道 所以正常次1级RP应该已经在指定通道。
        {
            qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<QString::asprintf("p1=%d调整%d级sensor,步骤：0,调整父RP,调整AP通道=%d,调整失败.",m_progress_flag.p1,m_progress_flag.p1,m_p_mw->n1_device_list.ap_channel_cfg);
            return -1;//更改ap 通道 失败
        }
    }
    m_timeout= m_p_mw->m_sec_go;    //记录起始时间
    set_count_down(60);
    qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<QString::asprintf("p1=%d调整%d级sensor,步骤：0,调整父RP,等待RP%04X上线，最多60秒",m_progress_flag.p1,m_progress_flag.p1,m_father_rp_id[adjust_step]);
    signal_settext_text_dev_p2(QString::asprintf("第%d次：调整父RP,等待RP%04X上线，最多60秒",ajust_timeout+1,m_p_mw->reversebytes_uint16t(m_father_rp_id[adjust_step])));
    while(dead_while)
    {
        if(m_p_mw->n1_device_list.rp[get_rp_index(m_father_rp_id[adjust_step])].timeout<30)
        {
            signal_settext_text_dev_p2(QString::asprintf("第%d次：调整父RP,RP%04X已经上线",ajust_timeout+1,m_p_mw->reversebytes_uint16t(m_father_rp_id[adjust_step])));
            qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<QString::asprintf("p1=%d调整%d级sensor,步骤：0,调整父RP,RPID=%04X已经上线,.",m_progress_flag.p1,m_progress_flag.p1,m_father_rp_id[adjust_step]);
            ajust_timeout = 0;
            break;  //rp在配置的通道 上线 进行下一步。
        }
        Sleep(100);
        if(m_p_mw->m_sec_go-m_timeout > 60 || m_p_mw->m_dev_adjust_count != 2) //超时60秒还没有上线，认为失败。 失败之后AP会去RP默认通道在找一次该RP
        {
            qDebug()<<"60s超时";
            if(adjust_step == m_rp_num -1) //此时是修改1级rp 所以需要修改AP的通道
            {
                signal_settext_text_dev_p2(QString::asprintf("第%d次：RP%04X超时没有上线，修改AP通道为%d",ajust_timeout+1,m_p_mw->reversebytes_uint16t(m_father_rp_id[adjust_step]),m_rp_default_channel));
                if(set_ap_channel(m_rp_default_channel)==-1) //更改AP通道到配置通道，准备搜索1级RP，因为之前已经调整过1级RP的通道 所以正常次1级RP应该已经在指定通道。
                {
                    qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<QString::asprintf("p1=%d调整%d级sensor,步骤：0,调整父RP,调整AP通道=%d,调整失败.",m_progress_flag.p1,m_progress_flag.p1,m_rp_default_channel);

                    return -1;  //更改ap 通道 失败
                }
            }
            else //此时修改的是2级活着2+级的RP 此时需要修改上一级的RP的下行通道
            {
                signal_settext_text_dev_p2(QString::asprintf("第%d次：RP%04X超时没有上线，修改上级RP%04X通道",ajust_timeout+1,m_p_mw->reversebytes_uint16t(m_father_rp_id[adjust_step]),m_p_mw->reversebytes_uint16t(m_father_rp_id[adjust_step+1])));
                set_rp_channel(m_father_rp_id[adjust_step+1],
                        m_p_mw->n1_device_list.rp[get_rp_index(m_father_rp_id[adjust_step+1])].up_channel_cfg |
                        ((m_p_mw->n1_device_list.rp[get_rp_index(m_father_rp_id[adjust_step+1])].down_channel==m_rp_default_channel?
                            m_p_mw->n1_device_list.rp[get_rp_index(m_father_rp_id[adjust_step+1])].down_channel_cfg:
                    m_rp_default_channel)<<4)|(1<<8) ); //设置rp为配置通道 下行为默认sensor通道 这样可以接收

            }
            m_timeout= m_p_mw->m_sec_go;    //记录起始时间
            dead_while = 1;
            signal_settext_text_dev_p2(QString::asprintf("第%d次：等待RPID=%04X上线",ajust_timeout+1,m_p_mw->reversebytes_uint16t(m_father_rp_id[adjust_step])));
            qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<QString::asprintf("p1=%d调整%d级sensor,步骤：0,调整父RP,等待RP%04X上线，最多60秒",m_progress_flag.p1,m_progress_flag.p1,m_father_rp_id[adjust_step]);
            set_count_down(60);
            while(dead_while)
            {
                if(m_p_mw->n1_device_list.rp[get_rp_index(m_father_rp_id[adjust_step])].timeout<30)
                {
                    signal_settext_text_dev_p2(QString::asprintf("第%d次：调整父RP,RPID=%04X已经上线",ajust_timeout+1,m_p_mw->reversebytes_uint16t(m_father_rp_id[adjust_step])));
                    qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<QString::asprintf("p1=%d调整%d级sensor,步骤：0,调整父RP,RPID=%04X已经上线,.",m_progress_flag.p1,m_progress_flag.p1,m_father_rp_id[adjust_step]);
                    if(adjust_step == 0)  //只有1级rp 将rp下行通道改为sensor默认通道
                        set_rp_channel(m_father_rp_id[adjust_step],m_p_mw->n1_device_list.rp[get_rp_index(m_father_rp_id[adjust_step])].up_channel_cfg |(m_sensor_default_channel<<4)|(1<<8) ); //设置rp为配置通道 下行为默认sensor通道 这样可以接收
                    else //下面还有子rp 将rp下行通道改为该rp的配置下行通道
                        set_rp_channel(m_father_rp_id[adjust_step],m_p_mw->n1_device_list.rp[get_rp_index(m_father_rp_id[adjust_step])].up_channel_cfg |(m_p_mw->n1_device_list.rp[get_rp_index(m_father_rp_id[adjust_step])].down_channel_cfg<<4)|(1<<8) ); //设置rp为配置通道 下行为默认rp通道 这样可以接收
                    m_timeout = 0;
                    ajust_timeout = 0;
                    return -1;  //已经找到1级rp 并且改了通道，继续执行循环
                }
                Sleep(100);
                if(m_p_mw->m_sec_go-m_timeout > 60 || m_p_mw->m_dev_adjust_count != 2) //超时60秒还没有上线，认为失败。
                {
                    qDebug()<<"60s超时";
                    signal_settext_text_dev_p2(QString::asprintf("第%d次：调整父RP,RPID=%04X超时没有上线",ajust_timeout+1,m_p_mw->reversebytes_uint16t(m_father_rp_id[adjust_step])));
                    m_timeout = 0;
                    ajust_timeout++;
                    if(ajust_timeout>=adjust_more_level_rp_times)   //3次没有调整成功 标记失败
                    {
                        ajust_timeout = 0;

                        signal_settext_text_dev_p2(QString::asprintf("第%d次：调整父RP,末级RPID=%04X超时没有上线,设置已经失败",ajust_timeout+1,m_p_mw->reversebytes_uint16t(m_father_rp_id[adjust_step])));
                        flag_adjust_fail_rp(m_p_mw->n1_device_list.rp[get_rp_index(m_father_rp_id[adjust_step])].rp_id);
                        return -2;  //设置已经失败 需要重新检索设备
                    }
                    return -1;
                }
            }
        }
    }

//运行到此处 说明1级RP已经上线，接下来配置1级rp的下行通道


    if(adjust_step == 0)  //已经调整到末级RP 需要将该RP的下行通道改为sensor的默认通道
    {
        if(m_p_mw->n1_device_list.rp[get_rp_index(m_father_rp_id[adjust_step])].down_channel == m_sensor_default_channel && m_p_mw->n1_device_list.rp[get_rp_index(m_father_rp_id[adjust_step])].up_channel == m_p_mw->n1_device_list.rp[get_rp_index(m_father_rp_id[adjust_step])].up_channel_cfg)
        {
            signal_settext_text_dev_p2(QString::asprintf("第%d次：调整父RP,末级RPID=%04X已经上线，下行通道为sensor默认通道",ajust_timeout+1,m_p_mw->reversebytes_uint16t(m_father_rp_id[adjust_step])));
            adjust_step--;
            ajust_timeout = 0;
            return 0;   // 假如只有1级rp  配置成功
        }
        else
        {

            dead_while = 1;

            signal_settext_text_dev_p2(QString::asprintf("第%d次：调整父RP,末级RPID=%04X已经上线，正在设置下行通道为sensor默认通道",ajust_timeout+1,m_p_mw->reversebytes_uint16t(m_father_rp_id[adjust_step])));
            qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<QString::asprintf("p1=%d调整%d级sensor,步骤：0,调整父RP,等待RP%04X上线，最多60秒",m_progress_flag.p1,m_progress_flag.p1,m_father_rp_id[adjust_step]);
            set_rp_channel(m_father_rp_id[adjust_step],m_p_mw->n1_device_list.rp[get_rp_index(m_father_rp_id[adjust_step])].up_channel_cfg |(m_sensor_default_channel<<4)|(1<<8) ); //设置rp为配置通道 下行为默认sensor通道 这样可以接收
            m_timeout= m_p_mw->m_sec_go;    //记录起始时间
            set_count_down(60);
            while(dead_while)
            {

                Sleep(100);
                if(m_p_mw->n1_device_list.rp[get_rp_index(m_father_rp_id[adjust_step])].down_channel == m_sensor_default_channel && m_p_mw->n1_device_list.rp[get_rp_index(m_father_rp_id[adjust_step])].up_channel == m_p_mw->n1_device_list.rp[get_rp_index(m_father_rp_id[adjust_step])].up_channel_cfg)
                {
                    m_timeout = 0;
                    signal_settext_text_dev_p2(QString::asprintf("第%d次：调整父RP,末级RPID=%04X已经上线，下行通道为sensor默认通道",ajust_timeout+1,m_p_mw->reversebytes_uint16t(m_father_rp_id[adjust_step])));
                    adjust_step = -1; //该函数已经调整完毕，
                    ajust_timeout = 0;
                    adjust_online_timeout = 0;
                    return 0;   // 假如只有1级rp  配置成功
                }

                if(m_p_mw->m_sec_go-m_timeout > 60 || m_p_mw->m_dev_adjust_count != 2) //超时60秒还没有上线，认为失败。
                {
                    signal_settext_text_dev_p2(QString::asprintf("第%d次：调整父RP,末级RPID=%04X超时没有上线",ajust_timeout+1,m_p_mw->reversebytes_uint16t(m_father_rp_id[adjust_step])));
                    qDebug()<<"60s超时";
                    m_timeout = 0;
                    adjust_online_timeout++;
                    if(adjust_online_timeout>=adjust_more_level_rp_times)   //3次没有调整成功 标记失败
                    {
                        adjust_online_timeout = 0;
                        signal_settext_text_dev_p2(QString::asprintf("第%d次：调整父RP,末级RPID=%04X超时没有上线,设置已经失败",ajust_timeout+1,m_p_mw->reversebytes_uint16t(m_father_rp_id[adjust_step])));
                        flag_adjust_fail_rp(m_p_mw->n1_device_list.rp[get_rp_index(m_father_rp_id[adjust_step])].rp_id);
                        return -2;  //设置已经失败 需要重新检索设备
                    }
                    return -1;                      //调到默认通道 找1级rp失败了 返回
                }
            }
        }
    }
    else
    {
        if(m_p_mw->n1_device_list.rp[get_rp_index(m_father_rp_id[adjust_step])].up_channel_cfg == m_p_mw->n1_device_list.rp[get_rp_index(m_father_rp_id[adjust_step])].up_channel)
        {
            signal_settext_text_dev_p2(QString::asprintf("第%d次：调整父RP,RPID=%04X已经上线，上行通道为配置通道",ajust_timeout+1,m_p_mw->reversebytes_uint16t(m_father_rp_id[adjust_step])));
            adjust_step--;
        }
        else
        {
            signal_settext_text_dev_p2(QString::asprintf("第%d次：调整父RP,RPID=%04X已经上线，正在配置上行通道为配置通道",ajust_timeout+1,m_p_mw->reversebytes_uint16t(m_father_rp_id[adjust_step])));
            set_rp_channel(m_father_rp_id[adjust_step],m_p_mw->n1_device_list.rp[get_rp_index(m_father_rp_id[adjust_step])].up_channel_cfg |(m_rp_default_channel<<4)|(1<<8) ); //设置rp为配置通道 下行为默认rp通道 这样可以接收
        }

        m_timeout = 0;
        return -1;
    }


//运行到此处1级RP下行通道已经配置成功，而且确定有2级RP需要配置
    return -1;


}


void Dev_Manage::poll(void)
{
    static int times = 0;
    if(m_p_mw->m_dev_adjust_count == 2)  //正在设置
    {
        adjust_channel();
        return;
    }
    else if(m_p_mw->m_dev_adjust_count == 1)   //按下停止按钮
    {
        m_p_mw->m_dev_adjust_count = 0;
        m_progress_flag.p1 = 0;
        m_progress_flag.p2 = 0;
        m_progress_flag.p2_num = 0;
        m_progress_flag.p3 = 0;
        m_sensor_num = 0;
        m_rp_num = 0;
        signal_settext_text_dev_p1(" ");
        signal_settext_text_dev_p2(" ");
        signal_addtext_text_dev_p3(" ");
        signal_settext_text_rp_list( make_string(m_father_rp_id,m_rp_num));
        signal_settext_text_sensor_list( make_string(m_sensor_id,m_sensor_num));
        for(int i=0;i<m_p_mw->n1_device_list.sensor_num_cfg;i++)
        {
            m_p_mw->n1_device_list.sensor[i].adjust_fail = 0;

        }
        for(int i=0;i<m_p_mw->n1_device_list.rp_num_cfg;i++)
        {
            m_p_mw->n1_device_list.rp[i].adjust_fail = 0;

        }
        return;
    }
    else if(m_p_mw->m_dev_adjust_count == 3)   //按下回滚按钮，需要清除状态 之后进入 4
    {
        m_p_mw->m_dev_adjust_count = 0;
        m_progress_flag.p1 = 0;
        m_progress_flag.p2 = 0;
        m_progress_flag.p2_num = 0;
        m_progress_flag.p3 = 0;
        m_sensor_num = 0;
        m_rp_num = 0;
        signal_settext_text_dev_p1(" ");
        signal_settext_text_dev_p2(" ");
        signal_addtext_text_dev_p3(" ");
        signal_settext_text_rp_list( make_string(m_father_rp_id,m_rp_num));
        signal_settext_text_sensor_list( make_string(m_sensor_id,m_sensor_num));
        for(int i=0;i<m_p_mw->n1_device_list.sensor_num_cfg;i++)
        {
            m_p_mw->n1_device_list.sensor[i].adjust_fail = 0;

        }
        for(int i=0;i<m_p_mw->n1_device_list.rp_num_cfg;i++)
        {
            m_p_mw->n1_device_list.rp[i].adjust_fail = 0;

        }
        m_p_mw->m_dev_adjust_count = 4;
        return;

    }
    else if(m_p_mw->m_dev_adjust_count == 4)
    {
        adjust_channel_to_back();
    }
    else if(m_p_mw->m_dev_adjust_count == 0) //暂停按钮
    {
        if(m_p_mw->m_dev_adjust_slot_flag == 1)
        {

            if(judge_slot_if_enough()==-1)
            {
                m_p_mw->ui->BTN_Adjust_slot_begin->setChecked(false);
                m_p_mw->ui->BTN_Adjust_slot_stop->setChecked(true);
                m_p_mw->m_dev_adjust_slot_flag = 0;
                return;
            }
            set_rp_slot();
            m_p_mw->m_dev_adjust_slot_flag = 2;
            return;
        }
        else if(m_p_mw->m_dev_adjust_slot_flag == 2)
        {
            auto_adjust_slot();
            return;
        }
        else if(m_p_mw->m_dev_adjust_slot_flag == 0)
        {
            if(m_p_mw->m_dev_band == 1)
            {
                if(m_p_mw->m_ap_id == 0)
                {
                    signal_get_ap_id();
                    signal_settext_text_dev_p1(QString::asprintf("获取APid t=%d",times));
                    Sleep(1000);
                }
                else
                    times = 0;

                band_dev();
                Sleep(1000);

            }




            Sleep(200);
        }




    }



}


void Dev_Manage::adjust_channel(void)
{
    static int adjust_step = 0 ;       //调整需要很多步，每一个级别的sensor或者rp都需要不同的步骤，通过这个变量表示处于那个步骤
    static int timeout = 0;    //调整多次不成功 放弃 次数标志
    static int re_adjust = 0;



    if(m_progress_flag.p3 == 0)  //没有正在调整的设备了，重新寻找设备 ，
    {
        get_need_set_sensor(); //找设备，根据等级往上找
        if(m_sensor_num == 0 && m_rp_num == 0) //没找到对应等级的sensor
        {
            m_progress_flag.p1++;   //升级
            qDebug()<<"dev_manage: sensor级别调整为"<<m_progress_flag.p1<<endl;
            if( m_progress_flag.p1>3)  //最后一级
            {
                m_p_mw->m_dev_adjust_count = 1;
                m_progress_flag.p3 = 2; //调整结束
                qDebug()<<"dev_manage: sensor级别大于3级，调整完毕"<<endl;
            }

        }
        else
        {
          m_progress_flag.p3 = 1;  //已经找到了一族设备。
          adjust_step = 0;    //找到设备之后把步骤清零，开始调整
          timeout = 0;  //把超时次数置零

          signal_settext_text_dev_p1(m_dev_adjust_p_level[m_progress_flag.p1]);
          signal_settext_text_rp_list( make_string(m_father_rp_id,m_rp_num));
          signal_settext_text_sensor_list( make_string(m_sensor_id,m_sensor_num));
          qDebug()<<"dev_manage: 已经找到sensor等级为"<<m_progress_flag.p1<<endl;
          qDebug()<<"dev_manage: sensor列表->";
          for(int i=0;i<m_sensor_num;i++)
          {
               qDebug()<<QString::asprintf("%04X",MainWindow::reversebytes_uint16t(m_sensor_id[i]));
          }
          qDebug()<<"dev_manage: rp列表->";
          for(int i=0;i<m_rp_num;i++)
          {
               qDebug()<<QString::asprintf("%04X",MainWindow::reversebytes_uint16t(m_father_rp_id[i]));
          }

        }

    }
    else if(m_progress_flag.p3 == 1) //正在调整设备的通道
    {
        if(m_sensor_num == 0 && m_rp_num != 0 && m_progress_flag.p1 == 0) //这是一组一级RP，排位是0级，由于全放在了rp数组中所以需要特殊调整，正常这个rp数组存放的是一串rp
        {
            int ret = 0;

            switch(adjust_step)
            {
                case 0:
                    signal_settext_text_dev_p2(QString::asprintf("第%d次：正在设置AP的通道为%d",timeout+1,m_rp_default_channel));
                    if(set_ap_channel(m_rp_default_channel)==0){
                        adjust_step++;                       
                        qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<
                                  QString::asprintf("p1=0调整1级RP,步骤：0->1,调整AP通道=%d，即将调整所选的RP通道，最多等待60秒.",m_rp_default_channel);

                    }
                    break;
                case 1:
                    signal_settext_text_dev_p2(QString::asprintf("第%d次：正在设置1级RP的通道",timeout+1));
                    Sleep(5000);
                    if(set_one_leve_rp_channel()==0)
                    {
                        adjust_step++;
                        qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<
                                  QString::asprintf("p1=0调整1级RP,步骤：1->2,已经设置过RP的通道，即将调回AP通道.");
                    }
                        break;
                case 2:
                    signal_settext_text_dev_p2(QString::asprintf("第%d次：正在设置AP的通道为%d",timeout+1,m_p_mw->n1_device_list.ap_channel_cfg));
                    if(set_ap_channel(m_p_mw->n1_device_list.ap_channel_cfg)==0){
                        adjust_step++;
                        qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<
                                  QString::asprintf("p1=0调整1级RP,步骤：2->3,已经将AP通道调回到%d,即将检查1级RP是否全部上线，最多等待30秒",m_p_mw->n1_device_list.ap_channel_cfg);
                        signal_settext_text_dev_p2(QString::asprintf("第%d次：正在check1级RP是否上线",timeout+1));
                        set_count_down(30);
                    }
                break;
                case 3:

                    ret = check_one_leve_rp_online();
                    if(ret==0) //成功了 晋级
                    {
                        adjust_step++;
                        qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<
                                  QString::asprintf("p1=0调整1级RP,步骤：3->4,1级RP已经全部上线，调整完成.");
                        signal_settext_text_dev_p2(QString::asprintf("第%d次：1级RP已经全部上线，调整完成",timeout+1));
                    }
                    else if(ret==-1)
                    {
                        Sleep(100);
                    }
                    else if(ret==-2)
                    {
                        adjust_step = 0;
                        timeout++;
                        if(timeout>=adjust_one_level_rp_times)  //已经调整了2次了 还是没有成功，进行下一步。
                        {
                            timeout = 0;
                            if(m_progress_flag.p1<1)
                                m_progress_flag.p1++;
                            qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<
                                      QString::asprintf("p1=0调整1级RP,步骤：3，已经超时1级RP并没有全部上线，2次之后放弃该验证");
                            signal_settext_text_dev_p2(QString::asprintf("第%d次：1级RP没有全部上线，放弃调整",timeout+1));
                            m_progress_flag.p3 = 0;   //置零 调整完毕 继续查找下一级需要调整的设备
                            break;
                        }
                        signal_settext_text_dev_p2(QString::asprintf("第%d次：1级RP没有全部上线，重新调整",timeout+1));
                        qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<
                                  QString::asprintf("p1=0调整1级RP,步骤：3->0，已经超时1级RP并没有全部上线，重新调整");
                    }
                break;
                case 4:
                    adjust_step = 0;
                    timeout = 0;
                    m_progress_flag.p3 = 0;  //置零 调整完毕 继续查找下一级需要调整的设备
                    if(m_progress_flag.p1<1)
                        m_progress_flag.p1++;
                    qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<
                              QString::asprintf("p1=0调整1级RP,步骤：4,所有rp已经调整成功");
                break;
            default:break;
            }
        }
        else if(m_sensor_num != 0 && m_rp_num == 0 && m_progress_flag.p1 == 1) //1级sensor 只有sensor 没有rp
        {
            int ret = 0;

            switch(adjust_step)
            {
                case 0:
                    signal_settext_text_dev_p2(QString::asprintf("第%d次：设置AP通道为%d",timeout+1,m_sensor_default_channel));
                    if(set_ap_channel(m_sensor_default_channel)==0){
                        adjust_step++;
                        set_sensor_adjust_flag();
                        qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<
                                  QString::asprintf("p1=1调整1级sensor,步骤：0->1,调整AP通道=%d，即将调整所选的sensor通道，最少等待%d秒.",m_sensor_default_channel,m_sensor_num*20);
                        signal_settext_text_dev_p2(QString::asprintf("第%d次：设置1级sensor通道",timeout+1));
                        set_count_down(m_sensor_num*10>90 ? (60+m_sensor_num*30) : 90);
                    }
                    break;
                case 1:

                    if(set_one_leve_sensor_channel()==0)
                    {
                        adjust_step++;
                        qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<
                                  QString::asprintf("p1=1调整1级sensor,步骤：1->2,已经调整完成sensor的通道，即将调回AP通道.");
                    }
                        break;
                case 2:
                    signal_settext_text_dev_p2(QString::asprintf("第%d次：设置AP通道为%d",timeout+1,m_p_mw->n1_device_list.ap_channel_cfg));
                    if(set_ap_channel(m_p_mw->n1_device_list.ap_channel_cfg)==0){
                        adjust_step++;
                        qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<
                                  QString::asprintf("p1=1调整1级sensor,步骤：2->3,已经将AP通道调回到%d,即将检查1级sensor是否全部上线，最多等待90秒",m_p_mw->n1_device_list.ap_channel_cfg);
                        signal_settext_text_dev_p2(QString::asprintf("第%d次：正在等待sensor上线",timeout+1));
                    }
                break;
                case 3:
                    ret = check_sensor_online();
                    if(ret==0) //成功了 晋级
                    {
                        adjust_step = 0;
                        timeout = 0;
                        m_progress_flag.p3 = 0;  //置零 调整完毕 继续查找下一级需要调整的设备
                        if(m_progress_flag.p1<2)
                            m_progress_flag.p1++;
                        qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<
                                  QString::asprintf("p1=1调整1级sensor,步骤：3,所有sensor已经调整成功");
                        signal_settext_text_dev_p2(QString::asprintf("第%d次：sensor已经全部上线",timeout+1));
                    }
                    else if(ret==-1)
                    {

                    }
                    else if(ret==-2)
                    {
                        adjust_step = 0;
                        set_sensor_adjust_flag();
                        timeout++;
                        if(timeout>=adjust_one_level_sensor_times)  //已经调整了3次了 还是没有成功，进行下一步。
                        {
                            for(int i=0;i<m_sensor_num;i++)   //标记设置失败
                            {
                                m_p_mw->n1_device_list.sensor[get_sensor_index(m_sensor_id[i])].adjust_fail = 1;
                            }
                            timeout = 0;
                            if(m_progress_flag.p1<2)
                                m_progress_flag.p1++;
                            qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<
                                      QString::asprintf("p1=1调整1级sensor,步骤：3，已经超时1级sensor并没有全部上线，3次之后放弃该验证");
                            signal_settext_text_dev_p2(QString::asprintf("第%d次：sensor没有全部上线，超过次数放弃设置",timeout+1));
                            m_progress_flag.p3 = 0;   //置零 调整完毕 继续查找下一级需要调整的设备
                            break;
                        }
                        signal_settext_text_dev_p2(QString::asprintf("第%d次：sensor没有全部上线",timeout+1));
                        qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<
                                  QString::asprintf("p1=1调整1级sensor,步骤：3->0，已经超时1级sensor并没有全部上线，重新调整");
                    }
                break;
            default:break;
            }


        }
        else if(m_sensor_num != 0 && m_rp_num != 0 && m_progress_flag.p1 > 1) //大于或等于2级sensor 有之少一个rp
        {
            int ret = 0;

            switch(adjust_step)
            {
                case 0:
                    ret = adjust_father_rp_channel();
                    if(ret==0)  //把多级RP找到并设置为指定的通道，末级RP的下行通道设置为sensor的默认通道
                    {
                        qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<
                                  QString::asprintf("p1=%d调整%d级sensor,步骤：0,调整%d个rp通道完成",m_progress_flag.p1,m_progress_flag.p1,m_rp_num);
                        signal_settext_text_dev_p2(QString::asprintf("第%d次：正在设置sensor通道",timeout+1));
                        adjust_step++;
                        set_sensor_adjust_flag();
                        set_count_down(m_sensor_num*10>90 ? (60+m_sensor_num*30) : 90);
                    }
                    else if(ret == -2)
                    {
                        m_progress_flag.p3 = 0;   //置零 调整完毕 继续查找下一级需要调整的设备
                        m_sensor_num = 0 ;
                        m_rp_num = 0;
                    }
                break;
                case 1:
                    if(set_one_leve_sensor_channel()==0)  //设置sensor到指定通道
                    {
                        //把rp的通道调回指定通道 方便下一级check sensor是否更改成功
                        signal_settext_text_dev_p2(QString::asprintf("第%d次：已经设置完成sensor通道，更改RP%04X下行通道为配置通道，正在确认sensor是否全部上线",timeout+1,m_p_mw->reversebytes_uint16t(m_p_mw->n1_device_list.rp[get_rp_index(m_father_rp_id[0])].rp_id)));
                        set_rp_channel(m_father_rp_id[0],m_p_mw->n1_device_list.rp[get_rp_index(m_father_rp_id[0])].up_channel_cfg |(m_p_mw->n1_device_list.rp[get_rp_index(m_father_rp_id[0])].down_channel_cfg<<4)|(1<<8) ); //设置rp为配置通道 下行为默认rp通道 这样可以接收
                        qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<
                                  QString::asprintf("p1=%d调整%d级sensor,步骤：1,调整%d个sensor通道完成",m_progress_flag.p1,m_progress_flag.p1,m_sensor_num);
                        adjust_step++;
                    }
                break;
                case 2:
                    if(check_sensor_online()==0)
                    {
                        signal_settext_text_dev_p2(QString::asprintf("第%d次：sensor已经全部上线",timeout+1,m_p_mw->reversebytes_uint16t(m_p_mw->n1_device_list.rp[get_rp_index(m_father_rp_id[0])].rp_id)));
                        qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<
                                  QString::asprintf("p1=%d调整%d级sensor,步骤：1,%d个sensor已经调整完成",m_progress_flag.p1,m_progress_flag.p1,m_sensor_num);
                        adjust_step = 0;
                        m_progress_flag.p3 = 0;
                        m_sensor_num = 0;
                        m_rp_num = 0;
                    }
                    else
                    {
                        timeout++;

                        if(timeout>=adjust_one_level_sensor_times)  //已经调整了3次了 还是没有成功，进行下一步。
                        {
                            adjust_step = 0;
                            for(int i=0;i<m_sensor_num;i++)   //标记设置失败
                            {
                                m_p_mw->n1_device_list.sensor[get_sensor_index(m_sensor_id[i])].adjust_fail = 1;
                            }
                            timeout = 0;
                            m_progress_flag.p3 = 0;//置零 调整完毕 继续查找下一级需要调整的设备
                            m_sensor_num = 0;
                            m_rp_num = 0;
                            signal_settext_text_dev_p2(QString::asprintf("第%d次：sensor没有全部上线，超过次数放弃设置",timeout+1));
                            qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<
                                      QString::asprintf("p1=%d调整%d级sensor,步骤：3，已经超时sensor并没有全部上线，%d次之后放弃该验证",m_progress_flag.p1,m_progress_flag.p1,adjust_one_level_sensor_times);

                            break;
                        }
                        set_sensor_adjust_flag();
                        set_rp_channel(m_father_rp_id[0],m_p_mw->n1_device_list.rp[get_rp_index(m_father_rp_id[0])].up_channel_cfg |(m_sensor_default_channel<<4)|(1<<8) ); //设置rp为配置通道 下行为默认rp通道 这样可以接收
                        signal_settext_text_dev_p2(QString::asprintf("第%d次：sensor没有全部上线，设置RP%0X4下行通道为sensor默认通道",timeout+1,m_p_mw->reversebytes_uint16t(m_p_mw->n1_device_list.rp[get_rp_index(m_father_rp_id[0])].rp_id)));
                        qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<
                                  QString::asprintf("p1=%d调整%d级sensor,步骤：1,还剩下%d个sensor没有调整完成",m_progress_flag.p1,m_progress_flag.p1,m_sensor_num);
                        adjust_step--;

                    }
                break;

            }
        }
    }

}

//判断过rp的时间槽是否够用  不够用做出提示，等用户决定是否继续
int Dev_Manage::judge_slot_if_enough(void)
{
    int level_1_sensor_count = 0;
    int level_2_sensor_count = 0;

    for(int i=0;i<m_p_mw->n1_device_list.rp_num_cfg;i++)
    {
        if(m_p_mw->n1_device_list.rp[i].level == 1)
        {
            level_1_sensor_count += m_p_mw->n1_device_list.rp[i].own_sensor_num[0];
            level_2_sensor_count += m_p_mw->n1_device_list.rp[i].own_sensor_num[1];
        }

    }
    if((level_1_sensor_count+level_2_sensor_count) > ((m_p_mw->ap_slot_num>>4)+1)*20)
    {
        QMessageBox::StandardButton rb = QMessageBox::information(NULL, QString( "警告" ) , QString( "RP时间槽不足，是否退出" ) ,QMessageBox::Yes | QMessageBox::No);
        if(rb == QMessageBox::Yes)
            return -1;

    }

    if((level_2_sensor_count) > ((m_p_mw->ap_slot_num>>4)+1)*12)
    {
        QMessageBox::StandardButton rb = QMessageBox::information(NULL, QString( "警告" ) , QString( "RP时间槽不足，是否退出" ) ,QMessageBox::Yes | QMessageBox::No);
        if(rb == QMessageBox::Yes)
            return -1;

    }
    return 0;
}

bool Dev_Manage::compareBarData(const rp_list &barAmount1, const rp_list &barAmount2)
{
    return barAmount1.dev_count>=barAmount2.dev_count ? true : false;
}

void Dev_Manage::set_rp_slot(void)
{

    struct {
        int level_1_slot_count;
        int level_2_slot_count;
        int all_count;
    }already_set_slot[2];

    QList<rp_list> level_1_rp_list;
    rp_list rplist;
    int level_1_count;

    already_set_slot[0].level_1_slot_count = 0;
    already_set_slot[0].level_2_slot_count = 0;
    already_set_slot[0].all_count = 0;
    already_set_slot[1].level_1_slot_count = 0;
    already_set_slot[1].level_2_slot_count = 0;
    already_set_slot[1].all_count = 0;

    int slot_flag = (m_p_mw->ap_slot_num>>4)+1;
    int level_1_slot_count = 10;   //1级rp下有10个时间槽
    int level_2_slot_count = 6;    //2级rp下有6个时间槽
    int slot;



    for(int i=0;i<m_p_mw->n1_device_list.rp_num_cfg;i++)
    {
        if(m_p_mw->n1_device_list.rp[i].level == 1)  //只管1级rp
        {
            rplist.level_1_dev_count = m_p_mw->n1_device_list.rp[i].own_sensor_num[0];
            rplist.level_2_dev_count = m_p_mw->n1_device_list.rp[i].own_sensor_num[1];
            rplist.dev_count = rplist.level_1_dev_count+rplist.level_2_dev_count;
            rplist.rp_id = m_p_mw->n1_device_list.rp[i].rp_id;
            level_1_rp_list.append(rplist);

        }
    }

    qSort(level_1_rp_list.begin(),level_1_rp_list.end(),compareBarData);

    level_1_count = level_1_rp_list.count();
    level_1_count--;

    m_p_mw->n1_device_list.rp[get_rp_index(level_1_rp_list[0].rp_id)].rp_type_cfg = 1;

    already_set_slot[0].level_1_slot_count = level_1_rp_list[0].level_1_dev_count;
    already_set_slot[0].level_2_slot_count = level_1_rp_list[0].level_2_dev_count;
    already_set_slot[0].all_count = level_1_rp_list[0].dev_count;

    while(1)
    {
        if(level_1_rp_list[level_1_count].level_1_dev_count<(level_1_slot_count*slot_flag-already_set_slot[0].level_1_slot_count)
                && level_1_rp_list[level_1_count].level_2_dev_count<(level_2_slot_count*slot_flag-already_set_slot[0].level_2_slot_count)
                && level_1_rp_list[level_1_count].dev_count < (level_1_slot_count*slot_flag - already_set_slot[0].all_count))
        {
            m_p_mw->n1_device_list.rp[get_rp_index(level_1_rp_list[level_1_count].rp_id)].rp_type_cfg = 1;
            already_set_slot[0].level_1_slot_count += level_1_rp_list[level_1_count].level_1_dev_count;
            already_set_slot[0].level_2_slot_count += level_1_rp_list[level_1_count].level_2_dev_count;
            already_set_slot[0].all_count += level_1_rp_list[level_1_count].dev_count;
            level_1_count--;
        }
        else
            break;
    }

    for(int i=1;i<=level_1_count;i++)
    {
        m_p_mw->n1_device_list.rp[get_rp_index(level_1_rp_list[i].rp_id)].rp_type_cfg = 3;
    }

    for(int i=0;i<m_p_mw->n1_device_list.rp_num_cfg;i++)
    {
        if(m_p_mw->n1_device_list.rp[i].level == 2)
        {
            m_p_mw->n1_device_list.rp[i].rp_type_cfg = m_p_mw->n1_device_list.rp[get_rp_index(m_p_mw->n1_device_list.rp[i].father_id_cfg)].rp_type_cfg;

        }

    }

    for(int i=0;i<m_p_mw->n1_device_list.rp_num_cfg;i++)
    {
        if(m_p_mw->n1_device_list.rp[i].level == 3)
        {
            m_p_mw->n1_device_list.rp[i].rp_type_cfg = m_p_mw->n1_device_list.rp[get_rp_index(m_p_mw->n1_device_list.rp[i].father_id_cfg)].rp_type_cfg;

        }

    }

    for(int i=0;i<m_p_mw->n1_device_list.rp_num_cfg;i++)
    {
        slot = find_rp_nouse_slot(m_p_mw->n1_device_list.rp[i].rp_type_cfg,m_p_mw->n1_device_list.rp[i].level);
        if(slot != -1)
            m_p_mw->n1_device_list.rp[i].set_slot = slot;

    }

}




int Dev_Manage::find_rp_nouse_slot(int rp_type ,int rp_level)
{
    unsigned char rp_0_slot[] = {14,18,22,26,30,44,48,52,56,60,78,82,86,90,94,108,112,116,120,124};   //    rpºÍËù´ø¼ì²âÆ÷¿ÉÓÃÊ±¼ä²Û...
    unsigned char rp_1_slot[] = {16,20,24,28,32,46,50,54,58,62,80,84,88,92,96,110,114,118,122,126}; //10*2

    unsigned char rprp_0_slot[] = {22,26,30,52,56,60,86,90,94,116,120,124};
    unsigned char rprp_1_slot[] = {24,28,32,54,58,62,88,92,96,118,122,126}; //6*2

    int slot_flag = (m_p_mw->ap_slot_num>>4)+1;
    int level_1_slot_count = 10*slot_flag;   //1级rp下有10个时间槽
    int level_2_slot_count = 6*slot_flag;    //2级rp下有6个时间槽

    int j = 0;

    if(rp_type == 1)
    {
        if(rp_level == 1)
        {
            for(int i=0;i<level_1_slot_count;i++)
            {
                for(j=0;j<m_p_mw->n1_device_list.rp_num_cfg;j++)
                {

                    if(rp_0_slot[i] == m_p_mw->n1_device_list.rp[j].set_slot)
                        break;
                }
                if(j>=m_p_mw->n1_device_list.rp_num_cfg)
                    return rp_0_slot[i];

            }
            return -1;

        }
        else if(rp_level == 2)
        {
            for(int i=0;i<level_2_slot_count;i++)
            {
                for(j=0;j<m_p_mw->n1_device_list.rp_num_cfg;j++)
                {

                    if(rprp_0_slot[i] == m_p_mw->n1_device_list.rp[j].set_slot)
                        break;
                }
                if(j>=m_p_mw->n1_device_list.rp_num_cfg)
                    return rprp_0_slot[i];

            }
            return -1;
        }

    }
    else if(rp_type == 3)
    {
        if(rp_level == 1)
        {
            for(int i=0;i<level_1_slot_count;i++)
            {
                for(j=0;j<m_p_mw->n1_device_list.rp_num_cfg;j++)
                {

                    if(rp_1_slot[i] == m_p_mw->n1_device_list.rp[j].set_slot)
                        break;
                }
                if(j>=m_p_mw->n1_device_list.rp_num_cfg)
                    return rp_1_slot[i];

            }
            return -1;

        }
        else if(rp_level == 2)
        {
            for(int i=0;i<level_2_slot_count;i++)
            {
                for(j=0;j<m_p_mw->n1_device_list.rp_num_cfg;j++)
                {

                    if(rprp_1_slot[i] == m_p_mw->n1_device_list.rp[j].set_slot)
                        break;
                }
                if(j>=m_p_mw->n1_device_list.rp_num_cfg)
                    return rprp_1_slot[i];

            }
            return -1;
        }

    }
    return -1;
}


void Dev_Manage::set_sensor_slot(void)
{
    int sensor_slot = 0;
    int index = 0;
    int canuse_slot = 0;
    unsigned int sensor_id = 0;

    for(int i=0;i<m_p_mw->n1_device_list.sensor_num_cfg;i++)
    {
        if(m_p_mw->n1_device_list.sensor[i].set_slot == 0)     //如果有设置时间槽，按设置时间槽算，如果没有按实际时间槽算（sensor超时小于30）
        {
            if(m_p_mw->n1_device_list.sensor[i].timeout<30)
                sensor_slot =m_p_mw->n1_device_list.sensor[i].slot;
            else
                continue;
        }
        else
        {
            sensor_slot =m_p_mw->n1_device_list.sensor[i].set_slot;
        }

        if(sensor_slot_id[sensor_slot].sensor_id == 0)  //该时间槽没有被占用
        {
            sensor_slot_id[sensor_slot].sensor_id = m_p_mw->n1_device_list.sensor[i].sensor_id;
            continue;
        }
        else if(sensor_slot_id[sensor_slot].sensor_id != m_p_mw->n1_device_list.sensor[i].sensor_id)
        {
            sensor_id = sensor_slot_id[sensor_slot].sensor_id;
            index = get_sensor_index(sensor_slot_id[sensor_slot].sensor_id);
            // 已经占据时间槽的sensor 级别小于新来的sensor，新来的放进去 老的提出来，更改这个老的senor的时间槽
            if(m_p_mw->n1_device_list.sensor[index].level<m_p_mw->n1_device_list.sensor[i].level)
            {
                sensor_slot_id[sensor_slot].sensor_id = m_p_mw->n1_device_list.sensor[i].sensor_id;
                canuse_slot = get_sensor_canuse_slot(sensor_id);
                if(canuse_slot != -1)
                    m_p_mw->n1_device_list.sensor[i].set_slot = canuse_slot;
            }
            else
            {
                canuse_slot = get_sensor_canuse_slot(m_p_mw->n1_device_list.sensor[i].sensor_id);
                if(canuse_slot != -1)
                    m_p_mw->n1_device_list.sensor[i].set_slot = canuse_slot;
            }
        }
    }
}

int Dev_Manage::get_sensor_canuse_slot(unsigned int sensor_id)
{
    int index = 0;
    int rp_index = 0;
    int i,j;
    unsigned char ap_slot[] = {33,34,35,36,63,64,65,68,69,70,98,99,100,127};
    unsigned char rp_0_slot[] = {14,18,22,26,30,44,48,52,56,60,78,82,86,90,94,108,112,116,120,124};   //    rpºÍËù´ø¼ì²âÆ÷¿ÉÓÃÊ±¼ä²Û...
    unsigned char rp_1_slot[] = {16,20,24,28,32,46,50,54,58,62,80,84,88,92,96,110,114,118,122,126}; //10*2

    unsigned char rprp_0_slot[] = {22,26,30,52,56,60,86,90,94,116,120,124};
    unsigned char rprp_1_slot[] = {24,28,32,54,58,62,88,92,96,118,122,126}; //6*2

    int slot_flag = (m_p_mw->ap_slot_num>>4)+1;


    index = get_sensor_index(sensor_id);


    if(m_p_mw->n1_device_list.sensor[index].level == 1)
    {
        for(i=7;i<64*slot_flag;i++)
        {
            for(j=0;j<sizeof(ap_slot);j++)
            {
                if(i == ap_slot[j])
                    break;
            }
            if(j<sizeof(ap_slot))
                continue;

            for(j=0;j<m_p_mw->n1_device_list.rp_num_cfg;j++)
            {
                if(i == m_p_mw->n1_device_list.rp[j].set_slot)
                    break;
            }
            if(j<m_p_mw->n1_device_list.rp_num_cfg)
                continue;

            for(j=0;j<m_p_mw->n1_device_list.sensor_num_cfg;j++)
            {
                if(m_p_mw->n1_device_list.sensor[j].set_slot!=0){
                    if(i == m_p_mw->n1_device_list.sensor[j].set_slot)
                        break;
                }
                else
                {
                    if(i == m_p_mw->n1_device_list.sensor[j].slot)
                        break;
                }
            }
            if(j<m_p_mw->n1_device_list.sensor_num_cfg)
                continue;
            else
                return i;
        }
        return -1;

    }
    else if(m_p_mw->n1_device_list.sensor[index].level == 2)
    {
        rp_index = get_rp_index(m_p_mw->n1_device_list.sensor[index].father_id_cfg);
        if(m_p_mw->n1_device_list.rp[rp_index].rp_type_cfg == 1)
        {
            for(i=0;i<10*slot_flag;i++)
            {
                for(j=0;j<m_p_mw->n1_device_list.rp_num_cfg;j++)
                {
                    if(rp_0_slot[i] == m_p_mw->n1_device_list.rp[j].set_slot)
                        break;
                }
                if(j<m_p_mw->n1_device_list.rp_num_cfg)
                    continue;

                for(j=0;j<m_p_mw->n1_device_list.sensor_num_cfg;j++)
                {
                    if(m_p_mw->n1_device_list.sensor[j].set_slot!=0 && m_p_mw->n1_device_list.sensor[j].level >=2){
                        if(rp_0_slot[i] == m_p_mw->n1_device_list.sensor[j].set_slot)
                            break;
                    }
                    else  if(m_p_mw->n1_device_list.sensor[j].set_slot == 0 && m_p_mw->n1_device_list.sensor[j].level >=2)
                    {
                        if(rp_0_slot[i] == m_p_mw->n1_device_list.sensor[j].slot)
                            break;
                    }
                }
                if(j<m_p_mw->n1_device_list.sensor_num_cfg)
                    continue;
                else
                    return rp_0_slot[i];
            }
            return -1;
        }
        else if(m_p_mw->n1_device_list.rp[rp_index].rp_type_cfg == 3)
        {
            for(i=0;i<10*slot_flag;i++)
            {
                for(j=0;j<m_p_mw->n1_device_list.rp_num_cfg;j++)
                {
                    if(rp_1_slot[i] == m_p_mw->n1_device_list.rp[j].set_slot)
                        break;
                }
                if(j<m_p_mw->n1_device_list.rp_num_cfg)
                    continue;

                for(j=0;j<m_p_mw->n1_device_list.sensor_num_cfg;j++)
                {
                    if(m_p_mw->n1_device_list.sensor[j].set_slot!=0 && m_p_mw->n1_device_list.sensor[j].level >=2){
                        if(rp_1_slot[i] == m_p_mw->n1_device_list.sensor[j].set_slot)
                            break;
                    }
                    else  if(m_p_mw->n1_device_list.sensor[j].set_slot == 0 && m_p_mw->n1_device_list.sensor[j].level >=2)
                    {
                        if(rp_1_slot[i] == m_p_mw->n1_device_list.sensor[j].slot)
                            break;
                    }
                }
                if(j<m_p_mw->n1_device_list.sensor_num_cfg)
                    continue;
                else
                    return rp_1_slot[i];
            }
            return -1;
        }

    }
    else if(m_p_mw->n1_device_list.sensor[index].level == 3)
    {
        rp_index = get_rp_index(m_p_mw->n1_device_list.sensor[index].father_id_cfg);
        if(m_p_mw->n1_device_list.rp[rp_index].rp_type_cfg == 1)
        {
            for(i=0;i<6*slot_flag;i++)
            {
                for(j=0;j<m_p_mw->n1_device_list.rp_num_cfg;j++)
                {
                    if(rprp_0_slot[i] == m_p_mw->n1_device_list.rp[j].set_slot)
                        break;
                }
                if(j<m_p_mw->n1_device_list.rp_num_cfg)
                    continue;

                for(j=0;j<m_p_mw->n1_device_list.sensor_num_cfg;j++)
                {
                    if(m_p_mw->n1_device_list.sensor[j].set_slot!=0 && m_p_mw->n1_device_list.sensor[j].level >=3){
                        if(rprp_0_slot[i] == m_p_mw->n1_device_list.sensor[j].set_slot)
                            break;
                    }
                    else  if(m_p_mw->n1_device_list.sensor[j].set_slot == 0 && m_p_mw->n1_device_list.sensor[j].level >=3)
                    {
                        if(rprp_0_slot[i] == m_p_mw->n1_device_list.sensor[j].slot)
                            break;
                    }
                }
                if(j<m_p_mw->n1_device_list.sensor_num_cfg)
                    continue;
                else
                    return rprp_0_slot[i];
            }
            return -1;
        }
        else if(m_p_mw->n1_device_list.rp[rp_index].rp_type_cfg == 3)
        {
            for(i=0;i<6*slot_flag;i++)
            {
                for(j=0;j<m_p_mw->n1_device_list.rp_num_cfg;j++)
                {
                    if(rprp_1_slot[i] == m_p_mw->n1_device_list.rp[j].set_slot)
                        break;
                }
                if(j<m_p_mw->n1_device_list.rp_num_cfg)
                    continue;

                for(j=0;j<m_p_mw->n1_device_list.sensor_num_cfg;j++)
                {
                    if(m_p_mw->n1_device_list.sensor[j].set_slot!=0 && m_p_mw->n1_device_list.sensor[j].level >=3){
                        if(rprp_1_slot[i] == m_p_mw->n1_device_list.sensor[j].set_slot)
                            break;
                    }
                    else  if(m_p_mw->n1_device_list.sensor[j].set_slot == 0 && m_p_mw->n1_device_list.sensor[j].level >=3)
                    {
                        if(rprp_1_slot[i] == m_p_mw->n1_device_list.sensor[j].slot)
                            break;
                    }
                }
                if(j<m_p_mw->n1_device_list.sensor_num_cfg)
                    continue;
                else
                    return rprp_1_slot[i];
            }
            return -1;
        }

    }
    return -1;
}

int Dev_Manage::find_sec_dev_send_to_ap(void)
{
    int i;
    int ap_sec_pre = 0;

    ap_sec_pre = m_p_mw->ap_syn_second+1;
    if(ap_sec_pre>29)
        ap_sec_pre = 0;
    for(i=0;i<m_p_mw->n1_device_list.rp_num_cfg;i++)
    {
        if(m_p_mw->n1_device_list.rp[i].sec_dot == ap_sec_pre &&
                m_p_mw->n1_device_list.rp[i].rp_type_cfg != m_p_mw->n1_device_list.rp[i].rp_type)
        {
            emit signal_set_sensor_rp_channel(m_p_mw->n1_device_list.rp[i].rp_id,m_p_mw->n1_device_list.rp[i].up_channel_cfg | (m_p_mw->n1_device_list.rp[i].down_channel_cfg<<4) | (m_p_mw->n1_device_list.rp[i].rp_type_cfg<<8),m_p_mw->n1_device_list.rp[i].sec_dot);
            signal_settext_text_dev_p2(QString::asprintf("设置RP%04X 分组=%d",m_p_mw->reversebytes_uint16t(m_p_mw->n1_device_list.rp[i].rp_id),m_p_mw->n1_device_list.rp[i].rp_type_cfg));
            return 0;
        }
        else if(m_p_mw->n1_device_list.rp[i].sec_dot == ap_sec_pre &&
                m_p_mw->n1_device_list.rp[i].set_slot!=m_p_mw->n1_device_list.rp[i].slot &&
                m_p_mw->n1_device_list.rp[i].set_slot!=0)
        {
            emit signal_set_sensor_rp_slot(m_p_mw->n1_device_list.rp[i].rp_id,m_p_mw->n1_device_list.rp[i].set_slot,m_p_mw->n1_device_list.rp[i].sec_dot);
            signal_settext_text_dev_p2(QString::asprintf("设置RP%04X slot=%d",m_p_mw->n1_device_list.rp[i].rp_id,m_p_mw->n1_device_list.rp[i].set_slot));
            return 0;
        }
    }

    for(i=0;i<m_p_mw->n1_device_list.sensor_num_cfg;i++)
    {
        if(m_p_mw->n1_device_list.sensor[i].sec_dot == ap_sec_pre &&
                        m_p_mw->n1_device_list.sensor[i].set_slot!=m_p_mw->n1_device_list.sensor[i].slot &&
                        m_p_mw->n1_device_list.sensor[i].set_slot!=0)
                {
                    emit signal_set_sensor_rp_slot(m_p_mw->n1_device_list.sensor[i].sensor_id,m_p_mw->n1_device_list.sensor[i].set_slot,m_p_mw->n1_device_list.sensor[i].sec_dot);
                    emit signal_settext_text_dev_p2(QString::asprintf("设置Sensor%04X slot=%d",m_p_mw->reversebytes_uint16t(m_p_mw->n1_device_list.sensor[i].sensor_id),m_p_mw->n1_device_list.sensor[i].set_slot));
                    return 0;
                }
    }
    return -1;
}

void Dev_Manage::auto_adjust_slot(void)
{
    static int time_count;
    set_sensor_slot();
    if(find_sec_dev_send_to_ap()==0)
        time_count = 0;
    else
        time_count++;
    Sleep(1000);
    if(time_count > 31)
    {
        time_count = 0;
        m_p_mw->m_dev_adjust_slot_flag = 0;
        m_p_mw->ui->BTN_Adjust_slot_begin->setChecked(false);
        m_p_mw->ui->BTN_Adjust_slot_stop->setChecked(true);
        QMessageBox::information(NULL, QString( "通知" ).toUtf8() , QString( "时间槽调整完毕" ).toUtf8() );
    }

}


void Dev_Manage::band_dev(void)
{
    int i;
    int ap_sec_pre = 0;

    ap_sec_pre = m_p_mw->ap_syn_second+1;
    if(ap_sec_pre>29)
        ap_sec_pre = 0;

    for(i=0;i<m_p_mw->n1_device_list.sensor_num_cfg;i++)
    {
        if(m_p_mw->n1_device_list.sensor[i].uiBindId != (m_p_mw->m_ap_id & 0x0fff) &&
                m_p_mw->n1_device_list.sensor[i].sec_dot == ap_sec_pre &&
                m_p_mw->n1_device_list.sensor[i].timeout < 30)
        {
            signal_band_sensor_rp(m_p_mw->n1_device_list.sensor[i].sensor_id,m_p_mw->m_ap_id,m_p_mw->n1_device_list.sensor[i].sec_dot);
            signal_settext_text_dev_p2(QString::asprintf("绑定Sensor%04X %d",m_p_mw->reversebytes_uint16t(m_p_mw->n1_device_list.sensor[i].sensor_id),i));
            return;
        }

        if(m_p_mw->n1_device_list.rp[i].uiBindId != (m_p_mw->m_ap_id & 0x0fff)  &&
                m_p_mw->n1_device_list.rp[i].sec_dot == ap_sec_pre &&
                m_p_mw->n1_device_list.rp[i].timeout < 30)
        {
            signal_band_sensor_rp(m_p_mw->n1_device_list.rp[i].rp_id,m_p_mw->m_ap_id,m_p_mw->n1_device_list.rp[i].sec_dot);
            signal_settext_text_dev_p2(QString::asprintf("绑定Sensor%04X %d",m_p_mw->reversebytes_uint16t(m_p_mw->n1_device_list.rp[i].rp_id),i));
            return;
        }



    }

}

int Dev_Manage::check_sensor_timeout()
{
    for(int i=0;i<m_p_mw->n1_device_list.sensor_num_cfg;i++)
    {
        if(m_p_mw->n1_device_list.sensor[i].timeout < 31)
            return -1;
    }
    return 0;
}

int Dev_Manage::find_nearest_sec_sensor_all(void)
{
    int dev_sec = 0;
    for(int i=0;i<m_p_mw->n1_device_list.sensor_num_cfg;i++)
    {
        dev_sec = m_p_mw->n1_device_list.sensor[i].sec_dot-1;
        if(dev_sec<0)
            dev_sec += 30;
        if(dev_sec == m_p_mw->ap_syn_second && m_p_mw->n1_device_list.sensor[i].timeout<30)  //sensor秒点=现在秒点-1 而且这个rp超时小于40 表示上线过
        {
            return i;
        }
    }
    return -1;
}

int Dev_Manage::set_sensor_channel_to_back()
{
    int index = 0;
    int time_ = 90;

    if(m_timeout==0)   //函数调用的起始时间，用来标定是否超时
        m_timeout= m_p_mw->m_sec_go;

    index = find_nearest_sec_sensor_all();  //找到秒点和已经上线的sensor

    if(index!=-1)
    {

        emit signal_set_sensor_rp_channel(m_p_mw->n1_device_list.sensor[index].sensor_id,m_sensor_default_channel,m_p_mw->n1_device_list.sensor[index].sec_dot);
        m_p_mw->n1_device_list.sensor[index].timeout = 31;

        emit signal_addtext_text_dev_p3(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + QString::asprintf("设置Sensor%04X channel=%x",m_p_mw->reversebytes_uint16t(m_p_mw->n1_device_list.sensor[index].sensor_id),m_p_mw->n1_device_list.sensor[index].channel_cfg));
        qDebug()<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<QString::asprintf("p1=%d调整1级sensor,步骤：2,设置sensor_id=%04X 通道=%x",m_progress_flag.p1,m_p_mw->n1_device_list.sensor[index].sensor_id,m_p_mw->n1_device_list.sensor[index].channel_cfg);
        Sleep(1000);
    }
    else
       Sleep(100);

    if((m_p_mw->m_sec_go-m_timeout)>(m_sensor_num*10>time_ ? (60+m_sensor_num*30) : time_)  )   //超过60秒 或者设置参数次数大于等于需要调整的rp个数后 退出 （此处可能不太严谨）
    {

        m_timeout = 0;  //用完之后清零
        return 0;
    }
    else if(check_sensor_timeout()==0)
    {
        m_timeout = 0;  //用完之后清零
        return 0;
    }
    else
        return -1;


}

void Dev_Manage::adjust_channel_to_back()
{
    static int step = 0;

    switch(step)
    {
        case 0 :
            if(set_sensor_channel_to_back() == 0)
                step++;
        break;
        case 1:
            m_p_mw->m_dev_adjust_count = 0;
        break;

    }



}



























