#ifndef COMPANY_H
#define COMPANY_H

#include "department.h"
#include <map>

class Company
{
public:
    Company();
    Company(std::string name, int id)
        :m_companyName(name), m_company(id)
    {}
    void addDepartment(Department *d);
    std::string companyName() const;
    void setCompanyName(const std::string &companyName);
    int company() const;
    void setCompany(int company);

    std::map<std::string, Department *> departments() const;

private:
    std::map<std::string, Department*> _departments;
    std::string m_companyName;
    int m_company;
};

#endif // COMPANY_H
