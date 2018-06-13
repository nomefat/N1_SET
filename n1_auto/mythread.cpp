#include "mythread.h"
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QContiguousCache>


namespace Ui {
class MainWindow;
}

MyThread::MyThread(QObject *parent):QThread(parent)
{
    stoped = 0;
    mw = (MainWindow *)parent;
}


/*
 *  该线程负责从网络数据队列中取出完整的一帧数据，并且调用数据处理函数.
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * */
void MyThread::run()
{
    int i = 0;
    unsigned char dat = 0;
    bool data_valid_flag = false;
    QByteArray n1_data;
    QString str;

    while(!stoped)
    {
        mw->n1_data_lock.lock();
        while(!mw->n1_data_queue.isEmpty())
        {
            dat = mw->n1_data_queue.dequeue();
//            qDebug()<<dat;
            if(dat == 0xfe)
                data_valid_flag = true;
            if(data_valid_flag == true)
            {
                n1_data[i++] = dat;
                if(i == n1_data[2])
                {
//                    qDebug()<<"data:"<<n1_data<<endl;
                    data_valid_flag = false;
                    i = 0;
                    mw->n1_data_process(n1_data);
                }

            }
        }
        mw->n1_data_lock.unlock();
        msleep(10);

    }

}





