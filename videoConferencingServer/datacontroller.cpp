#include "datacontroller.h"
#include <ctime>
#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonArray>
#include <QVariant>
#include <QDebug>
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>

using std::vector;
using std::string;
using std::cout;
using std::endl;

DataController::DataController()
{
    db.connectMySQL("localhost", "VideoConferencingServer", "", "VideoConferencingDB", 3306);
    db.createTables();
//            db.insertIntoTableEmployees("5631813", "1717", "Liana", "563181354@qq.com", "TechGROUP1", "Development", "Google","");
//            db.insertIntoTableEmployees("9129450", "5995", "Li Zhangyu", "912945084@qq.com", "TechGROUP2", "Development", "Google", "");
//            db.insertIntoTableEmployees("1693174", "1693", "Liang Zhidong", "1693174982@qq.com", "TechGROUP1", "Development", "Google", "18889999333","");
//            db.insertIntoTableEmployees("1", "1", "1", "1@qq.com", "TechGROUP1", "Development", "Google","");
//            db.insertIntoTableEmployees("2", "2", "2", "2@qq.com", "TechGROUP2", "Development", "Google", "");
//            db.insertIntoTableEmployees("3", "3", "3", "2@qq.com", "TechGROUP2", "Development", "Google", "");
//            db.insertIntoTableEmployees("7418907", "7418", "Zhang Jinming", "741890707@qq.com", "Analysis", "BigData", "Baidu","11111111111","");
//            db.insertIntoTableEmployees("1018772", "1018", "Lu Xingyu", "1018772325@qq.com", "test1", "Test", "Baidu","");
//            db.insertIntoTableEmployees("563", "1717", "Liana", "5634@qq.com","TechGROUP1", "Development", "Google","");
//            db.insertIntoTableEmployees("912", "5995", "Li", "912@qq.com", "TechGROUP2", "Development", "Google", "");
//            db.insertIntoTableEmployees("169", "1693", "Liang", "169@qq.com", "TechGROUP1", "Development", "Google", "18889999233","");
//            db.insertIntoTableEmployees("741", "7418", "Zhang", "741@qq.com", "Analysis", "BigData", "Baidu","11111111112","");
//            db.insertIntoTableEmployees("101", "1018", "Lu", "1018772325@qq.com", "test1", "Test", "Baidu","");
//            db.insertIntoTableEmployees("111", "111", "name1", "111@163.com", "GROUP1", "Department1", "Company1","11111111111");
//            db.insertIntoTableEmployees("222", "222", "name2", "222@163.com", "Group2", "Department2", "company2","12121212122");

//            db.insertIntoTableMeetings("1","1","2019-05-10","20:00", 1, "meeting1",10,30,"1--assistant-speaker");
//            db.insertIntoTableAttendees("1","1");
//            db.insertIntoTableNotifications("2", "1", 1, "subject", 0, "1");
//            db.insertIntoTableNotifications("169", "1", 1, "subject", 0, "1");
//            db.insertIntoTableNotifications("1693174", "1", 1, "subject", 0, "1");
//            db.insertIntoTableAttendees("1", "2");
//            db.insertIntoTableAttendees("1", "169");
//            db.insertIntoTableAttendees("1", "1693174");

//            db.insertIntoTableMeetings("169","1","2019-05-17","21:00", 1, "meeting2",10,30,"1-speaker");
//            db.insertIntoTableAttendees("2","169");
//            db.insertIntoTableAttendees("2","1");
//            db.insertIntoTableNotifications("2","169",1,"evening meeting",0,"2");
//            db.insertIntoTableNotifications("1693174","169",1,"evening meeting",0,"2");
//            db.insertIntoTableAttendees("2","2");
//            db.insertIntoTableAttendees("2","1693174");

//            db.insertIntoTableMeetings("1693174","1","2019-05-19","23:00", 1, "meeting3",10,30,"1-speaker");
//            db.insertIntoTableAttendees("3","1693174");
//            db.insertIntoTableAttendees("3","1");

//            db.insertIntoTableMeetings("563","1","2019-04-17","11:00", 1, "meeting4",10,30,"1-speaker");
//            db.insertIntoTableAttendees("4","563");
//            db.insertIntoTableAttendees("4","1");
//            db.updateMeetingStateByMeetingID("4",2);

//            db.insertIntoTableMeetings("563","2","2019-05-11","10:00", 1, "meeting5",10,30,"2-speaker");
//            db.insertIntoTableAttendees("5","563");
//            db.insertIntoTableAttendees("5","2");
//            db.insertIntoTableNotifications("1", "563", 1, "morning date", 0, "5");
//            db.insertIntoTableNotifications("169", "563", 1, "morning date", 0, "5");
//            db.insertIntoTableNotifications("2", "563", 1, "morning date", 0, "5");
//            db.insertIntoTableNotifications("5631813", "563", 1, "morning date", 0, "5");
//            db.insertIntoTableNotifications("912", "563", 1, "morning date", 0, "5");
//            db.insertIntoTableNotifications("9129450", "563", 1, "morning date", 0, "5");
//            db.insertIntoTableAttendees("5","1");
//            db.insertIntoTableAttendees("5","169");
//            db.insertIntoTableAttendees("5","2");
//            db.insertIntoTableAttendees("5","5631813");
//            db.insertIntoTableAttendees("5","912");
//            db.insertIntoTableAttendees("5","9129450");

//            db.insertIntoTableMeetings("2","563","2019-05-12","14:00", 1, "meeting8",10,30,"563-speaker");
//            db.insertIntoTableAttendees("6","2");
//            db.insertIntoTableAttendees("6","563");
//            db.insertIntoTableNotifications("1", "2", 1, "morning date", 0, "6");
//            db.insertIntoTableNotifications("169", "2", 1, "morning date", 0, "6");
//            db.insertIntoTableNotifications("2", "2", 1, "morning date", 0, "6");
//            db.insertIntoTableNotifications("5631813", "2", 1, "morning date", 0, "6");
//            db.insertIntoTableNotifications("912", "2", 1, "morning date", 0, "6");
//            db.insertIntoTableNotifications("9129450", "2", 1, "morning date", 0, "6");
//            db.insertIntoTableAttendees("6","1");
//            db.insertIntoTableAttendees("6","169");
//            db.insertIntoTableAttendees("6","2");
//            db.insertIntoTableAttendees("6","5631813");
//            db.insertIntoTableAttendees("6","912");
//            db.insertIntoTableAttendees("6","9129450");

    cout << "建表结束" << endl;
}

