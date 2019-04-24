#include "group.h"

QString Group::groupName() const
{
    return m_groupName;
}

void Group::setGroupName(const QString &groupName)
{
    m_groupName = groupName;
}

ConciseEmployee *Group::getConciseEmployee(int i)
{
    return _conciseEmployees.at(i);
}

int Group::conciseEmployeeCount()
{
    return _conciseEmployees.count();
}

void Group::insertConciseEmployee(ConciseEmployee *employee)
{
    m_employeesNumber++;
    _conciseEmployees.append(employee);
}

void Group::appendConciseEmployee(QQmlListProperty<ConciseEmployee> *ces, ConciseEmployee *ce)
{
    Group *group = qobject_cast<Group *>(ces->object);
    if(ce) {
        ce->setParent(group);
        group->_conciseEmployees.append(ce);
    }
}

int Group::countConciseEmployee(QQmlListProperty<ConciseEmployee> *ces)
{
    Group *group = qobject_cast<Group *>(ces->object);
    if(group)
        return group->_conciseEmployees.count();
    return 0;
}

ConciseEmployee *Group::atConciseEmployee(QQmlListProperty<ConciseEmployee> *ces, int i)
{
    Group *group = qobject_cast<Group *>(ces->object);
    if(group)
        return group->_conciseEmployees.at(i);
    return nullptr;
}

void Group::clearConciseEmployee(QQmlListProperty<ConciseEmployee> *ces)
{
    Group *group = qobject_cast<Group *>(ces->object);
    if(group)
        group->_conciseEmployees.clear();
}

QQmlListProperty<ConciseEmployee> Group::conciseEmployees()
{
    return QQmlListProperty<ConciseEmployee>(this,nullptr,Group::appendConciseEmployee,Group::countConciseEmployee,Group::atConciseEmployee,Group::clearConciseEmployee);
}

//QList<ConciseEmployee *> Group::conciseEmployee() const
//{
//    return _conciseEmployee;
//}

//void Group::setConciseEmployee(const QList<ConciseEmployee *> &conciseEmployee)
//{
//    _conciseEmployee = conciseEmployee;
//}

//Employee *Group::getEmployee(int i)
//{
//    return _employees.at(i);
//}

//int Group::employeeCount()
//{
//    return _employees.count();
//}

//void Group::insertEmplyee(Employee *employee)
//{
//    m_employeesNumber++;
//    _employees.append(employee);
//}

int Group::employeesNumber() const
{
    return m_employeesNumber;
}

void Group::setEmployeesNumber(int employeesNumber)
{
    m_employeesNumber = employeesNumber;
}

//void Group::appendEmployee(QQmlListProperty<Employee> *employees, Employee *employee)
//{
//    Group *group = qobject_cast<Group *>(employees->object);
//    if(employee) {
//        employee->setParent(group);
//        group->_employees.append(employee);
//    }
//}

//int Group::countEmployee(QQmlListProperty<Employee> *employees)
//{
//    Group *group = qobject_cast<Group *>(employees->object);
//    if(group)
//        return group->_employees.count();
//    return 0;
//}

//Employee *Group::atEmployee(QQmlListProperty<Employee> *employees, int i)
//{
//    Group *group = qobject_cast<Group *>(employees->object);
//    if(group)
//        return group->_employees.at(i);
//    return nullptr;
//}

//void Group::clearEmployee(QQmlListProperty<Employee> *employees)
//{
//    Group *group = qobject_cast<Group *>(employees->object);
//    if(group)
//        group->_employees.clear();
//}

QString ConciseEmployee::userID() const
{
    return m_userID;
}

void ConciseEmployee::setUserID(const QString &userID)
{
    m_userID = userID;
}

QString ConciseEmployee::realName() const
{
    return m_realName;
}

void ConciseEmployee::setRealName(const QString &realName)
{
    m_realName = realName;
}
