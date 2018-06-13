#include "handlethread.h"
#include "mainwindow.h"
#include "dev_manage.h"


HandleThread::HandleThread(MainWindow *parent):QThread(parent)
{
    stoped = 0;
    mw = (MainWindow *)parent;
    m_p_dev_manage = new Dev_Manage(parent);
}


void HandleThread::run()
{

    while(!stoped)
    {
        m_p_dev_manage->poll();

    }


}
