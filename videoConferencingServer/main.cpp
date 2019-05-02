#include <iostream>
#include "videoconferencingserver.h"
#include "datacontroller.h"
#include <streamingmediaforwading.h>
#include <stdio.h>
#include <regex>
#include <boost/thread.hpp>
#include <thread>

std::vector<std::string> destIPs;
int main()
{
    try {
        VideoConferencingServer *server = new VideoConferencingServer();
        server->run();
        delete server;
    } catch (std::exception &err) {
        std::cout << err.what() << std::endl;
    }
    return 0;
}

