/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/app/MainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_macrosip__MainWindow_t {
    QByteArrayData data[24];
    char stringdata0[308];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_macrosip__MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_macrosip__MainWindow_t qt_meta_stringdata_macrosip__MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 20), // "macrosip::MainWindow"
QT_MOC_LITERAL(1, 21, 17), // "onAccountSettings"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 10), // "onSettings"
QT_MOC_LITERAL(4, 51, 7), // "onAbout"
QT_MOC_LITERAL(5, 59, 6), // "onQuit"
QT_MOC_LITERAL(6, 66, 16), // "onSipInitialized"
QT_MOC_LITERAL(7, 83, 14), // "onIncomingCall"
QT_MOC_LITERAL(8, 98, 6), // "callId"
QT_MOC_LITERAL(9, 105, 4), // "from"
QT_MOC_LITERAL(10, 110, 4), // "name"
QT_MOC_LITERAL(11, 115, 18), // "onCallStateChanged"
QT_MOC_LITERAL(12, 134, 9), // "CallState"
QT_MOC_LITERAL(13, 144, 5), // "state"
QT_MOC_LITERAL(14, 150, 26), // "onRegistrationStateChanged"
QT_MOC_LITERAL(15, 177, 9), // "accountId"
QT_MOC_LITERAL(16, 187, 17), // "RegistrationState"
QT_MOC_LITERAL(17, 205, 4), // "code"
QT_MOC_LITERAL(18, 210, 6), // "reason"
QT_MOC_LITERAL(19, 217, 15), // "onTrayActivated"
QT_MOC_LITERAL(20, 233, 33), // "QSystemTrayIcon::ActivationRe..."
QT_MOC_LITERAL(21, 267, 15), // "onCallRequested"
QT_MOC_LITERAL(22, 283, 6), // "number"
QT_MOC_LITERAL(23, 290, 17) // "onHangupRequested"

    },
    "macrosip::MainWindow\0onAccountSettings\0"
    "\0onSettings\0onAbout\0onQuit\0onSipInitialized\0"
    "onIncomingCall\0callId\0from\0name\0"
    "onCallStateChanged\0CallState\0state\0"
    "onRegistrationStateChanged\0accountId\0"
    "RegistrationState\0code\0reason\0"
    "onTrayActivated\0QSystemTrayIcon::ActivationReason\0"
    "onCallRequested\0number\0onHangupRequested"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_macrosip__MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x0a /* Public */,
       3,    0,   70,    2, 0x0a /* Public */,
       4,    0,   71,    2, 0x0a /* Public */,
       5,    0,   72,    2, 0x0a /* Public */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    3,   74,    2, 0x08 /* Private */,
      11,    2,   81,    2, 0x08 /* Private */,
      14,    4,   86,    2, 0x08 /* Private */,
      19,    1,   95,    2, 0x08 /* Private */,
      21,    1,   98,    2, 0x08 /* Private */,
      23,    0,  101,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString,    8,    9,   10,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 12,    8,   13,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 16, QMetaType::Int, QMetaType::QString,   15,   13,   17,   18,
    QMetaType::Void, 0x80000000 | 20,   18,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void,

       0        // eod
};

void macrosip::MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onAccountSettings(); break;
        case 1: _t->onSettings(); break;
        case 2: _t->onAbout(); break;
        case 3: _t->onQuit(); break;
        case 4: _t->onSipInitialized(); break;
        case 5: _t->onIncomingCall((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 6: _t->onCallStateChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< CallState(*)>(_a[2]))); break;
        case 7: _t->onRegistrationStateChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< RegistrationState(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 8: _t->onTrayActivated((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 9: _t->onCallRequested((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->onHangupRequested(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject macrosip::MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_macrosip__MainWindow.data,
    qt_meta_data_macrosip__MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *macrosip::MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *macrosip::MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_macrosip__MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int macrosip::MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
