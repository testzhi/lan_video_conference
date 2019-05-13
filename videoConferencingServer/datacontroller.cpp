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



//void DataController::jsonStrMeetingsDetail(std::string emalid, std::string &jsonstr, unsigned long long &res)
//{
//    vector<string> meetingIds;
//    res = db.queryUnfinishedMeetingsIDByUserID(emalid, meetingIds);
//    cout << "Unfinished meetingLLLLLLLLLLLLL" << res << endl;
//    QJsonArray meetingsArray;
//    if(res != 0)
//    {
//        for (auto &anID: meetingIds)
//        {
//            vector<string> data;
//            auto m = db.queryMeetingDetailsOnlyByMeetingID(anID, data);
//            if(m > 0)
//            {
//                cout << "llll当前会议状态llll" << data[14] << endl;
//                if(atoi(data[14].c_str()) != 2)//未结束会议
//                {
//                    cout << "eeeeeeeeeeeeeeeee" <<endl;
//                    QJsonObject meeting;
//                    meeting.insert("MEETINGID", data[0].c_str());
//                    //                    meeting.insert("INITIATOR", data[1].c_str());
//                    meeting.insert("ASSISTANT", data[2].c_str());
//                    string assistantName; assistantName.clear();
//                    db.queryNameByUserID(data[2], assistantName);
//                    meeting.insert("ASSISTANTNAME", assistantName.c_str());
//                    meeting.insert("SPEAKER", data[3].c_str());
//                    string speakerName; speakerName.clear();
//                    db.queryNameByUserID(data[3], speakerName);
//                    meeting.insert("SPEAKERNAME", speakerName.c_str());
//                    meeting.insert("DATE", data[4].c_str());
//                    meeting.insert("TIME", data[5].c_str());
//                    meeting.insert("CATEGORY", data[6].c_str());
//                    meeting.insert("SUBJECT", data[7].c_str());
//                    //            meeting.insert("MEETINGNAME", data[8].c_str());
//                    //            meeting.insert("OWNUNIT", data[9].c_str());
//                    meeting.insert("MEETINGSCALE", data[10].c_str());
//                    meeting.insert("PREDICTEDDURATION", data[11].c_str());
//                    meeting.insert("MEETINGSTATE", data[14].c_str());
//                    meeting.insert("REMARK", data[15].c_str());
//                    meetingsArray.insert(0, meeting);
//                }
//            }

//        }
//    }
//    QJsonObject qdata;
//    qdata.insert("MEETINGS", meetingsArray);
//    QJsonObject json;
//    json.insert("DATA", QJsonValue(qdata));
//    json.insert("TYPE", "_INITIALIZE_MEETINGS_LIST");
//    QJsonDocument document;
//    document.setObject(json);
//    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
//    std::string strJson(byteArray);
//    jsonstr = strJson;
//}

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
