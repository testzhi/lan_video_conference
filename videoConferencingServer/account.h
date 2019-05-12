#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account
{
public:
    Account() {m_accessTimes = 0;}
    Account(std::string id, std::string email, std::string passwd)
        :m_userID(id), m_email(email), m_passwd(passwd)
    {m_accessTimes = 0;}
    Account(std::string id, std::string email)
        :m_userID(id), m_email(email)
    {m_accessTimes = 0;}

    std::string userID() const;
    std::string passwd() const;
    std::string email() const;

    void addAccessTime();
    void printAccountInfo();


    std::string ipAddress() const;
    void setIpAddress(const std::string &ipAddress);

    int state() const;
    void setState(int state);

protected:
    std::string m_userID;
    std::string m_email;
    std::string m_ipAddress;
    int m_state;

private:
    std::string m_passwd;
    int m_accessTimes;//查找次数

};

#endif // ACCOUNT_H
