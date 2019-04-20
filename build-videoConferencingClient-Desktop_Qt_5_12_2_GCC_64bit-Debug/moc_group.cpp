/****************************************************************************
** Meta object code from reading C++ file 'group.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../videoConferencingClient/group.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'group.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Group_t {
    QByteArrayData data[15];
    char stringdata0[178];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Group_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Group_t qt_meta_stringdata_Group = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Group"
QT_MOC_LITERAL(1, 6, 15), // "DefaultProperty"
QT_MOC_LITERAL(2, 22, 9), // "employees"
QT_MOC_LITERAL(3, 32, 16), // "groupNameChanged"
QT_MOC_LITERAL(4, 49, 0), // ""
QT_MOC_LITERAL(5, 50, 16), // "employeesChanged"
QT_MOC_LITERAL(6, 67, 9), // "groupName"
QT_MOC_LITERAL(7, 77, 12), // "setGroupName"
QT_MOC_LITERAL(8, 90, 26), // "QQmlListProperty<Employee>"
QT_MOC_LITERAL(9, 117, 11), // "getEmployee"
QT_MOC_LITERAL(10, 129, 9), // "Employee*"
QT_MOC_LITERAL(11, 139, 1), // "i"
QT_MOC_LITERAL(12, 141, 13), // "employeeCount"
QT_MOC_LITERAL(13, 155, 13), // "insertEmplyee"
QT_MOC_LITERAL(14, 169, 8) // "employee"

    },
    "Group\0DefaultProperty\0employees\0"
    "groupNameChanged\0\0employeesChanged\0"
    "groupName\0setGroupName\0"
    "QQmlListProperty<Employee>\0getEmployee\0"
    "Employee*\0i\0employeeCount\0insertEmplyee\0"
    "employee"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Group[] = {

 // content:
       8,       // revision
       0,       // classname
       1,   14, // classinfo
       8,   16, // methods
       2,   70, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // classinfo: key, value
       1,    2,

 // signals: name, argc, parameters, tag, flags
       3,    0,   56,    4, 0x06 /* Public */,
       5,    0,   57,    4, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       6,    0,   58,    4, 0x02 /* Public */,
       7,    1,   59,    4, 0x02 /* Public */,
       2,    0,   62,    4, 0x02 /* Public */,
       9,    1,   63,    4, 0x02 /* Public */,
      12,    0,   66,    4, 0x02 /* Public */,
      13,    1,   67,    4, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,    6,
    0x80000000 | 8,
    0x80000000 | 10, QMetaType::Int,   11,
    QMetaType::Int,
    QMetaType::Void, 0x80000000 | 10,   14,

 // properties: name, type, flags
       6, QMetaType::QString, 0x00495103,
       2, 0x80000000 | 8, 0x00495009,

 // properties: notify_signal_id
       0,
       1,

       0        // eod
};

void Group::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Group *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->groupNameChanged(); break;
        case 1: _t->employeesChanged(); break;
        case 2: { QString _r = _t->groupName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->setGroupName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: { QQmlListProperty<Employee> _r = _t->employees();
            if (_a[0]) *reinterpret_cast< QQmlListProperty<Employee>*>(_a[0]) = std::move(_r); }  break;
        case 5: { Employee* _r = _t->getEmployee((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< Employee**>(_a[0]) = std::move(_r); }  break;
        case 6: { int _r = _t->employeeCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->insertEmplyee((*reinterpret_cast< Employee*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Employee* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Group::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Group::groupNameChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Group::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Group::employeesChanged)) {
                *result = 1;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<Group *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->groupName(); break;
        case 1: *reinterpret_cast< QQmlListProperty<Employee>*>(_v) = _t->employees(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<Group *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setGroupName(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject Group::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Group.data,
    qt_meta_data_Group,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Group::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Group::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Group.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Group::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Group::groupNameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Group::employeesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
