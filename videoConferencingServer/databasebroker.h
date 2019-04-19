#ifndef DATABASEBROKER_H
#define DATABASEBROKER_H

#include <mariadb/mysql.h>
#include <string>
#include <vector>

class DataBaseBroker
{
public:
    DataBaseBroker();
    ~DataBaseBroker();
    bool connectMySQL(const char *host, const char *username, const char *password, const char *database, int port);
    bool createTables();

    bool canRegister(std::string email);
    //无效email-2 ，无效ID-1, 0命令执行失败  ，ID 1 ，email 2
    int isValidAccount(std::string emailId);

    //-1 email注册失败， 0命令执行失败， 1成功
    int insertIntoTableEmployees(std::string userid, std::string passwd, std::string userName, std::string email, std::string groupName, std::string departmentName, std::string companyName, std::string ip);
    int insertIntoTableEmployees(std::string userid, std::string passwd, std::string userName, std::string email, std::string groupName, std::string departmentName, std::string companyName, std::string phone, std::string ip);
    int insertIntoTableEmployees(std::string userid, std::string passwd, std::string userName, std::string email, std::string avatar, std::string groupName, std::string departmentName, std::string companyName, std::string phone, std::string ip);

    //0无结果 -1命令执行失败 1成功
    int queryEmployeeInfoByEmailID(std::string emailID, std::vector<std::string> &data);
    //id email passwd state ip
    int queryResultForLogin(std::string emailID, std::vector<std::string> &data);



    bool updateStateByEmaiID(std::string emailID, int state, std::string ip);

    const char *getErrorInfo() const;
    int getErrorNum() const;

private:
    int errorNum;                      //错误代号
    const char* errorInfo;
    MYSQL_RES *result;                 //用于存放结果 建议用char* 数组将此结果转存
    MYSQL *mysqlInstance;              //MySQL对象，必备的一个数据结构


    bool insertIntoTableCompanies(std::string name);
    bool insertIntoTableDepartments(std::string name, int companyid);
    bool insertIntoTableGroups(std::string name, int departmentid, int companyid);



    bool needCreateNewCompany(std::string comName);
    int getCompanyID(std::string comName);
    bool needCreateNewDepartment(std::string depaName, std::string comName, int &cid);
    int getDepartmentID(std::string depaName, int cid);
    bool needCreateNewGroup(std::string gName, std::string depaName, std::string comName, int &did, int &cid);
    int getGroupID(std::string gName, int did, int cid);


    //email 1 , id 0
    bool isEmail(std::string emailId);
    bool canCreateID(std::string id);
    void errorIntoMySQL();
    bool query(const std::string& querystr);
    bool getDatafromDB(std::string queryStr, std::vector<std::vector<std::string> >& data, int &row);
    bool isSameString(std::string userID_fk, std::string friendID_fk);
    void closeMySQL();
};

#endif // DATABASEBROKER_H
