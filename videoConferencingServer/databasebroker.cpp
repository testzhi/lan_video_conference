#include "databasebroker.h"
#include <iostream>
#include <cstring>

using std::cout;
using std::endl;
using std::string;
using std::vector;

DataBaseBroker::DataBaseBroker()
    :errorNum(0),errorInfo("ok"), mysqlInstance(mysql_init(nullptr))//分配内存并初始化一个MYSQL *对象
{
    mysql_library_init(0,nullptr,nullptr);
    mysql_init(mysqlInstance);
    mysql_options(mysqlInstance,MYSQL_SET_CHARSET_NAME,"utf8");
    //    mysql_options(mysqlInstance, MYSQL_SET_CHARSET_NAME,"gbk");
}
bool DataBaseBroker::connectMySQL(const char *host, const char *username, const char *password, const char *database, int port)
{
    if(mysql_real_connect(mysqlInstance, host, username, password, database, port, nullptr, 0) != nullptr)
    {
        cout << "数据库连接成功" << endl;
        return true;
    }
    else
    {
        errorIntoMySQL();
        return false;
    }
}
void DataBaseBroker::closeMySQL()
{
    mysql_close(mysqlInstance);
}
bool DataBaseBroker::createTables()
{
    string employees = "CREATE TABLE IF NOT EXISTS`VideoConferencingDB`.`EmployeesTable` ("
                       "`USERID` CHAR(7) NOT NULL,"
                       "`PASSWD` CHAR(20) NOT NULL,"
                       "`REALNAME` VARCHAR(10) NOT NULL,"
                       "`EMAIL` VARCHAR(20) NOT NULL,"
                       "`AVATAR` BLOB,"
                       "`GROUPID` INT NOT NULL,"
                       "`DEPARTMENTID` INT NOT NULL,"
                       "`COMPANYID` INT NOT NULL,"
                       "`PHONE` VARCHAR(11) NULL,"
                       "`STATE` TINYINT NOT NULL DEFAULT 0,"
                       "`IP` VARCHAR(20),"
                       "PRIMARY KEY (`USERID`),"
                       "UNIQUE INDEX `EMAIL_UNIQUE`  (`EMAIL`)"
                       ");";
    string companies = "CREATE TABLE IF NOT EXISTS`VideoConferencingDB`.`CompaniesTable` ("
                       "`COMPANYID` INT NOT NULL AUTO_INCREMENT,"
                       "`COMPANYNAME` VARCHAR(20) NOT NULL,"
                       "PRIMARY KEY (`COMPANYID`),"
                       "UNIQUE INDEX `COMPANYNAME_UNIQUE` (`COMPANYNAME`)"
                       ");";
    string departments = "CREATE TABLE IF NOT EXISTS`VideoConferencingDB`.`DepartmentsTable` ("
                         "`DEPARTMENTID` INT NOT NULL AUTO_INCREMENT,"
                         "`DEPARTMENTNAME` VARCHAR(20) NOT NULL,"
                         "`COMPANYID` INT NOT NULL,"
                         "PRIMARY KEY (`DEPARTMENTID`),"
                         "CONSTRAINT `FK_COMPANYID` FOREIGN KEY (`COMPANYID`) REFERENCES `CompaniesTable` (`COMPANYID`)"
                         ");";
    string groups = "CREATE TABLE IF NOT EXISTS`VideoConferencingDB`.`GroupsTable` ("
                    "`GROUPID` INT NOT NULL AUTO_INCREMENT,"
                    "`GROUPNAME` VARCHAR(20) NOT NULL,"
                    "`DEPARTMENTID` INT NOT NULL,"
                    "PRIMARY KEY (`GROUPID`),"
                    "CONSTRAINT `FK_DEPARTMENTID` FOREIGN KEY (`DEPARTMENTID`) REFERENCES `DepartmentsTable` (`DEPARTMENTID`)"
                    ");";
    string meetings = "CREATE TABLE IF NOT EXISTS`VideoConferencingDB`.`MeetingsTable` ("
                      "`MEETINGID` INT NOT NULL AUTO_INCREMENT,"
                      "`INITIATOR` VARCHAR(10),"
                      "`ASSISTANT` CHAR(7) NOT NULL,"
                      "`SPEAKER` CHAR(7) NOT NULL,"
                      "`DATE` DATE NOT NULL,"
                      "`TIME` TIME NOT NULL,"
                      "`CATAGRO` TINYINT NOT NULL,"
                      "`SUBJECT` VARCHAR(20) NOT NULL,"
                      "`MEETINGNAME` VARCHAR(20),"
                      "`OWNUNIT` VARCHAR(20),"
                      "`MEETINGSCALE` INT,"
                      "`PREDICTEDDURATION` INT,"
                      "`DURATION` INT,"
                      "`ATTENDEENUMBERS` INT,"
                      "`MEETINGSTATE` INT NOT NULL,"
                      "`REMARK` VARCHAR(20),"
                      "PRIMARY KEY (`MEETINGID`),"
                      "CONSTRAINT `FK_ASSISTANT` FOREIGN KEY (`ASSISTANT`) REFERENCES `EmployeesTable` (`USERID`),"
                      "CONSTRAINT `FK_SPEAKER` FOREIGN KEY (`SPEAKER`) REFERENCES `EmployeesTable` (`USERID`)"
                      ");";
    string attendees = "CREATE TABLE IF NOT EXISTS`VideoConferencingDB`.`AttendeesTable` ("
                       "`MEETINGID` INT NOT NULL,"
                       "`ATTENDEEID` INT NOT NULL,"
                       "`ATTENDSTATE` TINYINT,"
                       "`REMARK` VARCHAR(20),"
                       "CONSTRAINT `FK_MEETINGID` FOREIGN KEY (`MEETINGID`) REFERENCES `MeetingsTable` (`MEETINGID`)"
                       ");";
    string notifications = "CREATE TABLE IF NOT EXISTS`VideoConferencingDB`.`NotificationsTable` ("
                           "`NOTIFIEDID` CHAR(7) NOT NULL,"
                           "`NOTIFYID` CHAR(7),"
                           "`CATAGRO` TINYINT,"
                           "`SUBJECT` VARCHAR(20),"
                           "`STATE` INT NOT NULL,"
                           "`MEETINGID` INT NOT NULL,"
                           "CONSTRAINT `FK_NOTIFIEDID` FOREIGN KEY (`NOTIFIEDID`) REFERENCES `EmployeesTable` (`USERID`)"
                           ");";


    if(!query(employees)) return false;
    if(!query(companies)) return false;
    if(!query(departments)) return false;
    if(!query(groups)) return false;
    if(!query(meetings)) return false;
    if(!query(attendees)) return false;
    if(!query(notifications)) return false;
    cout << "建表成功" << endl;
    return true;
}



