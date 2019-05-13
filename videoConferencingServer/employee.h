#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "account.h"
#include "meeting.h"
#include <string>
#include <map>

class Company;
class Employee : public Account
{
public:
    Employee();
    Employee(std::string userid, std::string email, std::string name, std::string avatar, std::string gName, std::string dName, std::string cName, std::string phone)
        :Account(userid, email), m_realName(name), m_avatar(avatar), m_groupName(gName), m_departmentName(dName), m_companyName(cName), m_phone(phone)
    {}
    Employee(std::string userid, std::string email, std::string name, std::string avatar, std::string phone)
        :Account(userid, email), m_realName(name), m_avatar(avatar), m_phone(phone)
    {}
    Employee(std::string userid, std::string email, std::string passwd, std::string name, std::string avatar, std::string gName, std::string dName, std::string cName, std::string phone)
        :Account(userid, email, passwd), m_realName(name), m_avatar(avatar), m_groupName(gName), m_departmentName(dName), m_companyName(cName), m_phone(phone)
    {}
    Employee(std::string name, std::string avatar, std::string gName, std::string dName, std::string cName, std::string phone)
        :m_realName(name), m_avatar(avatar), m_groupName(gName), m_departmentName(dName), m_companyName(cName), m_phone(phone)
    {}

    void addMeeting(Meeting *m);

    std::string realName() const;
    std::string avatar() const;
    std::string groupName() const;
    std::string departmentName() const;
    std::string companyName() const;
    std::string phone() const;

    void setDepartmentName(const std::string &departmentName);
    void setCompanyName(const std::string &companyName);
    void setGroupName(const std::string &groupName);
    int getCompany() const;
    void setCompany(int value);

    int getGroup() const;
    void setGroup(int group);

    int getDepartment() const;
    void setDepartment(int department);

    Company *getMyCompany() const;
    void setMyCompany(Company *myCompany);

    std::map<int, Meeting *> getMeetings() const;

private:
    std::string m_realName;
    std::string m_avatar;
    std::string m_groupName;
    std::string m_departmentName;
    std::string m_companyName;
    int m_group;
    int m_department;
    int m_company;
    std::string m_phone;
    Company *_myCompany;
    std::map<int, Meeting*> _meetings;
};

#endif // EMPLOYEE_H
