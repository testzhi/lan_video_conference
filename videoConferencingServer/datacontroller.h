#ifndef DATACONTROLLER_H
#define DATACONTROLLER_H

#include "databasebroker.h"

class DataController
{
public:
    DataController();
    ~DataController();



    void jsonStrCreateRegisteredID(std::string &idJson, std::string email, std::string &id, int &insert);
    void jsonStrVerifyAccountResult(std::string emailid, std::string passwd, std::string &verifyResult, int &result);//result为查询结果，方便服务器判断， verifyresult是给客户端的结果回执
    void jsonStrAccountDetail(std::string emailid,std::string &jsonstr , int &res);
    void jsonStrColleagueDetail(std::string emailid, std::string &jsonstr , int &res);
    void jsonStrInvitationsDetail(std::string emailid, std::string &jsonstr , unsigned long long &res);
    void jsonStrMeetingsDetail(std::string emalid, std::string &jsonstr, unsigned long long &res);
    void jsonStrLaunchMeetingResult(unsigned long long meetingid, std::string &jsonstr);

    //online
    void jsonStrInvitationAddDetail(std::string meetingid, std::string &jsonstr , unsigned long long &res);
    void jsonStrMeetingAddDetail(std::string meetingid, std::string &jsonstr, int &res);
    DataBaseBroker getDb() const;

private:
    DataBaseBroker db;
};

#endif // DATACONTROLLER_H
