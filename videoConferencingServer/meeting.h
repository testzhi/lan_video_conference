#ifndef MEETING_H
#define MEETING_H


#include <string>

class Meeting
{
public:
    Meeting();
private:
    int m_meetingID;
    std::string initiator;
    std::string initiatorName;
    std::string speaker;
    std::string speakerName;
    std::string date;
    std::string time;
    int m_duration;
    int m_scale;
    std::string m_subject;
    std::string m_remark;
    int m_catagory;
    int m_state;
    std::string m_audioSource;
    std::string m_videoSource;
};

#endif // MEETING_H
