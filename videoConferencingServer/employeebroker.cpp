#include "employeebroker.h"
#include "attendee.h"
#include "group.h"
#include "company.h"
#include "department.h"
#include <iostream>
#include <cstring>

using std::string;
using std::cerr;
using std::vector;

EmployeeBroker::EmployeeBroker()
{

}

void EmployeeBroker::addEmployee(std::string userid, std::string passwd, std::string userName, std::string email, std::string avatar,std::string groupName, std::string departmentName, std::string companyName, std::string phone)
{
    insertIntoTableEmployees(userid, passwd, userName, email,"", groupName, departmentName, companyName, phone, "");
    Employee *e = new Employee(userid, email, passwd, userName, avatar, groupName, departmentName, companyName, phone);
    auto er = _employees[userid];
    if(!er)//不存在记录则插入
        _employees[userid] = e;
}

void EmployeeBroker::addEmployee(Employee *e)
{
    insertIntoTableEmployees(e->userID(), e->passwd(), e->realName(), e->email(), e->avatar(), e->groupName(), e->departmentName(), e->companyName(), e->phone(), "");
    auto er = _employees[e->userID()];
    if(!er)//不存在记录则插入
        _employees[e->userID()] = e;
}

Employee *EmployeeBroker::findByEmployeeID(std::string id)
{
    bool find = false;
    auto er = _employees[id];
    if(er)
    {
        cerr<<"在关联容器userid-employee中查找";
        find = true;
        return er;
    }
    if(find == false)
    {

        Employee *e = queryEmployeeInfoByEmailID(id);
        _employees[id] = e;
        e->setMyCompany(queryColleagues(e->getCompany(), e->companyName()));
        queryUnfinishedMeetings(id);
        return e;
    }
    return nullptr;
}

Company* EmployeeBroker::findColleagues(std::string employeeid)
{
    auto emp = _employees[employeeid];
    if(!emp)
        return nullptr;
    else
    {
        Company *com = emp->getMyCompany();
        return com;
    }
}

std::map<int, Meeting *> EmployeeBroker::findMeetings(std::string employeeid)
{
    auto emp = _employees[employeeid];
    return emp->getMeetings();
}


Employee * EmployeeBroker::queryEmployeeInfoByEmailID(std::string emailID)
{
    char *cmd1 = new char[200];
    if(!isEmail(emailID))
        sprintf(cmd1, "select `USERID` , `EMAIL`, `REALNAME`, `AVATAR`, `PHONE`, `GROUPID`, `DEPARTMENTID`, `COMPANYID` from EmployeesTable where `USERID` = '%s';", emailID.c_str());
    else
        sprintf(cmd1, "select `USERID` , `EMAIL`, `REALNAME`, `AVATAR`, `PHONE`, `GROUPID`, `DEPARTMENTID`, `COMPANYID` from EmployeesTable where `EMAIL` = '%s';", emailID.c_str());
    int q1 = mysql_real_query(mysqlInstance, cmd1, strlen(cmd1));
    delete [] cmd1;
    if(q1 != 0)
    {
        errorIntoMySQL();
        return nullptr;
    }
    result = mysql_store_result(mysqlInstance);
    auto row1 = mysql_num_rows(result);
    MYSQL_ROW line1 = mysql_fetch_row(result);
    if(row1 == 0)
        return nullptr;
    else {
        vector<string> data;
        for(int i = 0; i != 5; ++i)
        {
            if(line1[i])
                data.push_back(line1[i]);
            else
                data.push_back("");
        }
        Employee *emp = new Employee(data[0], data[1], data[2], data[3],data[4]);
        char *company = new char[100];
        sprintf(company, "select `COMPANYNAME` from CompaniesTable where COMPANYID = '%s';", line1[7]);
        emp->setCompany(atoi(line1[7]));
        int q2 = mysql_real_query(mysqlInstance, company, strlen(company));
        delete [] company;
        if(q2 != 0)
            errorIntoMySQL();
        result = mysql_store_result(mysqlInstance);
        mysql_num_rows(result);
        MYSQL_ROW line2 = mysql_fetch_row(result);
        if(line2[0])//公司6
            emp->setCompanyName(line2[0]);
        else
            emp->setCompanyName("");



        char *department = new char[100];
        sprintf(department, "select `DEPARTMENTNAME` from DepartmentsTable where DEPARTMENTID = '%s';", line1[6]);
        emp->setDepartment(atoi(line1[6]));
        int q3 = mysql_real_query(mysqlInstance, department, strlen(department));
        delete [] department;
        if(q3 != 0)
            errorIntoMySQL();
        result = mysql_store_result(mysqlInstance);
        mysql_num_rows(result);
        MYSQL_ROW line3 = mysql_fetch_row(result);
        if(line3[0])//部门5
            emp->setDepartmentName(line3[0]);
        else
            emp->setDepartmentName("");



        char *group = new char[100];
        sprintf(group, "select `GROUPNAME` from GroupsTable where GROUPID = '%s';", line1[5]);
        emp->setGroup(atoi(line1[5]));
        int q4 = mysql_real_query(mysqlInstance, group, strlen(group));
        delete [] group;
        if(q4 != 0)
            errorIntoMySQL();
        result = mysql_store_result(mysqlInstance);
        mysql_num_rows(result);
        MYSQL_ROW line4 = mysql_fetch_row(result);
        if(line4[0])// 组4
            emp->setGroupName(line4[0]);
        else
            emp->setGroupName("");


        return emp;
    }
}

