#include "group.h"

QString Group::groupName() const
{
    return m_groupName;
}

void Group::setGroupName(const QString &groupName)
{
    m_groupName = groupName;
}

QQmlListProperty<Employee> Group::employees()
{
    return QQmlListProperty<Employee>(this,nullptr,Group::appendEmployee,Group::countEmployee,Group::atEmployee,Group::clearEmployee);
}

Employee *Group::getEmployee(int i)
{
    return _employees.at(i);
}

int Group::employeeCount()
{
    return _employees.count();
}

void Group::insertEmplyee(Employee *employee)
{
    m_employeesNumber++;
    _employees.append(employee);
}

//QString Group::employeesNumber() const
//{
//    return QString::number(m_employeesNumber);
//}

//void Group::setEmployeesNumber(int employeesNumber)
//{
//    m_employeesNumber = employeesNumber;
//}

void Group::appendEmployee(QQmlListProperty<Employee> *employees, Employee *employee)
{
    Group *group = qobject_cast<Group *>(employees->object);
    if(employee) {
        employee->setParent(group);
        group->_employees.append(employee);
    }
}

int Group::countEmployee(QQmlListProperty<Employee> *employees)
{
    Group *group = qobject_cast<Group *>(employees->object);
    if(group)
        return group->_employees.count();
    return 0;
}

Employee *Group::atEmployee(QQmlListProperty<Employee> *employees, int i)
{
    Group *group = qobject_cast<Group *>(employees->object);
    if(group)
        return group->_employees.at(i);
    return nullptr;
}

void Group::clearEmployee(QQmlListProperty<Employee> *employees)
{
    Group *group = qobject_cast<Group *>(employees->object);
    if(group)
        group->_employees.clear();
}