//测试版本
int DataBaseBroker::insertIntoTableEmployees(string userid, string passwd, string userName, string email, string groupName, string departmentName, string companyName, string ip)
{
    if(!canRegister(email)) return -1;

    if(needCreateNewCompany(companyName))
        insertIntoTableCompanies(companyName);
    int comid;
    if(needCreateNewDepartment(departmentName, companyName, comid))
        insertIntoTableDepartments(departmentName, comid);
    int depaid;
    if(needCreateNewGroup(groupName, departmentName, companyName, depaid, comid))
        insertIntoTableGroups(groupName, depaid);
    int gid = getGroupID(groupName, depaid);

    char *cmd = new char[200];
    sprintf(cmd, "insert into EmployeesTable values('%s', '%s', '%s', '%s', NULL, '%d', '%d', '%d', NULL, '0', '%s');", userid.c_str(), passwd.c_str(), userName.c_str(), email.c_str(), gid, depaid, comid, ip.c_str());

    if(!query(cmd))
    {
        delete [] cmd;
        return 0;
    }
    delete [] cmd;
    return 1;
}
int DataBaseBroker::insertIntoTableEmployees(string userid, string passwd, string userName, string email, string groupName, string departmentName, string companyName, string phone, string ip)
{
    if(!canRegister(email)) return -1;

    if(needCreateNewCompany(companyName))
        insertIntoTableCompanies(companyName);
    int comid;
    if(needCreateNewDepartment(departmentName, companyName, comid))
        insertIntoTableDepartments(departmentName, comid);
    int depaid;
    if(needCreateNewGroup(groupName, departmentName, companyName, depaid, comid))
        insertIntoTableGroups(groupName, depaid);
    int gid = getGroupID(groupName, depaid);

    char *cmd = new char[200];
    sprintf(cmd, "insert into EmployeesTable values('%s', '%s', '%s', '%s', NULL, '%d', '%d', '%d', '%s', '0', '%s');", userid.c_str(), passwd.c_str(), userName.c_str(), email.c_str(), gid, depaid, comid, phone.c_str(), ip.c_str());

    if(!query(cmd))
    {
        delete [] cmd;
        return 0;
    }
    delete [] cmd;
    return 1;
}
//正式版本
int DataBaseBroker::insertIntoTableEmployees(std::string userid, std::string passwd, std::string userName, std::string email, std::string avatar, std::string groupName, std::string departmentName, std::string companyName, std::string phone, string ip)
{
    if(!canRegister(email)) return -1;

    if(needCreateNewCompany(companyName))
        insertIntoTableCompanies(companyName);
    int comid;
    if(needCreateNewDepartment(departmentName, companyName, comid))
        insertIntoTableDepartments(departmentName, comid);
    int depaid;
    if(needCreateNewGroup(groupName, departmentName, companyName, depaid, comid))
        insertIntoTableGroups(groupName, depaid);
    int gid = getGroupID(groupName, depaid);

    char *cmd = new char[200];
    sprintf(cmd, "insert into EmployeesTable values('%s', '%s', '%s', '%s', '%s', '%d', '%d', '%d', '%s', '0', '%s');", userid.c_str(), passwd.c_str(), userName.c_str(), email.c_str(), avatar.c_str(), gid, depaid, comid, phone.c_str(), ip.c_str());

    if(!query(cmd))
    {
        delete [] cmd;
        return 0;
    }
    delete [] cmd;
    return 1;
}

