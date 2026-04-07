/****************************************************************************
** Meta object code from reading C++ file 'ContactsWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/widgets/ContactsWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ContactsWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_macrosip__ContactsWidget_t {
    QByteArrayData data[17];
    char stringdata0[205];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_macrosip__ContactsWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_macrosip__ContactsWidget_t qt_meta_stringdata_macrosip__ContactsWidget = {
    {
QT_MOC_LITERAL(0, 0, 24), // "macrosip::ContactsWidget"
QT_MOC_LITERAL(1, 25, 15), // "contactSelected"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 17), // "macrosip::Contact"
QT_MOC_LITERAL(4, 60, 7), // "contact"
QT_MOC_LITERAL(5, 68, 11), // "callContact"
QT_MOC_LITERAL(6, 80, 6), // "number"
QT_MOC_LITERAL(7, 87, 11), // "editContact"
QT_MOC_LITERAL(8, 99, 13), // "deleteContact"
QT_MOC_LITERAL(9, 113, 19), // "onSearchTextChanged"
QT_MOC_LITERAL(10, 133, 4), // "text"
QT_MOC_LITERAL(11, 138, 19), // "onItemDoubleClicked"
QT_MOC_LITERAL(12, 158, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(13, 175, 4), // "item"
QT_MOC_LITERAL(14, 180, 6), // "column"
QT_MOC_LITERAL(15, 187, 13), // "onContextMenu"
QT_MOC_LITERAL(16, 201, 3) // "pos"

    },
    "macrosip::ContactsWidget\0contactSelected\0"
    "\0macrosip::Contact\0contact\0callContact\0"
    "number\0editContact\0deleteContact\0"
    "onSearchTextChanged\0text\0onItemDoubleClicked\0"
    "QTreeWidgetItem*\0item\0column\0onContextMenu\0"
    "pos"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_macrosip__ContactsWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       5,    1,   52,    2, 0x06 /* Public */,
       7,    1,   55,    2, 0x06 /* Public */,
       8,    1,   58,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   61,    2, 0x08 /* Private */,
      11,    2,   64,    2, 0x08 /* Private */,
      15,    1,   69,    2, 0x08 /* Private */,

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

void macrosip::ContactsWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ContactsWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->contactSelected((*reinterpret_cast< const macrosip::Contact(*)>(_a[1]))); break;
        case 1: _t->callContact((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->editContact((*reinterpret_cast< const macrosip::Contact(*)>(_a[1]))); break;
        case 3: _t->deleteContact((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->onSearchTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->onItemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->onContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ContactsWidget::*)(const macrosip::Contact & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContactsWidget::contactSelected)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ContactsWidget::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContactsWidget::callContact)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ContactsWidget::*)(const macrosip::Contact & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContactsWidget::editContact)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ContactsWidget::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContactsWidget::deleteContact)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject macrosip::ContactsWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_macrosip__ContactsWidget.data,
    qt_meta_data_macrosip__ContactsWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


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
            *reinterpret_cast<int*>(_a[0]) = -1;
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
