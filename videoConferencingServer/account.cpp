#include "account.h"
#include <iostream>

using std::cerr;
using std::endl;

std::string Account::userID() const
{
    return m_userID;
}

std::string Account::passwd() const
{
    return m_passwd;
}

std::string Account::email() const
{
    return m_email;
}

void Account::addAccessTime()
{
    ++m_accessTimes;
}

void Account::printAccountInfo(){
cerr << "account--id: " << m_userID << "  email: " << m_email << "    passwd: " << m_passwd << "    accessTimes: " << m_accessTimes << endl;
}

std::string Account::ipAddress() const
{
    return m_ipAddress;
}

void Account::setIpAddress(const std::string &ipAddress)
{
    m_ipAddress = ipAddress;
}

int Account::state() const
{
    return m_state;
}

void Account::setState(int state)
{
    m_state = state;
}
