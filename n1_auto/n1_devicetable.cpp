#include "n1_devicetable.h"
#include "ui_n1_devicetable.h"
#include <QStandardItemModel>
#include "mainwindow.h"
#include <QStandardItem>


#pragma execution_character_set("utf-8")




/*
 * 初始化显示设备界面
 *
 *
 *
 *
 *
 */
N1_DeviceTable::N1_DeviceTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::N1_DeviceTable)
{
    ui->setupUi(this);

    //准备数据模型
   n1_device_data_model = new QStandardItemModel(100,12);
   n1_device_data_model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("____设备ID")));
   n1_device_data_model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("配置父RP")));
   n1_device_data_model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("配置上行通道")));
   n1_device_data_model->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("配置下行行通道")));
   n1_device_data_model->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("配置时间槽")));
   n1_device_data_model->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("实际父RP")));
   n1_device_data_model->setHorizontalHeaderItem(6, new QStandardItem(QObject::tr("实际上行通道")));
   n1_device_data_model->setHorizontalHeaderItem(7, new QStandardItem(QObject::tr("实际下行通道")));
   n1_device_data_model->setHorizontalHeaderItem(8, new QStandardItem(QObject::tr("实际时间槽")));
   n1_device_data_model->setHorizontalHeaderItem(9, new QStandardItem(QObject::tr("绑定ID")));
   n1_device_data_model->setHorizontalHeaderItem(10, new QStandardItem(QObject::tr("已设置的标记")));
   n1_device_data_model->setHorizontalHeaderItem(11, new QStandardItem(QObject::tr("超时计数")));
   n1_device_data_model->setHorizontalHeaderItem(12, new QStandardItem(QObject::tr("信号强度")));
   //利用setModel()方法将数据模型与QTableView绑定
   ui->devicetable->setModel(n1_device_data_model);

   //设置选中时为整行选中
   ui->devicetable->setSelectionBehavior(QAbstractItemView::SelectRows);

   //设置表格的单元为只读属性，即不能编辑
   ui->devicetable->setEditTriggers(QAbstractItemView::NoEditTriggers);

   ui->devicetable->showGrid();

   ui->devicetable->resizeColumnsToContents();

   mw = (MainWindow*)parent;


   for(int i=0;i<100;i++)
   {

       for(int j=0;j<13;j++)
       {
           QStandardItem *item_column = new QStandardItem();
           n1_device_data_model->setItem(i,j,item_column);
       }


   }

    testTimer = new QTimer(this);
    connect( testTimer,SIGNAL(timeout()), this, SLOT(FlushDevData()) );
    testTimer->start(1000);
}

N1_DeviceTable::~N1_DeviceTable()
{
    delete ui;
}


