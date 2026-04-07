/****************************************************************************
** Meta object code from reading C++ file 'SipManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/sip/SipManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SipManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_macrosip__SipManager_t {
    QByteArrayData data[30];
    char stringdata0[355];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_macrosip__SipManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_macrosip__SipManager_t qt_meta_stringdata_macrosip__SipManager = {
    {
QT_MOC_LITERAL(0, 0, 20), // "macrosip::SipManager"
QT_MOC_LITERAL(1, 21, 11), // "initialized"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 16), // "shutdownComplete"
QT_MOC_LITERAL(4, 51, 12), // "incomingCall"
QT_MOC_LITERAL(5, 64, 6), // "callId"
QT_MOC_LITERAL(6, 71, 4), // "from"
QT_MOC_LITERAL(7, 76, 4), // "name"
QT_MOC_LITERAL(8, 81, 16), // "callStateChanged"
QT_MOC_LITERAL(9, 98, 9), // "CallState"
QT_MOC_LITERAL(10, 108, 5), // "state"
QT_MOC_LITERAL(11, 114, 21), // "callMediaStateChanged"
QT_MOC_LITERAL(12, 136, 11), // "MediaStatus"
QT_MOC_LITERAL(13, 148, 6), // "status"
QT_MOC_LITERAL(14, 155, 24), // "registrationStateChanged"
QT_MOC_LITERAL(15, 180, 9), // "accountId"
QT_MOC_LITERAL(16, 190, 17), // "RegistrationState"
QT_MOC_LITERAL(17, 208, 4), // "code"
QT_MOC_LITERAL(18, 213, 6), // "reason"
QT_MOC_LITERAL(19, 220, 17), // "buddyStateChanged"
QT_MOC_LITERAL(20, 238, 3), // "uri"
QT_MOC_LITERAL(21, 242, 14), // "PresenceStatus"
QT_MOC_LITERAL(22, 257, 15), // "messageReceived"
QT_MOC_LITERAL(23, 273, 2), // "to"
QT_MOC_LITERAL(24, 276, 4), // "body"
QT_MOC_LITERAL(25, 281, 13), // "messageStatus"
QT_MOC_LITERAL(26, 295, 15), // "mwiNotification"
QT_MOC_LITERAL(27, 311, 11), // "newMessages"
QT_MOC_LITERAL(28, 323, 11), // "oldMessages"
QT_MOC_LITERAL(29, 335, 19) // "audioDevicesChanged"

    },
    "macrosip::SipManager\0initialized\0\0"
    "shutdownComplete\0incomingCall\0callId\0"
    "from\0name\0callStateChanged\0CallState\0"
    "state\0callMediaStateChanged\0MediaStatus\0"
    "status\0registrationStateChanged\0"
    "accountId\0RegistrationState\0code\0"
    "reason\0buddyStateChanged\0uri\0"
    "PresenceStatus\0messageReceived\0to\0"
    "body\0messageStatus\0mwiNotification\0"
    "newMessages\0oldMessages\0audioDevicesChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_macrosip__SipManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    0,   70,    2, 0x06 /* Public */,
       4,    3,   71,    2, 0x06 /* Public */,
       8,    2,   78,    2, 0x06 /* Public */,
      11,    2,   83,    2, 0x06 /* Public */,
      14,    4,   88,    2, 0x06 /* Public */,
      19,    2,   97,    2, 0x06 /* Public */,
      22,    3,  102,    2, 0x06 /* Public */,
      25,    2,  109,    2, 0x06 /* Public */,
      26,    3,  114,    2, 0x06 /* Public */,
      29,    0,  121,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString,    5,    6,    7,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 9,    5,   10,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 12,    5,   13,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 16, QMetaType::Int, QMetaType::QString,   15,   10,   17,   18,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 21,   20,   13,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    6,   23,   24,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   23,   13,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   15,   27,   28,
    QMetaType::Void,

       0        // eod
};

void macrosip::SipManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SipManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->initialized(); break;
        case 1: _t->shutdownComplete(); break;
        case 2: _t->incomingCall((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 3: _t->callStateChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< CallState(*)>(_a[2]))); break;
        case 4: _t->callMediaStateChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< MediaStatus(*)>(_a[2]))); break;
        case 5: _t->registrationStateChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< RegistrationState(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 6: _t->buddyStateChanged((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< PresenceStatus(*)>(_a[2]))); break;
        case 7: _t->messageReceived((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 8: _t->messageStatus((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->mwiNotification((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 10: _t->audioDevicesChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SipManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SipManager::initialized)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SipManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SipManager::shutdownComplete)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SipManager::*)(int , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SipManager::incomingCall)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SipManager::*)(int , CallState );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SipManager::callStateChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SipManager::*)(int , MediaStatus );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SipManager::callMediaStateChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (SipManager::*)(int , RegistrationState , int , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SipManager::registrationStateChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (SipManager::*)(const QString & , PresenceStatus );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SipManager::buddyStateChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (SipManager::*)(const QString & , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SipManager::messageReceived)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (SipManager::*)(const QString & , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SipManager::messageStatus)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (SipManager::*)(int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SipManager::mwiNotification)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (SipManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SipManager::audioDevicesChanged)) {
                *result = 10;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject macrosip::SipManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_macrosip__SipManager.data,
    qt_meta_data_macrosip__SipManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *macrosip::SipManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *macrosip::SipManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_macrosip__SipManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int macrosip::SipManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void macrosip::SipManager::initialized()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void macrosip::SipManager::shutdownComplete()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void macrosip::SipManager::incomingCall(int _t1, const QString & _t2, const QString & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void macrosip::SipManager::callStateChanged(int _t1, CallState _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void macrosip::SipManager::callMediaStateChanged(int _t1, MediaStatus _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void macrosip::SipManager::registrationStateChanged(int _t1, RegistrationState _t2, int _t3, const QString & _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void macrosip::SipManager::buddyStateChanged(const QString & _t1, PresenceStatus _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void macrosip::SipManager::messageReceived(const QString & _t1, const QString & _t2, const QString & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void macrosip::SipManager::messageStatus(const QString & _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void macrosip::SipManager::mwiNotification(int _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void macrosip::SipManager::audioDevicesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
