#ifndef GROUP_H
#define GROUP_H

#include <employee.h>
#include <QQmlListProperty>

class Group:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString groupName READ groupName WRITE setGroupName NOTIFY groupNameChanged)
//    Q_PROPERTY(int employeesNumber READ employeesNumber NOTIFY employeesNumberChanged)
    Q_PROPERTY(QQmlListProperty<Employee> employees READ employees NOTIFY employeesChanged)
    Q_CLASSINFO("DefaultProperty","employees")

signals:
    void groupNameChanged();
    void employeesChanged();
//    void employeesNumberChanged();
public:
    Group(QObject *parent = 0):QObject(parent){
        m_employeesNumber = 0;
    }
    Q_INVOKABLE QString groupName() const;
    Q_INVOKABLE void setGroupName(const QString &groupName);

    Q_INVOKABLE QQmlListProperty<Employee> employees();
    Q_INVOKABLE Employee *getEmployee(int i);
    Q_INVOKABLE int employeeCount();
    Q_INVOKABLE void insertEmplyee(Employee *employee);
//    Q_INVOKABLE QString employeesNumber() const;
//    Q_INVOKABLE void setEmployeesNumber(int employeesNumber);

private:
    QString m_groupName;
    int m_employeesNumber;
    QList<Employee *> _employees;

    static void appendEmployee(QQmlListProperty<Employee> *employees,Employee *employee);
    static int countEmployee(QQmlListProperty<Employee> *employees);
    static Employee *atEmployee(QQmlListProperty<Employee> *employees,int i);
    static void clearEmployee(QQmlListProperty<Employee> *employees);
};

#endif // GROUP_H
