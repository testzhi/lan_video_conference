/****************************************************************************
** Meta object code from reading C++ file 'meeting.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../videoConferencingClient/meeting.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'meeting.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Meeting_t {
    QByteArrayData data[29];
    char stringdata0[291];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Meeting_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Meeting_t qt_meta_stringdata_Meeting = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Meeting"
QT_MOC_LITERAL(1, 8, 16), // "initiatorChanged"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 14), // "speakerChanged"
QT_MOC_LITERAL(4, 41, 11), // "dateChanged"
QT_MOC_LITERAL(5, 53, 11), // "timeChanged"
QT_MOC_LITERAL(6, 65, 12), // "themeChanged"
QT_MOC_LITERAL(7, 78, 12), // "scaleChanged"
QT_MOC_LITERAL(8, 91, 15), // "durationChanged"
QT_MOC_LITERAL(9, 107, 15), // "categoryChanged"
QT_MOC_LITERAL(10, 123, 12), // "stateChanged"
QT_MOC_LITERAL(11, 136, 9), // "initiator"
QT_MOC_LITERAL(12, 146, 12), // "setInitiator"
QT_MOC_LITERAL(13, 159, 7), // "speaker"
QT_MOC_LITERAL(14, 167, 10), // "setSpeaker"
QT_MOC_LITERAL(15, 178, 4), // "date"
QT_MOC_LITERAL(16, 183, 7), // "setDate"
QT_MOC_LITERAL(17, 191, 4), // "time"
QT_MOC_LITERAL(18, 196, 7), // "setTime"
QT_MOC_LITERAL(19, 204, 5), // "theme"
QT_MOC_LITERAL(20, 210, 8), // "setTheme"
QT_MOC_LITERAL(21, 219, 5), // "scale"
QT_MOC_LITERAL(22, 225, 8), // "setScale"
QT_MOC_LITERAL(23, 234, 8), // "duration"
QT_MOC_LITERAL(24, 243, 11), // "setDuration"
QT_MOC_LITERAL(25, 255, 8), // "category"
QT_MOC_LITERAL(26, 264, 11), // "setCategory"
QT_MOC_LITERAL(27, 276, 5), // "state"
QT_MOC_LITERAL(28, 282, 8) // "setState"

    },
    "Meeting\0initiatorChanged\0\0speakerChanged\0"
    "dateChanged\0timeChanged\0themeChanged\0"
    "scaleChanged\0durationChanged\0"
    "categoryChanged\0stateChanged\0initiator\0"
    "setInitiator\0speaker\0setSpeaker\0date\0"
    "setDate\0time\0setTime\0theme\0setTheme\0"
    "scale\0setScale\0duration\0setDuration\0"
    "category\0setCategory\0state\0setState"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Meeting[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      27,   14, // methods
       9,  194, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  149,    2, 0x06 /* Public */,
       3,    0,  150,    2, 0x06 /* Public */,
       4,    0,  151,    2, 0x06 /* Public */,
       5,    0,  152,    2, 0x06 /* Public */,
       6,    0,  153,    2, 0x06 /* Public */,
       7,    0,  154,    2, 0x06 /* Public */,
       8,    0,  155,    2, 0x06 /* Public */,
       9,    0,  156,    2, 0x06 /* Public */,
      10,    0,  157,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
      11,    0,  158,    2, 0x02 /* Public */,
      12,    1,  159,    2, 0x02 /* Public */,
      13,    0,  162,    2, 0x02 /* Public */,
      14,    1,  163,    2, 0x02 /* Public */,
      15,    0,  166,    2, 0x02 /* Public */,
      16,    1,  167,    2, 0x02 /* Public */,
      17,    0,  170,    2, 0x02 /* Public */,
      18,    1,  171,    2, 0x02 /* Public */,
      19,    0,  174,    2, 0x02 /* Public */,
      20,    1,  175,    2, 0x02 /* Public */,
      21,    0,  178,    2, 0x02 /* Public */,
      22,    1,  179,    2, 0x02 /* Public */,
      23,    0,  182,    2, 0x02 /* Public */,
      24,    1,  183,    2, 0x02 /* Public */,
      25,    0,  186,    2, 0x02 /* Public */,
      26,    1,  187,    2, 0x02 /* Public */,
      27,    0,  190,    2, 0x02 /* Public */,
      28,    1,  191,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   19,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   23,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   25,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   27,

 // properties: name, type, flags
      11, QMetaType::QString, 0x00495103,
      13, QMetaType::QString, 0x00495103,
      15, QMetaType::QString, 0x00495103,
      17, QMetaType::QString, 0x00495103,
      19, QMetaType::QString, 0x00495103,
      21, QMetaType::QString, 0x00495103,
      23, QMetaType::QString, 0x00495103,
      25, QMetaType::QString, 0x00495103,
      27, QMetaType::QString, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,
       5,
       6,
       7,
       8,

       0        // eod
};

