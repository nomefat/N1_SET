#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>

class MainWindow;

class MyThread : public QThread
{
    Q_OBJECT
public:
    MyThread(QObject *parent);
    bool stoped;
private:

    MainWindow *mw;
    void run();
};

#endif // MYTHREAD_H
