#ifndef DATABASEBROKER_H
#define DATABASEBROKER_H

#include <mariadb/mysql.h>
#include <string>
#include <vector>

class DataBaseBroker
{
public:
    DataBaseBroker();
    bool connectMySQL(const char *host, const char *username, const char *password, const char *database, int port);
    bool createTables();
    void closeMySQL();

    bool canRegister(std::string email);
    //无效email-2 ，无效ID-1, 0命令执行失败  ，ID 1 ，email 2
    int isValidAccount(std::string emailId);

    //-1 email注册失败， 0命令执行失败， 1成功
    int insertIntoTableEmployees(std::string userid, std::string passwd, std::string userName, std::string email, std::string groupName, std::string departmentName, std::string companyName, std::string ip);
    int insertIntoTableEmployees(std::string userid, std::string passwd, std::string userName, std::string email, std::string groupName, std::string departmentName, std::string companyName, std::string phone, std::string ip);

    //完全版本
    int insertIntoTableEmployees(std::string userid, std::string passwd, std::string userName, std::string email, std::string avatar, std::string groupName, std::string departmentName, std::string companyName, std::string phone, std::string ip);

    unsigned long long insertIntoTableMeetings(std::string assistant, std::string speaker, std::string date, std::string time, int catagro, std::string subject, int scale, int predictedDuration, std::string remark);//返回meetingID

    int insertIntoTableAttendees(std::string meetingId, std::string attendid);
    //完全版本
    int insertIntoTableAttendees(std::string meetingId, std::string attendid, int attendState, std::string remark);

    //完全版本
    int insertIntoTableNotifications(std::string notifiedID, std::string notifyid, int catagro, std::string subject, int state, std::string meetingID);

    //0无结果 -1命令执行失败 1成功
    int queryEmployeeInfoByEmailID(std::string emailID, std::vector<std::string> &data);
    //id email passwd state ip
    int queryResultForLogin(std::string emailID, std::vector<std::string> &data);
    int queryCompanyOfEmployeeID(std::string id, std::string &comid);


    //0无结果/命令执行失败  正数部门数
    unsigned long long queryDepartmentsInCompany(std::string comid, std::vector<std::vector<std::string>> &departments);
    //0无结果/命令执行失败  正数组数
    unsigned long long queryGroupsInDepartments(std::string departid, std::vector<std::vector<std::string>> &groups);
    //0无结果/命令执行失败  正数人数
    unsigned long long queryColleagueInfoByGroupID(std::string groupID, std::vector<std::vector<std::string> > &employees);


    unsigned long long queryInvitationsDecline(std::string emailID, std::vector<std::vector<std::string> > &data);
    unsigned long long queryInvitationsConsent(std::string emailID, std::vector<std::vector<std::string> > &data);
    unsigned long long queryInvitationsUndisposed(std::string emailID, std::vector<std::vector<std::string> > &data);
    unsigned long long queryInvitationsInvalid(std::string emailID, std::vector<std::vector<std::string> > &data);
    unsigned long long queryMeetingOfInvitionInfo(std::string meetingID, std::vector<std::string> &data);


    unsigned long long queryMeetingsIDByUserID(std::string emailID, std::vector<std::string> &meetingIds);
    unsigned long long queryMeetingDetailsOnlyByMeetingID(std::string meetingID, std::vector<std::string>  &data);



    bool updateStateByEmaiID(std::string emailID, int state, std::string ip);
    bool updateMeetingStateByMeetingID(std::string meetingID, int state);
    bool updateAttendeeByMeetingIDAndAttendeeID(std::string meetingid, std::string attendeeid, int state, std::string remark);
    bool updateNotificationsState(std::string notifiedID, std::string meetingid, int state);

    const char *getErrorInfo() const;
    int getErrorNum() const;

private:
    unsigned int errorNum;                      //错误代号
    const char* errorInfo;
    MYSQL_RES *result;                 //用于存放结果 建议用char* 数组将此结果转存
    MYSQL *mysqlInstance;              //MySQL对象，必备的一个数据结构


    bool insertIntoTableCompanies(std::string name);
    bool insertIntoTableDepartments(std::string name, int companyid);
    bool insertIntoTableGroups(std::string name, int departmentid);



    bool needCreateNewCompany(std::string comName);
    int getCompanyID(std::string comName);
    bool needCreateNewDepartment(std::string depaName, std::string comName, int &cid);
    int getDepartmentID(std::string depaName, int cid);
    bool needCreateNewGroup(std::string gName, std::string depaName, std::string comName, int &did, int &cid);
    int getGroupID(std::string gName, int did);


    unsigned long long queryInvitations(std::string emailID, int catagro, int state, std::vector<std::vector<std::string> > &data);
    unsigned long long queryMeetingDetailsByMeetingIDAndMeetingState(std::string meetingID, int meetingState, std::vector<std::string>  &data);


    //email 1 , id 0
    bool isEmail(std::string emailId);
    bool canCreateID(std::string id);
    void errorIntoMySQL();
    bool query(const std::string& querystr);
    bool getDatafromDB(std::string queryStr, std::vector<std::vector<std::string> >& data, int &row);
    bool isSameString(std::string userID_fk, std::string friendID_fk);
};

#endif // DATABASEBROKER_H