unsigned long long DataBaseBroker::insertIntoTableMeetings(std::string assistant, std::string speaker, std::string date, std::string time, int catagro, std::string subject, int scale, int predictedDuration, std::string remark)
{;
    char *cmd = new char[200];
    sprintf(cmd, "insert into MeetingsTable values(NULL, NULL, '%s', '%s', '%s', '%s', '%d', '%s', NULL, NULL, '%d', '%d', NULL, NULL, '0', '%s');" ,assistant.c_str(), speaker.c_str(), date.c_str(), time.c_str(), catagro, subject.c_str(), scale, predictedDuration, remark.c_str());

    if(!query(cmd))
    {
        delete [] cmd;
        return 0;
    }
    delete [] cmd;
    char *cmd2 = new char[50];
    sprintf(cmd2, "select * from MeetingsTable;");
    if(!query(cmd2))
    {
        delete [] cmd2;
        return 0;
    }
    result = mysql_store_result(mysqlInstance);
    auto row = mysql_num_rows(result);
    return row;
}

int DataBaseBroker::insertIntoTableAttendees(std::string meetingId, std::string attendid)
{
    char *cmd = new char[200];
    sprintf(cmd, "insert into AttendeesTable values('%s','%s', NULL, NULL);" , meetingId.c_str(), attendid.c_str());

    if(!query(cmd))
    {
        delete [] cmd;
        return 0;
    }
    delete [] cmd;
    return 1;
}

int DataBaseBroker::insertIntoTableAttendees(std::string meetingId, std::string attendid, int attendState, std::string remark)
{
    char *cmd = new char[200];
    sprintf(cmd, "insert into AttendeesTable values('%s','%s', '%d', '%s');" , meetingId.c_str(), attendid.c_str(), attendState, remark.c_str());

    if(!query(cmd))
    {
        delete [] cmd;
        return 0;
    }
    delete [] cmd;
    return 1;
}

int DataBaseBroker::insertIntoTableNotifications(std::string notifiedID, std::string notifyid, int catagro, std::string subject, int state, std::string meetingID)
{
    char *cmd = new char[200];
    sprintf(cmd, "insert into NotificationsTable values('%s','%s', '%d', '%s', '%d', '%s');", notifiedID.c_str(), notifyid.c_str(), catagro, subject.c_str(), state, meetingID.c_str());

    if(!query(cmd))
    {
        delete [] cmd;
        return 0;
    }
    delete [] cmd;
    return 1;
}


