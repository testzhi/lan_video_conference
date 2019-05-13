#include "company.h"

Company::Company()
{

}

void Company::addDepartment(Department *d)
{
    auto depa = _departments[d->departmentName()];
    if(!depa)
        _departments[d->departmentName()] = d;
}

std::string Company::companyName() const
{
    return m_companyName;
}

void Company::setCompanyName(const std::string &companyName)
{
    m_companyName = companyName;
}

int Company::company() const
{
    return m_company;
}

void Company::setCompany(int company)
{
    m_company = company;
}

std::map<std::string, Department *> Company::departments() const
{
    return _departments;
}
