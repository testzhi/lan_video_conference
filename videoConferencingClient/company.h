#ifndef COMPANY_H
#define COMPANY_H

#include <QQmlListProperty>

#include <department.h>

class Company:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString companyName READ companyName WRITE setCompanyName NOTIFY companyNameChanged)
    Q_PROPERTY(QString employeesNumber READ employeesNumber NOTIFY employeesNumberChanged)
    Q_PROPERTY(QQmlListProperty<Department> departments READ departments NOTIFY departmentsChanged)
    Q_CLASSINFO("DefaultProperty","departments")
signals:
    void companyNameChanged();
    void departmentsChanged();
    void employeesNumberChanged();
public:
    Company(QObject *parent = 0):QObject(parent){
        m_employeesNumber = 0;
    }
    Q_INVOKABLE QString companyName() const;
    Q_INVOKABLE void setCompanyName(const QString &companyName);

    Q_INVOKABLE QQmlListProperty<Department> departments();

    Q_INVOKABLE Department *getDepartment(int i);
    Q_INVOKABLE int departmentCount();
    Q_INVOKABLE void insertDepartment(Department *department);

    QString employeesNumber() const;

private:
    QString m_companyName;
    int m_employeesNumber;
    QList<Department *> _departments;
    static void appendDepartment(QQmlListProperty<Department> *departments, Department * department);
    static int countDepartment(QQmlListProperty<Department> *departments);
    static Department *atDepartment(QQmlListProperty<Department> *departments,int i);
    static void clearDepartment(QQmlListProperty<Department> *departments);
};

#endif // COMPANY_H