int DataBaseBroker::queryEmployeeInfoByEmailID(std::string emailID, std::vector<std::string> &data)
{
    char *cmd1 = new char[200];
    if(!isEmail(emailID))
        sprintf(cmd1, "select `USERID` , `EMAIL`, `REALNAME`, `AVATAR`, `PHONE`, `GROUPID`, `DEPARTMENTID`, `COMPANYID` from EmployeesTable where `USERID` = '%s';", emailID.c_str());
    else
        sprintf(cmd1, "select `USERID` , `EMAIL`, `REALNAME`, `AVATAR`, `PHONE`, `GROUPID`, `DEPARTMENTID`, `COMPANYID` from EmployeesTable where `EMAIL` = '%s';", emailID.c_str());
    if(!query(cmd1))
    {
        delete [] cmd1;
        return -1;
    }
    result = mysql_store_result(mysqlInstance);
    delete [] cmd1;
    auto row1 = mysql_num_rows(result);
    MYSQL_ROW line1 = mysql_fetch_row(result);
    if(row1 == 0)
        return 0;
    else {
        char *company = new char[100];
        sprintf(company, "select `COMPANYNAME` from CompaniesTable where COMPANYID = '%s';", line1[7]);
        if(!query(company))
        {
            delete [] company;
            return -1;
        }
        result = mysql_store_result(mysqlInstance);
        delete [] company;
        auto row2 = mysql_num_rows(result);
        if(row2 == 0) return 0;
        MYSQL_ROW line2 = mysql_fetch_row(result);

        char *department = new char[100];
        sprintf(department, "select `DEPARTMENTNAME` from DepartmentsTable where DEPARTMENTID = '%s';", line1[6]);
        if(!query(department))
        {
            delete [] department;
            return -1;
        }
        result = mysql_store_result(mysqlInstance);
        delete [] department;
        auto row3 = mysql_num_rows(result);
        if(row3 == 0) return 0;
        MYSQL_ROW line3 = mysql_fetch_row(result);

        char *group = new char[100];
        sprintf(group, "select `GROUPNAME` from GroupsTable where GROUPID = '%s';", line1[5]);
        if(!query(group))
        {
            delete [] group;
            return -1;
        }
        result = mysql_store_result(mysqlInstance);
        delete [] group;
        auto row4 = mysql_num_rows(result);
        if(row4 == 0) return 0;
        MYSQL_ROW line4 = mysql_fetch_row(result);

        for(int i = 0; i != 5; ++i)
        {
            if(line1[i])
                data.push_back(line1[i]);
            else
                data.push_back("");
        }
        if(line4[0])// 组4
            data.push_back(line4[1]);
        else
            data.push_back("");
        if(line3[0])//部门5
            data.push_back(line3[1]);
        else
            data.push_back("");
        if(line2[0])//公司6
            data.push_back(line2[1]);
        else
            data.push_back("");

        cout<< line2[1] << " " << line3[1] << " " << line4[1] <<"" <<endl;
        return 1;
    }
}
int DataBaseBroker::queryResultForLogin(std::string emailID, std::vector<std::string> &data)
{
    char *cmd = new char[150];
    if(!isEmail(emailID))
        sprintf(cmd, "select `USERID` , `EMAIL`, `PASSWD`, `STATE` from EmployeesTable where USERID = '%s';", emailID.c_str());
    else
        sprintf(cmd, "select `USERID` , `EMAIL`, `PASSWD`, `STATE` from EmployeesTable where EMAIL = '%s';", emailID.c_str());

    if(!query(cmd))
    {
        delete [] cmd;
        return -1;
    }
    result = mysql_store_result(mysqlInstance);
    delete [] cmd;
    auto row = mysql_num_rows(result);
    if(row == 0) return 0;

    MYSQL_ROW line = mysql_fetch_row(result);
    unsigned int field = mysql_num_fields(result);

    cout << line[0] << line[1] <<line[2];
    for(unsigned int i = 0; i != field; ++i)
    {
        if(line[i])
            data.push_back(line[i]);
        else
            data.push_back("");
    }

    cout<<"query succeed"<<endl;
    return 1;
}
int DataBaseBroker::queryCompanyOfEmployeeID(std::string id, std::string &comid)
{
    char *cmd = new char[150];
    sprintf(cmd, "select `COMPANYID` from EmployeesTable where `USERID` = '%s';", id.c_str());
    if(!query(cmd))
    {
        delete [] cmd;
        return -1;
    }
    result = mysql_store_result(mysqlInstance);
    auto row = mysql_num_rows(result);
    delete [] cmd;
    if(row == 0) return 0;
    MYSQL_ROW line = mysql_fetch_row(result);

    comid = line[0];
    return 1;
}