Company *EmployeeBroker::queryColleagues(int comid, std::string comName)
{
    Company *com = new Company(comName, comid);
    char *cmd = new char[150];
    sprintf(cmd, "select `DEPARTMENTNAME`, `DEPARTMENTID` from DepartmentsTable where `COMPANYID` = '%d';", comid);
    mysql_real_query(mysqlInstance, cmd, strlen(cmd));
    delete [] cmd;
    result = mysql_store_result(mysqlInstance);
    unsigned long long row = mysql_num_rows(result);
    for (unsigned long long i = 0; i != row; ++i)//departments
    {
        MYSQL_ROW line = mysql_fetch_row(result);
        Department *d = new Department(line[0], atoi(line[1]));
        char *cmd1 = new char[150];
        sprintf(cmd1, "select `GROUPNAME`, `GROUPID` from GroupsTable where `DEPARTMENTID` = '%s';", line[1]);
        mysql_real_query(mysqlInstance, cmd1, strlen(cmd1));
        delete [] cmd1;
        auto result_groups = mysql_store_result(mysqlInstance);
        unsigned long long row1 = mysql_num_rows(result_groups);
        for(unsigned long long j = 0; j != row1; ++j)//groups
        {
            MYSQL_ROW line1 = mysql_fetch_row(result_groups);
            Group *group = new Group(atoi(line1[1]), line1[0]);
            char *cmd2 = new char[200];
            sprintf(cmd2, "select `USERID` , `EMAIL`, `REALNAME`, `AVATAR`, `PHONE`, `IP` from EmployeesTable where `GROUPID` = '%s';", line1[1]);
            mysql_real_query(mysqlInstance, cmd2, strlen(cmd2));
            delete [] cmd2;
            auto result_attendees = mysql_store_result(mysqlInstance);
            unsigned long long row2 = mysql_num_rows(result_attendees);
            for(unsigned long long k = 0; k != row2; ++k)
            {
                MYSQL_ROW line2 = mysql_fetch_row(result_attendees);
                vector<string> data;
                for (int f = 0; f != 6; ++f)
                {
                    if(line2[f])
                        data.push_back(line2[f]);
                    else data.push_back("");
                }
                Employee *employee = new Employee(data[0], data[1], data[2], data[3], data[4]);
                employee->setIpAddress(data[5]);
                group->addGroupMembers(employee);
            }
            d->addGroup(group);
            mysql_free_result(result_attendees);
        }
        com->addDepartment(d);
        mysql_free_result(result_groups);
    }
    return com;
}

Employee *EmployeeBroker::queryUnfinishedMeetings(std::string id)
{
    auto employee = _employees[id];
    char *cmd = new char[150];
    sprintf(cmd, "select `MEETINGID` from AttendeesTable where `ATTENDEEID` = '%s'  and `ATTENDSTATE` = '1';", id.c_str());
    int r1 = mysql_real_query(mysqlInstance, cmd, strlen(cmd));
    delete [] cmd;
    if(r1 != 0)
        errorIntoMySQL();
    else {
        result = mysql_store_result(mysqlInstance);
        auto row = mysql_num_rows(result);
        for (unsigned long long i = 0; i != row; ++i)
        {
            MYSQL_ROW line = mysql_fetch_row(result);
            if(line[0])
            {
                int meetingid = atoi(line[0]);
                Meeting *meeting = queryMeetingDetail(meetingid);
                employee->addMeeting(meeting);
            }
        }
    }


    char *cmd2 = new char[150];
    sprintf(cmd2, "select `MEETINGID` from AttendeesTable where `ATTENDEEID` = '%s'  and `ATTENDSTATE` = '3';", id.c_str());
    int r2 = mysql_real_query(mysqlInstance, cmd2, strlen(cmd2));
    delete [] cmd2;
    if(r2 != 0)
        errorIntoMySQL();

    result = mysql_store_result(mysqlInstance);
    auto row2 = mysql_num_rows(result);
    delete [] cmd2;

    for (unsigned long long i = 0; i != row2; ++i)
    {
        MYSQL_ROW line = mysql_fetch_row(result);

        if(line[0])
        {
            int meetingid = atoi(line[0]);
            Meeting *meeting = queryMeetingDetail(meetingid);
            employee->addMeeting(meeting);
        }
    }

    return  employee;
}

