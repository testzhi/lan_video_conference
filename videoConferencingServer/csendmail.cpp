#include "csendmail.h"
#include <curl/curl.h>
#include <cstring>

using std::cerr;
using std::string;
using std::vector;
using std::endl;

CSendEmail::CSendEmail()
{
    m_curPos = 0;
    m_port = -1;
    m_user.clear();
    m_passwd.clear();
    m_smtpServer.clear();
    m_mailFrom.clear();
    m_recipients.clear();
    m_content.clear();
}

CSendEmail::CSendEmail(string user, string passwd, string server)
{
    m_curPos = 0;
    m_port = -1;
    m_user = user;
    m_passwd = passwd;
    m_smtpServer = server;
    m_mailFrom = "<" + user + ">";
    m_recipients.clear();
    m_content.clear();
}

CSendEmail::CSendEmail(string user, string passwd, string server, int port)
{
    m_curPos = 0;
    m_port = port;
    m_user = user;
    m_passwd = passwd;
    m_smtpServer = server;
    m_mailFrom = "<" + user + ">";
    m_recipients.clear();
    m_content.clear();
}

void CSendEmail::addRecipient(string recipient)
{
    cerr << "添加新的目的邮件地址" << recipient << endl;
    //    m_recipients.push_back("<"+recipient+">");
    m_recipients.push_back(recipient);
}

void CSendEmail::clearRecipients()
{
    cerr << "清除目的邮件地址" << endl;
    m_recipients.clear();
}

void CSendEmail::addContent(std::string date, std::string to, std::string messageID, std::string subject, std::vector<std::string> content)
{
    string tmp;
    tmp.clear();
    tmp = "Date: Mon, 29 Nov 2010 21:54:29 +1100\r\n";
    m_content.push_back(tmp);

    tmp.clear();
    tmp = "From: <" +m_user +"> (VB视频会议服务器代理邮箱)\r\n";
    m_content.push_back(tmp);

    tmp.clear();
    tmp = "To: "+to+"\r\n";
    m_content.push_back(tmp);

    tmp.clear();
    tmp = "Message-ID: <dcd7cb36-11db-487a-9f3a-e652a9458efd@rfcpedant.example.org>\r\n";
    m_content.push_back(tmp);

    tmp.clear();
    tmp = "Subject: "+subject+"\r\n";
    m_content.push_back(tmp);

    m_content.push_back("\r\n");

    for(auto l:content)
    {
        tmp.clear();
        tmp = l+"\r\n";
        m_content.push_back(tmp);
    }

}

void CSendEmail::addContent(std::string date, std::string to, std::string messageID, std::string subject, std::string content)
{
    string tmp;
    tmp.clear();
    tmp = "Date: Mon, 29 Nov 2010 21:54:29 +1100\r\n";
    m_content.push_back(tmp);

    tmp.clear();
    tmp = "From: <" +m_user +"> (VB视频会议服务器代理邮箱)\r\n";
    m_content.push_back(tmp);

    tmp.clear();
    tmp = "To: "+to+"\r\n";
    m_content.push_back(tmp);

    tmp.clear();
    tmp = "Message-ID: <dcd7cb36-11db-487a-9f3a-e652a9458efd@rfcpedant.example.org>\r\n";
    m_content.push_back(tmp);

    tmp.clear();
    tmp = "Subject: "+subject+"\r\n";
    m_content.push_back(tmp);

    m_content.push_back("\r\n");

    tmp.clear();
    tmp = content+"\r\n";
    m_content.push_back(tmp);

}

size_t CSendEmail::payload_source(void *ptr, size_t size, size_t nmemb, void *userp)
{
    CSendEmail * pSm = (CSendEmail *)userp;

    if(size*nmemb < 1)
        return 0;
    if(pSm->m_curPos < pSm->m_content.size())
    {
        size_t len;
        len = pSm->m_content[pSm->m_curPos].length();

        memcpy(ptr, pSm->m_content[pSm->m_curPos].c_str(), pSm->m_content[pSm->m_curPos].length());
        pSm->m_curPos++; /* advance pointer */
        return len;
    }
    return 0;
}

int CSendEmail::sendEmail()
{
    CURL *curl;
    CURLcode res = CURLE_OK;
    struct curl_slist *recipients = nullptr;
    struct upload_status upload_ctx;
    upload_ctx.lines_read = 0;

    curl = curl_easy_init();
    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_USERNAME, m_user.c_str());
        curl_easy_setopt(curl, CURLOPT_PASSWORD, m_passwd.c_str());
        curl_easy_setopt(curl, CURLOPT_URL, m_smtpServer.c_str());

//            curl_easy_setopt(curl, CURLOPT_USE_SSL, (long) CURLUSESSL_ALL);
#ifdef SKIP_PEER_VERIFICATION
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif
#ifdef SKIP_HOSTNAME_VERIFICATION
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif
//        curl_easy_setopt(curl, CURLOPT_SSLVERSION, 0L);
//        curl_easy_setopt(curl, CURLOPT_SSL_SESSIONID_CACHE, 0L);
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, m_mailFrom.c_str());

        for(auto &re : m_recipients)
        {
            string email = "<" + re +">";
            recipients = curl_slist_append(recipients, email.c_str());
        }
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
        curl_easy_setopt(curl, CURLOPT_READDATA, this);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        /* Send the message */
        res = curl_easy_perform(curl);

        /* Check for errors */
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        /* Free the list of recipients */
        curl_slist_free_all(recipients);

        /* Always cleanup */
        curl_easy_cleanup(curl);
    }
    return (int)res;
}

void CSendEmail::addRecipients(vector<string> recipients)
{
    for(auto &i : recipients)
    {
        addRecipient(i);
    }
}