unsigned long long DataBaseBroker::queryDepartmentsInCompany(std::string comid, vector<vector<string>> &departments)
{
    char *cmd = new char[150];
    sprintf(cmd, "select `DEPARTMENTNAME`, `DEPARTMENTID` from DepartmentsTable where `COMPANYID` = '%s';", comid.c_str());
    if(!query(cmd))
    {
        delete [] cmd;
        return 0;
    }
    result = mysql_store_result(mysqlInstance);
    unsigned long long row = mysql_num_rows(result);
    if(row == 0) return 0;

    delete [] cmd;
    for (unsigned long long i = 0; i != row; ++i)
    {
        MYSQL_ROW line = mysql_fetch_row(result);
        vector<string> linedata;
        for(unsigned int j = 0; j != 2; j++)
        {
            if(line[j])
                linedata.push_back(line[j]);
            else
                linedata.push_back("");
        }
        departments.push_back(linedata);
    }
    return row;
}
unsigned long long DataBaseBroker::queryGroupsInDepartments(std::string departid, std::vector<std::vector<std::string>> &groups)
{    char *cmd = new char[150];
     sprintf(cmd, "select `GROUPNAME`, `GROUPID` from GroupsTable where `DEPARTMENTID` = '%s';", departid.c_str());
      if(!query(cmd))
      {
          delete [] cmd;
          return 0;
      }
      result = mysql_store_result(mysqlInstance);
       unsigned long long row = mysql_num_rows(result);
        if(row == 0) return 0;

        delete [] cmd;
         for (unsigned long long i = 0; i != row; ++i)
         {
             MYSQL_ROW line = mysql_fetch_row(result);
             vector<string> linedata;
             for(unsigned int j = 0; j != 2; j++)
             {
                 if(line[j])
                     linedata.push_back(line[j]);
                 else
                     linedata.push_back("");
             }
             groups.push_back(linedata);
         }
          return row;
}
unsigned long long DataBaseBroker::queryColleagueInfoByGroupID(std::string groupID, std::vector<std::vector<std::string>> &employees)
{
    char *cmd = new char[200];
    sprintf(cmd, "select `USERID` , `EMAIL`, `REALNAME`, `AVATAR`, `PHONE` from EmployeesTable where `GROUPID` = '%s';", groupID.c_str());
    if(!query(cmd))
    {
        delete [] cmd;
        return 0;
    }
    result = mysql_store_result(mysqlInstance);
    unsigned long long row = mysql_num_rows(result);
    delete [] cmd;
    if(row == 0)
        return 0;
    unsigned int field = mysql_num_fields(result);


    MYSQL_ROW line=nullptr;
    line = mysql_fetch_row(result);
    while(nullptr!=line)
    {
        vector<string> linedata;
        for(unsigned int i = 0; i < field;i++)
        {
            if(line[i])
                linedata.push_back(line[i]);
            else
                linedata.push_back("");
        }
        line = mysql_fetch_row(result);
        employees.push_back(linedata);
    }
    return row;
}



unsigned long long DataBaseBroker::queryInvitationsDecline(std::string emailID, std::vector<std::vector<std::string>> &data)
{
    unsigned long long row = queryInvitations(emailID, 1, 2, data);
    return row;
}
unsigned long long DataBaseBroker::queryInvitationsConsent(std::string emailID, std::vector<std::vector<std::string> > &data)
{
    unsigned long long row = queryInvitations(emailID, 1, 1, data);
    return row;
}
unsigned long long DataBaseBroker::queryInvitationsUndisposed(std::string emailID, std::vector<std::vector<std::string> > &data)
{
    unsigned long long row = queryInvitations(emailID, 1, 0, data);
    return row;
}
unsigned long long DataBaseBroker::queryInvitationsInvalid(std::string emailID, std::vector<std::vector<std::string> > &data)
{
    unsigned long long row = queryInvitations(emailID, 1, -1, data);
    return row;
}
unsigned long long DataBaseBroker::queryMeetingOfInvitionInfo(std::string meetingID, std::vector<std::string> &data)
{
    auto row = queryMeetingDetailsByMeetingIDAndMeetingState(meetingID, 0, data);
    return row;
}

unsigned long long DataBaseBroker::queryMeetingsIDByUserID(std::string emailID, std::vector<std::string> &meetingIds)
{
    char *cmd = new char[150];
    sprintf(cmd, "select `MEETINGID` from AttendeesTable where `ATTENDEEID` = '%s';", emailID.c_str());
    if(!query(cmd))
    {
        delete [] cmd;
        return 0;
    }
    result = mysql_store_result(mysqlInstance);
    auto row = mysql_num_rows(result);
    delete [] cmd;
    if(row == 0) return 0;
    for (unsigned long long i = 0; i != row; ++i)
    {
         MYSQL_ROW line = mysql_fetch_row(result);

        if(line[0])
            meetingIds.push_back(line[0]);
        else
            meetingIds.push_back("");
    }
    return row;
}
unsigned long long DataBaseBroker::queryMeetingDetailsOnlyByMeetingID(std::string meetingID, std::vector<std::string> &data)
{
    char *cmd = new char[150];
    sprintf(cmd, "select * from MeetingsTable where `MEETINGID` = '%s';", meetingID.c_str());
    if(!query(cmd))
    {
        delete [] cmd;
        return 0;
    }
    result = mysql_store_result(mysqlInstance);
    auto row = mysql_num_rows(result);
    MYSQL_ROW line = mysql_fetch_row(result);
    delete [] cmd;
    if(row == 0) return 0;
    for (unsigned long long i = 0; i != row; ++i)
    {

        if(line[i])
            data.push_back(line[i]);
        else
            data.push_back("");
    }
    return row;
}





