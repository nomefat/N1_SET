#ifndef N1_DEVICETABLE_H
#define N1_DEVICETABLE_H

#include <QDialog>
#include <QStandardItemModel>
#include <QTimer>


namespace Ui {
class N1_DeviceTable;
}

class N1_DeviceTable : public QDialog
{
    Q_OBJECT

public:
    explicit N1_DeviceTable(QWidget *parent = 0);
    ~N1_DeviceTable();

    QStandardItemModel *n1_device_data_model = NULL;
    void *mw = NULL;
    QTimer *testTimer;

private:
    Ui::N1_DeviceTable *ui;
    void Flush_rp_Data(int row ,int index);
    void Flush_sensor_Data(int row ,int index);


private slots:
    void FlushDevData(void);

};

#endif // N1_DEVICETABLE_H
