#include "company.h"

QString Company::companyName() const
{
    return m_companyName;
}

void Company::setCompanyName(const QString &companyName)
{
    m_companyName = companyName;
}

QQmlListProperty<Department> Company::departments()
{
    return QQmlListProperty<Department>(this,nullptr,Company::appendDepartment,Company::countDepartment,Company::atDepartment,Company::clearDepartment);
}

Department *Company::getDepartment(int i)
{
    return _departments.at(i);
}

int Company::departmentCount()
{
    return _departments.count();
}

void Company::insertDepartment(Department *department)
{
    m_employeesNumber += department->employeesNumber().toInt();
    _departments.append(department);
}

QString Company::employeesNumber() const
{
    return QString::number(m_employeesNumber);
}

void Company::appendDepartment(QQmlListProperty<Department> *departments,Department *department){
    Company *company = qobject_cast<Company *>(departments->object);
    if(department) {
        department->setParent(company);
        company->_departments.append(department);
    }
}

int Company::countDepartment(QQmlListProperty<Department> *departments)
{
    Company *company = qobject_cast<Company *>(departments->object);
    if(company)
        return company->_departments.count();
    return 0;
}

Department *Company::atDepartment(QQmlListProperty<Department> *departments,int i)
{
    Company *company = qobject_cast<Company *>(departments->object);
    if(company)
        return company->_departments.at(i);
    return nullptr;
}

void Company::clearDepartment(QQmlListProperty<Department> *departments)
{
    Company *company = qobject_cast<Company *>(departments->object);
    if(company) {
        company->_departments.clear();
    }
}
