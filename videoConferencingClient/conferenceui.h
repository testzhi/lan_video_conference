#ifndef CONFERENCEUI_H
#define CONFERENCEUI_H

#include <QObject>

#include "employee.h"
#include "videoconferencingclient.h"

class ConferenceUI:public QObject
{
    Q_OBJECT
//    Q_PROPERTY(Company *company READ company WRITE setCompany NOTIFY companyChanged)
    Q_PROPERTY(Employee *employee READ employee WRITE setEmployee NOTIFY employeeChanged)
signals:
//    void companyChanged();
    void employeeChanged();
public:
    ConferenceUI(QObject *parent = 0):QObject(parent){}
//    Company *company() const;
//    void setCompany(Company *company);
    Employee *employee() const;
    Q_INVOKABLE void setEmployee(Employee *employee);

    Q_INVOKABLE void getLoginInformation(QString account,QString password);
    Q_INVOKABLE void getRegisterInformation(QString avator,QString name,QString password,QString company,QString department,QString group,QString phone,QString email);

    VideoConferencingClient *getVideoConferencing() const;
    void setVideoConferencing(VideoConferencingClient *videoConferencing);

private:
//    Company *m_company;
    Employee *m_employee;
    VideoConferencingClient *m_videoConferencing;
};

#endif // CONFERENCEUI_H
