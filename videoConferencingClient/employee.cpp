#include "employee.h"

#include <boost/thread.hpp>

#define PORT_BASE     6666
#define APORT_BASE     8888


void checkerror(int rtperr)
{
    if (rtperr < 0)
    {
        std::cout << "ERROR: " << RTPGetErrorString(rtperr) << std::endl;
        exit(-1);
    }
}

//void

void Employee::startReceive()
{
    std::cout << "receive" << std::endl;
    SVideoRecv sess;
    sess.InitBufferSize();
    std::string ipstr;
    int status;

    RTPUDPv4TransmissionParams transparams;
    RTPSessionParams sessparams;
    sessparams.SetOwnTimestampUnit(1.0/90000.0);
    transparams.SetPortbase(PORT_BASE);
    status = sess.Create(sessparams,&transparams);
    checkerror(status);

    RTPTime::Wait(RTPTime(10000,0));
    sess.BYEDestroy(RTPTime(10,0),0,0);
}

void Employee::AACStartReceive()
{
    AudioReceiver sess;
    sess.InitBufferSize();
    std::string ipstr;
    int status;

    RTPUDPv4TransmissionParams transparams;
    RTPSessionParams sessparams;
    sessparams.SetOwnTimestampUnit(1.0/8000.0);
    transparams.SetPortbase(APORT_BASE);
    status = sess.Create(sessparams,&transparams);
    checkerror(status);

    RTPTime::Wait(RTPTime(10000,0));
    sess.BYEDestroy(RTPTime(10,0),0,0);
}

void Employee::threadReceive()
{
//    boost::thread_group threadGroup;
//    for(int i = 0;i < 5;i++) {
        boost::thread thread(boost::bind(&Employee::startReceive,this));
//        threadGroup.add_thread(&thread);
        thread.detach();
//    }
        //    threadGroup.join_all();
}

void Employee::threadAACReceive()
{
    boost::thread thread(boost::bind(&Employee::AACStartReceive,this));
//        threadGroup.add_thread(&thread);
    thread.detach();
}



QString Employee::userID() const
{
    return m_userID;
}

void Employee::setUserID(const QString &userID)
{
    m_userID = userID;
}

QString Employee::userPassword() const
{
    return m_userPassword;
}

void Employee::setUserPassword(const QString &userPassword)
{
    m_userPassword = userPassword;
}

bool Employee::state() const
{
    return m_state;
}

void Employee::setState(bool state)
{
    m_state = state;
}

QString Employee::avatar() const
{
    return m_avatar;
}

void Employee::setAvatar(const QString &avatar)
{
    m_avatar = avatar;
}

QString Employee::company() const
{
    return m_company;
}

void Employee::setCompany(const QString &company)
{
    m_company = company;
}

QString Employee::department() const
{
    return m_department;
}

void Employee::setDepartment(const QString &department)
{
    m_department = department;
}

QString Employee::realName() const
{
    return m_realName;
}

void Employee::setRealName(const QString &realName)
{
    m_realName = realName;
}

QString Employee::phone() const
{
    return m_phone;
}

void Employee::setPhone(const QString &phone)
{
    m_phone = phone;
}

QString Employee::email() const
{
    return m_email;
}

void Employee::setEmail(const QString &email)
{
    m_email = email;
}

QString Employee::group() const
{
    return m_group;
}

void Employee::setGroup(const QString &group)
{
    m_group = group;
}

QQmlListProperty<Meeting> Employee::meetings()
{
    return QQmlListProperty<Meeting>(this,nullptr,Employee::appendMeeting,Employee::countMeeting,Employee::atMeeting,Employee::clearMeeting);
}

Meeting *Employee::getMeeting(int i)
{
    return _meetings[i];
}

int Employee::meetingCount()
{
    return _meetings.count();
}

Notification *Employee::getNotification(int i)
{
    return _notifications.at(i);
}

int Employee::notificationCount()
{
    return _notifications.count();
}

Attendee *Employee::getAttendee(int i)
{
    return _attendees.at(i);
}

int Employee::attendeeCount()
{
    return _attendees.count();
}

void Employee::insertMeeting(Meeting *meeting)
{
    _meetings.append(meeting);
}

