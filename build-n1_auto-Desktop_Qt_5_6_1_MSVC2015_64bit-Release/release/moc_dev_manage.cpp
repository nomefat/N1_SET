/****************************************************************************
** Meta object code from reading C++ file 'dev_manage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../n1_auto/dev_manage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dev_manage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Dev_Manage_t {
    QByteArrayData data[20];
    char stringdata0[341];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Dev_Manage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Dev_Manage_t qt_meta_stringdata_Dev_Manage = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Dev_Manage"
QT_MOC_LITERAL(1, 11, 21), // "signal_set_ap_channel"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 7), // "channel"
QT_MOC_LITERAL(4, 42, 21), // "signal_get_ap_channel"
QT_MOC_LITERAL(5, 64, 16), // "signal_get_ap_id"
QT_MOC_LITERAL(6, 81, 21), // "signal_band_sensor_rp"
QT_MOC_LITERAL(7, 103, 2), // "id"
QT_MOC_LITERAL(8, 106, 4), // "apid"
QT_MOC_LITERAL(9, 111, 3), // "sec"
QT_MOC_LITERAL(10, 115, 28), // "signal_set_sensor_rp_channel"
QT_MOC_LITERAL(11, 144, 25), // "signal_set_sensor_rp_slot"
QT_MOC_LITERAL(12, 170, 4), // "slot"
QT_MOC_LITERAL(13, 175, 20), // "signal_re_connect_n1"
QT_MOC_LITERAL(14, 196, 27), // "signal_settext_text_rp_list"
QT_MOC_LITERAL(15, 224, 3), // "str"
QT_MOC_LITERAL(16, 228, 31), // "signal_settext_text_sensor_list"
QT_MOC_LITERAL(17, 260, 26), // "signal_settext_text_dev_p1"
QT_MOC_LITERAL(18, 287, 26), // "signal_settext_text_dev_p2"
QT_MOC_LITERAL(19, 314, 26) // "signal_addtext_text_dev_p3"

    },
    "Dev_Manage\0signal_set_ap_channel\0\0"
    "channel\0signal_get_ap_channel\0"
    "signal_get_ap_id\0signal_band_sensor_rp\0"
    "id\0apid\0sec\0signal_set_sensor_rp_channel\0"
    "signal_set_sensor_rp_slot\0slot\0"
    "signal_re_connect_n1\0signal_settext_text_rp_list\0"
    "str\0signal_settext_text_sensor_list\0"
    "signal_settext_text_dev_p1\0"
    "signal_settext_text_dev_p2\0"
    "signal_addtext_text_dev_p3"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Dev_Manage[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       4,    0,   77,    2, 0x06 /* Public */,
       5,    0,   78,    2, 0x06 /* Public */,
       6,    3,   79,    2, 0x06 /* Public */,
      10,    3,   86,    2, 0x06 /* Public */,
      11,    3,   93,    2, 0x06 /* Public */,
      13,    0,  100,    2, 0x06 /* Public */,
      14,    1,  101,    2, 0x06 /* Public */,
      16,    1,  104,    2, 0x06 /* Public */,
      17,    1,  107,    2, 0x06 /* Public */,
      18,    1,  110,    2, 0x06 /* Public */,
      19,    1,  113,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    7,    8,    9,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    7,    3,    9,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    7,   12,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::QString,   15,

       0        // eod
};

void Dev_Manage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Dev_Manage *_t = static_cast<Dev_Manage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_set_ap_channel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->signal_get_ap_channel(); break;
        case 2: _t->signal_get_ap_id(); break;
        case 3: _t->signal_band_sensor_rp((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 4: _t->signal_set_sensor_rp_channel((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 5: _t->signal_set_sensor_rp_slot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 6: _t->signal_re_connect_n1(); break;
        case 7: _t->signal_settext_text_rp_list((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->signal_settext_text_sensor_list((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->signal_settext_text_dev_p1((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->signal_settext_text_dev_p2((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->signal_addtext_text_dev_p3((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Dev_Manage::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Dev_Manage::signal_set_ap_channel)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Dev_Manage::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Dev_Manage::signal_get_ap_channel)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Dev_Manage::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Dev_Manage::signal_get_ap_id)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Dev_Manage::*_t)(int , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Dev_Manage::signal_band_sensor_rp)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Dev_Manage::*_t)(int , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Dev_Manage::signal_set_sensor_rp_channel)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (Dev_Manage::*_t)(int , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Dev_Manage::signal_set_sensor_rp_slot)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (Dev_Manage::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Dev_Manage::signal_re_connect_n1)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (Dev_Manage::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Dev_Manage::signal_settext_text_rp_list)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (Dev_Manage::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Dev_Manage::signal_settext_text_sensor_list)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (Dev_Manage::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Dev_Manage::signal_settext_text_dev_p1)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (Dev_Manage::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Dev_Manage::signal_settext_text_dev_p2)) {
                *result = 10;
                return;
            }
        }
        {
            typedef void (Dev_Manage::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Dev_Manage::signal_addtext_text_dev_p3)) {
                *result = 11;
                return;
            }
        }
    }
}

const QMetaObject Dev_Manage::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Dev_Manage.data,
      qt_meta_data_Dev_Manage,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Dev_Manage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Dev_Manage::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Dev_Manage.stringdata0))
        return static_cast<void*>(const_cast< Dev_Manage*>(this));
    return QObject::qt_metacast(_clname);
}

int Dev_Manage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void Dev_Manage::signal_set_ap_channel(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Dev_Manage::signal_get_ap_channel()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void Dev_Manage::signal_get_ap_id()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void Dev_Manage::signal_band_sensor_rp(int _t1, int _t2, int _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Dev_Manage::signal_set_sensor_rp_channel(int _t1, int _t2, int _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Dev_Manage::signal_set_sensor_rp_slot(int _t1, int _t2, int _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Dev_Manage::signal_re_connect_n1()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}

// SIGNAL 7
void Dev_Manage::signal_settext_text_rp_list(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Dev_Manage::signal_settext_text_sensor_list(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void Dev_Manage::signal_settext_text_dev_p1(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void Dev_Manage::signal_settext_text_dev_p2(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void Dev_Manage::signal_addtext_text_dev_p3(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}
QT_END_MOC_NAMESPACE