void N1_DeviceTable::Flush_rp_Data(int row ,int index)
{
    int i;
    int flag[] = {-1,0,0,1};
    i = row;
    n1_device_data_model->item(i,0)->setText(QString::asprintf("%04X",MainWindow::reversebytes_uint16t(((MainWindow*)mw)->n1_device_list.rp[index].rp_id)));
    if(((MainWindow*)mw)->n1_device_list.rp[index].father_id_cfg == -1)
        n1_device_data_model->item(i,1)->setText(QString("AP"));
    else
        n1_device_data_model->item(i,1)->setText(QString::asprintf("%04X",MainWindow::reversebytes_uint16t(((MainWindow*)mw)->n1_device_list.rp[index].father_id_cfg)));

    n1_device_data_model->item(i,2)->setText(QString::asprintf("%d",((MainWindow*)mw)->n1_device_list.rp[index].up_channel_cfg));
    n1_device_data_model->item(i,3)->setText(QString::asprintf("%d",((MainWindow*)mw)->n1_device_list.rp[index].down_channel_cfg));
    n1_device_data_model->item(i,4)->setText(QString::asprintf("%d-%d",flag[((MainWindow*)mw)->n1_device_list.rp[index].rp_type_cfg],((MainWindow*)mw)->n1_device_list.rp[index].set_slot));
    if(((MainWindow*)mw)->n1_device_list.rp[i].father_id == -1)
        n1_device_data_model->item(i,5)->setText(QString("AP"));
    else
        n1_device_data_model->item(i,5)->setText(QString::asprintf("%04X",MainWindow::reversebytes_uint16t(((MainWindow*)mw)->n1_device_list.rp[index].father_id)));

    n1_device_data_model->item(i,6)->setText(QString::asprintf("%d",((MainWindow*)mw)->n1_device_list.rp[index].up_channel));
    n1_device_data_model->item(i,7)->setText(QString::asprintf("%d",((MainWindow*)mw)->n1_device_list.rp[index].down_channel));
    n1_device_data_model->item(i,8)->setText(QString::asprintf("%d-%d",flag[((MainWindow*)mw)->n1_device_list.rp[index].rp_type],((MainWindow*)mw)->n1_device_list.rp[index].slot));
    n1_device_data_model->item(i,9)->setText(QString::asprintf("%04X",((MainWindow*)mw)->n1_device_list.rp[index].uiBindId));
    if(((MainWindow*)mw)->n1_device_list.rp[index].adjust_fail == 0)
        n1_device_data_model->item(i,10)->setText(QString::asprintf(" "));
    else if(((MainWindow*)mw)->n1_device_list.rp[index].adjust_fail == 1)
        n1_device_data_model->item(i,10)->setText(QString::asprintf("设置失败"));
    else if(((MainWindow*)mw)->n1_device_list.rp[index].adjust_fail == 2)
        n1_device_data_model->item(i,10)->setText(QString::asprintf("上级设置失败"));
    else if(((MainWindow*)mw)->n1_device_list.rp[index].adjust_fail == 3)
        n1_device_data_model->item(i,10)->setText(QString::asprintf("上上级设置失败"));
    n1_device_data_model->item(i,11)->setText(QString::asprintf("%d",((MainWindow*)mw)->n1_device_list.rp[index].timeout++));
    n1_device_data_model->item(i,12)->setText(QString::asprintf("%d",((MainWindow*)mw)->n1_device_list.rp[index].rssi));
    if(((MainWindow*)mw)->n1_device_list.rp[index].timeout>30)
        n1_device_data_model->item(i,11)->setBackground(QBrush(QColor(0xf4,0xa4,0x60)));
    else
        n1_device_data_model->item(i,11)->setBackground(QBrush(QColor(255,255,255)));

    n1_device_data_model->item(i,0)->setBackground(QBrush(QColor(0xc9,0xc9,0xc9)));
    n1_device_data_model->item(i,1)->setBackground(QBrush(QColor(0xc9,0xc9,0xc9)));
    n1_device_data_model->item(i,2)->setBackground(QBrush(QColor(0xc9,0xc9,0xc9)));
    n1_device_data_model->item(i,3)->setBackground(QBrush(QColor(0xc9,0xc9,0xc9)));
    n1_device_data_model->item(i,4)->setBackground(QBrush(QColor(0xc9,0xc9,0xc9)));
    n1_device_data_model->item(i,5)->setBackground(QBrush(QColor(0xc9,0xc9,0xc9)));
    n1_device_data_model->item(i,6)->setBackground(QBrush(QColor(0xc9,0xc9,0xc9)));
    n1_device_data_model->item(i,7)->setBackground(QBrush(QColor(0xc9,0xc9,0xc9)));

    n1_device_data_model->item(i,9)->setBackground(QBrush(QColor(0xc9,0xc9,0xc9)));
    n1_device_data_model->item(i,10)->setBackground(QBrush(QColor(0xc9,0xc9,0xc9)));
    n1_device_data_model->item(i,12)->setBackground(QBrush(QColor(0xc9,0xc9,0xc9)));


    for(int i=0;i<((MainWindow*)mw)->n1_device_list.sensor_num_cfg;i++)
    {
        if(((MainWindow*)mw)->n1_device_list.rp[index].slot == ((MainWindow*)mw)->n1_device_list.sensor[i].slot )
        {
            n1_device_data_model->item(i,8)->setBackground(QBrush(QColor(0xb4,0xa4,0x60)));
            return;
        }
    }

    for(int i=0;i<((MainWindow*)mw)->n1_device_list.rp_num_cfg;i++)
    {
        if(((MainWindow*)mw)->n1_device_list.rp[index].slot == ((MainWindow*)mw)->n1_device_list.rp[i].slot && i!=index)
        {
            n1_device_data_model->item(i,8)->setBackground(QBrush(QColor(0xb4,0xa4,0x60)));
            return;
        }
    }

    n1_device_data_model->item(i,8)->setBackground(QBrush(QColor(0xc9,0xc9,0xc9)));

}

