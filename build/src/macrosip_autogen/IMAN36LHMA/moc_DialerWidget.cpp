/****************************************************************************
** Meta object code from reading C++ file 'DialerWidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/widgets/DialerWidget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DialerWidget.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_macrosip__DialerWidget_t {
    uint offsetsAndSizes[20];
    char stringdata0[23];
    char stringdata1[14];
    char stringdata2[1];
    char stringdata3[7];
    char stringdata4[16];
    char stringdata5[12];
    char stringdata6[6];
    char stringdata7[15];
    char stringdata8[14];
    char stringdata9[16];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_macrosip__DialerWidget_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_macrosip__DialerWidget_t qt_meta_stringdata_macrosip__DialerWidget = {
    {
        QT_MOC_LITERAL(0, 22),  // "macrosip::DialerWidget"
        QT_MOC_LITERAL(23, 13),  // "callRequested"
        QT_MOC_LITERAL(37, 0),  // ""
        QT_MOC_LITERAL(38, 6),  // "number"
        QT_MOC_LITERAL(45, 15),  // "hangupRequested"
        QT_MOC_LITERAL(61, 11),  // "dtmfPressed"
        QT_MOC_LITERAL(73, 5),  // "digit"
        QT_MOC_LITERAL(79, 14),  // "onDigitClicked"
        QT_MOC_LITERAL(94, 13),  // "onCallClicked"
        QT_MOC_LITERAL(108, 15)   // "onHangupClicked"
    },
    "macrosip::DialerWidget",
    "callRequested",
    "",
    "number",
    "hangupRequested",
    "dtmfPressed",
    "digit",
    "onDigitClicked",
    "onCallClicked",
    "onHangupClicked"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_macrosip__DialerWidget[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   50,    2, 0x06,    1 /* Public */,
       4,    0,   53,    2, 0x06,    3 /* Public */,
       5,    1,   54,    2, 0x06,    4 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       7,    0,   57,    2, 0x08,    6 /* Private */,
       8,    0,   58,    2, 0x08,    7 /* Private */,
       9,    0,   59,    2, 0x08,    8 /* Private */,

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

Q_CONSTINIT const QMetaObject macrosip::DialerWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_macrosip__DialerWidget.offsetsAndSizes,
    qt_meta_data_macrosip__DialerWidget,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_macrosip__DialerWidget_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<DialerWidget, std::true_type>,
        // method 'callRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'hangupRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'dtmfPressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onDigitClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onCallClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onHangupClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void macrosip::DialerWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DialerWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->callRequested((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->hangupRequested(); break;
        case 2: _t->dtmfPressed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->onDigitClicked(); break;
        case 4: _t->onCallClicked(); break;
        case 5: _t->onHangupClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DialerWidget::*)(const QString & );
            if (_t _q_method = &DialerWidget::callRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DialerWidget::*)();
            if (_t _q_method = &DialerWidget::hangupRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DialerWidget::*)(const QString & );
            if (_t _q_method = &DialerWidget::dtmfPressed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
}

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
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
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
