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
    //    mysql_options(mysqlInstance,MYSQL_SET_CHARSET_NAME,"gbk");
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
        insertIntoTableGroups(groupName, depaid, comid);
    int gid = getGroupID(groupName, depaid, comid);

    char cmd[200];
    sprintf(cmd, "insert into EmployeesTable values('%s', '%s', '%s', '%s', NULL, '%d', '%d', '%d', NULL, '0', '%s');", userid.c_str(), passwd.c_str(), userName.c_str(), email.c_str(), gid, depaid, comid, ip.c_str());

    if(!query(cmd))
        return 0;
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
        insertIntoTableGroups(groupName, depaid, comid);
    int gid = getGroupID(groupName, depaid, comid);

    char cmd[200];
    sprintf(cmd, "insert into EmployeesTable values('%s', '%s', '%s', '%s', NULL, '%d', '%d', '%d', '%s', '0', '%s');", userid.c_str(), passwd.c_str(), userName.c_str(), email.c_str(), gid, depaid, comid, phone.c_str(), ip.c_str());

    if(!query(cmd))
        return 0;
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
        insertIntoTableGroups(groupName, depaid, comid);
    int gid = getGroupID(groupName, depaid, comid);

    char cmd[200];
    sprintf(cmd, "insert into EmployeesTable values('%s', '%s', '%s', '%s', '%s', '%d', '%d', '%d', '%s', '0', '%s');", userid.c_str(), passwd.c_str(), userName.c_str(), email.c_str(), avatar.c_str(), gid, depaid, comid, phone.c_str(), ip.c_str());

    if(!query(cmd))
        return 0;
    return 1;
}

int DataBaseBroker::queryEmployeeInfoByEmailID(std::string emailID, std::vector<std::string> &data)
{
    char cmd[100];
    if(!isEmail(emailID))
        sprintf(cmd, "select * from EmployeesTable where USERID = '%s';", emailID.c_str());
    else
        sprintf(cmd, "select * from EmployeesTable where EMAIL = '%s';", emailID.c_str());

    if(!query(cmd))
        return -1;
    result=mysql_store_result(mysqlInstance);
    auto row1 = mysql_num_rows(result);

    MYSQL_ROW line1 = mysql_fetch_row(result);
    if(row1 == 0)
        return 0;
    else {
        char company[100], department[100], group[100];
        sprintf(company, "select * from CompaniesTable where COMPANYID = '%s';", line1[7]);
        if(!query(company))
            return -1;
        result=mysql_store_result(mysqlInstance);
        auto row2 = mysql_num_rows(result);
        if(row2 == 0) return 0;
        MYSQL_ROW line2 = mysql_fetch_row(result);

        sprintf(department, "select * from DepartmentsTable where DEPARTMENTID = '%s';", line1[6]);
        if(!query(department))
            return -1;
        result=mysql_store_result(mysqlInstance);
        auto row3 = mysql_num_rows(result);
        if(row3 == 0) return 0;
        MYSQL_ROW line3 = mysql_fetch_row(result);

        sprintf(group, "select * from GroupsTable where GROUPID = '%s';", line1[5]);
        if(!query(group))
            return -1;
        result=mysql_store_result(mysqlInstance);
        auto row4 = mysql_num_rows(result);
        if(row4 == 0) return 0;
        MYSQL_ROW line4 = mysql_fetch_row(result);

        if(line1[0])//id0
        {
            data.push_back(line1[0]);
        }else {
            data.push_back("");
        }
        if(line1[3])//email1
        {
            data.push_back(line1[3]);
        }else {
            data.push_back("");
        }
        if(line1[2])//name2
        {
            data.push_back(line1[2]);
        }else {
            data.push_back("");
        }
        if(line1[4])//avatar3
        {
            data.push_back(line1[4]);
        }else {
            data.push_back("");
        }
        if(line4[1])// 组4
        {
            data.push_back(line4[1]);
        }else {
            data.push_back("");
        }
        if(line3[1])//部门5
        {
            data.push_back(line3[1]);
        }else {
            data.push_back("");
        }
        if(line2[1])//公司6
        {
            data.push_back(line2[1]);
        }else {
            data.push_back("");
        }
        if(line1[8])//电话7
        {
            data.push_back(line1[8]);
        }else {
            data.push_back("");
        }
    }
    cout<<"query succeed"<<endl;
    return 1;
}

