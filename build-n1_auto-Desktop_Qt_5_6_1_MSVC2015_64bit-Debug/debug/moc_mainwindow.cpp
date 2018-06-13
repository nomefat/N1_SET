/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../n1_auto/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[46];
    char stringdata0[928];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 21), // "on_BTN_MODIFY_clicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 21), // "on_BTN_ADD_AP_clicked"
QT_MOC_LITERAL(4, 56, 21), // "on_BTN_ADD_RP_clicked"
QT_MOC_LITERAL(5, 78, 25), // "on_BTN_ADD_Sensor_clicked"
QT_MOC_LITERAL(6, 104, 18), // "on_BTN_DEL_clicked"
QT_MOC_LITERAL(7, 123, 21), // "on_saveconfig_clicked"
QT_MOC_LITERAL(8, 145, 21), // "on_openconfig_clicked"
QT_MOC_LITERAL(9, 167, 22), // "on_BTN_Connect_clicked"
QT_MOC_LITERAL(10, 190, 19), // "on_socket_connected"
QT_MOC_LITERAL(11, 210, 22), // "on_socket_disconnected"
QT_MOC_LITERAL(12, 233, 17), // "on_socket_receive"
QT_MOC_LITERAL(13, 251, 32), // "on_CLBtn_openDeviceTable_clicked"
QT_MOC_LITERAL(14, 284, 25), // "on_BTN_GetAPparam_clicked"
QT_MOC_LITERAL(15, 310, 21), // "on_BTN_Adjust_clicked"
QT_MOC_LITERAL(16, 332, 27), // "on_BTN_Adjust_pause_clicked"
QT_MOC_LITERAL(17, 360, 26), // "on_BTN_Adjust_stop_clicked"
QT_MOC_LITERAL(18, 387, 32), // "on_BTN_Adjust_slot_begin_clicked"
QT_MOC_LITERAL(19, 420, 31), // "on_BTN_Adjust_slot_stop_clicked"
QT_MOC_LITERAL(20, 452, 19), // "on_BTN_band_clicked"
QT_MOC_LITERAL(21, 472, 25), // "on_BTN_band_false_clicked"
QT_MOC_LITERAL(22, 498, 22), // "on_BTN_band_ap_clicked"
QT_MOC_LITERAL(23, 521, 28), // "on_BTN_band_false_AP_clicked"
QT_MOC_LITERAL(24, 550, 27), // "on_BTN_save_ap_pram_clicked"
QT_MOC_LITERAL(25, 578, 29), // "on_BTN_Adjust_to_back_clicked"
QT_MOC_LITERAL(26, 608, 21), // "socket_set_ap_channel"
QT_MOC_LITERAL(27, 630, 7), // "channel"
QT_MOC_LITERAL(28, 638, 21), // "socket_get_ap_channel"
QT_MOC_LITERAL(29, 660, 28), // "socket_set_sensor_rp_channel"
QT_MOC_LITERAL(30, 689, 2), // "id"
QT_MOC_LITERAL(31, 692, 3), // "sec"
QT_MOC_LITERAL(32, 696, 25), // "socket_set_sensor_rp_slot"
QT_MOC_LITERAL(33, 722, 4), // "slot"
QT_MOC_LITERAL(34, 727, 16), // "socket_get_ap_id"
QT_MOC_LITERAL(35, 744, 20), // "settext_text_rp_list"
QT_MOC_LITERAL(36, 765, 3), // "str"
QT_MOC_LITERAL(37, 769, 24), // "settext_text_sensor_list"
QT_MOC_LITERAL(38, 794, 19), // "settext_text_dev_p1"
QT_MOC_LITERAL(39, 814, 19), // "settext_text_dev_p2"
QT_MOC_LITERAL(40, 834, 21), // "socket_band_sensor_rp"
QT_MOC_LITERAL(41, 856, 4), // "apid"
QT_MOC_LITERAL(42, 861, 19), // "addtext_text_dev_p3"
QT_MOC_LITERAL(43, 881, 15), // "socket_band_ap_"
QT_MOC_LITERAL(44, 897, 9), // "yes_or_no"
QT_MOC_LITERAL(45, 907, 20) // "socket_save_ap_param"

    },
    "MainWindow\0on_BTN_MODIFY_clicked\0\0"
    "on_BTN_ADD_AP_clicked\0on_BTN_ADD_RP_clicked\0"
    "on_BTN_ADD_Sensor_clicked\0on_BTN_DEL_clicked\0"
    "on_saveconfig_clicked\0on_openconfig_clicked\0"
    "on_BTN_Connect_clicked\0on_socket_connected\0"
    "on_socket_disconnected\0on_socket_receive\0"
    "on_CLBtn_openDeviceTable_clicked\0"
    "on_BTN_GetAPparam_clicked\0"
    "on_BTN_Adjust_clicked\0on_BTN_Adjust_pause_clicked\0"
    "on_BTN_Adjust_stop_clicked\0"
    "on_BTN_Adjust_slot_begin_clicked\0"
    "on_BTN_Adjust_slot_stop_clicked\0"
    "on_BTN_band_clicked\0on_BTN_band_false_clicked\0"
    "on_BTN_band_ap_clicked\0"
    "on_BTN_band_false_AP_clicked\0"
    "on_BTN_save_ap_pram_clicked\0"
    "on_BTN_Adjust_to_back_clicked\0"
    "socket_set_ap_channel\0channel\0"
    "socket_get_ap_channel\0"
    "socket_set_sensor_rp_channel\0id\0sec\0"
    "socket_set_sensor_rp_slot\0slot\0"
    "socket_get_ap_id\0settext_text_rp_list\0"
    "str\0settext_text_sensor_list\0"
    "settext_text_dev_p1\0settext_text_dev_p2\0"
    "socket_band_sensor_rp\0apid\0"
    "addtext_text_dev_p3\0socket_band_ap_\0"
    "yes_or_no\0socket_save_ap_param"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      37,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  199,    2, 0x08 /* Private */,
       3,    0,  200,    2, 0x08 /* Private */,
       4,    0,  201,    2, 0x08 /* Private */,
       5,    0,  202,    2, 0x08 /* Private */,
       6,    0,  203,    2, 0x08 /* Private */,
       7,    0,  204,    2, 0x08 /* Private */,
       8,    0,  205,    2, 0x08 /* Private */,
       9,    0,  206,    2, 0x08 /* Private */,
      10,    0,  207,    2, 0x08 /* Private */,
      11,    0,  208,    2, 0x08 /* Private */,
      12,    0,  209,    2, 0x08 /* Private */,
      13,    0,  210,    2, 0x08 /* Private */,
      14,    0,  211,    2, 0x08 /* Private */,
      15,    0,  212,    2, 0x08 /* Private */,
      16,    0,  213,    2, 0x08 /* Private */,
      17,    0,  214,    2, 0x08 /* Private */,
      18,    0,  215,    2, 0x08 /* Private */,
      19,    0,  216,    2, 0x08 /* Private */,
      20,    0,  217,    2, 0x08 /* Private */,
      21,    0,  218,    2, 0x08 /* Private */,
      22,    0,  219,    2, 0x08 /* Private */,
      23,    0,  220,    2, 0x08 /* Private */,
      24,    0,  221,    2, 0x08 /* Private */,
      25,    0,  222,    2, 0x08 /* Private */,
      26,    1,  223,    2, 0x0a /* Public */,
      28,    0,  226,    2, 0x0a /* Public */,
      29,    3,  227,    2, 0x0a /* Public */,
      32,    3,  234,    2, 0x0a /* Public */,
      34,    0,  241,    2, 0x0a /* Public */,
      35,    1,  242,    2, 0x0a /* Public */,
      37,    1,  245,    2, 0x0a /* Public */,
      38,    1,  248,    2, 0x0a /* Public */,
      39,    1,  251,    2, 0x0a /* Public */,
      40,    3,  254,    2, 0x0a /* Public */,
      42,    1,  261,    2, 0x0a /* Public */,
      43,    1,  264,    2, 0x0a /* Public */,
      45,    0,  267,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   27,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   30,   27,   31,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   30,   33,   31,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   36,
    QMetaType::Void, QMetaType::QString,   36,
    QMetaType::Void, QMetaType::QString,   36,
    QMetaType::Void, QMetaType::QString,   36,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   30,   41,   31,
    QMetaType::Void, QMetaType::QString,   36,
    QMetaType::Void, QMetaType::UChar,   44,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_BTN_MODIFY_clicked(); break;
        case 1: _t->on_BTN_ADD_AP_clicked(); break;
        case 2: _t->on_BTN_ADD_RP_clicked(); break;
        case 3: _t->on_BTN_ADD_Sensor_clicked(); break;
        case 4: _t->on_BTN_DEL_clicked(); break;
        case 5: _t->on_saveconfig_clicked(); break;
        case 6: _t->on_openconfig_clicked(); break;
        case 7: _t->on_BTN_Connect_clicked(); break;
        case 8: _t->on_socket_connected(); break;
        case 9: _t->on_socket_disconnected(); break;
        case 10: _t->on_socket_receive(); break;
        case 11: _t->on_CLBtn_openDeviceTable_clicked(); break;
        case 12: _t->on_BTN_GetAPparam_clicked(); break;
        case 13: _t->on_BTN_Adjust_clicked(); break;
        case 14: _t->on_BTN_Adjust_pause_clicked(); break;
        case 15: _t->on_BTN_Adjust_stop_clicked(); break;
        case 16: _t->on_BTN_Adjust_slot_begin_clicked(); break;
        case 17: _t->on_BTN_Adjust_slot_stop_clicked(); break;
        case 18: _t->on_BTN_band_clicked(); break;
        case 19: _t->on_BTN_band_false_clicked(); break;
        case 20: _t->on_BTN_band_ap_clicked(); break;
        case 21: _t->on_BTN_band_false_AP_clicked(); break;
        case 22: _t->on_BTN_save_ap_pram_clicked(); break;
        case 23: _t->on_BTN_Adjust_to_back_clicked(); break;
        case 24: _t->socket_set_ap_channel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->socket_get_ap_channel(); break;
        case 26: _t->socket_set_sensor_rp_channel((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 27: _t->socket_set_sensor_rp_slot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 28: _t->socket_get_ap_id(); break;
        case 29: _t->settext_text_rp_list((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 30: _t->settext_text_sensor_list((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 31: _t->settext_text_dev_p1((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 32: _t->settext_text_dev_p2((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 33: _t->socket_band_sensor_rp((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 34: _t->addtext_text_dev_p3((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 35: _t->socket_band_ap_((*reinterpret_cast< unsigned char(*)>(_a[1]))); break;
        case 36: _t->socket_save_ap_param(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 37)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 37;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 37)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 37;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
