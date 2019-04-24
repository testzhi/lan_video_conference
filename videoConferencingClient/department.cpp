#include "department.h"

QString Department::departmentName() const
{
    return m_departmentName;
}

void Department::setDepartmentName(const QString &departmentName)
{
    m_departmentName = departmentName;
}

QQmlListProperty<Group> Department::groups()
{
    return  QQmlListProperty<Group>(this,nullptr,Department::appendGroup,Department::countGroup,Department::atGroup,Department::clearGroup);
}

Group *Department::getGroup(int i)
{
    return _groups.at(i);
}

int Department::groupCount()
{
    return _groups.count();
}

int Department::employeeCount()
{
    return m_employeesNumber;
}

void Department::insertGroup(Group *group)
{
    m_employeesNumber += group->conciseEmployeeCount();
    _groups.append(group);
}

QString Department::employeesNumber() const
{
    return QString::number(m_employeesNumber);
}

void Department::appendGroup(QQmlListProperty<Group> *groups, Group *group)
{
    Department *department = qobject_cast<Department *>(groups->object);
    if(group) {
        group->setParent(department);
        department->_groups.append(group);
    }
}

int Department::countGroup(QQmlListProperty<Group> *groups)
{
    Department *department = qobject_cast<Department *>(groups->object);
    if(department)
        return department->_groups.count();
    return 0;
}

Group *Department::atGroup(QQmlListProperty<Group> *groups, int i)
{
    Department *department = qobject_cast<Department *>(groups->object);
    if(department)
        return department->_groups.at(i);
    return nullptr;
}

void Department::clearGroup(QQmlListProperty<Group> *groups)
{
    Department *department = qobject_cast<Department *>(groups->object);
    if(department)
        department->_groups.clear();
}