int DataBaseBroker::queryResultForLogin(std::string emailID, std::vector<std::string> &data)
{
    char cmd[100];
    if(!isEmail(emailID))
        sprintf(cmd, "select * from EmployeesTable where USERID = '%s';", emailID.c_str());
    else
        sprintf(cmd, "select * from EmployeesTable where EMAIL = '%s';", emailID.c_str());

    if(!query(cmd))
        return -1;
    result=mysql_store_result(mysqlInstance);
    auto row = mysql_num_rows(result);
    if(row == 0)
        return 0;

    MYSQL_ROW line = mysql_fetch_row(result);

    if(line[0])
        data.push_back(line[0]);
    else
        data.push_back("");
    if(line[3])
        data.push_back(line[3]);
    else
        data.push_back("");
    if(line[1])
        data.push_back(line[1]);
    else
        data.push_back("");
    if(line[9])
        data.push_back(line[9]);
    else
        data.push_back("");
    if(line[10])
        data.push_back(line[10]);
    else
        data.push_back("");
    cout<<"query succeed"<<endl;
    return 1;
}
bool DataBaseBroker::updateStateByEmaiID(std::string emailID, int state, std::string ip)
{
    char cmd[200], cmd2[200];
    if(isValidAccount(emailID) == 1)
    {
        sprintf(cmd, "update EmployeesTable set IP = '%s' where USERID = '%s';", ip.c_str(), emailID.c_str());
        sprintf(cmd2, "update EmployeesTable set STATE = '%d' where USERID = '%s';", state, emailID.c_str());
    }
    else if (isValidAccount(emailID) == 2) {
        sprintf(cmd, "update EmployeesTable set IP = '%s' where EMAIL = '%s';", ip.c_str(), emailID.c_str());
        sprintf(cmd2, "update EmployeesTable set STATE = '%d' where USERID = '%s';", state, emailID.c_str());
    }
    if(!query(cmd))
        return false;
    if(!query(cmd2))
        return false;
    cout<<"update state success"<<endl;
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
                       "`STATE` INT NOT NULL DEFAULT 0,"
                       "`IP` VARCHAR(20),"
                       "PRIMARY KEY (`USERID`),"
                       "UNIQUE INDEX `EMAIL_UNIQUE` (`EMAIL` ASC)"
                       ");";
    string companies = "CREATE TABLE IF NOT EXISTS`VideoConferencingDB`.`CompaniesTable` ("
                       "`COMPANYID` INT NOT NULL AUTO_INCREMENT,"
                       "`COMPANYNAME` VARCHAR(20) NOT NULL,"
                       "PRIMARY KEY (`COMPANYID`),"
                       "UNIQUE INDEX `COMPANYNAME_UNIQUE` (`COMPANYNAME` ASC)"
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
                    "`COMPANYID` INT NOT NULL,"
                    "PRIMARY KEY (`GROUPID`),"
                    "CONSTRAINT `FK_DEPARTMENTID` FOREIGN KEY (`DEPARTMENTID`) REFERENCES `DepartmentsTable` (`DEPARTMENTID`)"
                    ");";

    if(!query(employees))
        return false;
    if(!query(companies))
        return false;
    if(!query(departments))
        return false;
    if(!query(groups))
        return false;
    cout << "建表成功" << endl;
    return true;
}



bool DataBaseBroker::canRegister(string email)
{
    char cmd[100];
    sprintf(cmd, "select * from EmployeesTable where EMAIL = '%s'", email.c_str());
    if(!query(cmd))
        return 0;
    result=mysql_store_result(mysqlInstance);
    auto row = mysql_num_rows(result);
    if(row == 0)
        return 1;
    return 0;
}
int DataBaseBroker::isValidAccount(std::string emailId)
{
    char cmd[200];
    bool em = isEmail(emailId);
    if(!em)
    {
        sprintf(cmd, "select * from EmployeesTable where USERID = '%s';", emailId.c_str());
    }else {
        sprintf(cmd, "select * from EmployeesTable where EMAIL = '%s';", emailId.c_str());
    }
    if(!query(cmd))
        return 0;
    result=mysql_store_result(mysqlInstance);
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
    char cmd[200];
    sprintf(cmd, "insert into CompaniesTable values(NULL, '%s');", name.c_str());
    if(!query(cmd))
        return false;
    return true;
}
bool DataBaseBroker::insertIntoTableDepartments(string name, int companyid)
{
    char cmd[200];
    sprintf(cmd, "insert into DepartmentsTable values(NULL, '%s', '%d');", name.c_str(), companyid);
    if(!query(cmd))
        return false;
    return true;
}
bool DataBaseBroker::insertIntoTableGroups(string name, int departmentid, int companyid)
{
    char cmd[200];
    sprintf(cmd, "insert into GroupsTable values(NULL, '%s', '%d', '%d');", name.c_str(), departmentid, companyid);
    if(!query(cmd))
        return false;
    return true;
}



