/****************************************************************************
** Meta object code from reading C++ file 'DialerWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/widgets/DialerWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DialerWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_macrosip__DialerWidget_t {
    QByteArrayData data[10];
    char stringdata0[124];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_macrosip__DialerWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_macrosip__DialerWidget_t qt_meta_stringdata_macrosip__DialerWidget = {
    {
QT_MOC_LITERAL(0, 0, 22), // "macrosip::DialerWidget"
QT_MOC_LITERAL(1, 23, 13), // "callRequested"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 6), // "number"
QT_MOC_LITERAL(4, 45, 15), // "hangupRequested"
QT_MOC_LITERAL(5, 61, 11), // "dtmfPressed"
QT_MOC_LITERAL(6, 73, 5), // "digit"
QT_MOC_LITERAL(7, 79, 14), // "onDigitClicked"
QT_MOC_LITERAL(8, 94, 13), // "onCallClicked"
QT_MOC_LITERAL(9, 108, 15) // "onHangupClicked"

    },
    "macrosip::DialerWidget\0callRequested\0"
    "\0number\0hangupRequested\0dtmfPressed\0"
    "digit\0onDigitClicked\0onCallClicked\0"
    "onHangupClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_macrosip__DialerWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    0,   47,    2, 0x06 /* Public */,
       5,    1,   48,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   51,    2, 0x08 /* Private */,
       8,    0,   52,    2, 0x08 /* Private */,
       9,    0,   53,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void macrosip::DialerWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DialerWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->callRequested((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->hangupRequested(); break;
        case 2: _t->dtmfPressed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->onDigitClicked(); break;
        case 4: _t->onCallClicked(); break;
        case 5: _t->onHangupClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DialerWidget::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DialerWidget::callRequested)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DialerWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DialerWidget::hangupRequested)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DialerWidget::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DialerWidget::dtmfPressed)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject macrosip::DialerWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_macrosip__DialerWidget.data,
    qt_meta_data_macrosip__DialerWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *macrosip::DialerWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *macrosip::DialerWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_macrosip__DialerWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int macrosip::DialerWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void macrosip::DialerWidget::callRequested(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void macrosip::DialerWidget::hangupRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void macrosip::DialerWidget::dtmfPressed(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
