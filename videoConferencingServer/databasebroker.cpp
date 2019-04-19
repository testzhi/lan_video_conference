#include "databasebroker.h"
#include <iostream>
#include <cstring>

using std::cout;
using std::endl;
using std::string;
using std::vector;

DataBaseBroker::DataBaseBroker()
//    :errorNum(0),errorInfo("ok"), mysqlInstance(mysql_init(NULL))//分配内存并初始化一个MYSQL *对象
{
    mysql_library_init(0,NULL,NULL);
    mysql_init(mysqlInstance);
    mysql_options(mysqlInstance,MYSQL_SET_CHARSET_NAME,"utf8");
    //    mysql_options(mysqlInstance,MYSQL_SET_CHARSET_NAME,"gbk");
}

bool DataBaseBroker::connectMySQL(char *server, char *username, char *password, char *database, int port)
{
    if(mysql_real_connect(mysqlInstance, server, username, password, database, port, 0, 0) != NULL)
    {
        cout << "connect mysql successfully" << endl;
        return true;
    }
    else
    {
        errorIntoMySQL();
        return false;
    }
}

bool DataBaseBroker::createTables()
{
    string accounts="create table if not exists EmployeesTable(USERID char(7) not null, PASSWD char(16) not null, REALNAME char(16) not null, AVATAR blob , GROUPID int not null, COMPANY varchar(16) not null, STATE bool default 0, IP varchar char(20), primary key(userID_pk))";

    if(!query(accounts))
        return false;
    cout << "create tables successfully" << endl;
    return true;
}

void DataBaseBroker::errorIntoMySQL()
{
    errorNum = mysql_errno(mysqlInstance);
    errorInfo = mysql_error(mysqlInstance);
    cout << "Error Number :" << errorNum << "-------" << errorInfo << endl;
}

bool DataBaseBroker::query(const std::string &querystr)
{
    auto cmd = querystr.c_str();
    if(0 == mysql_real_query(mysqlInstance, cmd, strlen(cmd)))
        return true;
    errorIntoMySQL();
    return false;
}

bool DataBaseBroker::insertIntoTableGroups(std::string userID_fk)
{
    string cmd = "insert into tableGroups values('" + userID_fk +"','0','DefaultGroup');";
    cout << cmd << "  ";

    if(!query(cmd))
        return true;
    else
    {
        cout<<"insert groups"<<endl;
        return false;
    }
}

bool DataBaseBroker::getDatafromDB(std::string queryStr, std::vector<std::vector<std::string> > &data, int &row)
{
    if(!query(queryStr))
        return false;
    result=mysql_store_result(mysqlInstance);

    row=mysql_num_rows(result);
    int field=mysql_num_fields(result);

    MYSQL_ROW line=NULL;
    line=mysql_fetch_row(result);

    cout<<"----line "<<row<<" "<<field<<endl;
    while(NULL!=line)
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

bool DataBaseBroker::isSameString(std::string userID_fk, std::string friendID_fk)
{
    if(userID_fk== friendID_fk)
    {
        cout << "the same parameter " << endl;
        return true;
    }
    return false;
}
