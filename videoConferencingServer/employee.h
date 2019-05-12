#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "account.h"
#include <string>

class Employee : public Account
{
public:
    Employee();
    Employee(std::string userid, std::string email, std::string name, std::string avatar, std::string gName, std::string dName, std::string cName, std::string phone)
        :Account(userid, email), m_realName(name), m_avatar(avatar), m_groupName(gName), m_departmentName(dName), m_companyName(cName), m_phone(phone)
    {}
    Employee(std::string userid, std::string email, std::string passwd, std::string name, std::string avatar, std::string gName, std::string dName, std::string cName, std::string phone)
        :Account(userid, email, passwd), m_realName(name), m_avatar(avatar), m_groupName(gName), m_departmentName(dName), m_companyName(cName), m_phone(phone)
    {}
    Employee(std::string name, std::string avatar, std::string gName, std::string dName, std::string cName, std::string phone)
        :m_realName(name), m_avatar(avatar), m_groupName(gName), m_departmentName(dName), m_companyName(cName), m_phone(phone)
    {}


private:
    std::string m_realName;
    std::string m_avatar;
    std::string m_groupName;
    std::string m_departmentName;
    std::string m_companyName;
    std::string m_phone;
};

#endif // EMPLOYEE_H
