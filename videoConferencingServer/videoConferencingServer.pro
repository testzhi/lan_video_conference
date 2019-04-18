TEMPLATE = app
CONFIG += console c++11


SOURCES += \
        main.cpp \
    videoconferencingserver.cpp \
    databasebroker.cpp

HEADERS += \
    videoconferencingserver.h \
    databasebroker.h

LIBS += -lboost_system -lboost_thread -lboost_date_time -lpthread -lmysqlclient
# -lmysqlclient
QT += core