Employee *EmployeeBroker::queryNotifications(std::string id)
{
    auto employee = _employees[id];
    char *cmd = new char[150];
    sprintf(cmd, "select `MEETINGID` from AttendeesTable where `ATTENDEEID` = '%s'  and `ATTENDSTATE` = '1';", id.c_str());
    int r1 = mysql_real_query(mysqlInstance, cmd, strlen(cmd));
    delete [] cmd;
    if(r1 != 0)
        errorIntoMySQL();

    result = mysql_store_result(mysqlInstance);
    auto row = mysql_num_rows(result);
    for (unsigned long long i = 0; i != row; ++i)
    {
        MYSQL_ROW line = mysql_fetch_row(result);
        if(line[0])
        {
            int meetingid = atoi(line[0]);
            Meeting *meeting = queryMeetingDetail(meetingid);
            employee->addMeeting(meeting);
        }
    }

    char *cmd2 = new char[150];
    sprintf(cmd2, "select `MEETINGID` from AttendeesTable where `ATTENDEEID` = '%s'  and `ATTENDSTATE` = '3';", id.c_str());
    int r2 = mysql_real_query(mysqlInstance, cmd2, strlen(cmd2));
    delete [] cmd2;
    if(r2 != 0)
        errorIntoMySQL();

    result = mysql_store_result(mysqlInstance);
    auto row2 = mysql_num_rows(result);
    delete [] cmd2;

    for (unsigned long long i = 0; i != row2; ++i)
    {
        MYSQL_ROW line = mysql_fetch_row(result);

        if(line[0])
        {
            int meetingid = atoi(line[0]);
            Meeting *meeting = queryMeetingDetail(meetingid);
            employee->addMeeting(meeting);
        }
    }

    return  employee;
}

Meeting *EmployeeBroker::queryMeetingDetail(int meetingid)
{
    char *cmd = new char[150];
    sprintf(cmd, "select * from MeetingsTable where `MEETINGID` = '%d';", meetingid);
    int r = mysql_real_query(mysqlInstance, cmd, strlen(cmd));
    delete [] cmd;
    if(r != 0)
    {
        errorIntoMySQL();
        return nullptr;
    }

    MYSQL_RES *res = mysql_store_result(mysqlInstance);
    auto row = mysql_num_rows(res);
    if(row == 0) return nullptr;
    MYSQL_ROW line = mysql_fetch_row(res);
    unsigned int field = mysql_num_fields(res);
    vector<string> data;
    for (unsigned int i = 0; i != field; ++i)
    {
        if(line[i])
            data.push_back(line[i]);
        else
            data.push_back("");
    }
    Meeting *meeting = new Meeting(atoi(data[0].c_str()), data[2], data[3], data[4], data[5], atoi(data[6].c_str()), data[7], atoi(data[10].c_str()), atoi(data[11].c_str()), atoi(data[14].c_str()), data[15]);
    meeting->setSpeakerName(queryNameByID(meeting->speaker()));
    meeting->setAssistantName(queryNameByID(meeting->assistant()));
    mysql_free_result(res);
    return meeting;
}

std::string EmployeeBroker::queryNameByID(std::string userID)
{
    char *cmd = new char[150];
    sprintf(cmd, "select `REALNAME` from EmployeesTable where USERID = '%s';", userID.c_str());
    int r = mysql_real_query(mysqlInstance, cmd, strlen(cmd));
    delete [] cmd;
    if(r != 0)
    {
        errorIntoMySQL();
        return "";
    }
    MYSQL_RES *res = mysql_store_result(mysqlInstance);
    auto row = mysql_num_rows(res);
    if(row == 0) return "";
    MYSQL_ROW line = mysql_fetch_row(res);
    mysql_free_result(res);
    if(line[0])
    {
        std::string str = line[0];
        return str;
    }
    else
        return "";
}