bool DataBaseBroker::needCreateNewCompany(string comName)
{
    char cmd[100];
    sprintf(cmd, "select * from CompaniesTable where COMPANYNAME = '%s'", comName.c_str());
    if(!query(cmd))
        return 0;
    result=mysql_store_result(mysqlInstance);
    auto row = mysql_num_rows(result);
    if(row == 0)
        return 1;
    return 0;
}
int DataBaseBroker::getCompanyID(std::string comName)
{
    char cmd[100];
    sprintf(cmd, "select * from CompaniesTable where COMPANYNAME = '%s'", comName.c_str());
    if(!query(cmd))
        return 0;
    result=mysql_store_result(mysqlInstance);
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
        char cmd[100];
        sprintf(cmd, "select * from DepartmentsTable where DEPARTMENTNAME = '%s' and COMPANYID = '%d'", depaName.c_str(), cid);
        if(!query(cmd))
            return 0;
        result=mysql_store_result(mysqlInstance);
        auto row = mysql_num_rows(result);
        if(row == 0)
            return 1;
    }
    return 0;
}
int DataBaseBroker::getDepartmentID(std::string depaName, int cid)
{
    char cmd[100];
    sprintf(cmd, "select * from DepartmentsTable where DEPARTMENTNAME = '%s' and COMPANYID = '%d'", depaName.c_str(), cid);
    if(!query(cmd))
        return 0;
    result=mysql_store_result(mysqlInstance);
    auto row = mysql_num_rows(result);
    if(row == 0)
        return -1;
    MYSQL_ROW line = mysql_fetch_row(result);
    return atoi(line[0]);
}
bool DataBaseBroker::needCreateNewGroup(std::string gName, std::string depaName, std::string comName, int &did, int &cid)
{
    cid = getCompanyID(comName);
    did = getDepartmentID(depaName, cid);
    if(cid != -1 && did != -1)
    {
        char cmd[100];
        sprintf(cmd, "select * from GroupsTable where GROUPNAME = '%s' and COMPANYID = '%d' and DEPARTMENTID = '%d'", gName.c_str(), cid, did);
        if(!query(cmd))
            return 0;
        result=mysql_store_result(mysqlInstance);
        auto row = mysql_num_rows(result);
        if(row == 0)
            return 1;
    }
    return 0;

}
int DataBaseBroker::getGroupID(std::string gName, int did, int cid)
{
    char cmd[100];
    sprintf(cmd, "select * from GroupsTable where GROUPNAME = '%s' and COMPANYID = '%d' and DEPARTMENTID = '%d'", gName.c_str(), cid, did);
    if(!query(cmd))
        return 0;
    result=mysql_store_result(mysqlInstance);
    auto row = mysql_num_rows(result);
    if(row == 0)
        return -1;
    MYSQL_ROW line = mysql_fetch_row(result);
    return atoi(line[0]);
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
    char cmd[100];
    sprintf(cmd, "select * from EmployeesTable where USERID = '%s'", id.c_str());
    if(!query(cmd))
        return 0;
    result=mysql_store_result(mysqlInstance);
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
    auto field=mysql_num_fields(result);

    MYSQL_ROW line=nullptr;
    line=mysql_fetch_row(result);

    cout<<"----line "<<row<<" "<<field<<endl;
    while(nullptr!=line)
    {
        vector<string> linedata;
        for(int i=0; i<field;i++)
        {
            if(line[i])
            {
                std::cout<<line[i]<<"  ";
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
