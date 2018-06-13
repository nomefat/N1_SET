#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QLineEdit>
#include <QInputDialog>
#include <QFileDialog>
#include <QHostAddress>
#include "QThread"
#include "dev_manage.h"
#include <windows.h>



#pragma execution_character_set("utf-8")

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    client_socket = new QTcpSocket(this);
    client_socket->connect(client_socket,SIGNAL(connected()),this,SLOT(on_socket_connected()));
    client_socket->connect(client_socket,SIGNAL(disconnected()),this,SLOT(on_socket_disconnected()));
    client_socket->connect(client_socket,SIGNAL(readyRead()),this,SLOT(on_socket_receive()));

    m_dev_adjust_count = 0;

    n1_data_process_thread = new MyThread(this);
    n1_data_process_thread->start();

    handle_thread = new HandleThread(this);
    handle_thread->start();

    memset(&n1_device_list,0,sizeof(n1_device_list));

    p_n1_device_table = new N1_DeviceTable(this);

    ap_slot_num = 5;

    m_count_down = 0;

    m_dev_adjust_count = 0;
    m_dev_adjust_slot_flag = 0;
    m_dev_band = 0;

    m_ap_id = 0;

}

MainWindow::~MainWindow()
{
    delete ui;
    n1_data_process_thread->stoped = false;
}


/*
 * 函数功能：槽函数，响应修改RP/Sensor的按钮
 *
 *
 *
 *
 *
 */
void MainWindow::on_BTN_MODIFY_clicked()
{
    QTreeWidgetItem *current_item = ui->treeWidget->currentItem();
    if(current_item == Q_NULLPTR)
    {
        QMessageBox::information(NULL, QString( "错误" ) , QString( "必须选定一个要修改的设备！" ) );
        return;
    }
    bool isOK;
    QString text = QInputDialog::getText(NULL,QString("输入"),QString("输入修改参数"),QLineEdit::Normal,current_item->text(0)+":"+current_item->text(1)+":"+current_item->text(2),&isOK);
//    if(text.length() <9)
//    {
//        QMessageBox::information(NULL, QString( "错误" ) , QString( "设备前缀加设备ID必须为6位！" ) );
//        return;
//    }
    QStringList para = text.split(':');
    if(isOK){
        current_item->setText(0,para[0]);
        current_item->setText(1,para[1]);
        current_item->setText(2,para[2]);
    }
}

/*
 * 函数功能：槽函数，响应添加AP的按钮
 *
 *
 *
 *
 *
 */
void MainWindow::on_BTN_ADD_AP_clicked()
{
    if(ui->treeWidget->topLevelItemCount()>0)
    {
        QMessageBox::information(NULL, QString( "警告" ).toUtf8() , QString( "AP只能添加一个！" ).toUtf8() );
        return;
    }
    ap_item = new QTreeWidgetItem(ui->treeWidget);
    ap_item->setText(0,tr("AP"));
    ap_item->setData(2,Qt::EditRole,2);

    ui->treeWidget->addTopLevelItem(ap_item);
    qDebug()<<"ddd";
}

/*
 * 函数功能：槽函数，响应添加RP的按钮
 *
 *
 *
 *
 *
 */
void MainWindow::on_BTN_ADD_RP_clicked()
{
    QTreeWidgetItem *current_item = ui->treeWidget->currentItem();
    if(current_item == Q_NULLPTR)
    {
        QMessageBox::information(NULL, QString( "警告" ) , QString( "必须选定一个上级设备！" ) );
        return;
    }
    if(current_item->text(0)[0] == 'S')
    {
        QMessageBox::information(NULL, QString( "错误" ) , QString( "RP的上级设备必须是AP或者RP！" ) );
        return;
    }
    bool isOK;
    QString text = QInputDialog::getText(NULL,QString("输入"),QString("输入 rp id"),QLineEdit::Normal,QString("RPID"),&isOK);
    if(text.length() !=4)
    {
        QMessageBox::information(NULL, QString( "错误" ) , QString( "设备ID必须为4位！" ) );
        return;
    }
    if(isOK){
        QTreeWidgetItem *child_item = new QTreeWidgetItem(current_item);
        text = "RP" + text;
        child_item->setText(0,text);
        child_item->setData(1,Qt::EditRole,current_item->text(2).toInt());
        child_item->setData(2,Qt::EditRole,find_no_using_channel());
    }

}

