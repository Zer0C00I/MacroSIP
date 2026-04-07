/****************************************************************************
** Meta object code from reading C++ file 'ContactsWidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/widgets/ContactsWidget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ContactsWidget.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_macrosip__ContactsWidget_t {
    uint offsetsAndSizes[34];
    char stringdata0[25];
    char stringdata1[16];
    char stringdata2[1];
    char stringdata3[18];
    char stringdata4[8];
    char stringdata5[12];
    char stringdata6[7];
    char stringdata7[12];
    char stringdata8[14];
    char stringdata9[20];
    char stringdata10[5];
    char stringdata11[20];
    char stringdata12[17];
    char stringdata13[5];
    char stringdata14[7];
    char stringdata15[14];
    char stringdata16[4];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_macrosip__ContactsWidget_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_macrosip__ContactsWidget_t qt_meta_stringdata_macrosip__ContactsWidget = {
    {
        QT_MOC_LITERAL(0, 24),  // "macrosip::ContactsWidget"
        QT_MOC_LITERAL(25, 15),  // "contactSelected"
        QT_MOC_LITERAL(41, 0),  // ""
        QT_MOC_LITERAL(42, 17),  // "macrosip::Contact"
        QT_MOC_LITERAL(60, 7),  // "contact"
        QT_MOC_LITERAL(68, 11),  // "callContact"
        QT_MOC_LITERAL(80, 6),  // "number"
        QT_MOC_LITERAL(87, 11),  // "editContact"
        QT_MOC_LITERAL(99, 13),  // "deleteContact"
        QT_MOC_LITERAL(113, 19),  // "onSearchTextChanged"
        QT_MOC_LITERAL(133, 4),  // "text"
        QT_MOC_LITERAL(138, 19),  // "onItemDoubleClicked"
        QT_MOC_LITERAL(158, 16),  // "QTreeWidgetItem*"
        QT_MOC_LITERAL(175, 4),  // "item"
        QT_MOC_LITERAL(180, 6),  // "column"
        QT_MOC_LITERAL(187, 13),  // "onContextMenu"
        QT_MOC_LITERAL(201, 3)   // "pos"
    },
    "macrosip::ContactsWidget",
    "contactSelected",
    "",
    "macrosip::Contact",
    "contact",
    "callContact",
    "number",
    "editContact",
    "deleteContact",
    "onSearchTextChanged",
    "text",
    "onItemDoubleClicked",
    "QTreeWidgetItem*",
    "item",
    "column",
    "onContextMenu",
    "pos"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_macrosip__ContactsWidget[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   56,    2, 0x06,    1 /* Public */,
       5,    1,   59,    2, 0x06,    3 /* Public */,
       7,    1,   62,    2, 0x06,    5 /* Public */,
       8,    1,   65,    2, 0x06,    7 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       9,    1,   68,    2, 0x08,    9 /* Private */,
      11,    2,   71,    2, 0x08,   11 /* Private */,
      15,    1,   76,    2, 0x08,   14 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, 0x80000000 | 12, QMetaType::Int,   13,   14,
    QMetaType::Void, QMetaType::QPoint,   16,

       0        // eod
};

Q_CONSTINIT const QMetaObject macrosip::ContactsWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_macrosip__ContactsWidget.offsetsAndSizes,
    qt_meta_data_macrosip__ContactsWidget,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_macrosip__ContactsWidget_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ContactsWidget, std::true_type>,
        // method 'contactSelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const macrosip::Contact &, std::false_type>,
        // method 'callContact'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'editContact'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const macrosip::Contact &, std::false_type>,
        // method 'deleteContact'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onSearchTextChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
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

void macrosip::ContactsWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ContactsWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->contactSelected((*reinterpret_cast< std::add_pointer_t<macrosip::Contact>>(_a[1]))); break;
        case 1: _t->callContact((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->editContact((*reinterpret_cast< std::add_pointer_t<macrosip::Contact>>(_a[1]))); break;
        case 3: _t->deleteContact((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->onSearchTextChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->onItemDoubleClicked((*reinterpret_cast< std::add_pointer_t<QTreeWidgetItem*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 6: _t->onContextMenu((*reinterpret_cast< std::add_pointer_t<QPoint>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ContactsWidget::*)(const macrosip::Contact & );
            if (_t _q_method = &ContactsWidget::contactSelected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ContactsWidget::*)(const QString & );
            if (_t _q_method = &ContactsWidget::callContact; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ContactsWidget::*)(const macrosip::Contact & );
            if (_t _q_method = &ContactsWidget::editContact; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ContactsWidget::*)(const QString & );
            if (_t _q_method = &ContactsWidget::deleteContact; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject *macrosip::ContactsWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *macrosip::ContactsWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_macrosip__ContactsWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int macrosip::ContactsWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void macrosip::ContactsWidget::contactSelected(const macrosip::Contact & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void macrosip::ContactsWidget::callContact(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void macrosip::ContactsWidget::editContact(const macrosip::Contact & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void macrosip::ContactsWidget::deleteContact(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
