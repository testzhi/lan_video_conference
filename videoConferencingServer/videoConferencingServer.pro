TEMPLATE = app
CONFIG += console c++11


SOURCES += \
        main.cpp \
    videoconferencingserver.cpp \
    databasebroker.cpp \
    datacontroller.cpp \
    streamingmediaforwading.cpp \
    csendmail.cpp

HEADERS += \
    videoconferencingserver.h \
    databasebroker.h \
    datacontroller.h \
    streamingmediaforwading.h \
    csendmail.h

LIBS += -lboost_system -lboost_thread -lboost_date_time -lpthread -lmysqlclient -ljrtp -ljthread -lcurl
# -lmysqlclient
QT += core
