#ifndef HANDLETHREAD_H
#define HANDLETHREAD_H

#include <QObject>
#include <QThread>


class MainWindow;
class Dev_Manage;

class HandleThread : public QThread
{

    Q_OBJECT
public:
    HandleThread(MainWindow *parent);
    bool stoped;
private:

    MainWindow *mw;
    Dev_Manage *m_p_dev_manage;
    void run();
};

#endif // HANDLETHREAD_H
