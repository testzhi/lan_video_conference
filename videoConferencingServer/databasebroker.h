#ifndef DATABASEBROKER_H
#define DATABASEBROKER_H

#include <mariadb/mysql.h>
#include <string>
#include <vector>

class DataBaseBroker
{
public:
    DataBaseBroker();
    bool connectMySQL(char* server, char* username, char* password, char* database,int port);//connect to database
    bool createTables();
    void closeMySQL();

    int errorNum;                      //错误代号
    const char* errorInfo;
private:
    MYSQL_RES *result;                 //用于存放结果 建议用char* 数组将此结果转存
    MYSQL *mysqlInstance;              //MySQL对象，必备的一个数据结构

    void errorIntoMySQL();
    bool query(const std::string& querystr);
    bool insertIntoTableGroups(std::string userID_fk);
    bool getDatafromDB(std::string queryStr, std::vector<std::vector<std::string> >& data, int &row);

    bool isSameString(std::string userID_fk, std::string friendID_fk);
};

#endif // DATABASEBROKER_H
