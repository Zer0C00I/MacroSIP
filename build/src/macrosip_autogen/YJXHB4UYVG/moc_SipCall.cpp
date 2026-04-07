/****************************************************************************
** Meta object code from reading C++ file 'SipCall.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/sip/SipCall.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SipCall.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_macrosip__SipCall_t {
    QByteArrayData data[13];
    char stringdata0[148];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_macrosip__SipCall_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_macrosip__SipCall_t qt_meta_stringdata_macrosip__SipCall = {
    {
QT_MOC_LITERAL(0, 0, 17), // "macrosip::SipCall"
QT_MOC_LITERAL(1, 18, 12), // "stateChanged"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 9), // "CallState"
QT_MOC_LITERAL(4, 42, 8), // "newState"
QT_MOC_LITERAL(5, 51, 18), // "mediaStatusChanged"
QT_MOC_LITERAL(6, 70, 11), // "MediaStatus"
QT_MOC_LITERAL(7, 82, 6), // "status"
QT_MOC_LITERAL(8, 89, 12), // "dtmfReceived"
QT_MOC_LITERAL(9, 102, 5), // "digit"
QT_MOC_LITERAL(10, 108, 21), // "transferStatusChanged"
QT_MOC_LITERAL(11, 130, 10), // "statusCode"
QT_MOC_LITERAL(12, 141, 6) // "reason"

    },
    "macrosip::SipCall\0stateChanged\0\0"
    "CallState\0newState\0mediaStatusChanged\0"
    "MediaStatus\0status\0dtmfReceived\0digit\0"
    "transferStatusChanged\0statusCode\0"
    "reason"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_macrosip__SipCall[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       5,    1,   37,    2, 0x06 /* Public */,
       8,    1,   40,    2, 0x06 /* Public */,
      10,    2,   43,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   11,   12,

       0        // eod
};

void macrosip::SipCall::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SipCall *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->stateChanged((*reinterpret_cast< CallState(*)>(_a[1]))); break;
        case 1: _t->mediaStatusChanged((*reinterpret_cast< MediaStatus(*)>(_a[1]))); break;
        case 2: _t->dtmfReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->transferStatusChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SipCall::*)(CallState );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SipCall::stateChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SipCall::*)(MediaStatus );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SipCall::mediaStatusChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SipCall::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SipCall::dtmfReceived)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SipCall::*)(int , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SipCall::transferStatusChanged)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject macrosip::SipCall::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_macrosip__SipCall.data,
    qt_meta_data_macrosip__SipCall,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *macrosip::SipCall::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *macrosip::SipCall::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_macrosip__SipCall.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int macrosip::SipCall::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void macrosip::SipCall::stateChanged(CallState _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void macrosip::SipCall::mediaStatusChanged(MediaStatus _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void macrosip::SipCall::dtmfReceived(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void macrosip::SipCall::transferStatusChanged(int _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
