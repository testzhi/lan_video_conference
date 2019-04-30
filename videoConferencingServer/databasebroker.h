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

    //判断USERID是否重复
    bool canRegister(std::string email);
    //返回值：无效email-2 ，无效ID-1, 0命令执行失败  ，有效ID 1 ，有效email 2
    int isValidAccount(std::string emailId);



    //-1 email注册失败， 0命令执行失败， 1成功
    //测试版
    int insertIntoTableEmployees(std::string userid, std::string passwd, std::string userName, std::string email, std::string groupName, std::string departmentName, std::string companyName, std::string ip);
    //测试版
    int insertIntoTableEmployees(std::string userid, std::string passwd, std::string userName, std::string email, std::string groupName, std::string departmentName, std::string companyName, std::string phone, std::string ip);
    //完全版本
    int insertIntoTableEmployees(std::string userid, std::string passwd, std::string userName, std::string email, std::string avatar, std::string groupName, std::string departmentName, std::string companyName, std::string phone, std::string ip);
    //测试版，返回meetingID
    unsigned long long insertIntoTableMeetings(std::string assistant, std::string speaker, std::string date, std::string time, int catagro, std::string subject, int scale, int predictedDuration, std::string remark);//返回meetingID
    //测试版
    int insertIntoTableAttendees(std::string meetingId, std::string attendid);
    //完全版本
    int insertIntoTableAttendees(std::string meetingId, std::string attendid, int attendState, std::string remark);
    //完全版本
    int insertIntoTableNotifications(std::string notifiedID, std::string notifyid, int catagro, std::string subject, int state, std::string meetingID);



    //0无结果 -1命令执行失败 1查询成功;根据emailid查询用户id email name avatar phone groupname departname companyname
    int queryEmployeeInfoByEmailID(std::string emailID, std::vector<std::string> &data);
    //    0无结果 -1命令执行失败 1查询成功;验证登陆密码
    int queryResultForLogin(std::string emailID, std::vector<std::string> &data);
    //0无结果 -1命令执行失败 1查询成功;通过userid通过userid查询ip
    int queryIpByUserID(std::string userID, int state, std::string &Ip);
    //0无结果 -1命令执行失败 1查询成功;通过userid查询username
    int queryNameByUserID(std::string userID, std::string &name);
    //0无结果 -1命令执行失败 1查询成功;通过userid查询companyid
    int queryCompanyOfEmployeeID(std::string id, std::string &comid);
    //0无结果 -1命令执行失败 1查询成功;通过userid通过userid查询userstate
    int queryStateByUserID(std::string userID, int &state);

    //0无结果/命令执行失败  正数部门数;通过companyid查询所有departmentid和departmentname
    unsigned long long queryDepartmentsInCompany(std::string comid, std::vector<std::vector<std::string>> &departments);
    //0无结果/命令执行失败  正数组数;通过departmentid查询所有groupid和groupname
    unsigned long long queryGroupsInDepartments(std::string departid, std::vector<std::vector<std::string>> &groups);
    //0无结果/命令执行失败  正数人数;通过groupid查询所有所有组内成员id email name avatar phone
    unsigned long long queryColleagueInfoByGroupID(std::string groupID, std::vector<std::vector<std::string> > &employees);


    //    //0无结果/命令执行失败  正数会议邀请数;根据userid 查询该用户的所有拒绝state=2会议category=1邀请
    //        unsigned long long queryInvitationsDecline(std::string emailID, std::vector<std::vector<std::string> > &data);
    //0无结果/命令执行失败  正数会议邀请数;;根据userid 查询该用户的所有同意state=1会议category=1邀请
    unsigned long long queryInvitationsConsent(std::string emailID, std::vector<std::vector<std::string> > &data);
    //0无结果/命令执行失败  正数会议邀请数;;根据userid 查询该用户的所有未处理state=0会议category=1邀请
    unsigned long long queryInvitationsUndisposed(std::string emailID, std::vector<std::vector<std::string> > &data);
    //0无结果/命令执行失败  正数会议邀请数;;根据userid 查询该用户的所有超时且未处理state=-1会议category=1邀请（暂未考虑）
    unsigned long long queryInvitationsInvalid(std::string emailID, std::vector<std::vector<std::string> > &data);
    //     根据meetingid和meetingstate获取meeting表所有字段对应信息
    unsigned long long queryMeetingOfInvitionInfo(std::string meetingID, std::vector<std::string> &data);
    //根据meetingid 且meetingstate不为 某个值的 会议所有字段信息
    unsigned long long queryMeetingNOTENDByMeetingID(std::string meetingID, int meetingState, std::vector<std::string>  &data);


    //通过attendeeid查询该用户的所有meetingid s
    unsigned long long queryMeetingsIDByUserID(std::string emailID, std::vector<std::string> &meetingIds);
    //通过meetingid查询meeting表所有字段对应信息
    int queryMeetingDetailsOnlyByMeetingID(std::string meetingID, std::vector<std::string>  &data);
    //通过meetingid查询meeting表subject
    unsigned long long queryMeetingSubjectByMeetingID(std::string meetingID, std::string &data);

    //根据meetingid查询meetingstate
    int queryMeetingStateByMeetingID(std::string meetingID, int &state);
    //通过meetingid和指定参与会议状态attendeestate查询所有与会者（包括speaker和assistant）的ATTENDEEID s
    unsigned long long queryAttendeesByStateAndMeetingID(std::string meetingID, int attendeeState, std::vector<std::string> &data);
    //根据attendeeid，attendeestate查询 meetingids
    unsigned long long queryMeetingIDByAttendeeIDAndAttendeeState(std::string attendeeID, int attendeeState, std::vector<std::string> &meetingIDs);
    //根据meetingid查询speaker和assistant
    unsigned int queryMeetingSpeakerAndAssistantByMeetingID(std::string meetingID, std::string &speaker, std::string &assistant);


    //根据emailid修改emploees的state
    bool updateStateByEmaiID(std::string emailID, int state, std::string ip);
    //通过meetingid修改meetingstate
    bool updateMeetingStateByMeetingID(std::string meetingID, int state);
    //通过meetingid和attedeeid修改attendeestate和remark
    bool updateAttendeeByMeetingIDAndAttendeeID(std::string meetingid, std::string attendeeid, int state, std::string remark);
    //    根据catagory=1会议被通知人（notifierdID）和meetingid更改通知状态（notificationstate）
    bool updateNotificationsState(std::string notifiedID, std::string meetingid, int state);



    //通过被通知的userID和meetingid删除notification
    void deleteNotificationByUserIDAndMeetingID(std::string userID, std::string meetingID);
    std::string getErrorInfo();


