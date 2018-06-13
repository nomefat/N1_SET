/********************************************************************************
** Form generated from reading UI file 'n1_devicetable.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_N1_DEVICETABLE_H
#define UI_N1_DEVICETABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_N1_DeviceTable
{
public:
    QDialogButtonBox *buttonBox;
    QTableView *devicetable;

    void setupUi(QDialog *N1_DeviceTable)
    {
        if (N1_DeviceTable->objectName().isEmpty())
            N1_DeviceTable->setObjectName(QStringLiteral("N1_DeviceTable"));
        N1_DeviceTable->resize(966, 786);
        buttonBox = new QDialogButtonBox(N1_DeviceTable);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(760, 750, 171, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        devicetable = new QTableView(N1_DeviceTable);
        devicetable->setObjectName(QStringLiteral("devicetable"));
        devicetable->setGeometry(QRect(10, 10, 941, 731));

        retranslateUi(N1_DeviceTable);
        QObject::connect(buttonBox, SIGNAL(accepted()), N1_DeviceTable, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), N1_DeviceTable, SLOT(reject()));

        QMetaObject::connectSlotsByName(N1_DeviceTable);
    } // setupUi

    void retranslateUi(QDialog *N1_DeviceTable)
    {
        N1_DeviceTable->setWindowTitle(QApplication::translate("N1_DeviceTable", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class N1_DeviceTable: public Ui_N1_DeviceTable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_N1_DEVICETABLE_H
