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
struct qt_meta_stringdata_ConciseEmployee_t {
    QByteArrayData data[6];
    char stringdata0[63];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConciseEmployee_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConciseEmployee_t qt_meta_stringdata_ConciseEmployee = {
    {
QT_MOC_LITERAL(0, 0, 15), // "ConciseEmployee"
QT_MOC_LITERAL(1, 16, 13), // "userIDChanged"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 15), // "realNameChanged"
QT_MOC_LITERAL(4, 47, 6), // "userID"
QT_MOC_LITERAL(5, 54, 8) // "realName"

    },
    "ConciseEmployee\0userIDChanged\0\0"
    "realNameChanged\0userID\0realName"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConciseEmployee[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       2,   26, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,
       3,    0,   25,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       4, QMetaType::QString, 0x00495103,
       5, QMetaType::QString, 0x00495103,

 // properties: notify_signal_id
       0,
       1,

       0        // eod
};

void ConciseEmployee::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ConciseEmployee *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->userIDChanged(); break;
        case 1: _t->realNameChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ConciseEmployee::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConciseEmployee::userIDChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ConciseEmployee::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConciseEmployee::realNameChanged)) {
                *result = 1;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<ConciseEmployee *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->userID(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->realName(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<ConciseEmployee *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setUserID(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setRealName(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject ConciseEmployee::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_ConciseEmployee.data,
    qt_meta_data_ConciseEmployee,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ConciseEmployee::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConciseEmployee::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ConciseEmployee.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ConciseEmployee::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
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
void ConciseEmployee::userIDChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ConciseEmployee::realNameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
struct qt_meta_stringdata_Group_t {
    QByteArrayData data[19];
    char stringdata0[295];
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
QT_MOC_LITERAL(5, 50, 22), // "conciseEmployeeChanged"
QT_MOC_LITERAL(6, 73, 22), // "employeesNumberChanged"
QT_MOC_LITERAL(7, 96, 9), // "groupName"
QT_MOC_LITERAL(8, 106, 12), // "setGroupName"
QT_MOC_LITERAL(9, 119, 18), // "getConciseEmployee"
QT_MOC_LITERAL(10, 138, 16), // "ConciseEmployee*"
QT_MOC_LITERAL(11, 155, 1), // "i"
QT_MOC_LITERAL(12, 157, 20), // "conciseEmployeeCount"
QT_MOC_LITERAL(13, 178, 21), // "insertConciseEmployee"
QT_MOC_LITERAL(14, 200, 8), // "employee"
QT_MOC_LITERAL(15, 209, 15), // "employeesNumber"
QT_MOC_LITERAL(16, 225, 18), // "setEmployeesNumber"
QT_MOC_LITERAL(17, 244, 16), // "conciseEmployees"
QT_MOC_LITERAL(18, 261, 33) // "QQmlListProperty<ConciseEmplo..."

    },
    "Group\0DefaultProperty\0employees\0"
    "groupNameChanged\0\0conciseEmployeeChanged\0"
    "employeesNumberChanged\0groupName\0"
    "setGroupName\0getConciseEmployee\0"
    "ConciseEmployee*\0i\0conciseEmployeeCount\0"
    "insertConciseEmployee\0employee\0"
    "employeesNumber\0setEmployeesNumber\0"
    "conciseEmployees\0QQmlListProperty<ConciseEmployee>"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Group[] = {

 // content:
       8,       // revision
       0,       // classname
       1,   14, // classinfo
      11,   16, // methods
       3,   90, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // classinfo: key, value
       1,    2,

 // signals: name, argc, parameters, tag, flags
       3,    0,   71,    4, 0x06 /* Public */,
       5,    0,   72,    4, 0x06 /* Public */,
       6,    0,   73,    4, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       7,    0,   74,    4, 0x02 /* Public */,
       8,    1,   75,    4, 0x02 /* Public */,
       9,    1,   78,    4, 0x02 /* Public */,
      12,    0,   81,    4, 0x02 /* Public */,
      13,    1,   82,    4, 0x02 /* Public */,
      15,    0,   85,    4, 0x02 /* Public */,
      16,    1,   86,    4, 0x02 /* Public */,
      17,    0,   89,    4, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,    7,
    0x80000000 | 10, QMetaType::Int,   11,
    QMetaType::Int,
    QMetaType::Void, 0x80000000 | 10,   14,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   15,
    0x80000000 | 18,

 // properties: name, type, flags
       7, QMetaType::QString, 0x00495103,
      15, QMetaType::Int, 0x00495001,
      17, 0x80000000 | 18, 0x00495009,

 // properties: notify_signal_id
       0,
       2,
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
        case 1: _t->conciseEmployeeChanged(); break;
        case 2: _t->employeesNumberChanged(); break;
        case 3: { QString _r = _t->groupName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->setGroupName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: { ConciseEmployee* _r = _t->getConciseEmployee((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< ConciseEmployee**>(_a[0]) = std::move(_r); }  break;
        case 6: { int _r = _t->conciseEmployeeCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->insertConciseEmployee((*reinterpret_cast< ConciseEmployee*(*)>(_a[1]))); break;
        case 8: { int _r = _t->employeesNumber();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->setEmployeesNumber((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: { QQmlListProperty<ConciseEmployee> _r = _t->conciseEmployees();
            if (_a[0]) *reinterpret_cast< QQmlListProperty<ConciseEmployee>*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ConciseEmployee* >(); break;
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
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Group::conciseEmployeeChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Group::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Group::employeesNumberChanged)) {
                *result = 2;
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
        case 1: *reinterpret_cast< int*>(_v) = _t->employeesNumber(); break;
        case 2: *reinterpret_cast< QQmlListProperty<ConciseEmployee>*>(_v) = _t->conciseEmployees(); break;
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
void Group::groupNameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Group::conciseEmployeeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Group::employeesNumberChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
