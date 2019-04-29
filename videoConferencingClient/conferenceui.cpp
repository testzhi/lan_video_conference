#include "conferenceui.h"
#include <vector>

//Company *ConferenceUI::company() const
//{
//    return m_company;
//}

//void ConferenceUI::setCompany(Company *company)
//{
//    m_company = company;
//}

Employee *ConferenceUI::employee() const
{
    return m_employee;
}

void ConferenceUI::setEmployee(Employee *employee)
{
    m_employee = employee;
}

void ConferenceUI::getLoginInformation(QString account, QString password)
{
    m_employee->setUserID(account);
    m_employee->setUserPassword(password);
    m_videoConferencing->requestLogin(account.toStdString(),password.toStdString());
}

void ConferenceUI::getRegisterInformation(QString avator, QString name, QString password, QString company, QString department, QString group, QString phone, QString email)
{
    m_employee->setAvatar(avator);
    m_employee->setRealName(name);
    m_employee->setUserPassword(password);
    m_employee->setCompany(company);
    m_employee->setDepartment(department);
    m_employee->setGroup(group);
    m_employee->setPhone(phone);
    m_employee->setEmail(email);
    m_videoConferencing->requestRegister(name.toStdString(),password.toStdString(),email.toStdString(),"",company.toStdString(),department.toStdString(),group.toStdString(),phone.toStdString());
}

void ConferenceUI::getLaunchMeetingMessage(QString speaker, QString date, QString time, QString category, QString subject, QString scale, QString dura, QString remark, QList<QString> attendees)
{
    std::vector<std::string> atts;
    for(int i = 0;i != attendees.count();i++)
        atts.push_back(attendees[i].toStdString());
    m_videoConferencing->requestLaunchMeeting(m_employee->userID().toStdString(),m_employee->userID().toStdString(),speaker.toStdString(),date.toStdString(),time.toStdString(),category.toStdString(),subject.toStdString(),scale.toStdString(),dura.toStdString(),remark.toStdString(),atts);
}

void ConferenceUI::getReplyMeetingInvitation(QString result, QString meetingID, QString cause)
{
    m_videoConferencing->requestReplyMeetingInvitation(m_employee->userID().toStdString(),result.toStdString(),meetingID.toStdString(),cause.toStdString());
}

void ConferenceUI::getExitMessage()
{
    m_employee->loginSucceeded("Exit");
    m_videoConferencing->requestExit(m_employee->userID().toStdString());
}

void ConferenceUI::getStartMeetingMessage(QString meetingID)
{
    m_videoConferencing->requestStartMeeting(m_employee->userID().toStdString(),meetingID.toStdString());
}

void ConferenceUI::getStopMeetingMessage(QString meetingID)
{
    m_videoConferencing->requestStopMeeting(m_employee->userID().toStdString(),meetingID.toStdString());
}

void ConferenceUI::getAttendMeetingMessage(QString meetingID)
{
    m_videoConferencing->requestAttendMeeting(m_employee->userID().toStdString(),meetingID.toStdString());
}

VideoConferencingClient *ConferenceUI::getVideoConferencing() const
{
    return m_videoConferencing;
}

void ConferenceUI::setVideoConferencing(VideoConferencingClient *videoConferencing)
{
    m_videoConferencing = videoConferencing;
}