bool DataBaseBroker::updateStateByEmaiID(std::string emailID, int state, std::string ip)
{
    char *cmd = new char[150];
    char *cmd2 = new char[150];
    if(isValidAccount(emailID) == 1)
    {
        sprintf(cmd, "update EmployeesTable set `IP` = '%s' where USERID = '%s';", ip.c_str(), emailID.c_str());
        sprintf(cmd2, "update EmployeesTable set `STATE` = '%d' where USERID = '%s';", state, emailID.c_str());
    }
    else if (isValidAccount(emailID) == 2)
    {
        sprintf(cmd, "update EmployeesTable set `IP` = '%s' where EMAIL = '%s';", ip.c_str(), emailID.c_str());
        sprintf(cmd2, "update EmployeesTable set `STATE` = '%d' where EMAIL = '%s';", state, emailID.c_str());
    }
    if(!query(cmd))
    {
        delete [] cmd;
        return false;
    }
    if(!query(cmd2))
    {
        delete [] cmd2;
        return false;
    }
    delete [] cmd;
    delete [] cmd2;
    cout << "状态修改成功" << endl;
    return true;
}

bool DataBaseBroker::updateMeetingStateByMeetingID(std::string meetingID, int state)
{
    char *cmd = new char[150];
     sprintf(cmd, "update MeetingsTable set `MEETINGSTATE` = '%d' where `MEETINGID` = '%s';", state, meetingID.c_str());
    if(!query(cmd))
    {
        delete [] cmd;
        return false;
    }
    delete [] cmd;
    cout << "会议状态修改成功" << endl;
    return true;
}

bool DataBaseBroker::updateAttendeeByMeetingIDAndAttendeeID(std::string meetingid, std::string attendeeid, int state, std::string remark)
{
    char *cmd = new char[150];
     sprintf(cmd, "update AttendeesTable set `ATTENDSTATE` = '%d', `REMARK` = '%s' where `MEETINGID` = '%s' and `ATTENDEEID` = '%s';", state, remark.c_str(), meetingid.c_str(), attendeeid.c_str());
    if(!query(cmd))
    {
        delete [] cmd;
        return false;
    }
    delete [] cmd;
    cout << "参会情况修改成功" << endl;
    return true;
}

bool DataBaseBroker::updateNotificationsState(std::string notifiedID, std::string meetingid, int state)
{
    char *cmd = new char[150];
     sprintf(cmd, "update NotificationsTable set `STATE` = '%d' where `MEETINGID` = '%s' and `NOTIFIEDID` = '%s';", state, meetingid.c_str(), notifiedID.c_str());
    if(!query(cmd))
    {
        delete [] cmd;
        return false;
    }
    delete [] cmd;
    cout << "会议状态修改成功" << endl;
    return true;
}


const char *DataBaseBroker::getErrorInfo() const
{
    return errorInfo;
}
int DataBaseBroker::getErrorNum() const
{
    return errorNum;
}


bool DataBaseBroker::canRegister(string email)
{
    char *cmd = new char[100];
    sprintf(cmd, "select `USERID` from EmployeesTable where EMAIL = '%s'", email.c_str());
    if(!query(cmd))
    {
        delete [] cmd;
        return 0;
    }
    result = mysql_store_result(mysqlInstance);
    delete [] cmd;
    auto row = mysql_num_rows(result);
    if(row == 0)
        return 1;
    return 0;
}
int DataBaseBroker::isValidAccount(std::string emailId)
{
    char *cmd = new char[100];
    bool em = isEmail(emailId);
    if(!em)
    {
        sprintf(cmd, "select `USERID` from EmployeesTable where USERID = '%s';", emailId.c_str());
    }else {
        sprintf(cmd, "select `USERID` from EmployeesTable where EMAIL = '%s';", emailId.c_str());
    }
    if(!query(cmd))
    {
        delete [] cmd;
        return 0;
    }
    result = mysql_store_result(mysqlInstance);
    delete [] cmd;
    auto row = mysql_num_rows(result);
    if(em)
    {
        if(row == 0) return -2;
        else return 2;
    }else {
        if(row == 0) return -1;
        else return 1;
    }
}


