TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        gra.cpp \
        gracz.cpp \
        main.cpp \
        menutlo.cpp \
        owoc.cpp \
        particle.cpp \
        plansza.cpp \
        silnik.cpp \
        spadanie.cpp \
        specjalne.cpp
INCLUDEPATH += "C:/SFML-2.5.1/include"


LIBS += -L"C:/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

HEADERS += \
    MenuTlo.h \
    gra.h \
    gracz.h \
    owoc.h \
    particle.h \
    plansza.h \
    silnik.h \
    spadanie.h \
    specjalne.h