void Meeting::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Meeting *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->initiatorChanged(); break;
        case 1: _t->speakerChanged(); break;
        case 2: _t->dateChanged(); break;
        case 3: _t->timeChanged(); break;
        case 4: _t->themeChanged(); break;
        case 5: _t->scaleChanged(); break;
        case 6: _t->durationChanged(); break;
        case 7: _t->categoryChanged(); break;
        case 8: _t->stateChanged(); break;
        case 9: { QString _r = _t->initiator();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->setInitiator((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: { QString _r = _t->speaker();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 12: _t->setSpeaker((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 13: { QString _r = _t->date();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 14: _t->setDate((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 15: { QString _r = _t->time();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 16: _t->setTime((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 17: { QString _r = _t->theme();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 18: _t->setTheme((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 19: { QString _r = _t->scale();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 20: _t->setScale((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 21: { QString _r = _t->duration();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 22: _t->setDuration((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 23: { QString _r = _t->category();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 24: _t->setCategory((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 25: { QString _r = _t->state();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 26: _t->setState((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Meeting::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Meeting::initiatorChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Meeting::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Meeting::speakerChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Meeting::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Meeting::dateChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Meeting::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Meeting::timeChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Meeting::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Meeting::themeChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Meeting::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Meeting::scaleChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Meeting::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Meeting::durationChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (Meeting::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Meeting::categoryChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (Meeting::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Meeting::stateChanged)) {
                *result = 8;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<Meeting *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->initiator(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->speaker(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->date(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->time(); break;
        case 4: *reinterpret_cast< QString*>(_v) = _t->theme(); break;
        case 5: *reinterpret_cast< QString*>(_v) = _t->scale(); break;
        case 6: *reinterpret_cast< QString*>(_v) = _t->duration(); break;
        case 7: *reinterpret_cast< QString*>(_v) = _t->category(); break;
        case 8: *reinterpret_cast< QString*>(_v) = _t->state(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<Meeting *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setInitiator(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setSpeaker(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setDate(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setTime(*reinterpret_cast< QString*>(_v)); break;
        case 4: _t->setTheme(*reinterpret_cast< QString*>(_v)); break;
        case 5: _t->setScale(*reinterpret_cast< QString*>(_v)); break;
        case 6: _t->setDuration(*reinterpret_cast< QString*>(_v)); break;
        case 7: _t->setCategory(*reinterpret_cast< QString*>(_v)); break;
        case 8: _t->setState(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject Meeting::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Meeting.data,
    qt_meta_data_Meeting,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Meeting::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Meeting::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Meeting.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Meeting::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 27)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 27;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 27)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 27;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 9;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Meeting::initiatorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Meeting::speakerChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Meeting::dateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Meeting::timeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Meeting::themeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Meeting::scaleChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void Meeting::durationChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void Meeting::categoryChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void Meeting::stateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
