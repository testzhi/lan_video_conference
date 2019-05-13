#ifndef ATTENDEE_H
#define ATTENDEE_H

#include <string>

class Attendee
{
public:
    Attendee();
    Attendee(std::string id, std::string email, std::string name, std::string avatar, std::string phone ,int status, std::string ip)
        :m_attendeeID(id), m_email(email), m_realName(name), m_avatar(avatar), m_phone(phone) , m_status(status), m_ip(ip)
    {}
    Attendee(std::string id, std::string email, std::string name, std::string avatar, std::string phone , std::string ip)
        :m_attendeeID(id), m_email(email), m_realName(name), m_avatar(avatar), m_phone(phone), m_ip(ip)
    {}
    std::string attendeeID() const;

    int status() const;
    void setStatus(int status);

private:
    std::string m_attendeeID;
    std::string m_email;
    std::string m_realName;
    std::string m_avatar;
        std::string m_phone;
    int m_status;
    std::string m_ip;
};

#endif // ATTENDEE_H
