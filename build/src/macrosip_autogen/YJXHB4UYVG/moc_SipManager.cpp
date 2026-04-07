/****************************************************************************
** Meta object code from reading C++ file 'SipManager.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/sip/SipManager.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SipManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_macrosip__SipManager_t {
    uint offsetsAndSizes[60];
    char stringdata0[21];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[17];
    char stringdata4[13];
    char stringdata5[7];
    char stringdata6[5];
    char stringdata7[5];
    char stringdata8[17];
    char stringdata9[10];
    char stringdata10[6];
    char stringdata11[22];
    char stringdata12[12];
    char stringdata13[7];
    char stringdata14[25];
    char stringdata15[10];
    char stringdata16[18];
    char stringdata17[5];
    char stringdata18[7];
    char stringdata19[18];
    char stringdata20[4];
    char stringdata21[15];
    char stringdata22[16];
    char stringdata23[3];
    char stringdata24[5];
    char stringdata25[14];
    char stringdata26[16];
    char stringdata27[12];
    char stringdata28[12];
    char stringdata29[20];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_macrosip__SipManager_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_macrosip__SipManager_t qt_meta_stringdata_macrosip__SipManager = {
    {
        QT_MOC_LITERAL(0, 20),  // "macrosip::SipManager"
        QT_MOC_LITERAL(21, 11),  // "initialized"
        QT_MOC_LITERAL(33, 0),  // ""
        QT_MOC_LITERAL(34, 16),  // "shutdownComplete"
        QT_MOC_LITERAL(51, 12),  // "incomingCall"
        QT_MOC_LITERAL(64, 6),  // "callId"
        QT_MOC_LITERAL(71, 4),  // "from"
        QT_MOC_LITERAL(76, 4),  // "name"
        QT_MOC_LITERAL(81, 16),  // "callStateChanged"
        QT_MOC_LITERAL(98, 9),  // "CallState"
        QT_MOC_LITERAL(108, 5),  // "state"
        QT_MOC_LITERAL(114, 21),  // "callMediaStateChanged"
        QT_MOC_LITERAL(136, 11),  // "MediaStatus"
        QT_MOC_LITERAL(148, 6),  // "status"
        QT_MOC_LITERAL(155, 24),  // "registrationStateChanged"
        QT_MOC_LITERAL(180, 9),  // "accountId"
        QT_MOC_LITERAL(190, 17),  // "RegistrationState"
        QT_MOC_LITERAL(208, 4),  // "code"
        QT_MOC_LITERAL(213, 6),  // "reason"
        QT_MOC_LITERAL(220, 17),  // "buddyStateChanged"
        QT_MOC_LITERAL(238, 3),  // "uri"
        QT_MOC_LITERAL(242, 14),  // "PresenceStatus"
        QT_MOC_LITERAL(257, 15),  // "messageReceived"
        QT_MOC_LITERAL(273, 2),  // "to"
        QT_MOC_LITERAL(276, 4),  // "body"
        QT_MOC_LITERAL(281, 13),  // "messageStatus"
        QT_MOC_LITERAL(295, 15),  // "mwiNotification"
        QT_MOC_LITERAL(311, 11),  // "newMessages"
        QT_MOC_LITERAL(323, 11),  // "oldMessages"
        QT_MOC_LITERAL(335, 19)   // "audioDevicesChanged"
    },
    "macrosip::SipManager",
    "initialized",
    "",
    "shutdownComplete",
    "incomingCall",
    "callId",
    "from",
    "name",
    "callStateChanged",
    "CallState",
    "state",
    "callMediaStateChanged",
    "MediaStatus",
    "status",
    "registrationStateChanged",
    "accountId",
    "RegistrationState",
    "code",
    "reason",
    "buddyStateChanged",
    "uri",
    "PresenceStatus",
    "messageReceived",
    "to",
    "body",
    "messageStatus",
    "mwiNotification",
    "newMessages",
    "oldMessages",
    "audioDevicesChanged"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_macrosip__SipManager[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   80,    2, 0x06,    1 /* Public */,
       3,    0,   81,    2, 0x06,    2 /* Public */,
       4,    3,   82,    2, 0x06,    3 /* Public */,
       8,    2,   89,    2, 0x06,    7 /* Public */,
      11,    2,   94,    2, 0x06,   10 /* Public */,
      14,    4,   99,    2, 0x06,   13 /* Public */,
      19,    2,  108,    2, 0x06,   18 /* Public */,
      22,    3,  113,    2, 0x06,   21 /* Public */,
      25,    2,  120,    2, 0x06,   25 /* Public */,
      26,    3,  125,    2, 0x06,   28 /* Public */,
      29,    0,  132,    2, 0x06,   32 /* Public */,

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

Q_CONSTINIT const QMetaObject macrosip::SipManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_macrosip__SipManager.offsetsAndSizes,
    qt_meta_data_macrosip__SipManager,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_macrosip__SipManager_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<SipManager, std::true_type>,
        // method 'initialized'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'shutdownComplete'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'incomingCall'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'callStateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<CallState, std::false_type>,
        // method 'callMediaStateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<MediaStatus, std::false_type>,
        // method 'registrationStateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<RegistrationState, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'buddyStateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<PresenceStatus, std::false_type>,
        // method 'messageReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'messageStatus'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'mwiNotification'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'audioDevicesChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void macrosip::SipManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SipManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->initialized(); break;
        case 1: _t->shutdownComplete(); break;
        case 2: _t->incomingCall((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 3: _t->callStateChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<CallState>>(_a[2]))); break;
        case 4: _t->callMediaStateChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<MediaStatus>>(_a[2]))); break;
        case 5: _t->registrationStateChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<RegistrationState>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4]))); break;
        case 6: _t->buddyStateChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<PresenceStatus>>(_a[2]))); break;
        case 7: _t->messageReceived((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 8: _t->messageStatus((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 9: _t->mwiNotification((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 10: _t->audioDevicesChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SipManager::*)();
            if (_t _q_method = &SipManager::initialized; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SipManager::*)();
            if (_t _q_method = &SipManager::shutdownComplete; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SipManager::*)(int , const QString & , const QString & );
            if (_t _q_method = &SipManager::incomingCall; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SipManager::*)(int , CallState );
            if (_t _q_method = &SipManager::callStateChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SipManager::*)(int , MediaStatus );
            if (_t _q_method = &SipManager::callMediaStateChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (SipManager::*)(int , RegistrationState , int , const QString & );
            if (_t _q_method = &SipManager::registrationStateChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (SipManager::*)(const QString & , PresenceStatus );
            if (_t _q_method = &SipManager::buddyStateChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (SipManager::*)(const QString & , const QString & , const QString & );
            if (_t _q_method = &SipManager::messageReceived; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (SipManager::*)(const QString & , int );
            if (_t _q_method = &SipManager::messageStatus; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (SipManager::*)(int , int , int );
            if (_t _q_method = &SipManager::mwiNotification; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (SipManager::*)();
            if (_t _q_method = &SipManager::audioDevicesChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 10;
                return;
            }
        }
    }
}

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
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
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
