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
        err = db.getErrorInfo();
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
    dd.insert("COMPANY", data[7].c_str());
    dd.insert("DEPARTMENT", data[6].c_str());
    dd.insert("GROUP", data[5].c_str());
    dd.insert("PHONE", data[4].c_str());
    QJsonObject jsonMsg;
    jsonMsg.insert("DATA", dd);
    jsonMsg.insert("TYPE", "_INITIALIZE_ACCOUNT_DETAIL");
    QJsonDocument document;
    document.setObject(jsonMsg);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    string strJson(byteArray);
    jsonstr = strJson;
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
    QJsonObject qdata;
    QJsonArray invitationsArray;
    if(res != 0)
    {
        for (auto &anInvi: invi)
        {
            QJsonObject meeting;
            vector<string> data;
            auto meetingNumber = db.queryMeetingOfInvitionInfo(anInvi[5], data);
            if(meetingNumber != 0)
            {
                meeting.insert("MEETINGID", data[0].c_str());
                //            meeting.insert("INITIATOR", data[1].c_str());
                meeting.insert("ASSISTANT", data[2].c_str());
                string assistantName;   assistantName.clear();
                db.queryNameByUserID(data[2], assistantName);
                meeting.insert("ASSISTANTNAME", data[2].c_str());
                meeting.insert("SPEAKER", data[3].c_str());
                string speakerName;     speakerName.clear();
                db.queryNameByUserID(data[3], speakerName);
                meeting.insert("SPEAKERNAME", speakerName.c_str());
                meeting.insert("DATE", data[4].c_str());
                meeting.insert("TIME", data[5].c_str());
                meeting.insert("SUBJECT", data[7].c_str());
                //            meeting.insert("MEETINGNAME", data[8].c_str());
                //            meeting.insert("OWNUNIT", data[9].c_str());
                //                            meeting.insert("MEETINGSCALE", data[10].c_str());
                //            meeting.insert("PREDICTEDDURATION", data[11].c_str());
                //            meeting.insert("MEETINGSTATE", data[14].c_str());
                meeting.insert("REMARK", data[15].c_str());
                invitationsArray.insert(0, meeting);
            }
        }
    }
    qdata.insert("INVITATIONS", invitationsArray);
    json.insert("DATA", QJsonValue(qdata));
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
    res = db.queryUnfinishedMeetingsIDByUserID(emalid, meetingIds);
    cout << "Unfinished meetingLLLLLLLLLLLLL" << res << endl;
    QJsonArray meetingsArray;
    if(res != 0)
    {
        for (auto &anID: meetingIds)
        {
            vector<string> data;
            auto m = db.queryMeetingDetailsOnlyByMeetingID(anID, data);
            if(m > 0)
            {
                cout << "llll当前会议状态llll" << data[14] << endl;
                if(atoi(data[14].c_str()) != 2)//未结束会议
                {
                    cout << "eeeeeeeeeeeeeeeee" <<endl;
                    QJsonObject meeting;
                    meeting.insert("MEETINGID", data[0].c_str());
                    //                    meeting.insert("INITIATOR", data[1].c_str());
                    meeting.insert("ASSISTANT", data[2].c_str());
                    string assistantName; assistantName.clear();
                    db.queryNameByUserID(data[2], assistantName);
                    meeting.insert("ASSISTANTNAME", assistantName.c_str());
                    meeting.insert("SPEAKER", data[3].c_str());
                    string speakerName; speakerName.clear();
                    db.queryNameByUserID(data[3], speakerName);
                    meeting.insert("SPEAKERNAME", speakerName.c_str());
                    meeting.insert("DATE", data[4].c_str());
                    meeting.insert("TIME", data[5].c_str());
                    meeting.insert("CATEGORY", data[6].c_str());
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
    }
    QJsonObject qdata;
    qdata.insert("MEETINGS", meetingsArray);
    QJsonObject json;
    json.insert("DATA", QJsonValue(qdata));
    json.insert("TYPE", "_INITIALIZE_MEETINGS_LIST");
    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    std::string strJson(byteArray);
    jsonstr = strJson;
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

void DataController::jsonStartMeeting(std::string meetingID, std::string &jsonStr)
{
    QJsonObject data;
    data.insert("MEETINGID", meetingID.c_str());

    QJsonObject json;
    json.insert("DATA", QJsonValue(data));
    json.insert("TYPE", "_ONLINE_START_A_MEETING");
    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    std::string strJson(byteArray);
    jsonStr = strJson;
}

void DataController::jsonStopMeeting(std::string meetingID, std::string &jsonStr)
{
    QJsonObject data;
    data.insert("MEETINGID", meetingID.c_str());

    QJsonObject json;
    json.insert("DATA", QJsonValue(data));
    json.insert("TYPE", "_ONLINE_STOP_A_MEETING");
    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    std::string strJson(byteArray);
    jsonStr = strJson;
}

void DataController::jsonNewMeetingAttendeesList(std::string meetingID, std::string &jsonstr)
{
    QJsonObject data;
    data.insert("MEETINGID", meetingID.c_str());

    QJsonArray attendeesArray;
    vector<string> attendees;
    db.queryAttendeesByStateAndMeetingID(meetingID, 2, attendees);
    if(!attendees.empty())
    {
        for(auto &a:attendees)
        {
            vector<string> userInfo;
            db.queryEmployeeInfoByEmailID(a, userInfo);
            QJsonObject user;
            user.insert("USERID", userInfo[0].c_str());
            user.insert("AVATAR",userInfo[3].c_str());
            user.insert("EMAIL",userInfo[1].c_str());
            user.insert("REALNAME",userInfo[2].c_str());
            //                user.insert("DEPARTMENTNAME",userInfo[6].c_str());
            //                user.insert("GROUPNAME",userInfo[5].c_str());
            //                user.insert("COMPANYNAME",userInfo[7].c_str());
            //                user.insert("PHONE",userInfo[4].c_str());
            //            user.insert();//权限
            attendeesArray.insert(0, user);
        }
    }
    data.insert("ATTENDEES", attendeesArray);
    QJsonObject json;
    json.insert("DATA", QJsonValue(data));
    json.insert("TYPE", "_ONLINE_MEETING_ATTENDEES_LIST");
    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    std::string strJson(byteArray);
    jsonstr = strJson;
}

void DataController::jsonStrNewAttendeeDetail(std::string emailid, std::string meetingID, std::string &jsonstr)
{
    cout <<"++++++++++++++"<<endl;
    vector<string> data;
    db.queryEmployeeInfoByEmailID(emailid, data);
    QJsonObject dd;
    dd.insert("USERID", data[0].c_str());
    dd.insert("EMAIL", data[1].c_str());
    dd.insert("REALNAME", data[2].c_str());
    dd.insert("AVATAR", data[3].c_str());
    dd.insert("MEETINGID", meetingID.c_str());
    //    dd.insert("COMPANY", data[5].c_str());
    //    dd.insert("DEPARTMENT", data[6].c_str());
    //    dd.insert("GROUP", data[7].c_str());
    //    dd.insert("PHONE", data[4].c_str());
    QJsonObject jsonMsg;
    jsonMsg.insert("DATA", dd);
    jsonMsg.insert("TYPE", "_ONLINE_ATTENDEE");
    QJsonDocument document;
    document.setObject(jsonMsg);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    string strJson(byteArray);
    jsonstr = strJson;
}

void DataController::jsonExitMeeting(std::string meetingID, std::string userID, std::string &jsonstr)
{
    QJsonObject data;
    data.insert("MEETINGID", meetingID.c_str());
    data.insert("USERID", userID.c_str());

    QJsonObject json;
    json.insert("DATA", QJsonValue(data));
    json.insert("TYPE", "_ONLINE_EXIT_A_MEETING");
    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    std::string strJson(byteArray);
    jsonstr = strJson;
}

void DataController::jsonStrInvitationAddDetail(std::string meetingid, std::string &jsonstr, unsigned long long &res)
{
    QJsonObject json;
    QJsonObject qdata;

    vector<string> data;
    res = db.queryMeetingOfInvitionInfo(meetingid, data);
    if(res != 0)
    {
        qdata.insert("MEETINGID", data[0].c_str());
        //            meeting.insert("INITIATOR", data[1].c_str());
        qdata.insert("ASSISTANT", data[2].c_str());
        string assistantName; assistantName.clear();
        db.queryNameByUserID(data[2], assistantName);
        qdata.insert("ASSISTANTNAME", assistantName.c_str());
        qdata.insert("SPEAKER", data[3].c_str());
        string speakerName; speakerName.clear();
        db.queryNameByUserID(data[3], speakerName);
        qdata.insert("SPEAKERNAME", speakerName.c_str());
        qdata.insert("DATE", data[4].c_str());
        qdata.insert("TIME", data[5].c_str());
        qdata.insert("SUBJECT", data[7].c_str());
        //            qdata.insert("MEETINGNAME", data[8].c_str());
        //            qdata.insert("OWNUNIT", data[9].c_str());
        //                            meeting.insert("MEETINGSCALE", data[10].c_str());
        //            qdata.insert("PREDICTEDDURATION", data[11].c_str());
        //            qdata.insert("MEETINGSTATE", data[14].c_str());
        qdata.insert("REMARK", data[15].c_str());
    }
    json.insert("DATA", QJsonValue(qdata));
    json.insert("TYPE", "_ONLINE_MEETING_INVITATION");
    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    std::string strJson(byteArray);
    jsonstr = strJson;
}

void DataController::jsonStrMeetingAddDetail(std::string meetingid, std::string &jsonstr, int &res)
{
    vector<string> meetingIds;
    QJsonObject qdata;

    vector<string> data;
    res = db.queryMeetingDetailsOnlyByMeetingID(meetingid, data);
    if(res > 0)
    {
        if(atoi(data[14].c_str()) != 2)//未结束会议
        {
            qdata.insert("MEETINGID", data[0].c_str());
            //                    meeting.insert("INITIATOR", data[1].c_str());
            qdata.insert("ASSISTANT", data[2].c_str());
            string assistantName; assistantName.clear();
            db.queryNameByUserID(data[2], assistantName);
            qdata.insert("ASSISTANTNAME", assistantName.c_str());
            qdata.insert("SPEAKER", data[3].c_str());
            string speakerName; speakerName.clear();
            db.queryNameByUserID(data[3], speakerName);
            qdata.insert("SPEAKERNAME", speakerName.c_str());
            qdata.insert("DATE", data[4].c_str());
            qdata.insert("TIME", data[5].c_str());
            qdata.insert("CATEGORY", data[6].c_str());
            qdata.insert("SUBJECT", data[7].c_str());
            //            meeting.insert("MEETINGNAME", data[8].c_str());
            //            meeting.insert("OWNUNIT", data[9].c_str());
            qdata.insert("MEETINGSCALE", data[10].c_str());
            qdata.insert("PREDICTEDDURATION", data[11].c_str());
            qdata.insert("MEETINGSTATE", data[14].c_str());
            qdata.insert("REMARK", data[15].c_str());
        }
    }

    QJsonObject json;
    json.insert("DATA", QJsonValue(qdata));
    json.insert("TYPE", "_ONLINE_MEETING");
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
