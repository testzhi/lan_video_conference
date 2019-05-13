#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include "group.h"
#include <map>

class Department
{
public:
    Department();
    Department(std::string name, int did)
        :m_departmentName(name), m_department(did)
    {}
    void addGroup(Group *g);

    std::string departmentName() const;
    void setDepartmentName(const std::string &departmentName);
    int department() const;
    void setDepartment(int department);

    std::map<std::string, Group *> groups() const;

private:
    std::map<std::string, Group*> _groups;
    std::string m_departmentName;
    int m_department;
};

#endif // DEPARTMENT_H
