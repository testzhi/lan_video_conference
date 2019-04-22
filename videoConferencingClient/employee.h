#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <vector>
#include <QObject>
#include <QQmlListProperty>

#include <meeting.h>
#include "notification.h"

class Employee:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userID READ userID WRITE setUserID NOTIFY userIDChanged)
    Q_PROPERTY(QString userPassword READ userPassword WRITE setUserPassword NOTIFY userPasswordChanged)
    Q_PROPERTY(bool state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(QString avatar READ avatar WRITE setAvatar NOTIFY avatarChanged)
    Q_PROPERTY(QString company READ company WRITE setCompany NOTIFY companyChanged)
    Q_PROPERTY(QString department READ department WRITE setDepartment NOTIFY departmentChanged)
    Q_PROPERTY(QString realName READ realName WRITE setRealName NOTIFY realNameChanged)
    Q_PROPERTY(QString phone READ phone WRITE setPhone NOTIFY phoneChanged)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(QString group READ group WRITE setGroup NOTIFY groupChanged)
    Q_PROPERTY(QQmlListProperty<Meeting> meetings READ meetings NOTIFY meetingsChanged)
    Q_PROPERTY(QQmlListProperty<Notification> notifications READ notifications NOTIFY notificationsChanged)
    Q_CLASSINFO("DefaultProperty", "meetings")
signals:
    void userIDChanged();
    void userPasswordChanged();
    void stateChanged();
    void avatarChanged();
    void companyChanged();
    void departmentChanged();
    void realNameChanged();
    void phoneChanged();
    void emailChanged();
    void groupChanged();
    void meetingsChanged();
    void notificationsChanged();

    void registerSuccessfully();//注册成功
    void emailAlreadyRegistered();//注册失败 之 email已被占用
    void loginSucceeded();//登录成功
    void loginFailed(QString err);
public:
    Employee(QObject *parent = 0):QObject(parent){
//        m_userID = "111";
        m_userPassword = "12345678";
        m_state = 0;
        m_avatar = "../resources/1.jpg";
        m_company = "tieto";
        m_department = "development";
//        m_realName = "李章玉";
        m_phone = "13996506909";
        m_email = "912945084@qq.com";
        m_group = "Ginkgoes";
    }
    Employee(std::string userID, std::string userPassword, bool state, std::string avatar, std::string company, std::string department, std::string group, std::string realName, std::string phone);

    Q_INVOKABLE QString userID() const;
    Q_INVOKABLE void setUserID(const QString &userID);
    Q_INVOKABLE QString userPassword() const;
    Q_INVOKABLE void setUserPassword(const QString &userPassword);
    Q_INVOKABLE bool state() const;
    Q_INVOKABLE void setState(bool state);
    Q_INVOKABLE QString avatar() const;
    Q_INVOKABLE void setAvatar(const QString &avatar);
    Q_INVOKABLE QString company() const;
    Q_INVOKABLE void setCompany(const QString &company);
    Q_INVOKABLE QString department() const;
    Q_INVOKABLE void setDepartment(const QString &department);
    Q_INVOKABLE QString realName() const;
    Q_INVOKABLE void setRealName(const QString &realName);
    Q_INVOKABLE QString phone() const;
    Q_INVOKABLE void setPhone(const QString &phone);
    Q_INVOKABLE QString email() const;
    Q_INVOKABLE void setEmail(const QString &email);
    Q_INVOKABLE QString group() const;
    Q_INVOKABLE void setGroup(const QString &group);
    Q_INVOKABLE void setMeetings(const QList<Meeting *> &meetings);
    Q_INVOKABLE QQmlListProperty<Meeting> meetings();
    Q_INVOKABLE Meeting *getMeeting(int i);
    Q_INVOKABLE int meetingCount();
    Q_INVOKABLE Notification *getNotification(int i);
    Q_INVOKABLE int notificationCount();

    void insertMeeting(Meeting *meeting);
    void insertNotification(Notification *notification);
    void sortMeeting();

    QQmlListProperty<Notification> notifications();

private:
    QString m_userID;
    QString m_userPassword;
    bool m_state;
    QString m_avatar;
    QString m_company;
    QString m_department;
    QString m_realName;
    QString m_phone;
    QString m_email;
    QString m_group;
    QList<Meeting *> _meetings;
    QList<Notification *> _notifications;

    static void appendMeeting(QQmlListProperty<Meeting> *meetings,Meeting * meeting);
    static int countMeeting(QQmlListProperty<Meeting> *meetings);
    static Meeting *atMeeting(QQmlListProperty<Meeting> *meetings,int i);
    static void clearMeeting(QQmlListProperty<Meeting> *meetings);
    static void appendNotification(QQmlListProperty<Notification> *notifications,Notification *notification);
    static int countNotification(QQmlListProperty<Notification> *notifications);
    static Notification *atNotification(QQmlListProperty<Notification> *notifications,int i);
    static void clearNotification(QQmlListProperty<Notification> *notification);

};

#endif // EMPLOYEE_H