DataController::~DataController()
{
    db.closeMySQL();
}

void DataController::jsonStrCreateRegisteredID(std::string &idJson, string email, string &id, int &insert)
{
    idJson.clear();
    id.clear();

    int rr = db.canRegister(email);
    QJsonObject data;
    if(!rr)
    {
        data.insert("RESULT", "-1");
        data.insert("USERID", "");
        data.insert("EMAIL", email.c_str());
        data.insert("ERROR", "The email HAS BEEN REGISTERED.");
        insert = -1;
    }else {
        auto low = 1000000;
        auto high = 9999999;
        srand(time(nullptr));
        long int rnum = rand()%(high-low+1)+low;
        string iid =std::to_string(rnum);
        id =iid;
        while(!db.canRegister(iid))
        {
            srand(time(nullptr));
            rnum = rand()%(high-low+1)+low;
            iid =std::to_string(rnum);
            id = iid;
        }
        data.insert("RESULT", "1");
        data.insert("USERID", id.c_str());
        data.insert("EMAIL", email.c_str());
        data.insert("ERROR", "");
        insert = 1;
    }

    QJsonObject jsonMsg;
    jsonMsg.insert("DATA", data);
    jsonMsg.insert("TYPE", "_REGISTER");
    QJsonDocument document;
    document.setObject(jsonMsg);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    string strJson(byteArray);
    idJson = strJson;
    cout << strJson << endl;
}

