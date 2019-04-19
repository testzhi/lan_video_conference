#include <iostream>
#include "videoconferencingserver.h"
#include "databasebroker.h"
#include <stdio.h>
int main()
{
        VideoConferencingServer *server = new VideoConferencingServer();
        server->run();

//    DataBaseBroker db;
//    db.connectMySQL("localhost", "VideoConferencingServer", "", "VideoConferencingDB", 3306);
//    db.createTables();

//    db.insertIntoTableEmployees("563181354", "1717", "Liana", "563181354@qq.com", "analysis", "AI", "google");
//    db.insertIntoTableEmployees("599599599", "5995", "lzy", "599@qq.com", "AVATARlzy", "analysis", "compute", "google", "18982777901");
//    db.insertIntoTableEmployees("zjm", "5995", "zjm", "zjm@qq.com", "AVATARzjm", "analysis2", "compute", "google", "18982777901");
//    db.insertIntoTableEmployees("777777777", "7777", "Liang", "777@qq.com", "analysis", "compute", "baidu","11111111111");
//    db.insertIntoTableEmployees("222222222", "222", "luoooooo", "222@qq.com", "gro", "test", "baidu");


    return 0;
}