/*
 * 函数功能：槽函数，响应添加检测器的按钮
 *
 *
 *
 *
 *
 */
void MainWindow::on_BTN_ADD_Sensor_clicked()
{
    QTreeWidgetItem *current_item = ui->treeWidget->currentItem();
    if(current_item == Q_NULLPTR)
    {
        QMessageBox::information(NULL, QString( "警告" ) , QString( "必须选定一个上级设备！" ) );
        return;
    }
    if(current_item->text(0)[0] == 'S')
    {
        QMessageBox::information(NULL, QString( "错误" ) , QString( "检测器的上级设备必须是AP或者RP！" ) );
        return;
    }
    bool isOK;
    QString text = QInputDialog::getText(NULL,QString("输入"),QString("输入 Sensor id"),QLineEdit::Normal,QString("S_ID"),&isOK);
    if(text.length() !=4)
    {
        QMessageBox::information(NULL, QString( "错误" ) , QString( "设备ID必须为4位！" ) );
        return;
    }
    if(isOK){
        QTreeWidgetItem *child_item = new QTreeWidgetItem(current_item);
        text = "S_" + text;
        child_item->setText(0,text);
        child_item->setData(1,Qt::EditRole,current_item->text(2).toInt());
    }

}
/*
 * 函数功能：槽函数，响应删除检测器的按钮
 *
 *
 *
 *
 *
 */
void MainWindow::on_BTN_DEL_clicked()
{
    QTreeWidgetItem *current_item = ui->treeWidget->currentItem();
    if(current_item == Q_NULLPTR)
    {
        QMessageBox::information(NULL, QString( "警告" ) , QString( "必须选定一个设备！" ) );
        return;
    }
    if(current_item->parent() == Q_NULLPTR)
        ui->treeWidget->clear();
    else
        current_item->parent()->removeChild(current_item);
}

/*
 * 函数功能：遍历treewidget 找到可用的通道
 *
 *
 *
 *
 *
 */
int MainWindow::find_no_using_channel()
{
    QTreeWidgetItemIterator it(ui->treeWidget);
    int channel_array[32];
    memset(channel_array,0,32);
    channel_array[0] = channel_array[1] = 1;
    QString c = 0;
    while(*it)
    {
        c = (*it)->text(2);
        qDebug()<<c.toInt();
        channel_array[c.toInt()] = 1;
        ++it;
    }
    for(int i=0;i<16;i++)                //暂时只从2-15中找寻
    {
        if(channel_array[i] == 0)
            return i;
    }
    return 1;  // 没有可用通道 暂时定为1通道
}
/*
 * 函数功能：槽函数，响应存储配置参数的按钮
 *
 *
 *
 *
 *
 */
void MainWindow::on_saveconfig_clicked()
{
    QTreeWidgetItemIterator it(ui->treeWidget);
    QDir dir;
    QString path = dir.currentPath();
    QString fileName = QFileDialog::getSaveFileName(this,
          tr("保存配置文件"), path, tr("config Files ( *.cfg)"));
    if(fileName.isEmpty())
        return;
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&file);

    QString c = 0;

    while(*it)
    {
        if((*it)->parent() != Q_NULLPTR)
            c = (*it)->parent()->text(0);
        else
            c = "NULL";
        out << c <<","<< (*it)->text(0)<<","<< (*it)->text(1)<<","<< (*it)->text(2)<<"\n";
        ++it;
    }
    file.close();
    QMessageBox::information(this,tr("提示"),tr("保存成功"),QMessageBox::Ok);
    get_n1_config_param();
}
/*
 * 函数功能：槽函数，响应加载配置参数的按钮
 *
 *
 *
 *
 *
 */