void N1_DeviceTable::Flush_sensor_Data(int row ,int index)
{
    int j;
    j = row;
    QString s = QString::asprintf("%04X",MainWindow::reversebytes_uint16t(((MainWindow*)mw)->n1_device_list.sensor[index].sensor_id));
    n1_device_data_model->item(j,0)->setText(QString::asprintf("%08X",MainWindow::reversebytes_uint16t(((MainWindow*)mw)->n1_device_list.sensor[index].sensor_id)));
    if(((MainWindow*)mw)->n1_device_list.sensor[index].father_id_cfg == -1)
        n1_device_data_model->item(j,1)->setText(QString("AP"));
    else
        n1_device_data_model->item(j,1)->setText(QString::asprintf("%04X",MainWindow::reversebytes_uint16t(((MainWindow*)mw)->n1_device_list.sensor[index].father_id_cfg)));

    n1_device_data_model->item(j,2)->setText(QString::asprintf("%d",((MainWindow*)mw)->n1_device_list.sensor[index].channel_cfg));
    n1_device_data_model->item(j,3)->setText("0");
    n1_device_data_model->item(j,4)->setText(QString::asprintf("%d",((MainWindow*)mw)->n1_device_list.sensor[index].set_slot));
    if(((MainWindow*)mw)->n1_device_list.sensor[index].father_id == -1)
        n1_device_data_model->item(j,5)->setText(QString("AP"));
    else
        n1_device_data_model->item(j,5)->setText(QString::asprintf("%04X",MainWindow::reversebytes_uint16t(((MainWindow*)mw)->n1_device_list.sensor[index].father_id)));

    n1_device_data_model->item(j,6)->setText(QString::asprintf("%d",((MainWindow*)mw)->n1_device_list.sensor[index].channel));
    n1_device_data_model->item(j,7)->setText("0");
    n1_device_data_model->item(j,8)->setText(QString::asprintf("%d",((MainWindow*)mw)->n1_device_list.sensor[index].slot));
    n1_device_data_model->item(j,9)->setText(QString::asprintf("%04X",((MainWindow*)mw)->n1_device_list.sensor[index].uiBindId));
    if(((MainWindow*)mw)->n1_device_list.sensor[index].adjust_fail == 0)
        n1_device_data_model->item(j,10)->setText(QString::asprintf(" "));
    else if(((MainWindow*)mw)->n1_device_list.sensor[index].adjust_fail == 1)
        n1_device_data_model->item(j,10)->setText(QString::asprintf("设置失败"));
    else if(((MainWindow*)mw)->n1_device_list.sensor[index].adjust_fail == 2)
        n1_device_data_model->item(j,10)->setText(QString::asprintf("上级设置失败"));
    else if(((MainWindow*)mw)->n1_device_list.sensor[index].adjust_fail == 3)
        n1_device_data_model->item(j,10)->setText(QString::asprintf("上上级设置失败"));
    n1_device_data_model->item(j,11)->setText(QString::asprintf("%d",((MainWindow*)mw)->n1_device_list.sensor[index].timeout++));
    n1_device_data_model->item(j,12)->setText(QString::asprintf("%d",((MainWindow*)mw)->n1_device_list.sensor[index].rssi));
    if(((MainWindow*)mw)->n1_device_list.sensor[index].timeout>30)
        n1_device_data_model->item(j,11)->setBackground(QBrush(QColor(0xf4,0xa4,0x60)));
    else
        n1_device_data_model->item(j,11)->setBackground(QBrush(QColor(255,255,255)));


    for(int i=0;i<((MainWindow*)mw)->n1_device_list.sensor_num_cfg;i++)
    {
        if(((MainWindow*)mw)->n1_device_list.sensor[index].slot == ((MainWindow*)mw)->n1_device_list.sensor[i].slot && i!=index)
        {
            n1_device_data_model->item(j,8)->setBackground(QBrush(QColor(0xb4,0xa4,0x60)));
            return;
        }
    }

    for(int i=0;i<((MainWindow*)mw)->n1_device_list.rp_num_cfg;i++)
    {
        if(((MainWindow*)mw)->n1_device_list.sensor[index].slot == ((MainWindow*)mw)->n1_device_list.rp[i].slot)
        {
            n1_device_data_model->item(j,8)->setBackground(QBrush(QColor(0xb4,0xa4,0x60)));
            return;
        }
    }
    n1_device_data_model->item(j,8)->setBackground(QBrush(QColor(255,255,255)));
}




/*
 * 定时刷新设备界面
 *
 *
 *
 *
 *
 */
void N1_DeviceTable::FlushDevData()
{
    int row = 0;
    testTimer->start(1000);
    for(int i=0;i<((MainWindow*)mw)->n1_device_list.sensor_num_cfg;i++)  //1级sensor
    {
        if(((MainWindow*)mw)->n1_device_list.sensor[i].father_id_cfg == -1)
            Flush_sensor_Data(row++,i);

    }


    for(int i=0;i<((MainWindow*)mw)->n1_device_list.rp_num_cfg;i++)
    {
        if(((MainWindow*)mw)->n1_device_list.rp[i].father_id_cfg == -1)  //1级rp
        {
            row++;
            Flush_rp_Data(row++,i);

            for(int j=0;j<((MainWindow*)mw)->n1_device_list.sensor_num_cfg;j++)  //2级sensor
            {
                if(((MainWindow*)mw)->n1_device_list.sensor[j].father_id_cfg == ((MainWindow*)mw)->n1_device_list.rp[i].rp_id)
                    Flush_sensor_Data(row++,j);
            }
            for(int k=0;k<((MainWindow*)mw)->n1_device_list.rp_num_cfg;k++)
            {
                if(((MainWindow*)mw)->n1_device_list.rp[k].father_id_cfg == ((MainWindow*)mw)->n1_device_list.rp[i].rp_id)  //2级rp
                {
                    row++;
                    Flush_rp_Data(row++,k);

                    for(int x=0;x<((MainWindow*)mw)->n1_device_list.sensor_num_cfg;x++)  //2级sensor
                    {
                        if(((MainWindow*)mw)->n1_device_list.sensor[x].father_id_cfg == ((MainWindow*)mw)->n1_device_list.rp[k].rp_id)
                            Flush_sensor_Data(row++,x);
                    }

                }
            }
        }
    }















}