private:

    MYSQL_RES *result;                 //用于存放结果 建议用char* 数组将此结果转存
    MYSQL *mysqlInstance;              //MySQL对象，必备的一个数据结构

    //根据companyname插入新公司（需要自己判断无重复）
    bool insertIntoTableCompanies(std::string name);
    //根据groupname，companyid插入新部门（需要自己判断无重复）
    bool insertIntoTableDepartments(std::string name, int companyid);
    //根据groupname，departmentid插入新组（需要自己判断无重复）
    bool insertIntoTableGroups(std::string name, int departmentid);


    //需要创建新公司
    bool needCreateNewCompany(std::string comName);
    //根据公司名获取companyid
    int getCompanyID(std::string comName);
    //需要创建新部门
    bool needCreateNewDepartment(std::string depaName, std::string comName, int &cid);
    //    根据department和公司id获取companyid
    int getDepartmentID(std::string depaName, int cid);
    //需要创建新组
    bool needCreateNewGroup(std::string gName, std::string depaName, std::string comName, int &did, int &cid);
    //    根据部门和部门id获取companyid
    int getGroupID(std::string gName, int did);

    //根据完全条件查询通知
    unsigned long long queryInvitations(std::string emailID, int catagro, int state, std::vector<std::vector<std::string> > &data);
    //    根据meetingid和meetingstate获取么额听表所有字段对应信息
    unsigned long long queryMeetingDetailsByMeetingIDAndMeetingState(std::string meetingID, int meetingState, std::vector<std::string>  &data);


    //email 1 , id 0
    bool isEmail(std::string emailId);
    //生成id时判断该id是否被占用
    bool canCreateID(std::string id);
    //填写错误信息
    void errorIntoMySQL();
    //执行命令
    bool query(const std::string& querystr);
};

#endif // DATABASEBROKER_H