void MainWindow::on_openconfig_clicked()
{
    QTreeWidgetItemIterator it(ui->treeWidget);
    QDir dir;
    QString path = dir.currentPath();
    QString fileName = QFileDialog::getOpenFileName(this,
          tr("保存配置文件"), path, tr("config Files ( *.cfg)"));
    if(fileName.isEmpty())
        return;
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    QString dev_list[100];
    int i = 0;
    while(!in.atEnd())
    {
        dev_list[i++] = in.readLine();
    }
    if(i == 0)
        return;
    QString father,me,p1,p2;
    QStringList ql;
    int j = 0,length = i;

    ui->treeWidget->clear();
    while(1)
    {
        if(!dev_list[j].isEmpty())
        {
            ql = dev_list[j].split(QRegExp(","));
            j++;
            if(j>=length)
                j = 0;
            if(ql[0]=="NULL")
            {
                ap_item = new QTreeWidgetItem(ui->treeWidget);
                ap_item->setText(0,ql[1]);
                ap_item->setText(1,ql[2]);
                ap_item->setText(2,ql[3]);
                i--;
            }
            else
            {
                QTreeWidgetItemIterator it(ui->treeWidget);
                while(*it)
                {
                    if((*it)->text(0) == ql[0])
                    {
                        QTreeWidgetItem *child_item = new QTreeWidgetItem(*it);
                        child_item->setText(0,ql[1]);
                        child_item->setText(1,ql[2]);
                        child_item->setText(2,ql[3]);
                        i--;
                        break;
                    }
                    ++it;
                }

            }
        }
        if(i<=0)
            break;
    }
    get_n1_config_param();
}
/*
 * 函数功能：槽函数，响应网络连接按钮
 *
 *
 *
 *
 *
 */
void MainWindow::on_BTN_Connect_clicked()
{
    client_socket->abort();
    QString str_ip = ui->lineEdit_ip->text();
    if(str_ip.isEmpty()){
        QMessageBox::information(NULL, QString( "警告" ) , QString( "ip地址格式错误！" ) );
        return;
    }
    client_socket->connectToHost(QHostAddress(str_ip),20000);
}
/*
 * 函数功能：槽函数，响应网络连接成功
 *
 *
 *
 *
 *
 */
void MainWindow::on_socket_connected()
{
    ui->BTN_Connect->setText(tr("已连接"));
    char n1_connect_cmd[] = {0xca,1,3};

    client_socket->write(n1_connect_cmd,3);


}

/*
 * 函数功能：槽函数，响应网络断开连接
 *
 *
 *
 *
 *
 */
void MainWindow::on_socket_disconnected()
{
    ui->BTN_Connect->setText(tr("连接"));
    Sleep(200);
    on_BTN_Connect_clicked();

}

void MainWindow::on_socket_receive()
{
    n1_data_lock.lock();
    QByteArray data = client_socket->readAll();

    for(int i=0;i<data.length();i++){
        n1_data_queue.enqueue(data[i]);
    }
    n1_data_lock.unlock();
}


void MainWindow::socket_set_ap_channel(int channel)
{
    char n1_connect_cmd[] = {0xfe,0x1c,0x0f,0xff,0,0xad,1,0,1,1,0,0,1,0x0e,0};
    n1_connect_cmd[14] = channel;
    client_socket->write(n1_connect_cmd,15);

}

void MainWindow::socket_band_ap_(unsigned char yes_or_no)
{
    char n1_connect_cmd[] = {0xfe,0x1c,0x0f,0xff,0,0xad,1,0,1,1,0,24,1,0x0e,0};
    n1_connect_cmd[14] = yes_or_no;
    client_socket->write(n1_connect_cmd,15);

}

