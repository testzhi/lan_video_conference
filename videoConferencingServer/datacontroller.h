#ifndef DATACONTROLLER_H
#define DATACONTROLLER_H

#include "databasebroker.h"

class DataController
{
public:
    DataController();
    ~DataController();


    std::vector<std::string> getEmployeeInfo(std::string emailID);

    void jsonStrCreateRegisteredID(std::string &idJson, std::string email, std::string &id, int &insert);
    void jsonStrVerifyAccountResult(std::string emailid, std::string passwd, std::string &verifyResult, int &result);//result为查询结果，方便服务器判断， verifyresult是给客户端的结果回执
    void jsonStrAccountDetail(std::string emailid,std::string &jsonstr , int &res);


    DataBaseBroker getDb() const;

private:
    DataBaseBroker db;
};

#endif // DATACONTROLLER_H