bool DataBaseBroker::insertIntoTableCompanies(string name)
{
    char *cmd = new char[100];
    sprintf(cmd, "insert into CompaniesTable values(NULL, '%s');", name.c_str());
    if(!query(cmd))
    {
        delete [] cmd;
        return false;
    }
    delete [] cmd;
    return true;
}
bool DataBaseBroker::insertIntoTableDepartments(string name, int companyid)
{
    char *cmd = new char[100];
    sprintf(cmd, "insert into DepartmentsTable values(NULL, '%s', '%d');", name.c_str(), companyid);
    if(!query(cmd))
    {
        delete [] cmd;
        return false;
    }
    delete [] cmd;
    return true;
}
bool DataBaseBroker::insertIntoTableGroups(string name, int departmentid)
{
    char *cmd = new char[100];
    sprintf(cmd, "insert into GroupsTable values(NULL, '%s', '%d');", name.c_str(), departmentid);
    if(!query(cmd))
    {
        delete [] cmd;
        return false;
    }
    delete [] cmd;
    return true;
}



bool DataBaseBroker::needCreateNewCompany(string comName)
{
    char *cmd = new char[100];
    sprintf(cmd, "select `COMPANYID` from CompaniesTable where COMPANYNAME = '%s'", comName.c_str());
    if(!query(cmd))
    {
        delete [] cmd;
        return 0;
    }
    result = mysql_store_result(mysqlInstance);
    delete [] cmd;
    auto row = mysql_num_rows(result);
    if(row == 0)
        return 1;
    return 0;
}
int DataBaseBroker::getCompanyID(std::string comName)
{
    char *cmd = new char[150];
    sprintf(cmd, "select `COMPANYID` from CompaniesTable where COMPANYNAME = '%s'", comName.c_str());
    if(!query(cmd))
    {
        delete [] cmd;
        return 0;
    }
    result = mysql_store_result(mysqlInstance);
    delete [] cmd;
    auto row = mysql_num_rows(result);
    if(row == 0)
        return -1;
    MYSQL_ROW line = mysql_fetch_row(result);
    return atoi(line[0]);
}
bool DataBaseBroker::needCreateNewDepartment(std::string depaName, std::string comName, int &cid)
{
    cid = getCompanyID(comName);
    if(cid != -1)
    {
        char *cmd = new char[150];
        sprintf(cmd, "select `DEPARTMENTID` from DepartmentsTable where DEPARTMENTNAME = '%s' and COMPANYID = '%d'", depaName.c_str(), cid);
        if(!query(cmd))
        {
            delete [] cmd;
            return 0;
        }
        result = mysql_store_result(mysqlInstance);
        delete [] cmd;
        auto row = mysql_num_rows(result);
        if(row == 0)
            return 1;
    }
    return 0;
}
int DataBaseBroker::getDepartmentID(std::string depaName, int cid)
{
    if(cid > 0)
    {
        char *cmd = new char[150];
        sprintf(cmd, "select `DEPARTMENTID` from DepartmentsTable where DEPARTMENTNAME = '%s' and COMPANYID = '%d'", depaName.c_str(), cid);
        if(!query(cmd))
        {
            delete [] cmd;
            return 0;
        }
        result=mysql_store_result(mysqlInstance);
        delete [] cmd;
        auto row = mysql_num_rows(result);
        if(row == 0)
            return -1;
        MYSQL_ROW line = mysql_fetch_row(result);
        return atoi(line[0]);
    }
    else return -1;
}
bool DataBaseBroker::needCreateNewGroup(std::string gName, std::string depaName, std::string comName, int &did, int &cid)
{
    cid = getCompanyID(comName);
    did = getDepartmentID(depaName, cid);
    if(cid > 0 && did > 0)
    {
        char *cmd = new char[150];
        sprintf(cmd, "select `GROUPID` from GroupsTable where GROUPNAME = '%s' and DEPARTMENTID = '%d'", gName.c_str(), did);
        if(!query(cmd))
        {
            delete [] cmd;
            return 0;
        }
        result=mysql_store_result(mysqlInstance);
        delete [] cmd;
        auto row = mysql_num_rows(result);
        if(row == 0)
            return 1;
    }
    return 0;

}
int DataBaseBroker::getGroupID(std::string gName, int did)
{
    char *cmd = new char[150];
    sprintf(cmd, "select `GROUPID` from GroupsTable where GROUPNAME = '%s' and DEPARTMENTID = '%d'", gName.c_str(), did);
    if(!query(cmd))
    {
        delete [] cmd;
        return 0;
    }
    result = mysql_store_result(mysqlInstance);
    delete [] cmd;
    auto row = mysql_num_rows(result);
    if(row == 0)
        return -1;
    MYSQL_ROW line = mysql_fetch_row(result);
    return atoi(line[0]);
}



