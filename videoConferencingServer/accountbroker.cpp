#include "accountbroker.h"
#include <cstring>
#include <iostream>

using std::string;
using std::cerr;
using std::endl;

AccountBroker::AccountBroker()
{

}

int AccountBroker::validateForLogin(std::string emailid, std::string passwd, std::string ip)
{
    bool find = false;
    if(!isEmail(emailid))//userid
    {
        auto acc = _userIDToAccounts[emailid];
        if(acc)
        {
            cerr<<"从关联容器userid-account中查找";
            find = true;
            acc->addAccessTime();
            acc->printAccountInfo();
            if(acc->passwd() == passwd)//验证密码
            {
                acc->setState(1);
                acc->setIpAddress(ip);
                changeStateAndIPInDB(emailid, 1, ip);
                _emailToAccounts[acc->email()]->setState(1);
                _emailToAccounts[acc->email()]->setIpAddress(ip);
                return 1;
            }
            else return 0;
        }
    }else {//email
        auto acc = _emailToAccounts[emailid];
        if(acc)
        {
            cerr<<"从关联容器email-account中查找";
            find = true;
            acc->addAccessTime();
            acc->printAccountInfo();
            if(acc->passwd() == passwd)
            {
                acc->setState(1);
                acc->setIpAddress(ip);
                changeStateAndIPInDB(emailid, 1, ip);
                _userIDToAccounts[acc->userID()]->setState(1);
                _userIDToAccounts[acc->userID()]->setIpAddress(ip);
                return 1;
            }
            else return 0;
        }
    }
    if(find == false)
    {
        char *cmd = new char[150];
        if(!isEmail(emailid))
            sprintf(cmd, "select `USERID` , `EMAIL`, `PASSWD` from EmployeesTable where USERID = '%s';", emailid.c_str());
        else
            sprintf(cmd, "select `USERID` , `EMAIL`, `PASSWD` from EmployeesTable where EMAIL = '%s';", emailid.c_str());

        int res = mysql_real_query(mysqlInstance, cmd, strlen(cmd));
        delete [] cmd;
        if(res == 0)
        {
            cerr<<"从数据库中查找";
            string i0, i1, i2;
            i0.clear();i1.clear();i2.clear();
            result = mysql_store_result(mysqlInstance);
            auto row = mysql_num_rows(result);
            if(row == 0) return -1;
            MYSQL_ROW line = mysql_fetch_row(result);
            if(line[0]) i0 = line[0];//userid
            else i0 = "";
            if(line[1]) i1 = line[1];//email
            else i1 = "";
            if(line[2]) i2 = line[2];//passwd
            else i2 = "";
            Account *ac = new Account(i0, i1, i2);
            ac->addAccessTime();
            ac->printAccountInfo();
            _userIDToAccounts[i0] = ac;
            _emailToAccounts[i1] = ac;

            if(i2 == passwd)
            {
                ac->setState(1);
                ac->setIpAddress(ip);
                changeStateAndIPInDB(emailid, 1, ip);
                return 1;
            }
            else return 0;

        }else {
            errorIntoMySQL();
            return -3;
        }
    }
    return -3;
}


void AccountBroker::clearAccounts()
{
    _emailToAccounts.clear();
    _userIDToAccounts.clear();
}

void AccountBroker::exit(std::string emailid)
{
    bool find = false;
    if(!isEmail(emailid))//userid
    {
        auto acc = _userIDToAccounts[emailid];
        if(acc)
        {
            cerr<<"关联容器userid-account中修改";
            find = true;
            acc->setState(0);
            acc->setIpAddress("");
            changeStateAndIPInDB(emailid, 0, "");
            _emailToAccounts[acc->email()]->setState(0);
            _emailToAccounts[acc->email()]->setIpAddress("");
        }
    }else {//email
        auto acc = _emailToAccounts[emailid];
        if(acc)
        {
            cerr<<"关联容器email-account中修改";
            find = true;
            acc->setState(0);
            acc->setIpAddress("");
            changeStateAndIPInDB(emailid, 0, "");
            _userIDToAccounts[acc->userID()]->setState(0);
            _userIDToAccounts[acc->userID()]->setIpAddress("");
        }
    }
    if(find == false)
        changeStateAndIPInDB(emailid, 0, "");
}


void AccountBroker::changeStateAndIPInDB(std::string emailid, int state, std::string ip)
{
    char *cmd = new char[150];
    char *cmd2 = new char[150];
    if(isValidAccount(emailid) == 1)
    {
        sprintf(cmd, "update EmployeesTable set `IP` = '%s' where USERID = '%s';", ip.c_str(), emailid.c_str());
        sprintf(cmd2, "update EmployeesTable set `STATE` = '%d' where USERID = '%s';", state, emailid.c_str());
    }
    else if (isValidAccount(emailid) == 2)
    {
        sprintf(cmd, "update EmployeesTable set `IP` = '%s' where EMAIL = '%s';", ip.c_str(), emailid.c_str());
        sprintf(cmd2, "update EmployeesTable set `STATE` = '%d' where EMAIL = '%s';", state, emailid.c_str());
    }

    if(mysql_real_query(mysqlInstance, cmd, strlen(cmd)) != 0)
        errorIntoMySQL();
    delete [] cmd;
    if(mysql_real_query(mysqlInstance, cmd2, strlen(cmd2)) != 0)
        errorIntoMySQL();
    delete [] cmd2;
    cerr << "状态修改成功" << endl;
}
