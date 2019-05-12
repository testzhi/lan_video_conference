#ifndef EMPLOYEEBROKER_H
#define EMPLOYEEBROKER_H

#include "databasebroker.h"
#include "employee.h"
#include <map>
class EmployeeBroker : DataBaseBroker
{
public:
    EmployeeBroker();

    Employee *findByEmployeeID(std::string id);
};

#endif // EMPLOYEEBORKER_H