unsigned long long DataBaseBroker::queryInvitations(std::string emailID, int catagro, int state, std::vector<std::vector<std::string> > &data)
{
    char *cmd = new char[150];
    sprintf(cmd, "select * from NotificationsTable where `NOTIFIEDID` = '%s' and 'CATAGRO' = '%d' and 'STATE' = '%d';", emailID.c_str(), catagro, state);
    if(!query(cmd))
    {
        delete [] cmd;
        return 0;
    }
    result = mysql_store_result(mysqlInstance);
    auto row = mysql_num_rows(result);
    unsigned int field = mysql_num_fields(result);
    delete [] cmd;
    if(row == 0) return 0;
    for (unsigned long long i = 0; i != row; ++i)
    {
        MYSQL_ROW line = mysql_fetch_row(result);
        vector<string> linedata;
        for(unsigned int j = 0; j != field; j++)
        {
            if(line[j])
                linedata.push_back(line[j]);
            else
                linedata.push_back("");
        }
        data.push_back(linedata);
    }
    return row;
}
unsigned long long DataBaseBroker::queryMeetingDetailsByMeetingIDAndMeetingState(std::string meetingID, int meetingState, std::vector<std::string>  &data)
{
    char *cmd = new char[150];
    sprintf(cmd, "select * from MeetingsTable where `MEETINGID` = '%s' and `MEETINGIDSTATE` = '%d';", meetingID.c_str(), meetingState);
    if(!query(cmd))
    {
        delete [] cmd;
        return 0;
    }
    result = mysql_store_result(mysqlInstance);
    auto row = mysql_num_rows(result);
    MYSQL_ROW line = mysql_fetch_row(result);
    delete [] cmd;
    if(row == 0) return 0;
    for (unsigned long long i = 0; i != row; ++i)
    {

        if(line[i])
            data.push_back(line[i]);
        else
            data.push_back("");
    }
    return row;
}



bool DataBaseBroker::isEmail(std::string emailId)
{
    string::size_type i = emailId.find("@");
    if(i == string::npos)
        return false;
    return true;
}

bool DataBaseBroker::canCreateID(std::string id)
{
    char *cmd = new char[100];
    sprintf(cmd, "select * from EmployeesTable where USERID = '%s'", id.c_str());
    if(!query(cmd))
    {
        delete [] cmd;
        return 0;
    }
    result = mysql_store_result(mysqlInstance);
    delete [] cmd;
    auto row = mysql_num_rows(result);
    if(row == 0)
        return 1;
    return 0;
}

void DataBaseBroker::errorIntoMySQL()
{
    errorNum = mysql_errno(mysqlInstance);
    errorInfo = mysql_error(mysqlInstance);
    cout << "数据库错误信息: " << errorNum << "-------" << errorInfo << endl;
}
bool DataBaseBroker::query(const string &querystr)
{
    auto cmd = querystr.c_str();
    if(0 == mysql_real_query(mysqlInstance, cmd, strlen(cmd)))
        return true;
    errorIntoMySQL();
    return false;
}
bool DataBaseBroker::getDatafromDB(string queryStr, std::vector<std::vector<string> > &data, int &row)
{
    if(!query(queryStr))
        return false;
    result=mysql_store_result(mysqlInstance);

    row = mysql_num_rows(result);
    unsigned int field = mysql_num_fields(result);

    MYSQL_ROW line=nullptr;
    line=mysql_fetch_row(result);

    cout<<"----line "<<row<<" "<<field<<endl;
    while(nullptr!=line)
    {
        vector<string> linedata;
        for(unsigned int i = 0; i < field;i++)
        {
            if(line[i])
            {
                std::cout << line[i] << "  ";
                linedata.push_back(line[i]);
            }
            else
            {
                linedata.push_back("");
            }
        }
        line=mysql_fetch_row(result);
        data.push_back(linedata);
    }
    return true;
}
bool DataBaseBroker::isSameString(string userID_fk, string friendID_fk)
{
    if(userID_fk== friendID_fk)
    {
        cout << "the same parameter " << endl;
        return true;
    }
    return false;
}
