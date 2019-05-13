#include "department.h"

Department::Department()
{

}

void Department::addGroup(Group *g)
{
    auto group = _groups[g->groupName()];
    if(!group)
        _groups[g->groupName()] = g;
}

std::string Department::departmentName() const
{
    return m_departmentName;
}

void Department::setDepartmentName(const std::string &departmentName)
{
    m_departmentName = departmentName;
}

int Department::department() const
{
    return m_department;
}

void Department::setDepartment(int department)
{
    m_department = department;
}

std::map<std::string, Group *> Department::groups() const
{
    return _groups;
}




