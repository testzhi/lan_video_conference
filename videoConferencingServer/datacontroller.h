#ifndef DATACONTROLLER_H
#define DATACONTROLLER_H

#include "databasebroker.h"
#include <iostream>

class DataController
{
public:
    DataController()
    {
        db.connectMySQL("localhost", "VideoConferencingServer", "", "VideoConferencingDB", 3306);
        db.createTables();

        ////    mysql -u VideoConferencingServer
        ////    drop database VideoConferencingDB;  create database VideoConferencingDB;     use VideoConferencingDB;
        ////    select * from EmployeesTable; select * from MeetingsTable; select * from AttendeesTable; select * from NotificationsTable;

//        db.insertIntoTableEmployees("5631813", "1717", "Liana",     "563181@qq.com", "TechGROUP1", "Development", "Google","");
//        db.insertIntoTableEmployees("563", "1717", "Liana Xu", "5634@qq.com","TechGROUP1", "Development", "Google","");
//        db.insertIntoTableEmployees("1", "3", "name1", "1@qq.com", "TechGROUP1", "Development", "Google","");
//        db.insertIntoTableEmployees("7", "7", "name7", "16931742@qq.com", "TechGROUP1", "Development", "Google", "");
//        db.insertIntoTableEmployees("6", "6", "name6", "169@qq.com", "TechGROUP1", "Development", "Google","");

//        db.insertIntoTableEmployees("4", "4", "梁组", "9129484@qq.com", "TechGROUP2", "Development", "Google", "");
//        db.insertIntoTableEmployees("5", "5", "凉凉", "912@qq.com", "TechGROUP2", "Development", "Google", "");
//        db.insertIntoTableEmployees("2", "2", "章鱼专用2", "2@qq.com", "TechGROUP2", "Development", "Google", "");
//        db.insertIntoTableEmployees("3", "3", "章鱼", "3@qq.com", "TechGROUP3", "Development", "Google", "");


        std::cout << "建表结束" << std::endl;
    }
    ~DataController();



    void jsonStrCreateRegisteredID(std::string &idJson, std::string email, std::string &id, int &insert);
    void jsonStrVerifyAccountResult(std::string emailid, std::string passwd, std::string &verifyResult, int &result);//result为查询结果，方便服务器判断， verifyresult是给客户端的结果回执
    void jsonStrAccountDetail(std::string emailid,std::string &jsonstr , int &res);
    void jsonStrColleagueDetail(std::string emailid, std::string &jsonstr , int &res);
    void jsonStrInvitationsDetail(std::string emailid, std::string &jsonstr , unsigned long long &res);
    void jsonStrMeetingsDetail(std::string emalid, std::string &jsonstr, unsigned long long &res);
    void jsonStrLaunchMeetingResult(unsigned long long meetingid, std::string &jsonstr);
    void jsonStartMeeting(std::string meetingID, std::string &jsonStr);
    void jsonStopMeeting(std::string meetingID, std::string &jsonStr);
    void jsonNewMeetingAttendeesList(std::string meetingID, std::string &jsonstr);
    void jsonStrNewAttendeeDetail(std::string emailid, std::string meetingID, std::string &jsonstr);
    void jsonExitMeeting(std::string meetingID, std::string userID, std::string &jsonstr);

    //online
    void jsonStrInvitationAddDetail(std::string meetingid, std::string &jsonstr , unsigned long long &res);
    void jsonStrMeetingAddDetail(std::string meetingid, std::string &jsonstr, int &res);
    DataBaseBroker getDb() const;

private:
    DataBaseBroker db;
};

#endif // DATACONTROLLER_H
