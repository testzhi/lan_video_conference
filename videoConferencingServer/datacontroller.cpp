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
    //    db.insertIntoTableEmployees("563181354", "1717", "Liana", "563181354@qq.com", "analysis", "AI", "google","");
    //    db.insertIntoTableEmployees("599599599", "5995", "lzy", "599@qq.com", "AVATARlzy", "analysis", "compute", "google", "18982777901","");
    //    db.insertIntoTableEmployees("zjm", "5995", "zjm", "zjm@qq.com", "AVATARzjm", "analysis2", "compute", "google", "18982777901","");
    //    db.insertIntoTableEmployees("777777777", "7777", "Liang", "777@qq.com", "analysis", "compute", "baidu","11111111111","");
    //    db.insertIntoTableEmployees("222222222", "222", "luoooooo", "222@qq.com", "gro", "test", "baidu","");
    //    db.insertIntoTableEmployees("1111111", "123123123", "luoooooo", "1222@qq.com", "gro", "test", "baidu","");
    cout << "建表结束" << endl;
}

DataController::~DataController()
{
    db.closeMySQL();
}

vector<string> DataController::getEmployeeInfo(string emailID)
{
    vector<string> data;
    db.queryEmployeeInfoByEmailID(emailID, data);

    return data;
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
    dd.insert("COMPANY", data[6].c_str());
    dd.insert("DEPARTMENT", data[5].c_str());
    dd.insert("GROUP", data[4].c_str());
    dd.insert("PHONE", data[7].c_str());
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

DataBaseBroker DataController::getDb() const
{
    return db;
}
