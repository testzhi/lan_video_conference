#include <iostream>
#include "videoconferencingserver.h"
#include "datacontroller.h"
#include <stdio.h>
#include <regex>
#include <boost/thread.hpp>


int main()
{
    try {
        int num = 2;
        VideoConferencingServer *server = new VideoConferencingServer();
        server->run();
        boost::thread_group group;
        for(int i = 0; i != num; ++i)
            group.create_thread(boost::bind(&VideoConferencingServer::run, server));
        group.join_all();
        delete server;
    } catch (std::exception &err) {
        std::cout << err.what() << std::endl;
    }
    return 0;
}

