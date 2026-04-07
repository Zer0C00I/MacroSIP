/****************************************************************************
** Meta object code from reading C++ file 'CallsWidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/widgets/CallsWidget.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CallsWidget.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_macrosip__CallsWidget_t {
    uint offsetsAndSizes[30];
    char stringdata0[22];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[21];
    char stringdata4[7];
    char stringdata5[7];
    char stringdata6[7];
    char stringdata7[16];
    char stringdata8[6];
    char stringdata9[20];
    char stringdata10[17];
    char stringdata11[5];
    char stringdata12[7];
    char stringdata13[14];
    char stringdata14[4];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_macrosip__CallsWidget_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_macrosip__CallsWidget_t qt_meta_stringdata_macrosip__CallsWidget = {
    {
        QT_MOC_LITERAL(0, 21),  // "macrosip::CallsWidget"
        QT_MOC_LITERAL(22, 12),  // "callSelected"
        QT_MOC_LITERAL(35, 0),  // ""
        QT_MOC_LITERAL(36, 20),  // "macrosip::CallRecord"
        QT_MOC_LITERAL(57, 6),  // "record"
        QT_MOC_LITERAL(64, 6),  // "redial"
        QT_MOC_LITERAL(71, 6),  // "number"
        QT_MOC_LITERAL(78, 15),  // "onFilterChanged"
        QT_MOC_LITERAL(94, 5),  // "index"
        QT_MOC_LITERAL(100, 19),  // "onItemDoubleClicked"
        QT_MOC_LITERAL(120, 16),  // "QTreeWidgetItem*"
        QT_MOC_LITERAL(137, 4),  // "item"
        QT_MOC_LITERAL(142, 6),  // "column"
        QT_MOC_LITERAL(149, 13),  // "onContextMenu"
        QT_MOC_LITERAL(163, 3)   // "pos"
    },
    "macrosip::CallsWidget",
    "callSelected",
    "",
    "macrosip::CallRecord",
    "record",
    "redial",
    "number",
    "onFilterChanged",
    "index",
    "onItemDoubleClicked",
    "QTreeWidgetItem*",
    "item",
    "column",
    "onContextMenu",
    "pos"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_macrosip__CallsWidget[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   44,    2, 0x06,    1 /* Public */,
       5,    1,   47,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       7,    1,   50,    2, 0x08,    5 /* Private */,
       9,    2,   53,    2, 0x08,    7 /* Private */,
      13,    1,   58,    2, 0x08,   10 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, 0x80000000 | 10, QMetaType::Int,   11,   12,
    QMetaType::Void, QMetaType::QPoint,   14,

       0        // eod
};

Q_CONSTINIT const QMetaObject macrosip::CallsWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_macrosip__CallsWidget.offsetsAndSizes,
    qt_meta_data_macrosip__CallsWidget,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_macrosip__CallsWidget_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<CallsWidget, std::true_type>,
        // method 'callSelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const macrosip::CallRecord &, std::false_type>,
        // method 'redial'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onFilterChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onItemDoubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QTreeWidgetItem *, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onContextMenu'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPoint &, std::false_type>
    >,
    nullptr
} };

void macrosip::CallsWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CallsWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->callSelected((*reinterpret_cast< std::add_pointer_t<macrosip::CallRecord>>(_a[1]))); break;
        case 1: _t->redial((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->onFilterChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->onItemDoubleClicked((*reinterpret_cast< std::add_pointer_t<QTreeWidgetItem*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 4: _t->onContextMenu((*reinterpret_cast< std::add_pointer_t<QPoint>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CallsWidget::*)(const macrosip::CallRecord & );
            if (_t _q_method = &CallsWidget::callSelected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CallsWidget::*)(const QString & );
            if (_t _q_method = &CallsWidget::redial; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *macrosip::CallsWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *macrosip::CallsWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_macrosip__CallsWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int macrosip::CallsWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void macrosip::CallsWidget::callSelected(const macrosip::CallRecord & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void macrosip::CallsWidget::redial(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