void MainWindow::socket_set_sensor_rp_channel(int id, int channel,int sec)
{
    char n1_connect_cmd[] = {0xfe,0x0c,0x0e,0xff,0,0x34,1,0,0x2,0x27,0,0x16,0x12,0x00};
    channel = (channel<<4)|6;
    n1_connect_cmd[8] = id;
    n1_connect_cmd[9] = id>>8;
    n1_connect_cmd[10] = channel>>8;
    n1_connect_cmd[11] = channel;
    n1_connect_cmd[12] = sec;
    client_socket->write(n1_connect_cmd,14);

}


void MainWindow::socket_set_sensor_rp_slot(int id, int slot,int sec)
{
    char n1_connect_cmd[] = {0xfe,0x0c,0x0e,0xff,0,0x34,1,0,0x2,0x27,0,0x16,0x12,0x00};
    slot = (slot<<4)|5;
    n1_connect_cmd[8] = id;
    n1_connect_cmd[9] = id>>8;
    n1_connect_cmd[10] = slot>>8;
    n1_connect_cmd[11] = slot;
    n1_connect_cmd[12] = sec;
    client_socket->write(n1_connect_cmd,14);

}

void MainWindow::socket_band_sensor_rp(int id, int apid,int sec)
{
    char n1_connect_cmd[] = {0xfe,0x0c,0x0e,0xff,0,0x34,1,0,0x2,0x27,0,0x16,0x12,0x00};
    apid = (apid<<4)|10;
    n1_connect_cmd[8] = id;
    n1_connect_cmd[9] = id>>8;
    n1_connect_cmd[10] = apid>>8;
    n1_connect_cmd[11] = apid;
    n1_connect_cmd[12] = sec;
    client_socket->write(n1_connect_cmd,14);

}

void MainWindow::socket_save_ap_param(void)
{
    char n1_connect_cmd[] = {0xfe,0x12,0x0e,0xff,0,0x34,1,0,0x2,0x27,0,0x16,0x12,0x00};
    client_socket->write(n1_connect_cmd,14);

}

void MainWindow::socket_get_ap_channel()
{
    char n1_connect_cmd[] = {0xfe,0x1c,0x0f,0xff,0,0x8F,1,0,1,0,0,0,1,0x0e,0};
    client_socket->write(n1_connect_cmd,15);

}


void MainWindow::socket_get_ap_id()
{
    char n1_connect_cmd[] = {0xfe,0x1c,0x0f,0xff,0,0x8F,1,0,1,0,0,5,1,0x0e,0};
    client_socket->write(n1_connect_cmd,15);

}







/*
 *
 * 处理N1转发上来的数据
 *
 *
 *
 *
 *
 *
 *
 */
