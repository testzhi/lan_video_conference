#include "employee.h"
#include "company.h"

Employee::Employee()
{

}

void Employee::addMeeting(Meeting *m)
{
    auto meeting = _meetings[m->meetingID()];
    if(!meeting)
        _meetings[m->meetingID()] = m;
}

std::string Employee::realName() const
{
    return m_realName;
}

std::string Employee::avatar() const
{
    return m_avatar;
}

std::string Employee::groupName() const
{
    return m_groupName;
}

std::string Employee::departmentName() const
{
    return m_departmentName;
}

std::string Employee::companyName() const
{
    return m_companyName;
}

std::string Employee::phone() const
{
    return m_phone;
}

void Employee::setDepartmentName(const std::string &departmentName)
{
    m_departmentName = departmentName;
}

void Employee::setCompanyName(const std::string &companyName)
{
    m_companyName = companyName;
}

void Employee::setGroupName(const std::string &groupName)
{
    m_groupName = groupName;
}

int Employee::getCompany() const
{
    return m_company;
}

void Employee::setCompany(int value)
{
    m_company = value;
}

int Employee::getGroup() const
{
    return m_group;
}

void Employee::setGroup(int group)
{
    m_group = group;
}

int Employee::getDepartment() const
{
    return m_department;
}

void Employee::setDepartment(int department)
{
    m_department = department;
}

Company *Employee::getMyCompany() const
{
    return _myCompany;
}

void Employee::setMyCompany(Company *myCompany)
{
    _myCompany = myCompany;
}

std::map<int, Meeting *> Employee::getMeetings() const
{
    return _meetings;
}
