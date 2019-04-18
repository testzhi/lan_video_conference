#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <group.h>
#include <QQmlListProperty>

class Department:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString departmentName READ departmentName WRITE setDepartmentName NOTIFY departmentNameChanged)
    Q_PROPERTY(QString employeesNumber READ employeesNumber NOTIFY employeesNumberChanged)
    Q_PROPERTY(QQmlListProperty<Group> groups READ groups NOTIFY groupsChanged)
signals:
    void departmentNameChanged();
    void groupsChanged();
    void employeesNumberChanged();
public:
    Department(QObject *parent = 0):QObject(parent){
        m_employeesNumber = 0;
    }
    Q_INVOKABLE QString departmentName() const;
    Q_INVOKABLE void setDepartmentName(const QString &departmentName);
    
    Q_INVOKABLE QQmlListProperty<Group> groups();
    Q_INVOKABLE Group *getGroup(int i);
    Q_INVOKABLE int groupCount();
    Q_INVOKABLE int employeeCount();
    Q_INVOKABLE void insertGroup(Group *group);
    
    Q_INVOKABLE QString employeesNumber() const;

private:
    QString m_departmentName;
    int m_employeesNumber;
    QList<Group *> _groups;
    
    static void appendGroup(QQmlListProperty<Group> *groups,Group *group);
    static int countGroup(QQmlListProperty<Group> *groups);
    static Group *atGroup(QQmlListProperty<Group> *groups,int i);
    static void clearGroup(QQmlListProperty<Group> *groups);
};

#endif // DEPARTMENT_H