void MainWindow::n1_data_process(QByteArray n1_data)
{
    static int f = 999;
    SNP_PHR_t *p_head = (SNP_PHR_t *)(n1_data.data()+17);
    int index = -1;

    SNP_SYNC_PACKET_t *p_syn_packet = (SNP_SYNC_PACKET_t *)(n1_data.data()+17);
    SNP_STATE_PACKET_t *p_stat_packet = (SNP_STATE_PACKET_t *)(n1_data.data()+17);
    SNP_SEN_MODE_B_PACKET_t *p_event_packet = (SNP_SEN_MODE_B_PACKET_t *)(n1_data.data()+17);
    SNNDATA_MESSAGE * p_n1_head = (SNNDATA_MESSAGE *)(n1_data.data());
    enum Excep
    {
    EXCEP_ONE,
    EXCEP_TWO
    };

    if(n1_data.data()[1] == 0x04)
    {
        if(p_head->uiType == SNP_PACKET_TYPE_SYNC)    //同步包
        {
            if(m_dev_adjust_count == 2)
            {
                m_count_down_lock.lock();
                if(m_count_down>0)
                {
                    m_count_down--;
                    Sleep(1);
                    ui->lcdNumber_count_down->display(m_count_down);
                }
                else
                    ui->lcdNumber_count_down->display(m_count_down);
                m_count_down_lock.unlock();
                m_sec_go++;

            }

            try
            {
                ui->lcdNumber_Synpacket_number->display(p_syn_packet->ucCurSecNr);

                ap_syn_second = p_syn_packet->ucCurSecNr;
            }
            catch(Excep exc)
            {
                ap_syn_second++;
                if(ap_syn_second>=30)
                    ap_syn_second = 0;
            }



            ap_slot_num = p_syn_packet->SystemParameter[0];
            ui->LED_SendInterval->display(((ap_slot_num>>4)+1)*0.125);


        }
        else if(p_head->uiType == SNP_PACKET_TYPE_STATE)//状态包
        {

            if(p_stat_packet->ucCfgComb == 0x07 || p_stat_packet->uiSubType == 0Xc8)  //RP
            {
                index = find_rp_index(p_stat_packet->sPhr.uiDevId);
                if(index == -1) //没有事先配置好的rp 不予添加
                    return;
                n1_device_list.rp[index].rp_id = p_stat_packet->sPhr.uiDevId;
                n1_device_list.rp[index].father_id = p_stat_packet->uiRpId;
                n1_device_list.rp[index].up_channel = p_stat_packet->uiChannel & 0x0f;
                n1_device_list.rp[index].down_channel = (p_stat_packet->uiChannel >> 4) & 0x0f;
                n1_device_list.rp[index].rp_type = (p_stat_packet->uiChannel>>8)&0x03;
                n1_device_list.rp[index].slot = ((((p_n1_head->sTime &0xff00) >> 8) | ((p_n1_head->sTime &0x00ff) << 8))/64)%(64*((ap_slot_num>>4)+1));
//                n1_device_list.rp[index].sec_dot = ((p_stat_packet->ulFactoryId & 0XFF)  + ((p_stat_packet->ulFactoryId>>8) & 0XFF) + ((p_stat_packet->ulFactoryId>>16) & 0XFF) + ((p_stat_packet->ulFactoryId>>24) & 0XFF)+0x199)%30;
                n1_device_list.rp[index].uiBindId = p_stat_packet->uiBindId;
                n1_device_list.rp[index].timeout = 0;
                n1_device_list.rp[index].rssi = n1_data[15]-46;
            }
            else //if(p_stat_packet->ucCfgComb == 0x03 || p_stat_packet->ucCfgComb == 8 || p_stat_packet->ucCfgComb == 0) //Sensor
            {
                index = find_sensor_index(p_stat_packet->sPhr.uiDevId);
                if(index == -1) //没有事先配置好的sensor 不予添加
                    return;
                n1_device_list.sensor[index].sensor_id = p_stat_packet->sPhr.uiDevId;
                n1_device_list.sensor[index].father_id = p_stat_packet->uiRpId;
                n1_device_list.sensor[index].channel = p_stat_packet->uiChannel & 0x0f;
                n1_device_list.sensor[index].slot =((((p_n1_head->sTime &0xff00) >> 8) | ((p_n1_head->sTime &0x00ff) << 8))/64)%(64*((ap_slot_num>>4)+1));
                n1_device_list.sensor[index].sec_dot = ((p_stat_packet->ulFactoryId & 0XFF)  + ((p_stat_packet->ulFactoryId>>8) & 0XFF) + ((p_stat_packet->ulFactoryId>>16) & 0XFF) + ((p_stat_packet->ulFactoryId>>24) & 0XFF)+0x19b)%30;
                n1_device_list.sensor[index].uiBindId = p_stat_packet->uiBindId;
                n1_device_list.sensor[index].timeout = 0;
                n1_device_list.sensor[index].rssi = n1_data[15]-46;
            }
        }
        else if(p_head->uiType>=0x64 && p_head->uiType<=0x79)
        {
            index = find_sensor_index(p_event_packet->sPhr.uiDevId);
            if(index == -1) //没有事先配置好的sensor 不予添加
                return;
            n1_device_list.sensor[index].sensor_id = p_event_packet->sPhr.uiDevId;
            n1_device_list.sensor[index].slot = ((((p_n1_head->sTime &0xff00) >> 8) | ((p_n1_head->sTime &0x00ff) << 8))/64)%(64*((ap_slot_num>>4)+1));
            n1_device_list.sensor[index].timeout = 0;
            n1_device_list.sensor[index].rssi = n1_data[15]-46;
//            n1_device_list.sensor[index].sec_dot = ((p_event_packet->sPhr.uiDevId & 0XFF)  + (p_event_packet->sPhr.uiDevId>>8 & 0XFF)+0x19b)%30;
        }
    }
    else if(n1_data.data()[11] == 0x0 && n1_data.data()[9] == 0x0)
    {
        n1_device_list.ap_channel = n1_data[14];
        ui->LED_Channel->display(n1_device_list.ap_channel);

    }
    else if(n1_data.data()[11] == 0x05)
    {

        m_ap_id = (n1_data.data()[20]<<8) | n1_data.data()[21];
    }

}