void Employee::insertNotification(Notification *notification)
{
    _notifications.append(notification);
}

void Employee::sortMeeting()
{
    qSort(_meetings.begin(),_meetings.end(),[](const Meeting *infoA,const Meeting *infoB){
        if(infoA->date() == infoB->date())
            return infoA->time() < infoB->time();
        else return infoA->date() < infoB->date();
    });
}

QQmlListProperty<Notification> Employee::notifications()
{
    return QQmlListProperty<Notification>(this,nullptr,Employee::appendNotification,Employee::countNotification,Employee::atNotification,Employee::clearNotification);
}

Company *Employee::companys() const
{
    return m_companys;
}

void Employee::setCompanys(Company *companys)
{
    m_companys = companys;
}

QList<Notification *> Employee::getNotifications() const
{
    return _notifications;
}

void Employee::setNotifications(const QList<Notification *> &notifications)
{
    _notifications = notifications;
}

void Employee::setMeetings(const QList<Meeting *> &meetings)
{
    _meetings = meetings;
}

void Employee::appendMeeting(QQmlListProperty<Meeting> *meetings,Meeting *meeting){
    Employee *employee = qobject_cast<Employee *>(meetings->object);
    if(meeting) {
        meeting->setParent(employee);
        employee->_meetings.append(meeting);
    }
}

int Employee::countMeeting(QQmlListProperty<Meeting> *meetings)
{
    Employee *employee = qobject_cast<Employee *>(meetings->object);
    if(employee)
        return employee->_meetings.count();
    return 0;
}

Meeting *Employee::atMeeting(QQmlListProperty<Meeting> *meetings,int i)
{
    Employee *employee = qobject_cast<Employee *>(meetings->object);
    if(employee)
        return employee->_meetings.at(i);
    return nullptr;
}

void Employee::clearMeeting(QQmlListProperty<Meeting> *meetings)
{
    Employee *employee = qobject_cast<Employee *>(meetings->object);
    if(employee) {
        employee->_meetings.clear();
    }
}

void Employee::appendNotification(QQmlListProperty<Notification> *notifications, Notification *notification)
{
    Employee *employee = qobject_cast<Employee *>(notifications->object);
    if(notification) {
        notification->setParent(employee);
        employee->_notifications.append(notification);
    }
}

int Employee::countNotification(QQmlListProperty<Notification> *notifications)
{
    Employee *employee = qobject_cast<Employee *>(notifications->object);
    if(employee)
        return employee->_notifications.count();
    return 0;
}

Notification *Employee::atNotification(QQmlListProperty<Notification> *notifications, int i)
{
    Employee *employee = qobject_cast<Employee *>(notifications->object);
    if(employee)
        return employee->_notifications.at(i);
    return nullptr;
}

void Employee::clearNotification(QQmlListProperty<Notification> *notification)
{
    Employee *employee = qobject_cast<Employee *>(notification->object);
    if(employee)
        employee->_notifications.clear();
}

QQmlListProperty<Attendee> Employee::attendees()
{
    return QQmlListProperty<Attendee>(this,nullptr,Employee::appendAttendee,Employee::countAttendee,Employee::atAttendee,Employee::clearAttendee);
}

void Employee::setAttendees(const QList<Attendee *> &attendees)
{
    _attendees = attendees;
}

void Employee::appendAttendee(QQmlListProperty<Attendee> *attendees, Attendee *attendee)
{
    Employee *employee = qobject_cast<Employee *>(attendees->object);
    if(attendee) {
        attendee->setParent(employee);
        employee->_attendees.append(attendee);
    }
}

int Employee::countAttendee(QQmlListProperty<Attendee> *attendees)
{
    Employee *employee = qobject_cast<Employee *>(attendees->object);
    if(employee)
        return employee->_attendees.count();
    return 0;
}

Attendee *Employee::atAttendee(QQmlListProperty<Attendee> *attendees, int i)
{
    Employee *employee = qobject_cast<Employee *>(attendees->object);
    if(employee)
        return employee->_attendees.at(i);
    return nullptr;
}

void Employee::clearAttendee(QQmlListProperty<Attendee> *attendees)
{
    Employee *employee = qobject_cast<Employee *>(attendees->object);
    if(employee) {
        employee->_attendees.clear();
    }
}
