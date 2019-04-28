/****************************************************************************
** Meta object code from reading C++ file 'attendee.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../videoConferencingClient/attendee.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'attendee.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Attendee_t {
    QByteArrayData data[15];
    char stringdata0[157];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Attendee_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Attendee_t qt_meta_stringdata_Attendee = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Attendee"
QT_MOC_LITERAL(1, 9, 13), // "userIDChanged"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 15), // "realNameChanged"
QT_MOC_LITERAL(4, 40, 13), // "avatarChanged"
QT_MOC_LITERAL(5, 54, 12), // "emailChanged"
QT_MOC_LITERAL(6, 67, 19), // "jurisdictionChanged"
QT_MOC_LITERAL(7, 87, 6), // "camera"
QT_MOC_LITERAL(8, 94, 11), // "std::string"
QT_MOC_LITERAL(9, 106, 8), // "filePath"
QT_MOC_LITERAL(10, 115, 6), // "userID"
QT_MOC_LITERAL(11, 122, 8), // "realName"
QT_MOC_LITERAL(12, 131, 6), // "avatar"
QT_MOC_LITERAL(13, 138, 5), // "email"
QT_MOC_LITERAL(14, 144, 12) // "jurisdiction"

    },
    "Attendee\0userIDChanged\0\0realNameChanged\0"
    "avatarChanged\0emailChanged\0"
    "jurisdictionChanged\0camera\0std::string\0"
    "filePath\0userID\0realName\0avatar\0email\0"
    "jurisdiction"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Attendee[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       5,   52, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,
       4,    0,   46,    2, 0x06 /* Public */,
       5,    0,   47,    2, 0x06 /* Public */,
       6,    0,   48,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       7,    1,   49,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, 0x80000000 | 8,    9,

 // properties: name, type, flags
      10, QMetaType::QString, 0x00495103,
      11, QMetaType::QString, 0x00495103,
      12, QMetaType::QString, 0x00495103,
      13, QMetaType::QString, 0x00495103,
      14, QMetaType::QString, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,

       0        // eod
};

void Attendee::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Attendee *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->userIDChanged(); break;
        case 1: _t->realNameChanged(); break;
        case 2: _t->avatarChanged(); break;
        case 3: _t->emailChanged(); break;
        case 4: _t->jurisdictionChanged(); break;
        case 5: _t->camera((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Attendee::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Attendee::userIDChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Attendee::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Attendee::realNameChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Attendee::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Attendee::avatarChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Attendee::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Attendee::emailChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Attendee::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Attendee::jurisdictionChanged)) {
                *result = 4;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<Attendee *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->userID(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->realName(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->avatar(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->email(); break;
        case 4: *reinterpret_cast< QString*>(_v) = _t->jurisdiction(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<Attendee *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setUserID(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setRealName(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setAvatar(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setEmail(*reinterpret_cast< QString*>(_v)); break;
        case 4: _t->setJurisdiction(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject Attendee::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Attendee.data,
    qt_meta_data_Attendee,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Attendee::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Attendee::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Attendee.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Attendee::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Attendee::userIDChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Attendee::realNameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Attendee::avatarChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Attendee::emailChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Attendee::jurisdictionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