int MainWindow::find_rp_index_zero(unsigned int rp_id)
{
    int index = 0,null_index = -1;
    for(index;index<RP_MUX_NUM;index++)
    {
        if(null_index == -1 && n1_device_list.rp[index].rp_id == 0)
        {
            n1_device_list.rp_num_cfg++;
            return index;
        }

    }
    return null_index;

}

int MainWindow::find_rp_index(unsigned int rp_id)
{
    int index = 0,null_index = -1;
    for(index;index<RP_MUX_NUM;index++)
    {
        if(null_index == -1 && n1_device_list.rp[index].rp_id == 0)
            null_index = -1;
        if(n1_device_list.rp[index].rp_id == rp_id)
            return index;
    }

    return null_index;

}

/*
 *
 *
 *
 *
 *
 *
 */
int MainWindow::find_sensor_index_zero(unsigned int sensor_id)
{
    int index = 0,null_index = -1;
    for(index;index<Sensor_MUX_NUM;index++)
    {
        if(null_index == -1 && n1_device_list.sensor[index].sensor_id == 0)
        {
            null_index = index;
            n1_device_list.sensor_num_cfg++;
            return null_index;
        }
    }
    return null_index;


}

/*
 *
 *
 *
 *
 *
 *
 */
int MainWindow::find_sensor_index(unsigned int sensor_id)
{
    int index = 0,null_index = -1;
    for(index;index<Sensor_MUX_NUM;index++)
    {
        if(null_index == -1 && n1_device_list.sensor[index].sensor_id == 0)
            null_index = -1;
        if(n1_device_list.sensor[index].sensor_id == sensor_id)
        {
            n1_device_list.sensor_num_rcv++;
            return index;
        }
    }

    return null_index;


}

/*
 * 获取设备配置表，在打开配置文件和保存配置文件是调用，更新设备配置表到内存中
 *
 *
 *
 *
 *
 */
