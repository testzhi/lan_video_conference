/****************************************************************************
** Meta object code from reading C++ file 'xvideorecord.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../videoConferencingClient/xvideorecord.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'xvideorecord.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_XVideoRecordThread_t {
    QByteArrayData data[5];
    char stringdata0[80];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_XVideoRecordThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_XVideoRecordThread_t qt_meta_stringdata_XVideoRecordThread = {
    {
QT_MOC_LITERAL(0, 0, 18), // "XVideoRecordThread"
QT_MOC_LITERAL(1, 19, 15), // "sig_GetOneFrame"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 20), // "sig_totalTimeChanged"
QT_MOC_LITERAL(4, 57, 22) // "sig_currentTimeChanged"

    },
    "XVideoRecordThread\0sig_GetOneFrame\0\0"
    "sig_totalTimeChanged\0sig_currentTimeChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_XVideoRecordThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       3,    2,   32,    2, 0x06 /* Public */,
       4,    2,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QImage,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::LongLong,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::LongLong,    2,    2,

       0        // eod
};

void XVideoRecordThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<XVideoRecordThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_GetOneFrame((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 1: _t->sig_totalTimeChanged((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 2: _t->sig_currentTimeChanged((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (XVideoRecordThread::*)(QImage );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&XVideoRecordThread::sig_GetOneFrame)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (XVideoRecordThread::*)(QString , qint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&XVideoRecordThread::sig_totalTimeChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (XVideoRecordThread::*)(QString , qint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&XVideoRecordThread::sig_currentTimeChanged)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject XVideoRecordThread::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_XVideoRecordThread.data,
    qt_meta_data_XVideoRecordThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *XVideoRecordThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *XVideoRecordThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_XVideoRecordThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int XVideoRecordThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void XVideoRecordThread::sig_GetOneFrame(QImage _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void XVideoRecordThread::sig_totalTimeChanged(QString _t1, qint64 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void XVideoRecordThread::sig_currentTimeChanged(QString _t1, qint64 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
