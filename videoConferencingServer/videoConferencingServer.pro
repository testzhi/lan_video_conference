TEMPLATE = app
CONFIG += console c++11


SOURCES += \
        main.cpp \
    videoconferencingserver.cpp \
    databasebroker.cpp \
    datacontroller.cpp \
    streamingmediaforwading.cpp \
    account.cpp \
    accountbroker.cpp

HEADERS += \
    videoconferencingserver.h \
    databasebroker.h \
    datacontroller.h \
    streamingmediaforwading.h \
    account.h \
    accountbroker.h

LIBS += -lboost_system -lboost_thread -lboost_date_time -lpthread -lmysqlclient -ljrtp -ljthread
# -lmysqlclient
QT += core
