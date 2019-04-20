/****************************************************************************
** Meta object code from reading C++ file 'conferenceui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../videoConferencingClient/conferenceui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'conferenceui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ConferenceUI_t {
    QByteArrayData data[18];
    char stringdata0[182];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConferenceUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConferenceUI_t qt_meta_stringdata_ConferenceUI = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ConferenceUI"
QT_MOC_LITERAL(1, 13, 14), // "companyChanged"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 15), // "employeeChanged"
QT_MOC_LITERAL(4, 45, 19), // "getLoginInformation"
QT_MOC_LITERAL(5, 65, 7), // "account"
QT_MOC_LITERAL(6, 73, 8), // "password"
QT_MOC_LITERAL(7, 82, 22), // "getRegisterInformation"
QT_MOC_LITERAL(8, 105, 6), // "avator"
QT_MOC_LITERAL(9, 112, 4), // "name"
QT_MOC_LITERAL(10, 117, 7), // "company"
QT_MOC_LITERAL(11, 125, 10), // "department"
QT_MOC_LITERAL(12, 136, 5), // "group"
QT_MOC_LITERAL(13, 142, 5), // "phone"
QT_MOC_LITERAL(14, 148, 5), // "email"
QT_MOC_LITERAL(15, 154, 8), // "Company*"
QT_MOC_LITERAL(16, 163, 8), // "employee"
QT_MOC_LITERAL(17, 172, 9) // "Employee*"

    },
    "ConferenceUI\0companyChanged\0\0"
    "employeeChanged\0getLoginInformation\0"
    "account\0password\0getRegisterInformation\0"
    "avator\0name\0company\0department\0group\0"
    "phone\0email\0Company*\0employee\0Employee*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConferenceUI[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       2,   58, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       4,    2,   36,    2, 0x02 /* Public */,
       7,    8,   41,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    5,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    8,    9,    6,   10,   11,   12,   13,   14,

 // properties: name, type, flags
      10, 0x80000000 | 15, 0x0049510b,
      16, 0x80000000 | 17, 0x0049510b,

 // properties: notify_signal_id
       0,
       1,

       0        // eod
};

void ConferenceUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ConferenceUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->companyChanged(); break;
        case 1: _t->employeeChanged(); break;
        case 2: _t->getLoginInformation((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->getRegisterInformation((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6])),(*reinterpret_cast< QString(*)>(_a[7])),(*reinterpret_cast< QString(*)>(_a[8]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ConferenceUI::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConferenceUI::companyChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ConferenceUI::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConferenceUI::employeeChanged)) {
                *result = 1;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Company* >(); break;
        case 1:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Employee* >(); break;
        }
    }

#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<ConferenceUI *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< Company**>(_v) = _t->company(); break;
        case 1: *reinterpret_cast< Employee**>(_v) = _t->employee(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<ConferenceUI *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setCompany(*reinterpret_cast< Company**>(_v)); break;
        case 1: _t->setEmployee(*reinterpret_cast< Employee**>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject ConferenceUI::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_ConferenceUI.data,
    qt_meta_data_ConferenceUI,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ConferenceUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConferenceUI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ConferenceUI.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ConferenceUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
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
void ConferenceUI::companyChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ConferenceUI::employeeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
