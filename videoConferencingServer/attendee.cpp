#include "attendee.h"

Attendee::Attendee()
{

}

std::string Attendee::attendeeID() const
{
    return m_attendeeID;
}

int Attendee::status() const
{
    return m_status;
}

void Attendee::setStatus(int status)
{
    m_status = status;
}
