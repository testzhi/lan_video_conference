/****************************************************************************
** Meta object code from reading C++ file 'xvideo.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../videoConferencingClient/xvideo.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'xvideo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_XVideo_t {
    QByteArrayData data[28];
    char stringdata0[316];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_XVideo_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_XVideo_t qt_meta_stringdata_XVideo = {
    {
QT_MOC_LITERAL(0, 0, 6), // "XVideo"
QT_MOC_LITERAL(1, 7, 12), // "widthChanged"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 6), // "nWidth"
QT_MOC_LITERAL(4, 28, 13), // "heightChanged"
QT_MOC_LITERAL(5, 42, 7), // "nHeight"
QT_MOC_LITERAL(6, 50, 19), // "strVideoPathChanged"
QT_MOC_LITERAL(7, 70, 7), // "strPath"
QT_MOC_LITERAL(8, 78, 15), // "durationChanged"
QT_MOC_LITERAL(9, 94, 9), // "nDuration"
QT_MOC_LITERAL(10, 104, 15), // "positionChanged"
QT_MOC_LITERAL(11, 120, 9), // "nPosition"
QT_MOC_LITERAL(12, 130, 20), // "sig_totalTimeChanged"
QT_MOC_LITERAL(13, 151, 3), // "str"
QT_MOC_LITERAL(14, 155, 22), // "sig_currentTimeChanged"
QT_MOC_LITERAL(15, 178, 16), // "slot_GetOneFrame"
QT_MOC_LITERAL(16, 195, 5), // "image"
QT_MOC_LITERAL(17, 201, 21), // "slot_totalTimeChanged"
QT_MOC_LITERAL(18, 223, 3), // "sec"
QT_MOC_LITERAL(19, 227, 23), // "slot_currentTimeChanged"
QT_MOC_LITERAL(20, 251, 7), // "SetSize"
QT_MOC_LITERAL(21, 259, 5), // "width"
QT_MOC_LITERAL(22, 265, 6), // "height"
QT_MOC_LITERAL(23, 272, 9), // "startPlay"
QT_MOC_LITERAL(24, 282, 9), // "pausePlay"
QT_MOC_LITERAL(25, 292, 8), // "setScale"
QT_MOC_LITERAL(26, 301, 1), // "s"
QT_MOC_LITERAL(27, 303, 12) // "strVideoPath"

    },
    "XVideo\0widthChanged\0\0nWidth\0heightChanged\0"
    "nHeight\0strVideoPathChanged\0strPath\0"
    "durationChanged\0nDuration\0positionChanged\0"
    "nPosition\0sig_totalTimeChanged\0str\0"
    "sig_currentTimeChanged\0slot_GetOneFrame\0"
    "image\0slot_totalTimeChanged\0sec\0"
    "slot_currentTimeChanged\0SetSize\0width\0"
    "height\0startPlay\0pausePlay\0setScale\0"
    "s\0strVideoPath"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_XVideo[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       5,  128, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       4,    1,   87,    2, 0x06 /* Public */,
       6,    1,   90,    2, 0x06 /* Public */,
       8,    1,   93,    2, 0x06 /* Public */,
      10,    1,   96,    2, 0x06 /* Public */,
      12,    1,   99,    2, 0x06 /* Public */,
      14,    1,  102,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      15,    1,  105,    2, 0x0a /* Public */,
      17,    2,  108,    2, 0x0a /* Public */,
      19,    2,  113,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      20,    2,  118,    2, 0x02 /* Public */,
      23,    0,  123,    2, 0x02 /* Public */,
      24,    0,  124,    2, 0x02 /* Public */,
      25,    1,  125,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::QString,   13,

 // slots: parameters
    QMetaType::Void, QMetaType::QImage,   16,
    QMetaType::Void, QMetaType::QString, QMetaType::LongLong,   13,   18,
    QMetaType::Void, QMetaType::QString, QMetaType::LongLong,   13,   18,

 // methods: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   21,   22,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   26,

 // properties: name, type, flags
       3, QMetaType::Int, 0x00495003,
       5, QMetaType::Int, 0x00495003,
      27, QMetaType::QString, 0x00495103,
       9, QMetaType::Int, 0x00495003,
      11, QMetaType::Int, 0x00495003,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,

       0        // eod
};

void XVideo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<XVideo *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->widthChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->heightChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->strVideoPathChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->durationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->positionChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->sig_totalTimeChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->sig_currentTimeChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->slot_GetOneFrame((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 8: _t->slot_totalTimeChanged((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 9: _t->slot_currentTimeChanged((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 10: _t->SetSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->startPlay(); break;
        case 12: _t->pausePlay(); break;
        case 13: _t->setScale((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (XVideo::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&XVideo::widthChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (XVideo::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&XVideo::heightChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (XVideo::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&XVideo::strVideoPathChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (XVideo::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&XVideo::durationChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (XVideo::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&XVideo::positionChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (XVideo::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&XVideo::sig_totalTimeChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (XVideo::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&XVideo::sig_currentTimeChanged)) {
                *result = 6;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<XVideo *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->getWidth(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->getHeight(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->getStrVideoPath(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->getDuration(); break;
        case 4: *reinterpret_cast< int*>(_v) = _t->getPosition(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<XVideo *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setWidth(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->setHeight(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setStrVideoPath(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setDuration(*reinterpret_cast< int*>(_v)); break;
        case 4: _t->setPosition(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject XVideo::staticMetaObject = { {
    &QQuickPaintedItem::staticMetaObject,
    qt_meta_stringdata_XVideo.data,
    qt_meta_data_XVideo,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *XVideo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *XVideo::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_XVideo.stringdata0))
        return static_cast<void*>(this);
    return QQuickPaintedItem::qt_metacast(_clname);
}

int XVideo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QQuickPaintedItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
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
void XVideo::widthChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void XVideo::heightChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void XVideo::strVideoPathChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void XVideo::durationChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void XVideo::positionChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void XVideo::sig_totalTimeChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void XVideo::sig_currentTimeChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