void MainWindow::get_n1_config_param()
{
    int index = -1;
    QTreeWidgetItemIterator it(ui->treeWidget);
    memset(&n1_device_list,0,sizeof(struct _n1_device_list));

    while(*it)
    {
        qDebug()<<(*it)->text(1);
        if((*it)->text(0) == "AP"){
            n1_device_list.ap_channel_cfg = (*it)->text(2).toInt();
        }
        else if((*it)->text(0)[0] == 'R')
            {
                index = find_rp_index_zero((*it)->text(0).right(4).toInt());
                if(index == -1)
                    return;
                n1_device_list.rp[index].rp_id = reversebytes_uint16t((*it)->text(0).right(4).toInt(nullptr,16));
                if((*it)->parent()->text(0) == "AP")
                    n1_device_list.rp[index].father_id_cfg = -1;
                else
                    n1_device_list.rp[index].father_id_cfg = reversebytes_uint16t((*it)->parent()->text(0).right(4).toInt(nullptr,16));
                n1_device_list.rp[index].up_channel_cfg = (*it)->text(1).toInt();
                n1_device_list.rp[index].down_channel_cfg = (*it)->text(2).toInt();
                n1_device_list.rp[index].timeout = 31;

            }
        else if((*it)->text(0)[0] == 'S')
            {
                index = find_sensor_index_zero((*it)->text(0).right(4).toInt());
                if(index == -1)
                    return;
                n1_device_list.sensor[index].sensor_id = reversebytes_uint16t((*it)->text(0).right(4).toInt(nullptr,16));
                if((*it)->parent()->text(0) == "AP")
                    n1_device_list.sensor[index].father_id_cfg = -1;
                else
                    n1_device_list.sensor[index].father_id_cfg = reversebytes_uint16t((*it)->parent()->text(0).right(4).toInt(nullptr,16));
                n1_device_list.sensor[index].channel_cfg = (*it)->text(1).toInt();
                n1_device_list.sensor[index].timeout = 31;
            }
        ++it;

    }
    add_rp_level();
    add_rp_own_sensor_count();
    add_sensor_level();
    add_rp_sec();
}


void MainWindow::dev_param_poll_set()
{
    static int i=0;
    QThread::msleep(1000);
    qDebug()<<i++;


}

void MainWindow::add_rp_level(void)
{
    int index = 0;
    int i1,i2;
    for(index;index<n1_device_list.rp_num_cfg;index++)
    {
        if(n1_device_list.rp[index].father_id_cfg == -1)        //父RP==0
            n1_device_list.rp[index].level = 1;
        else
        {
            i1 = find_rp_index(n1_device_list.rp[index].father_id_cfg);
            if(i1>=0)
            {
                if(n1_device_list.rp[i1].father_id_cfg == -1)    //父RP==0
                    n1_device_list.rp[index].level = 2;
                else
                {
                    i2 = find_rp_index(n1_device_list.rp[i1].father_id_cfg);
                    if(i2>=0)
                    {
                        if(n1_device_list.rp[i2].father_id_cfg == -1)    //父RP==0
                            n1_device_list.rp[index].level = 3;
                    }
                }
            }
        }
    }

}

void MainWindow::add_rp_sec(void)
{
    for(int index=0;index<n1_device_list.rp_num_cfg;index++)
    {
        n1_device_list.rp[index].sec_dot = ((n1_device_list.rp[index].rp_id & 0XFF)  + ((n1_device_list.rp[index].rp_id>>8) & 0XFF) +0x199)%30;
    }
}


void MainWindow::add_rp_own_sensor_count(void)
{

    for(int index=0;index<n1_device_list.rp_num_cfg;index++)
    {
        n1_device_list.rp[index].own_sensor_num[0] = 0;
        n1_device_list.rp[index].own_sensor_num[1] = 0;
    }


    for(int index=0;index<n1_device_list.rp_num_cfg;index++)  //记录所有RP带的sensor个数
    {

        for(int index1=0;index1<n1_device_list.sensor_num_cfg;index1++)
        {
            if(n1_device_list.sensor[index1].father_id_cfg == n1_device_list.rp[index].rp_id)
                n1_device_list.rp[index].own_sensor_num[0]++;
        }
        n1_device_list.rp[index].own_sensor_num[0]++;       //包含他自己
    }

    for(int index=0;index<n1_device_list.rp_num_cfg;index++)
    {
        if(n1_device_list.rp[index].level == 1)
        {
            for(int index1=0;index1<n1_device_list.rp_num_cfg;index1++)
            {
                if(n1_device_list.rp[index1].father_id_cfg == n1_device_list.rp[index].rp_id)
                    n1_device_list.rp[index].own_sensor_num[1] += n1_device_list.rp[index1].own_sensor_num[0];
            }
        }

    }


}


