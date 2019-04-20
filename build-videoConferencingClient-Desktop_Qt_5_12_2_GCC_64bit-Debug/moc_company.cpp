/****************************************************************************
** Meta object code from reading C++ file 'company.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../videoConferencingClient/company.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'company.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Company_t {
    QByteArrayData data[17];
    char stringdata0[242];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Company_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Company_t qt_meta_stringdata_Company = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Company"
QT_MOC_LITERAL(1, 8, 15), // "DefaultProperty"
QT_MOC_LITERAL(2, 24, 11), // "departments"
QT_MOC_LITERAL(3, 36, 18), // "companyNameChanged"
QT_MOC_LITERAL(4, 55, 0), // ""
QT_MOC_LITERAL(5, 56, 18), // "departmentsChanged"
QT_MOC_LITERAL(6, 75, 22), // "employeesNumberChanged"
QT_MOC_LITERAL(7, 98, 11), // "companyName"
QT_MOC_LITERAL(8, 110, 14), // "setCompanyName"
QT_MOC_LITERAL(9, 125, 28), // "QQmlListProperty<Department>"
QT_MOC_LITERAL(10, 154, 13), // "getDepartment"
QT_MOC_LITERAL(11, 168, 11), // "Department*"
QT_MOC_LITERAL(12, 180, 1), // "i"
QT_MOC_LITERAL(13, 182, 15), // "departmentCount"
QT_MOC_LITERAL(14, 198, 16), // "insertDepartment"
QT_MOC_LITERAL(15, 215, 10), // "department"
QT_MOC_LITERAL(16, 226, 15) // "employeesNumber"

    },
    "Company\0DefaultProperty\0departments\0"
    "companyNameChanged\0\0departmentsChanged\0"
    "employeesNumberChanged\0companyName\0"
    "setCompanyName\0QQmlListProperty<Department>\0"
    "getDepartment\0Department*\0i\0departmentCount\0"
    "insertDepartment\0department\0employeesNumber"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Company[] = {

 // content:
       8,       // revision
       0,       // classname
       1,   14, // classinfo
       9,   16, // methods
       3,   76, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // classinfo: key, value
       1,    2,

 // signals: name, argc, parameters, tag, flags
       3,    0,   61,    4, 0x06 /* Public */,
       5,    0,   62,    4, 0x06 /* Public */,
       6,    0,   63,    4, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       7,    0,   64,    4, 0x02 /* Public */,
       8,    1,   65,    4, 0x02 /* Public */,
       2,    0,   68,    4, 0x02 /* Public */,
      10,    1,   69,    4, 0x02 /* Public */,
      13,    0,   72,    4, 0x02 /* Public */,
      14,    1,   73,    4, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,    7,
    0x80000000 | 9,
    0x80000000 | 11, QMetaType::Int,   12,
    QMetaType::Int,
    QMetaType::Void, 0x80000000 | 11,   15,

 // properties: name, type, flags
       7, QMetaType::QString, 0x00495103,
      16, QMetaType::QString, 0x00495001,
       2, 0x80000000 | 9, 0x00495009,

 // properties: notify_signal_id
       0,
       2,
       1,

       0        // eod
};

void Company::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Company *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->companyNameChanged(); break;
        case 1: _t->departmentsChanged(); break;
        case 2: _t->employeesNumberChanged(); break;
        case 3: { QString _r = _t->companyName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->setCompanyName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: { QQmlListProperty<Department> _r = _t->departments();
            if (_a[0]) *reinterpret_cast< QQmlListProperty<Department>*>(_a[0]) = std::move(_r); }  break;
        case 6: { Department* _r = _t->getDepartment((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< Department**>(_a[0]) = std::move(_r); }  break;
        case 7: { int _r = _t->departmentCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->insertDepartment((*reinterpret_cast< Department*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Department* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Company::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Company::companyNameChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Company::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Company::departmentsChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Company::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Company::employeesNumberChanged)) {
                *result = 2;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<Company *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->companyName(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->employeesNumber(); break;
        case 2: *reinterpret_cast< QQmlListProperty<Department>*>(_v) = _t->departments(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<Company *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setCompanyName(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject Company::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Company.data,
    qt_meta_data_Company,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Company::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Company::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Company.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Company::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
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
void Company::companyNameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Company::departmentsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Company::employeesNumberChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
