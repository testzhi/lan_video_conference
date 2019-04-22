TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH +=  ./usr/local/include

LIBS += -L./usr/local/lib/ -lavcodec -lavdevice -lavfilter \
-lavformat -lavutil -lswresample -lswscale

LIBS += -L./usr/local/lib/ -lSDL2

LIBS += -L./usr/local/lib -ljthread -ljrtp

SOURCES += \
        main.cpp \
    crtpsender.cpp

HEADERS += \
    crtpsender.h
