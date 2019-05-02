TEMPLATE = app
CONFIG += console c++11


SOURCES += \
        main.cpp \
    videoconferencingserver.cpp \
    databasebroker.cpp \
    datacontroller.cpp \
    streamingmediaforwading.cpp

HEADERS += \
    videoconferencingserver.h \
    databasebroker.h \
    datacontroller.h \
    streamingmediaforwading.h

LIBS += -lboost_system -lboost_thread -lboost_date_time -lpthread -lmysqlclient -ljrtp -ljthread
# -lmysqlclient
QT += core