void MainWindow::add_sensor_level(void)
{
    int index = 0;
    int i1;
    for(index;index<n1_device_list.sensor_num_cfg;index++)
    {
        if(n1_device_list.sensor[index].father_id_cfg == -1)        //父RP==0
            n1_device_list.sensor[index].level = 1;
        else
        {
            i1 = find_rp_index(n1_device_list.sensor[index].father_id_cfg);
            if(i1>=0)
            {
                n1_device_list.sensor[index].level = n1_device_list.rp[i1].level +1;
            }
        }
    }
}



void MainWindow::settext_text_rp_list(QString str)
{
    ui->text_adjust_rplist->setText(str);
}


void MainWindow::settext_text_sensor_list(QString str)
{
    ui->text_adjust_sensor_list->setText(str);
}

void MainWindow::settext_text_dev_p1(QString str)
{
    ui->text_adjust_level->setText(str);
}

void MainWindow::settext_text_dev_p2(QString str)
{
    ui->text_adjust_level_2->setText(str);
}

void MainWindow::addtext_text_dev_p3(QString str)
{
    ui->text_adjust_level_3->append(str);
}



//大端切换小端
int MainWindow::reversebytes_uint32t(int value){
    return (value & 0x000000FFU) << 24 | (value & 0x0000FF00U) << 8 |
        (value & 0x00FF0000U) >> 8 | (value & 0xFF000000U) >> 24;
}

//大端切换小端
int MainWindow::reversebytes_uint16t(int value){
    return (value & 0x000000FFU) << 8 | (value & 0x0000FF00U) >> 8;
}


void MainWindow::on_CLBtn_openDeviceTable_clicked()
{

    p_n1_device_table->show();
}

void MainWindow::on_BTN_GetAPparam_clicked()
{
    ui->LED_Channel->display(0);
    socket_get_ap_channel();

}

void MainWindow::on_BTN_Adjust_clicked()
{
    m_dev_adjust_count = 2; //开始设置通道，进入调度函数


}

void MainWindow::on_BTN_Adjust_pause_clicked()
{
   m_dev_adjust_count = 0; //暂停设置通道，不进入调度函数

}

void MainWindow::on_BTN_Adjust_stop_clicked()
{
   m_dev_adjust_count = 1; //停止设置通道，清除当前进度，进入暂停状态，不进入调度函数

}



//开始自动配置时间槽
void MainWindow::on_BTN_Adjust_slot_begin_clicked()
{
    if(m_dev_adjust_count == 2)
    {
        QMessageBox::information(NULL, QString( "警告" ) , QString( "必须先停止或者暂停通道设置！" ) );
        ui->BTN_Adjust_slot_begin->setChecked(false);
        ui->BTN_Adjust_slot_stop->setChecked(true);
        return;
    }
    m_dev_adjust_slot_flag = 1;

}

//停止自动配置时间槽
void MainWindow::on_BTN_Adjust_slot_stop_clicked()
{
    m_dev_adjust_slot_flag = 0;
}






void MainWindow::on_BTN_band_clicked()
{
    m_dev_band = 1;
}

void MainWindow::on_BTN_band_false_clicked()
{
    m_dev_band = 0;
}

void MainWindow::on_BTN_band_ap_clicked()
{
    socket_band_ap_(1);
}

void MainWindow::on_BTN_band_false_AP_clicked()
{
    socket_band_ap_(0);
}

void MainWindow::on_BTN_save_ap_pram_clicked()
{
    socket_save_ap_param();
}

void MainWindow::on_BTN_Adjust_to_back_clicked()
{
    m_dev_adjust_count = 3;
}
