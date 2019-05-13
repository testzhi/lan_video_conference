TEMPLATE = app
CONFIG += console c++11


SOURCES += \
        main.cpp \
    videoconferencingserver.cpp \
    databasebroker.cpp \
    datacontroller.cpp \
    streamingmediaforwading.cpp \
    account.cpp \
    accountbroker.cpp \
    employee.cpp \
    employeebroker.cpp \
    group.cpp \
    department.cpp \
    company.cpp \
    attendee.cpp \
    meeting.cpp

HEADERS += \
    videoconferencingserver.h \
    databasebroker.h \
    datacontroller.h \
    streamingmediaforwading.h \
    account.h \
    accountbroker.h \
    employee.h \
    employeebroker.h \
    group.h \
    department.h \
    company.h \
    attendee.h \
    meeting.h

LIBS += -lboost_system -lboost_thread -lboost_date_time -lpthread -lmysqlclient -ljrtp -ljthread
# -lmysqlclient
QT += core
