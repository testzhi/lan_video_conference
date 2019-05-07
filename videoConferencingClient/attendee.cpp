#include "attendee.h"
#include <iostream>


QString Attendee::jurisdiction() const
{
    return m_jurisdiction;
}

void Attendee::setJurisdiction(const QString &jurisdiction)
{
    m_jurisdiction = jurisdiction;
}

QString Attendee::avatar() const
{
    return m_avatar;
}

void Attendee::setAvatar(const QString &avatar)
{
    m_avatar = avatar;
}

QString Attendee::email() const
{
    return m_email;
}

void Attendee::setEmail(const QString &email)
{
    m_email = email;
}

QString Attendee::realName() const
{
    return m_realName;
}

void Attendee::setRealName(const QString &realName)
{
    m_realName = realName;
}

QString Attendee::userID() const
{
    return m_userID;
}

void Attendee::setUserID(const QString &userID)
{
    m_userID = userID;
}






