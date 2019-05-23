#ifndef CSENDMAIL_H
#define CSENDMAIL_H

#include <iostream>
#include <vector>
#include <string>

struct upload_status
{
    int lines_read;
};

class CSendEmail
{
public:
    CSendEmail();
    CSendEmail(std::string user, std::string passwd, std::string server);
    CSendEmail(std::string user, std::string passwd, std::string server, int port);
    void addRecipient(std::string recipient);
    void addRecipients(std::vector<std::string> recipients);
    void clearRecipients();
    void addContent(std::string date, std::string to, std::string messageID, std::string subject, std::vector<std::string> content);
    void addContent(std::string date, std::string to, std::string messageID, std::string subject, std::string content);
    static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp);
    int sendEmail();

private:
    std::string m_user;
    std::string m_passwd;
    std::string m_smtpServer;
    int m_port;
    std::vector<std::string> m_recipients;
    std::string m_mailFrom;
    std::vector<std::string> m_content;
    int m_curPos;
};

#endif // CSENDMAIL_H
