#include "meeting.h"

using namespace std;

Meeting::Meeting(string initiator, string speaker, string date, string time, string theme, string scale, string duration, string category, string state):m_initiator(QString::fromStdString(initiator)),m_speaker(QString::fromStdString(speaker)),m_date(QString::fromStdString(date)),m_time(QString::fromStdString(time)),m_theme(QString::fromStdString(theme)),m_scale(QString::fromStdString(scale)),m_duration(QString::fromStdString(duration)),m_category(QString::fromStdString(category)),m_state(QString::fromStdString(state))
{

}

QString Meeting::initiator() const
{
    return m_initiator;
}

void Meeting::setInitiator(const QString &initiator)
{
    m_initiator = initiator;
}

QString Meeting::speaker() const
{
    return m_speaker;
}

void Meeting::setSpeaker(const QString &speaker)
{
    m_speaker = speaker;
}

QString Meeting::date() const
{
    return m_date;
}

void Meeting::setDate(const QString &date)
{
    m_date = date;
}

QString Meeting::time() const
{
    return m_time;
}

void Meeting::setTime(const QString &time)
{
    m_time = time;
}

QString Meeting::theme() const
{
    return m_theme;
}

void Meeting::setTheme(const QString &theme)
{
    m_theme = theme;
}

QString Meeting::scale() const
{
    return m_scale;
}

void Meeting::setScale(const QString &scale)
{
    m_scale = scale;
}

QString Meeting::duration() const
{
    return m_duration;
}

void Meeting::setDuration(const QString &duration)
{
    m_duration = duration;
}

QString Meeting::category() const
{
    return m_category;
}

void Meeting::setCategory(const QString &category)
{
    m_category = category;
}

QString Meeting::state() const
{
    return m_state;
}

void Meeting::setState(const QString &state)
{
    m_state = state;
}
