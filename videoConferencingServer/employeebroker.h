#ifndef EMPLOYEEBROKER_H
#define EMPLOYEEBROKER_H

#include "databasebroker.h"
#include "employee.h"
#include <map>

class EmployeeBroker : DataBaseBroker
{
public:
    EmployeeBroker();
    void addEmployee(std::string userid, std::string passwd, std::string userName, std::string email, std::string avatar, std::string groupName, std::string departmentName, std::string companyName, std::string phone);
    void addEmployee(Employee *e);

    Employee *findByEmployeeID(std::string id);
    Company *findColleagues(std::string employeeid);
    std::map<int, Meeting *> findMeetings(std::string employeeid);
private:
    Employee *queryEmployeeInfoByEmailID(std::string emailID);
    Company *queryColleagues(int comid, std::string comName);
    Employee *queryUnfinishedMeetings(std::string id);
    Employee *queryNotifications(std::string id);
    Meeting *queryMeetingDetail(int meetingid);
    std::string queryNameByID(std::string userID);
private:
    std::map<std::string, Employee*> _employees;
};

#endif // EMPLOYEEBORKER_H
