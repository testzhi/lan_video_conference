#ifndef GROUP_H
#define GROUP_H

//#include <employee.h>
#include <QQmlListProperty>

class ConciseEmployee:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userID READ userID WRITE setUserID NOTIFY userIDChanged)
    Q_PROPERTY(QString realName READ realName WRITE setRealName NOTIFY realNameChanged)
signals:
    void userIDChanged();
    void realNameChanged();
public:
    QString userID() const;
    void setUserID(const QString &userID);

    QString realName() const;
    void setRealName(const QString &realName);

private:
    QString m_userID;
    QString m_realName;
};

class Group:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString groupName READ groupName WRITE setGroupName NOTIFY groupNameChanged)
        Q_PROPERTY(int employeesNumber READ employeesNumber NOTIFY employeesNumberChanged)
//    void setUserID(const QString &userID);

//    emplQString userID() const;
//    void setUserID(const QString &userID);

//
    Q_PROPERTY(QQmlListProperty<ConciseEmployee> conciseEmployees READ conciseEmployees NOTIFY conciseEmployeeChanged)
    Q_CLASSINFO("DefaultProperty","employees")

signals:
    void groupNameChanged();
    void conciseEmployeeChanged();
//    void employeesChanged();
    void employeesNumberChanged();
public:
    Group(QObject *parent = 0):QObject(parent){
        m_employeesNumber = 0;
    }
    Q_INVOKABLE QString groupName() const;
    Q_INVOKABLE void setGroupName(const QString &groupName);

//    Q_INVOKABLE QQmlListProperty<Employee> employees();
    Q_INVOKABLE ConciseEmployee *getConciseEmployee(int i);
    Q_INVOKABLE int conciseEmployeeCount();
    Q_INVOKABLE void insertConciseEmployee(ConciseEmployee *employee);
    Q_INVOKABLE int employeesNumber() const;
    Q_INVOKABLE void setEmployeesNumber(int employeesNumber);

    Q_INVOKABLE QQmlListProperty<ConciseEmployee> conciseEmployees();

private:
    QString m_groupName;
    int m_employeesNumber;
    QList<ConciseEmployee *> _conciseEmployees;

//        static void appendEmployee(QQmlListProperty<Employee> *employees,Employee *employee);
//    static int countEmployee(QQmlListProperty<Employee> *employees);
//    static Employee *atEmployee(QQmlListProperty<Employee> *employees,int i);
//    static void clearEmployee(QQmlListProperty<Employee> *employees);
    static void appendConciseEmployee(QQmlListProperty<ConciseEmployee> *ces,ConciseEmployee *ce);
    static int countConciseEmployee(QQmlListProperty<ConciseEmployee> *ces);
    static ConciseEmployee *atConciseEmployee(QQmlListProperty<ConciseEmployee> *ces,int i);
    static void clearConciseEmployee(QQmlListProperty<ConciseEmployee> *ces);
};

#endif // GROUP_H