void DataController::jsonStrVerifyAccountResult(std::string emailid, std::string passwd, std::string &verifyResult, int &result)
{
    verifyResult.clear();
    vector<string> data;
    data.clear();
    int i = db.queryResultForLogin(emailid, data);
    string err;
    string res; res.clear();
    if(i == -1)
    {
        err = string(db.getErrorInfo());
        result = -1;
    }
    else if (i == 0)
    {
        err = "InvalidAccount";
        result = -1;
        res = "-1";
    }
    else
    {
        if(passwd ==  data[2])
        {
            int state = atoi(data[3].c_str());

            //            if(state == 0)
            //            {
            err="";
            result = 1;
            res = "1";
            //            }
            //            else
            //            {
            //                err="Repeat Login";
            //                result = -3;
            //                res = "-3";
            //            }
        }
        else
        {
            err = "WrongPassword";
            result = -2;
            res = "-2";
        }
    }

    QJsonObject dd;
    dd.insert("RESULT", res.c_str());
    dd.insert("ERROR", err.c_str());
    dd.insert("EMAILID", emailid.c_str());
    QJsonObject jsonMsg;
    jsonMsg.insert("DATA", dd);
    jsonMsg.insert("TYPE", "_LOGIN");
    QJsonDocument document;
    document.setObject(jsonMsg);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    string strJson(byteArray);
    verifyResult = strJson;
    cout << strJson << endl;
}

void DataController::jsonStrAccountDetail(string emailid, string &jsonstr, int &res)
{
    vector<string> data;
    res = db.queryEmployeeInfoByEmailID(emailid, data);
    QJsonObject dd;
    dd.insert("USERID", data[0].c_str());
    dd.insert("EMAIL", data[1].c_str());
    dd.insert("REALNAME", data[2].c_str());
    dd.insert("AVATAR", data[3].c_str());
    dd.insert("COMPANY", data[5].c_str());
    dd.insert("DEPARTMENT", data[6].c_str());
    dd.insert("GROUP", data[7].c_str());
    dd.insert("PHONE", data[4].c_str());
    QJsonObject jsonMsg;
    jsonMsg.insert("DATA", dd);
    jsonMsg.insert("TYPE", "_INITIALIZE_ACCOUNT_DETAIL");
    QJsonDocument document;
    document.setObject(jsonMsg);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    string strJson(byteArray);
    jsonstr = strJson;
    cout << strJson << endl;
}

void DataController::jsonStrColleagueDetail(std::string emailid, std::string &jsonstr, int &res)
{

    string comid;
    int r = db.queryCompanyOfEmployeeID(emailid, comid);
    QJsonArray departmentsArray;
    if(r != 1)
        res = 0;
    else
    {
        vector<vector<string>> depas;
        unsigned long long p = db.queryDepartmentsInCompany(comid,depas);
        if(p == 0) res = 0;
        for (auto &i:depas)
        {
            QJsonObject aDepartment;
            aDepartment.insert("DEPARTMENTNAME", i[0].c_str());
            vector<vector<string>> gros;
            db.queryGroupsInDepartments(i[1], gros);
            QJsonArray groupsInDepartment;
            for(auto &j:gros)
            {
                QJsonObject aGroup;
                aGroup.insert("GROUPNAME", j[0].c_str());
                vector<vector<string>> empls;
                unsigned long long pp = db.queryColleagueInfoByGroupID(j[1], empls);
                if(pp == 0) res = 0;
                QJsonArray employeesInAGroup;
                for(auto &k:empls)
                {
                    QJsonObject employee;
                    employee.insert("USERID", k[0].c_str());
                    employee.insert("EMAIL", k[1].c_str());
                    employee.insert("REALNAME", k[2].c_str());
                    employee.insert("AVATAR", k[3].c_str());
                    employee.insert("PHONE", k[4].c_str());
                    employeesInAGroup.insert(0, employee);
                }
                aGroup.insert("EMPLOYEES", employeesInAGroup);
                groupsInDepartment.insert(0, aGroup);
            }
            aDepartment.insert("GROUPS",groupsInDepartment);
            departmentsArray.insert(0, aDepartment);

        }
    }
    QJsonObject data;
    data.insert("DEPARTMENTS", departmentsArray);
    QJsonObject json;
    json.insert("DATA", QJsonValue(data));
    json.insert("TYPE", "_INITIALIZE_COLLEAGUE_LIST");
    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    std::string strJson(byteArray);
    jsonstr = strJson;
    res = 1;
}

