#include <iostream>
#include "videoconferencingserver.h"
#include "datacontroller.h"
#include <stdio.h>
#include <regex>
int main()
{
    VideoConferencingServer *server = new VideoConferencingServer();
    server->run();

//    string email_address;
//    string user_name, domain_name;

//    std::regex pattern("([0-9A-Za-z\\-_\\.]+)@([0-9A-Za-z]+\\.[0-9A-Za-z]{1,2,3,4,5,6,7,8,9}(\\.[0-9A-Za-z]{1,2,3,4,5,6,7,8,9})?)");



//    // 输入文件结尾符（Windows用Ctrl+Z，UNIX用Ctrl+D）结束循环
//    while ( std::cin >> email_address )
//    {
//        if ( regex_match( email_address, pattern ) )
//        {
//            std::cout << "您输入的电子邮件地址合法" << std::endl;

//            // 截取第一组
//            user_name = regex_replace( email_address, pattern, string("$1") );

//            // 截取第二组
//            domain_name = regex_replace( email_address, pattern, string("$2") );

//            std::cout << "用户名：" << user_name << std::endl;
//            std::cout << "域名：" << domain_name << std::endl;
//        }
//        else
//        {
//            std::cout << "您输入的电子邮件地址不合法" << std::endl << std::endl;
//        }
//    }
    return 0;
}
