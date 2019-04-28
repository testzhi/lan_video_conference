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
        ////    drop database VideoConferencingDB;
        ////    create database VideoConferencingDB;
        ////
        ///

        ////    select * from EmployeesTable;
        ////    select * from MeetingsTable;
        ////    select * from AttendeesTable;
        ////    select * from NotificationsTable;

        //    //    db.insertIntoTableEmployees("test", "passwd", "TEST测试名", "test@qq.com", "AVATAR", "TESTGROUP", "TESTDEPARTMENT", "Google","phone", "ip");
//            db.insertIntoTableEmployees("5631813", "1717", "Liana",     "563181354@qq.com", "TechGROUP1", "Development", "Google","");
//            db.insertIntoTableEmployees("563", "1717", "Liana Xu", "5634@qq.com","TechGROUP1", "Development", "Google","");
//            db.insertIntoTableEmployees("1", "1", "name1", "1@qq.com", "TechGROUP1", "Development", "Google","");
//            db.insertIntoTableEmployees("1693174", "1693", "Liang Zhidong", "1693174982@qq.com", "TechGROUP1", "Development", "Google", "");
//            db.insertIntoTableEmployees("169", "1693", "Liang", "169@qq.com", "TechGROUP1", "Development", "Google","");

//            db.insertIntoTableEmployees("9129450", "5995", "Li Zhangyu", "912945084@qq.com", "TechGROUP2", "Development", "Google", "");
//            db.insertIntoTableEmployees("912", "5995", "Li", "912@qq.com", "TechGROUP2", "Development", "Google", "");
//            db.insertIntoTableEmployees("2", "2", "name2", "2@qq.com", "TechGROUP2", "Development", "Google", "");

//            db.insertIntoTableEmployees("3", "3", "3", "3@qq.com", "TechGROUP3", "Development", "Google", "");


//            db.insertIntoTableEmployees("111", "111", "name1", "111@163.com", "GROUP1", "Department1", "Company1", "");

//            db.insertIntoTableEmployees("222", "222", "name2", "222@163.com", "Group2", "Department2", "company2", "");

//            db.insertIntoTableEmployees("7418907", "7418", "Zhang Jinming", "741890707@qq.com", "Analysis", "BigData", "Baidu","");
//            db.insertIntoTableEmployees("1018772", "1018", "Lu Xingyu", "1018772325@qq.com", "test1", "Test", "Baidu","");
//            db.insertIntoTableEmployees("741", "7418", "Zhang", "741@qq.com", "Analysis", "BigData", "Baidu","");
//            db.insertIntoTableEmployees("101", "1018", "Lu", "1018772325@qq.com", "test1", "Test", "Baidu","");

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

    //online
    void jsonStrInvitationAddDetail(std::string meetingid, std::string &jsonstr , unsigned long long &res);
    void jsonStrMeetingAddDetail(std::string meetingid, std::string &jsonstr, int &res);
    DataBaseBroker getDb() const;

private:
    DataBaseBroker db;
};

#endif // DATACONTROLLER_H
