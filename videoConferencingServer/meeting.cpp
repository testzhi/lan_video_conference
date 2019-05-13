#include "meeting.h"
#include "attendee.h"

Meeting::Meeting()
{

}

void Meeting::addAttendee(Attendee *a)
{
    auto att = _attendees[a->attendeeID()];
    if(!att)
        _attendees[a->attendeeID()] = a;
}

int Meeting::meetingID() const
{
    return m_meetingID;
}

int Meeting::state() const
{
    return m_state;
}

void Meeting::setState(int state)
{
    m_state = state;
}

std::string Meeting::assistant() const
{
    return m_assistant;
}

std::string Meeting::assistantName() const
{
    return m_assistantName;
}

std::string Meeting::speaker() const
{
    return m_speaker;
}

std::string Meeting::speakerName() const
{
    return m_speakerName;
}

std::string Meeting::date() const
{
    return m_date;
}

std::string Meeting::time() const
{
    return m_time;
}

int Meeting::catagory() const
{
    return m_catagory;
}

std::string Meeting::subject() const
{
    return m_subject;
}

int Meeting::scale() const
{
    return m_scale;
}

int Meeting::preDuration() const
{
    return m_preDuration;
}

std::string Meeting::remark() const
{
    return m_remark;
}

void Meeting::setAssistantName(const std::string &assistantName)
{
    m_assistantName = assistantName;
}

void Meeting::setSpeakerName(const std::string &speakerName)
{
    m_speakerName = speakerName;
}
