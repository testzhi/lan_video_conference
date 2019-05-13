#ifndef DATACONTROLLER_H
#define DATACONTROLLER_H

#include "databasebroker.h"
#include <iostream>

class DataController
{
public:
    DataController(){}
    ~DataController(){}


//    void jsonStrMeetingsDetail(std::string emalid, std::string &jsonstr, unsigned long long &res);
    void jsonStrLaunchMeetingResult(unsigned long long meetingid, std::string &jsonstr);
    void jsonStartMeeting(std::string meetingID, std::string &jsonStr);
    void jsonStopMeeting(std::string meetingID, std::string &jsonStr);
    void jsonNewMeetingAttendeesList(std::string meetingID, std::string &jsonstr);
    void jsonStrNewAttendeeDetail(std::string emailid, std::string meetingID, std::string &jsonstr);
    void jsonExitMeeting(std::string meetingID, std::string userID, std::string &jsonstr);

    //online
    void jsonStrInvitationAddDetail(std::string meetingid, std::string &jsonstr , unsigned long long &res);
    void jsonStrMeetingAddDetail(std::string meetingid, std::string &jsonstr, int &res);
    DataBaseBroker getDb() const;

private:
    DataBaseBroker db;
};

#endif // DATACONTROLLER_H
