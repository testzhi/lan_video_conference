#ifndef MEETING_H
#define MEETING_H


#include <string>
#include <map>
class Attendee;
class Meeting
{
public:
    Meeting();
    Meeting(int id, std::string assistant, std::string speaker, std::string date, std::string time, int catagory, std::string subject, int scale, int preDuration, int state, std::string remark)
        :m_meetingID(id), m_assistant(assistant), m_speaker(speaker), m_date(date), m_time(time), m_catagory(catagory), m_subject(subject), m_scale(scale), m_preDuration(preDuration), m_state(state), m_remark(remark)
    {}
    void addAttendee(Attendee *a);
    int meetingID() const;

    int state() const;
    void setState(int state);
    std::string assistant() const;
    std::string assistantName() const;
    std::string speaker() const;
    std::string speakerName() const;
    std::string date() const;
    std::string time() const;
    int catagory() const;
    std::string subject() const;
    int scale() const;
    int preDuration() const;
    std::string remark() const;

    void setAssistantName(const std::string &assistantName);

    void setSpeakerName(const std::string &speakerName);

private:
    int m_meetingID;
    std::string m_initiator;
    std::string m_initiatorName;
    std::string m_assistant;
    std::string m_assistantName;
    std::string m_speaker;
    std::string m_speakerName;
    std::string m_date;
    std::string m_time;
    int m_catagory;
    std::string m_subject;
    int m_scale;
    int m_preDuration;
    int m_state;
    std::string m_remark;

    std::string m_audioSource;
    std::string m_videoSource;
    std::map<std::string, Attendee*> _attendees;
};

#endif // MEETING_H
