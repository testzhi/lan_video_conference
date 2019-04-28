/****************************************************************************
** Meta object code from reading C++ file 'department.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../videoConferencingClient/department.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'department.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Department_t {
    QByteArrayData data[17];
    char stringdata0[212];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Department_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Department_t qt_meta_stringdata_Department = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Department"
QT_MOC_LITERAL(1, 11, 21), // "departmentNameChanged"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 13), // "groupsChanged"
QT_MOC_LITERAL(4, 48, 22), // "employeesNumberChanged"
QT_MOC_LITERAL(5, 71, 14), // "departmentName"
QT_MOC_LITERAL(6, 86, 17), // "setDepartmentName"
QT_MOC_LITERAL(7, 104, 6), // "groups"
QT_MOC_LITERAL(8, 111, 23), // "QQmlListProperty<Group>"
QT_MOC_LITERAL(9, 135, 8), // "getGroup"
QT_MOC_LITERAL(10, 144, 6), // "Group*"
QT_MOC_LITERAL(11, 151, 1), // "i"
QT_MOC_LITERAL(12, 153, 10), // "groupCount"
QT_MOC_LITERAL(13, 164, 13), // "employeeCount"
QT_MOC_LITERAL(14, 178, 11), // "insertGroup"
QT_MOC_LITERAL(15, 190, 5), // "group"
QT_MOC_LITERAL(16, 196, 15) // "employeesNumber"

    },
    "Department\0departmentNameChanged\0\0"
    "groupsChanged\0employeesNumberChanged\0"
    "departmentName\0setDepartmentName\0"
    "groups\0QQmlListProperty<Group>\0getGroup\0"
    "Group*\0i\0groupCount\0employeeCount\0"
    "insertGroup\0group\0employeesNumber"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Department[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       3,   86, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    0,   70,    2, 0x06 /* Public */,
       4,    0,   71,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       5,    0,   72,    2, 0x02 /* Public */,
       6,    1,   73,    2, 0x02 /* Public */,
       7,    0,   76,    2, 0x02 /* Public */,
       9,    1,   77,    2, 0x02 /* Public */,
      12,    0,   80,    2, 0x02 /* Public */,
      13,    0,   81,    2, 0x02 /* Public */,
      14,    1,   82,    2, 0x02 /* Public */,
      16,    0,   85,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,    5,
    0x80000000 | 8,
    0x80000000 | 10, QMetaType::Int,   11,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void, 0x80000000 | 10,   15,
    QMetaType::QString,

 // properties: name, type, flags
       5, QMetaType::QString, 0x00495103,
      16, QMetaType::QString, 0x00495001,
       7, 0x80000000 | 8, 0x00495009,

 // properties: notify_signal_id
       0,
       2,
       1,

       0        // eod
};

void Department::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Department *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->departmentNameChanged(); break;
        case 1: _t->groupsChanged(); break;
        case 2: _t->employeesNumberChanged(); break;
        case 3: { QString _r = _t->departmentName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->setDepartmentName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: { QQmlListProperty<Group> _r = _t->groups();
            if (_a[0]) *reinterpret_cast< QQmlListProperty<Group>*>(_a[0]) = std::move(_r); }  break;
        case 6: { Group* _r = _t->getGroup((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< Group**>(_a[0]) = std::move(_r); }  break;
        case 7: { int _r = _t->groupCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 8: { int _r = _t->employeeCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->insertGroup((*reinterpret_cast< Group*(*)>(_a[1]))); break;
        case 10: { QString _r = _t->employeesNumber();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Group* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Department::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Department::departmentNameChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Department::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Department::groupsChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Department::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Department::employeesNumberChanged)) {
                *result = 2;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<Department *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->departmentName(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->employeesNumber(); break;
        case 2: *reinterpret_cast< QQmlListProperty<Group>*>(_v) = _t->groups(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<Department *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setDepartmentName(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject Department::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Department.data,
    qt_meta_data_Department,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Department::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Department::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Department.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Department::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Department::departmentNameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Department::groupsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Department::employeesNumberChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
