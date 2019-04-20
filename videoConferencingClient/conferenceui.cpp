#include "conferenceui.h"

Company *ConferenceUI::company() const
{
    return m_company;
}

void ConferenceUI::setCompany(Company *company)
{
    m_company = company;
}

Employee *ConferenceUI::employee() const
{
    return m_employee;
}

void ConferenceUI::setEmployee(Employee *employee)
{
    m_employee = employee;
}

void ConferenceUI::getLoginInformation(QString account, QString password)
{
//    m_employee->setUserID();
    m_employee->setUserPassword(password);
    m_videoConferencing.requestLogin(account.toStdString(),password.toStdString());
}

void ConferenceUI::getRegisterInformation(QString avator, QString name, QString password, QString company, QString department, QString group, QString phone, QString email)
{
    m_employee->setAvatar(avator);
    m_employee->setRealName(name);
    m_employee->setUserPassword(password);
    m_employee->setCompany(company);
    m_employee->setDepartment(department);
    m_employee->setGroup(group);
    m_employee->setPhone(phone);
    m_employee->setEmail(email);
//    m_videoConferencing.requestRegister(name.toStdString(),password.toStdString(),email.toStdString(),avator.toStdString(),company.toStdString(),department.toStdString(),group.toStdString(),phone.toStdString());
}