void DataController::jsonStrInvitationsDetail(std::string emailid, std::string &jsonstr, unsigned long long &res)
{
    vector<vector<string>> invi;
    res = db.queryInvitationsUndisposed(emailid, invi);
    QJsonObject json;
    QJsonObject data;
    QJsonArray invitationsArray;
    if(res != 0)
    {
        res = 1;

        for (auto &anInvi: invi)
        {
            QJsonObject meeting;
            vector<string> data;
            db.queryMeetingOfInvitionInfo(anInvi[5], data);

            meeting.insert("INITIATOR", data[1].c_str());
            meeting.insert("ASSISTANT", data[2].c_str());
            meeting.insert("SPEAKER", data[3].c_str());
            meeting.insert("DATE", data[4].c_str());
            meeting.insert("TIME", data[5].c_str());
            meeting.insert("SUBJECT", data[7].c_str());
            //            meeting.insert("MEETINGNAME", data[8].c_str());
            //            meeting.insert("OWNUNIT", data[9].c_str());
            meeting.insert("MEETINGSCALE", data[10].c_str());
            meeting.insert("PREDICTEDDURATION", data[11].c_str());
            meeting.insert("MEETINGSTATE", data[14].c_str());
            meeting.insert("REMARK", data[15].c_str());
            invitationsArray.insert(0, meeting);
        }
    }
    data.insert("INVITATIONS", invitationsArray);
    json.insert("DATA", QJsonValue(data));
    json.insert("TYPE", "_INITIALIZE_MEETING_INVITATIONS_LIST");
    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    std::string strJson(byteArray);
    jsonstr = strJson;

}

void DataController::jsonStrMeetingsDetail(std::string emalid, std::string &jsonstr, unsigned long long &res)
{
    vector<string> meetingIds;
    res = db.queryMeetingsIDByUserID(emalid, meetingIds);
    if(res != 0)
    {
        res = 1;
        QJsonArray meetingsArray;
        for (auto &anID: meetingIds) {

            vector<string> data;
            auto m = db.queryMeetingDetailsOnlyByMeetingID(anID, data);

            if(m > 0)
            {
                if(atoi(data[14].c_str()) == 2)
                {
                    QJsonObject meeting;
                    meeting.insert("INITIATOR", data[1].c_str());
                    meeting.insert("ASSISTANT", data[2].c_str());
                    meeting.insert("SPEAKER", data[3].c_str());
                    meeting.insert("DATE", data[4].c_str());
                    meeting.insert("TIME", data[5].c_str());
                    meeting.insert("SUBJECT", data[7].c_str());
                    //            meeting.insert("MEETINGNAME", data[8].c_str());
                    //            meeting.insert("OWNUNIT", data[9].c_str());
                    meeting.insert("MEETINGSCALE", data[10].c_str());
                    meeting.insert("PREDICTEDDURATION", data[11].c_str());
                    meeting.insert("MEETINGSTATE", data[14].c_str());
                    meeting.insert("REMARK", data[15].c_str());
                    meetingsArray.insert(0, meeting);
                }
            }

        }
        QJsonObject data;
        data.insert("MEETINGS", meetingsArray);
        QJsonObject json;
        json.insert("DATA", QJsonValue(data));
        json.insert("TYPE", "_INITIALIZE_MEETINGS_LIST");
        QJsonDocument document;
        document.setObject(json);
        QByteArray byteArray = document.toJson(QJsonDocument::Compact);
        std::string strJson(byteArray);
        jsonstr = strJson;
    }
}

void DataController::jsonStrLaunchMeetingResult(unsigned long long meetingid, std::string &jsonstr)
{
    QJsonObject data;
    if(meetingid != 0)
    {
        string ss = std::to_string(meetingid);
        data.insert("MEETINGID", ss.c_str());
        data.insert("RESULT", "1");
    }else
    {
        data.insert("MEETINGID", "");
        data.insert("RESULT", "0");
    }

    QJsonObject json;
    json.insert("DATA", QJsonValue(data));
    json.insert("TYPE", "_LAUNCH_MEETING_RESULT");
    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    std::string strJson(byteArray);
    jsonstr = strJson;
}

DataBaseBroker DataController::getDb() const
{
    return db;
}
