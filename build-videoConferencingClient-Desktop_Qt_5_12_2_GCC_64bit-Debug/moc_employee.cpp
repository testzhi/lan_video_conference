/****************************************************************************
** Meta object code from reading C++ file 'employee.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../videoConferencingClient/employee.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'employee.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Employee_t {
    QByteArrayData data[65];
    char stringdata0[838];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Employee_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Employee_t qt_meta_stringdata_Employee = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Employee"
QT_MOC_LITERAL(1, 9, 15), // "DefaultProperty"
QT_MOC_LITERAL(2, 25, 9), // "attendees"
QT_MOC_LITERAL(3, 35, 8), // "meetings"
QT_MOC_LITERAL(4, 44, 13), // "userIDChanged"
QT_MOC_LITERAL(5, 58, 0), // ""
QT_MOC_LITERAL(6, 59, 19), // "userPasswordChanged"
QT_MOC_LITERAL(7, 79, 12), // "stateChanged"
QT_MOC_LITERAL(8, 92, 13), // "avatarChanged"
QT_MOC_LITERAL(9, 106, 14), // "companyChanged"
QT_MOC_LITERAL(10, 121, 17), // "departmentChanged"
QT_MOC_LITERAL(11, 139, 15), // "realNameChanged"
QT_MOC_LITERAL(12, 155, 12), // "phoneChanged"
QT_MOC_LITERAL(13, 168, 12), // "emailChanged"
QT_MOC_LITERAL(14, 181, 12), // "groupChanged"
QT_MOC_LITERAL(15, 194, 15), // "meetingsChanged"
QT_MOC_LITERAL(16, 210, 20), // "notificationsChanged"
QT_MOC_LITERAL(17, 231, 15), // "companysChanged"
QT_MOC_LITERAL(18, 247, 16), // "attendeesChanged"
QT_MOC_LITERAL(19, 264, 20), // "registerSuccessfully"
QT_MOC_LITERAL(20, 285, 22), // "emailAlreadyRegistered"
QT_MOC_LITERAL(21, 308, 14), // "loginSucceeded"
QT_MOC_LITERAL(22, 323, 4), // "type"
QT_MOC_LITERAL(23, 328, 11), // "loginFailed"
QT_MOC_LITERAL(24, 340, 3), // "err"
QT_MOC_LITERAL(25, 344, 18), // "initCompanyMessage"
QT_MOC_LITERAL(26, 363, 23), // "initNotificationMessage"
QT_MOC_LITERAL(27, 387, 15), // "initMeetingList"
QT_MOC_LITERAL(28, 403, 6), // "userID"
QT_MOC_LITERAL(29, 410, 9), // "setUserID"
QT_MOC_LITERAL(30, 420, 12), // "userPassword"
QT_MOC_LITERAL(31, 433, 15), // "setUserPassword"
QT_MOC_LITERAL(32, 449, 5), // "state"
QT_MOC_LITERAL(33, 455, 8), // "setState"
QT_MOC_LITERAL(34, 464, 6), // "avatar"
QT_MOC_LITERAL(35, 471, 9), // "setAvatar"
QT_MOC_LITERAL(36, 481, 7), // "company"
QT_MOC_LITERAL(37, 489, 10), // "setCompany"
QT_MOC_LITERAL(38, 500, 10), // "department"
QT_MOC_LITERAL(39, 511, 13), // "setDepartment"
QT_MOC_LITERAL(40, 525, 8), // "realName"
QT_MOC_LITERAL(41, 534, 11), // "setRealName"
QT_MOC_LITERAL(42, 546, 5), // "phone"
QT_MOC_LITERAL(43, 552, 8), // "setPhone"
QT_MOC_LITERAL(44, 561, 5), // "email"
QT_MOC_LITERAL(45, 567, 8), // "setEmail"
QT_MOC_LITERAL(46, 576, 5), // "group"
QT_MOC_LITERAL(47, 582, 8), // "setGroup"
QT_MOC_LITERAL(48, 591, 25), // "QQmlListProperty<Meeting>"
QT_MOC_LITERAL(49, 617, 10), // "getMeeting"
QT_MOC_LITERAL(50, 628, 8), // "Meeting*"
QT_MOC_LITERAL(51, 637, 1), // "i"
QT_MOC_LITERAL(52, 639, 12), // "meetingCount"
QT_MOC_LITERAL(53, 652, 15), // "getNotification"
QT_MOC_LITERAL(54, 668, 13), // "Notification*"
QT_MOC_LITERAL(55, 682, 17), // "notificationCount"
QT_MOC_LITERAL(56, 700, 11), // "getAttendee"
QT_MOC_LITERAL(57, 712, 9), // "Attendee*"
QT_MOC_LITERAL(58, 722, 13), // "attendeeCount"
QT_MOC_LITERAL(59, 736, 11), // "sortMeeting"
QT_MOC_LITERAL(60, 748, 13), // "notifications"
QT_MOC_LITERAL(61, 762, 30), // "QQmlListProperty<Notification>"
QT_MOC_LITERAL(62, 793, 8), // "companys"
QT_MOC_LITERAL(63, 802, 8), // "Company*"
QT_MOC_LITERAL(64, 811, 26) // "QQmlListProperty<Attendee>"

    },
    "Employee\0DefaultProperty\0attendees\0"
    "meetings\0userIDChanged\0\0userPasswordChanged\0"
    "stateChanged\0avatarChanged\0companyChanged\0"
    "departmentChanged\0realNameChanged\0"
    "phoneChanged\0emailChanged\0groupChanged\0"
    "meetingsChanged\0notificationsChanged\0"
    "companysChanged\0attendeesChanged\0"
    "registerSuccessfully\0emailAlreadyRegistered\0"
    "loginSucceeded\0type\0loginFailed\0err\0"
    "initCompanyMessage\0initNotificationMessage\0"
    "initMeetingList\0userID\0setUserID\0"
    "userPassword\0setUserPassword\0state\0"
    "setState\0avatar\0setAvatar\0company\0"
    "setCompany\0department\0setDepartment\0"
    "realName\0setRealName\0phone\0setPhone\0"
    "email\0setEmail\0group\0setGroup\0"
    "QQmlListProperty<Meeting>\0getMeeting\0"
    "Meeting*\0i\0meetingCount\0getNotification\0"
    "Notification*\0notificationCount\0"
    "getAttendee\0Attendee*\0attendeeCount\0"
    "sortMeeting\0notifications\0"
    "QQmlListProperty<Notification>\0companys\0"
    "Company*\0QQmlListProperty<Attendee>"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Employee[] = {

 // content:
       8,       // revision
       0,       // classname
       2,   14, // classinfo
      49,   18, // methods
      14,  342, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      21,       // signalCount

 // classinfo: key, value
       1,    2,
       1,    3,

 // signals: name, argc, parameters, tag, flags
       4,    0,  263,    5, 0x06 /* Public */,
       6,    0,  264,    5, 0x06 /* Public */,
       7,    0,  265,    5, 0x06 /* Public */,
       8,    0,  266,    5, 0x06 /* Public */,
       9,    0,  267,    5, 0x06 /* Public */,
      10,    0,  268,    5, 0x06 /* Public */,
      11,    0,  269,    5, 0x06 /* Public */,
      12,    0,  270,    5, 0x06 /* Public */,
      13,    0,  271,    5, 0x06 /* Public */,
      14,    0,  272,    5, 0x06 /* Public */,
      15,    0,  273,    5, 0x06 /* Public */,
      16,    0,  274,    5, 0x06 /* Public */,
      17,    0,  275,    5, 0x06 /* Public */,
      18,    0,  276,    5, 0x06 /* Public */,
      19,    0,  277,    5, 0x06 /* Public */,
      20,    0,  278,    5, 0x06 /* Public */,
      21,    1,  279,    5, 0x06 /* Public */,
      23,    1,  282,    5, 0x06 /* Public */,
      25,    0,  285,    5, 0x06 /* Public */,
      26,    0,  286,    5, 0x06 /* Public */,
      27,    0,  287,    5, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
      28,    0,  288,    5, 0x02 /* Public */,
      29,    1,  289,    5, 0x02 /* Public */,
      30,    0,  292,    5, 0x02 /* Public */,
      31,    1,  293,    5, 0x02 /* Public */,
      32,    0,  296,    5, 0x02 /* Public */,
      33,    1,  297,    5, 0x02 /* Public */,
      34,    0,  300,    5, 0x02 /* Public */,
      35,    1,  301,    5, 0x02 /* Public */,
      36,    0,  304,    5, 0x02 /* Public */,
      37,    1,  305,    5, 0x02 /* Public */,
      38,    0,  308,    5, 0x02 /* Public */,
      39,    1,  309,    5, 0x02 /* Public */,
      40,    0,  312,    5, 0x02 /* Public */,
      41,    1,  313,    5, 0x02 /* Public */,
      42,    0,  316,    5, 0x02 /* Public */,
      43,    1,  317,    5, 0x02 /* Public */,
      44,    0,  320,    5, 0x02 /* Public */,
      45,    1,  321,    5, 0x02 /* Public */,
      46,    0,  324,    5, 0x02 /* Public */,
      47,    1,  325,    5, 0x02 /* Public */,
       3,    0,  328,    5, 0x02 /* Public */,
      49,    1,  329,    5, 0x02 /* Public */,
      52,    0,  332,    5, 0x02 /* Public */,
      53,    1,  333,    5, 0x02 /* Public */,
      55,    0,  336,    5, 0x02 /* Public */,
      56,    1,  337,    5, 0x02 /* Public */,
      58,    0,  340,    5, 0x02 /* Public */,
      59,    0,  341,    5, 0x02 /* Public */,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void, QMetaType::QString,   24,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   28,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   30,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,   32,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   34,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   36,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   38,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   40,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   42,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   44,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   46,
    0x80000000 | 48,
    0x80000000 | 50, QMetaType::Int,   51,
    QMetaType::Int,
    0x80000000 | 54, QMetaType::Int,   51,
    QMetaType::Int,
    0x80000000 | 57, QMetaType::Int,   51,
    QMetaType::Int,
    QMetaType::Void,

 // properties: name, type, flags
      28, QMetaType::QString, 0x00495103,
      30, QMetaType::QString, 0x00495103,
      32, QMetaType::Bool, 0x00495103,
      34, QMetaType::QString, 0x00495103,
      36, QMetaType::QString, 0x00495103,
      38, QMetaType::QString, 0x00495103,
      40, QMetaType::QString, 0x00495103,
      42, QMetaType::QString, 0x00495103,
      44, QMetaType::QString, 0x00495103,
      46, QMetaType::QString, 0x00495103,
       3, 0x80000000 | 48, 0x00495009,
      60, 0x80000000 | 61, 0x00495009,
      62, 0x80000000 | 63, 0x0049510b,
       2, 0x80000000 | 64, 0x00495009,

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
       9,
      10,
      11,
      12,
      13,

       0        // eod
};

