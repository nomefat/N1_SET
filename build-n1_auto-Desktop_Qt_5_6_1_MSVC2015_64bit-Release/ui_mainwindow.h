/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QPushButton *BTN_ADD_RP;
    QPushButton *BTN_MODIFY;
    QPushButton *BTN_ADD_AP;
    QPushButton *BTN_ADD_Sensor;
    QPushButton *BTN_DEL;
    QTreeWidget *treeWidget;
    QPushButton *saveconfig;
    QPushButton *openconfig;
    QLabel *label;
    QFrame *line;
    QTextBrowser *text_adjust_sensor_list;
    QLCDNumber *lcdNumber_Synpacket_number;
    QCommandLinkButton *CLBtn_openDeviceTable;
    QGroupBox *groupBox;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *BTN_Connect;
    QLineEdit *lineEdit_ip;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *BTN_GetAPparam;
    QLabel *label_3;
    QLCDNumber *LED_SendInterval;
    QLabel *label_2;
    QLCDNumber *LED_Channel;
    QTextBrowser *text_adjust_level;
    QTextBrowser *text_adjust_timeout;
    QTextBrowser *text_adjust_rplist;
    QTextBrowser *text_adjust_level_2;
    QTextBrowser *text_adjust_level_3;
    QLCDNumber *lcdNumber_count_down;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_6;
    QRadioButton *BTN_Adjust_slot_begin;
    QRadioButton *BTN_Adjust_slot_stop;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_5;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *BTN_Adjust;
    QRadioButton *BTN_Adjust_stop;
    QRadioButton *BTN_Adjust_pause;
    QRadioButton *BTN_Adjust_to_back;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    QLabel *label_5;
    QLabel *label_4;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_7;
    QRadioButton *BTN_band;
    QRadioButton *BTN_band_false;
    QGroupBox *groupBox_5;
    QHBoxLayout *horizontalLayout_8;
    QRadioButton *BTN_band_ap;
    QRadioButton *BTN_band_false_AP;
    QPushButton *BTN_save_ap_pram;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1024, 768);
        QFont font;
        font.setFamily(QString::fromUtf8("\344\273\277\345\256\213"));
        font.setPointSize(12);
        MainWindow->setFont(font);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setEnabled(true);
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(9, 9, 424, 701));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        BTN_ADD_RP = new QPushButton(layoutWidget);
        BTN_ADD_RP->setObjectName(QStringLiteral("BTN_ADD_RP"));

        gridLayout->addWidget(BTN_ADD_RP, 1, 1, 1, 1);

        BTN_MODIFY = new QPushButton(layoutWidget);
        BTN_MODIFY->setObjectName(QStringLiteral("BTN_MODIFY"));

        gridLayout->addWidget(BTN_MODIFY, 1, 3, 1, 1);

        BTN_ADD_AP = new QPushButton(layoutWidget);
        BTN_ADD_AP->setObjectName(QStringLiteral("BTN_ADD_AP"));

        gridLayout->addWidget(BTN_ADD_AP, 1, 0, 1, 1);

        BTN_ADD_Sensor = new QPushButton(layoutWidget);
        BTN_ADD_Sensor->setObjectName(QStringLiteral("BTN_ADD_Sensor"));

        gridLayout->addWidget(BTN_ADD_Sensor, 1, 2, 1, 1);

        BTN_DEL = new QPushButton(layoutWidget);
        BTN_DEL->setObjectName(QStringLiteral("BTN_DEL"));

        gridLayout->addWidget(BTN_DEL, 1, 4, 1, 1);

        treeWidget = new QTreeWidget(layoutWidget);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));

        gridLayout->addWidget(treeWidget, 0, 0, 1, 5);

        saveconfig = new QPushButton(layoutWidget);
        saveconfig->setObjectName(QStringLiteral("saveconfig"));

        gridLayout->addWidget(saveconfig, 2, 0, 1, 2);

        openconfig = new QPushButton(layoutWidget);
        openconfig->setObjectName(QStringLiteral("openconfig"));

        gridLayout->addWidget(openconfig, 2, 3, 1, 2);

        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 2, 2, 1, 1);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(450, 0, 20, 731));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        text_adjust_sensor_list = new QTextBrowser(centralWidget);
        text_adjust_sensor_list->setObjectName(QStringLiteral("text_adjust_sensor_list"));
        text_adjust_sensor_list->setGeometry(QRect(940, 160, 71, 511));
        lcdNumber_Synpacket_number = new QLCDNumber(centralWidget);
        lcdNumber_Synpacket_number->setObjectName(QStringLiteral("lcdNumber_Synpacket_number"));
        lcdNumber_Synpacket_number->setGeometry(QRect(990, 680, 31, 31));
        lcdNumber_Synpacket_number->setAutoFillBackground(true);
        lcdNumber_Synpacket_number->setDigitCount(2);
        lcdNumber_Synpacket_number->setSegmentStyle(QLCDNumber::Flat);
        lcdNumber_Synpacket_number->setProperty("value", QVariant(1));
        CLBtn_openDeviceTable = new QCommandLinkButton(centralWidget);
        CLBtn_openDeviceTable->setObjectName(QStringLiteral("CLBtn_openDeviceTable"));
        CLBtn_openDeviceTable->setGeometry(QRect(920, 0, 101, 41));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(470, 10, 351, 81));
        layoutWidget1 = new QWidget(groupBox);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(20, 10, 313, 60));
        gridLayout_2 = new QGridLayout(layoutWidget1);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        BTN_Connect = new QPushButton(layoutWidget1);
        BTN_Connect->setObjectName(QStringLiteral("BTN_Connect"));

        horizontalLayout->addWidget(BTN_Connect);

        lineEdit_ip = new QLineEdit(layoutWidget1);
        lineEdit_ip->setObjectName(QStringLiteral("lineEdit_ip"));

        horizontalLayout->addWidget(lineEdit_ip);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        BTN_GetAPparam = new QPushButton(layoutWidget1);
        BTN_GetAPparam->setObjectName(QStringLiteral("BTN_GetAPparam"));
        BTN_GetAPparam->setStyleSheet(QLatin1String("alternate-background-color: rgb(170, 255, 127);\n"
"border-color: rgb(255, 85, 0);\n"
"background-color: rgb(255, 255, 0);"));

        horizontalLayout_2->addWidget(BTN_GetAPparam);

        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);

        LED_SendInterval = new QLCDNumber(layoutWidget1);
        LED_SendInterval->setObjectName(QStringLiteral("LED_SendInterval"));
        LED_SendInterval->setSegmentStyle(QLCDNumber::Flat);

        horizontalLayout_2->addWidget(LED_SendInterval);

        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        LED_Channel = new QLCDNumber(layoutWidget1);
        LED_Channel->setObjectName(QStringLiteral("LED_Channel"));
        LED_Channel->setDigitCount(2);
        LED_Channel->setSegmentStyle(QLCDNumber::Flat);

        horizontalLayout_2->addWidget(LED_Channel);


        gridLayout_2->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        text_adjust_level = new QTextBrowser(centralWidget);
        text_adjust_level->setObjectName(QStringLiteral("text_adjust_level"));
        text_adjust_level->setGeometry(QRect(470, 160, 301, 41));
        text_adjust_timeout = new QTextBrowser(centralWidget);
        text_adjust_timeout->setObjectName(QStringLiteral("text_adjust_timeout"));
        text_adjust_timeout->setGeometry(QRect(860, 400, 51, 41));
        text_adjust_rplist = new QTextBrowser(centralWidget);
        text_adjust_rplist->setObjectName(QStringLiteral("text_adjust_rplist"));
        text_adjust_rplist->setGeometry(QRect(860, 160, 61, 101));
        text_adjust_level_2 = new QTextBrowser(centralWidget);
        text_adjust_level_2->setObjectName(QStringLiteral("text_adjust_level_2"));
        text_adjust_level_2->setGeometry(QRect(470, 220, 371, 41));
        text_adjust_level_3 = new QTextBrowser(centralWidget);
        text_adjust_level_3->setObjectName(QStringLiteral("text_adjust_level_3"));
        text_adjust_level_3->setGeometry(QRect(470, 270, 441, 171));
        lcdNumber_count_down = new QLCDNumber(centralWidget);
        lcdNumber_count_down->setObjectName(QStringLiteral("lcdNumber_count_down"));
        lcdNumber_count_down->setGeometry(QRect(790, 160, 64, 41));
        lcdNumber_count_down->setAutoFillBackground(true);
        lcdNumber_count_down->setLineWidth(1);
        lcdNumber_count_down->setMidLineWidth(1);
        lcdNumber_count_down->setDigitCount(3);
        lcdNumber_count_down->setSegmentStyle(QLCDNumber::Flat);
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(480, 470, 136, 56));
        horizontalLayout_6 = new QHBoxLayout(groupBox_3);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        BTN_Adjust_slot_begin = new QRadioButton(groupBox_3);
        BTN_Adjust_slot_begin->setObjectName(QStringLiteral("BTN_Adjust_slot_begin"));

        horizontalLayout_6->addWidget(BTN_Adjust_slot_begin);

        BTN_Adjust_slot_stop = new QRadioButton(groupBox_3);
        BTN_Adjust_slot_stop->setObjectName(QStringLiteral("BTN_Adjust_slot_stop"));

        horizontalLayout_6->addWidget(BTN_Adjust_slot_stop);

        layoutWidget2 = new QWidget(centralWidget);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(472, 90, 292, 58));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        groupBox_2 = new QGroupBox(layoutWidget2);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        BTN_Adjust = new QRadioButton(groupBox_2);
        BTN_Adjust->setObjectName(QStringLiteral("BTN_Adjust"));

        horizontalLayout_3->addWidget(BTN_Adjust);

        BTN_Adjust_stop = new QRadioButton(groupBox_2);
        BTN_Adjust_stop->setObjectName(QStringLiteral("BTN_Adjust_stop"));

        horizontalLayout_3->addWidget(BTN_Adjust_stop);

        BTN_Adjust_pause = new QRadioButton(groupBox_2);
        BTN_Adjust_pause->setObjectName(QStringLiteral("BTN_Adjust_pause"));

        horizontalLayout_3->addWidget(BTN_Adjust_pause);

        BTN_Adjust_to_back = new QRadioButton(groupBox_2);
        BTN_Adjust_to_back->setObjectName(QStringLiteral("BTN_Adjust_to_back"));

        horizontalLayout_3->addWidget(BTN_Adjust_to_back);


        horizontalLayout_5->addWidget(groupBox_2);

        layoutWidget3 = new QWidget(centralWidget);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(782, 90, 231, 61));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(layoutWidget3);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_4->addWidget(label_6);

        label_5 = new QLabel(layoutWidget3);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_4->addWidget(label_5);

        label_4 = new QLabel(layoutWidget3);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(480, 540, 168, 56));
        horizontalLayout_7 = new QHBoxLayout(groupBox_4);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        BTN_band = new QRadioButton(groupBox_4);
        BTN_band->setObjectName(QStringLiteral("BTN_band"));

        horizontalLayout_7->addWidget(BTN_band);

        BTN_band_false = new QRadioButton(groupBox_4);
        BTN_band_false->setObjectName(QStringLiteral("BTN_band_false"));

        horizontalLayout_7->addWidget(BTN_band_false);

        groupBox_5 = new QGroupBox(centralWidget);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(480, 610, 168, 56));
        horizontalLayout_8 = new QHBoxLayout(groupBox_5);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        BTN_band_ap = new QRadioButton(groupBox_5);
        BTN_band_ap->setObjectName(QStringLiteral("BTN_band_ap"));

        horizontalLayout_8->addWidget(BTN_band_ap);

        BTN_band_false_AP = new QRadioButton(groupBox_5);
        BTN_band_false_AP->setObjectName(QStringLiteral("BTN_band_false_AP"));

        horizontalLayout_8->addWidget(BTN_band_false_AP);

        BTN_save_ap_pram = new QPushButton(centralWidget);
        BTN_save_ap_pram->setObjectName(QStringLiteral("BTN_save_ap_pram"));
        BTN_save_ap_pram->setGeometry(QRect(480, 680, 171, 24));
        MainWindow->setCentralWidget(centralWidget);
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        line->raise();
        text_adjust_sensor_list->raise();
        lcdNumber_Synpacket_number->raise();
        CLBtn_openDeviceTable->raise();
        groupBox->raise();
        text_adjust_level->raise();
        text_adjust_timeout->raise();
        text_adjust_rplist->raise();
        text_adjust_level_2->raise();
        text_adjust_level_3->raise();
        lcdNumber_count_down->raise();
        groupBox_3->raise();
        groupBox_4->raise();
        groupBox_5->raise();
        BTN_save_ap_pram->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "N1 Auto manage", 0));
        BTN_ADD_RP->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240&RP", 0));
        BTN_MODIFY->setText(QApplication::translate("MainWindow", "\344\277\256\346\224\271&M", 0));
        BTN_ADD_AP->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240&AP", 0));
        BTN_ADD_Sensor->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240&Sensor", 0));
        BTN_DEL->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244&D", 0));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(2, QApplication::translate("MainWindow", "\344\270\213\350\241\214\351\200\232\351\201\223", 0));
        ___qtreewidgetitem->setText(1, QApplication::translate("MainWindow", "\344\270\212\350\241\214\351\200\232\351\201\223", 0));
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "\350\256\276\345\244\207ID", 0));
        saveconfig->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\351\205\215\347\275\256&V", 0));
        openconfig->setText(QApplication::translate("MainWindow", "\345\212\240\350\275\275\351\205\215\347\275\256&O", 0));
        label->setText(QApplication::translate("MainWindow", "\350\256\276\345\244\207\351\205\215\347\275\256\350\241\250", 0));
        CLBtn_openDeviceTable->setText(QApplication::translate("MainWindow", "\346\230\276\347\244\272\350\256\276\345\244\207", 0));
        groupBox->setTitle(QString());
        BTN_Connect->setText(QApplication::translate("MainWindow", "\350\277\236\346\216\245", 0));
        BTN_GetAPparam->setText(QApplication::translate("MainWindow", "\350\216\267\345\217\226AP\345\217\202\346\225\260", 0));
        label_3->setText(QApplication::translate("MainWindow", "\344\274\240\350\276\223\351\227\264\351\232\224", 0));
        label_2->setText(QApplication::translate("MainWindow", "\351\200\232\351\201\223", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "\350\207\252\345\212\250\351\205\215\347\275\256\346\227\266\351\227\264\346\247\275", 0));
        BTN_Adjust_slot_begin->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213", 0));
        BTN_Adjust_slot_stop->setText(QApplication::translate("MainWindow", "\345\201\234\346\255\242", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "\350\256\276\347\275\256\351\200\232\351\201\223", 0));
        BTN_Adjust->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213", 0));
        BTN_Adjust_stop->setText(QApplication::translate("MainWindow", "\345\201\234\346\255\242", 0));
        BTN_Adjust_pause->setText(QApplication::translate("MainWindow", "\346\232\202\345\201\234", 0));
        BTN_Adjust_to_back->setText(QApplication::translate("MainWindow", "\345\233\236\350\260\203", 0));
        label_6->setText(QApplication::translate("MainWindow", "\345\200\222\350\256\241\346\227\266", 0));
        label_5->setText(QApplication::translate("MainWindow", "RP\345\210\227\350\241\250", 0));
        label_4->setText(QApplication::translate("MainWindow", "\346\243\200\346\265\213\345\231\250\345\210\227\350\241\250", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "RP and Sensor", 0));
        BTN_band->setText(QApplication::translate("MainWindow", "\347\273\221\345\256\232", 0));
        BTN_band_false->setText(QApplication::translate("MainWindow", "\345\217\226\346\266\210\347\273\221\345\256\232", 0));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "AP", 0));
        BTN_band_ap->setText(QApplication::translate("MainWindow", "\347\273\221\345\256\232", 0));
        BTN_band_false_AP->setText(QApplication::translate("MainWindow", "\345\217\226\346\266\210\347\273\221\345\256\232", 0));
        BTN_save_ap_pram->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230AP\345\217\202\346\225\260", 0));
        menu->setTitle(QApplication::translate("MainWindow", "\345\270\256\345\212\251", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
