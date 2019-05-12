#ifndef ACCOUNTBROKER_H
#define ACCOUNTBROKER_H

#include "databasebroker.h"
#include "account.h"
#include <string>
#include <map>

class AccountBroker : public DataBaseBroker
{
public:
    AccountBroker();
    int validateForLogin(std::string emailid, std::string passwd, std::string ip);
    void clearAccounts();
    void clearUpSeldomeAccessAccounts()
    {}
    void exit(std::string emailid);

private:
    void changeStateAndIPInDB(std::string emailid, int state, std::string ip);

private:
    std::map<std::string, Account*> _emailToAccounts;
    std::map<std::string, Account*> _userIDToAccounts;
};

#endif // ACCOUNTBROKER_H
