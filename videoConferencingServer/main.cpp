#include <iostream>
#include "videoconferencingserver.h"
#include "databasebroker.h"

int main()
{
    VideoConferencingServer *server = new VideoConferencingServer();
    server->run();

    DataBaseBroker db;
    char *serv = "localhost";         char *username = "chinwag";
    char *password= "chinwag123";       char *database = "chinwagServer";
    int port = 3306;
    db.connectMySQL(serv, username, password, database, port);
    db.createTables();

    return 0;
}