void Employee::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Employee *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->userIDChanged(); break;
        case 1: _t->userPasswordChanged(); break;
        case 2: _t->stateChanged(); break;
        case 3: _t->avatarChanged(); break;
        case 4: _t->companyChanged(); break;
        case 5: _t->departmentChanged(); break;
        case 6: _t->realNameChanged(); break;
        case 7: _t->phoneChanged(); break;
        case 8: _t->emailChanged(); break;
        case 9: _t->groupChanged(); break;
        case 10: _t->meetingsChanged(); break;
        case 11: _t->notificationsChanged(); break;
        case 12: _t->companysChanged(); break;
        case 13: _t->attendeesChanged(); break;
        case 14: _t->registerSuccessfully(); break;
        case 15: _t->emailAlreadyRegistered(); break;
        case 16: _t->loginSucceeded((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 17: _t->loginFailed((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 18: _t->initCompanyMessage(); break;
        case 19: _t->initNotificationMessage(); break;
        case 20: _t->initMeetingList(); break;
        case 21: { QString _r = _t->userID();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 22: _t->setUserID((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 23: { QString _r = _t->userPassword();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 24: _t->setUserPassword((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 25: { bool _r = _t->state();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 26: _t->setState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 27: { QString _r = _t->avatar();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 28: _t->setAvatar((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 29: { QString _r = _t->company();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 30: _t->setCompany((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 31: { QString _r = _t->department();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 32: _t->setDepartment((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 33: { QString _r = _t->realName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 34: _t->setRealName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 35: { QString _r = _t->phone();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 36: _t->setPhone((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 37: { QString _r = _t->email();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 38: _t->setEmail((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 39: { QString _r = _t->group();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 40: _t->setGroup((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 41: { QQmlListProperty<Meeting> _r = _t->meetings();
            if (_a[0]) *reinterpret_cast< QQmlListProperty<Meeting>*>(_a[0]) = std::move(_r); }  break;
        case 42: { Meeting* _r = _t->getMeeting((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< Meeting**>(_a[0]) = std::move(_r); }  break;
        case 43: { int _r = _t->meetingCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 44: { Notification* _r = _t->getNotification((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< Notification**>(_a[0]) = std::move(_r); }  break;
        case 45: { int _r = _t->notificationCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 46: { Attendee* _r = _t->getAttendee((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< Attendee**>(_a[0]) = std::move(_r); }  break;
        case 47: { int _r = _t->attendeeCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 48: _t->sortMeeting(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Employee::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Employee::userIDChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Employee::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Employee::userPasswordChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Employee::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Employee::stateChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Employee::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Employee::avatarChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Employee::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Employee::companyChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Employee::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Employee::departmentChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Employee::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Employee::realNameChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (Employee::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Employee::phoneChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (Employee::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Employee::emailChanged)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (Employee::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Employee::groupChanged)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (Employee::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Employee::meetingsChanged)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (Employee::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Employee::notificationsChanged)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (Employee::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Employee::companysChanged)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (Employee::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Employee::attendeesChanged)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (Employee::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Employee::registerSuccessfully)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (Employee::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Employee::emailAlreadyRegistered)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (Employee::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Employee::loginSucceeded)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (Employee::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Employee::loginFailed)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (Employee::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Employee::initCompanyMessage)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (Employee::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Employee::initNotificationMessage)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (Employee::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Employee::initMeetingList)) {
                *result = 20;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 12:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Company* >(); break;
        }
    }

#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<Employee *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->userID(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->userPassword(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->state(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->avatar(); break;
        case 4: *reinterpret_cast< QString*>(_v) = _t->company(); break;
        case 5: *reinterpret_cast< QString*>(_v) = _t->department(); break;
        case 6: *reinterpret_cast< QString*>(_v) = _t->realName(); break;
        case 7: *reinterpret_cast< QString*>(_v) = _t->phone(); break;
        case 8: *reinterpret_cast< QString*>(_v) = _t->email(); break;
        case 9: *reinterpret_cast< QString*>(_v) = _t->group(); break;
        case 10: *reinterpret_cast< QQmlListProperty<Meeting>*>(_v) = _t->meetings(); break;
        case 11: *reinterpret_cast< QQmlListProperty<Notification>*>(_v) = _t->notifications(); break;
        case 12: *reinterpret_cast< Company**>(_v) = _t->companys(); break;
        case 13: *reinterpret_cast< QQmlListProperty<Attendee>*>(_v) = _t->attendees(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<Employee *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setUserID(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setUserPassword(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setState(*reinterpret_cast< bool*>(_v)); break;
        case 3: _t->setAvatar(*reinterpret_cast< QString*>(_v)); break;
        case 4: _t->setCompany(*reinterpret_cast< QString*>(_v)); break;
        case 5: _t->setDepartment(*reinterpret_cast< QString*>(_v)); break;
        case 6: _t->setRealName(*reinterpret_cast< QString*>(_v)); break;
        case 7: _t->setPhone(*reinterpret_cast< QString*>(_v)); break;
        case 8: _t->setEmail(*reinterpret_cast< QString*>(_v)); break;
        case 9: _t->setGroup(*reinterpret_cast< QString*>(_v)); break;
        case 12: _t->setCompanys(*reinterpret_cast< Company**>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject Employee::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Employee.data,
    qt_meta_data_Employee,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Employee::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Employee::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Employee.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Employee::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 49)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 49;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 49)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 49;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 14;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Employee::userIDChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Employee::userPasswordChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Employee::stateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Employee::avatarChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Employee::companyChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Employee::departmentChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void Employee::realNameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void Employee::phoneChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void Employee::emailChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void Employee::groupChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void Employee::meetingsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void Employee::notificationsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void Employee::companysChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}

// SIGNAL 13
void Employee::attendeesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}

// SIGNAL 14
void Employee::registerSuccessfully()
{
    QMetaObject::activate(this, &staticMetaObject, 14, nullptr);
}

// SIGNAL 15
void Employee::emailAlreadyRegistered()
{
    QMetaObject::activate(this, &staticMetaObject, 15, nullptr);
}

// SIGNAL 16
void Employee::loginSucceeded(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void Employee::loginFailed(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void Employee::initCompanyMessage()
{
    QMetaObject::activate(this, &staticMetaObject, 18, nullptr);
}

// SIGNAL 19
void Employee::initNotificationMessage()
{
    QMetaObject::activate(this, &staticMetaObject, 19, nullptr);
}

// SIGNAL 20
void Employee::initMeetingList()
{
    QMetaObject::activate(this, &staticMetaObject, 20, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
