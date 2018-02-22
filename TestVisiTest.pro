TEMPLATE     = vcapp
TARGET       = TestVisiTest
CONFIG      += warn_on qt debug_and_release windows console
HEADERS     += MonInterface.h vecteur.h CommunicationFPGA.h
SOURCES     += TestVisiTest.cpp MonInterface.cpp vecteur.cpp
INCLUDEPATH += ..\TestVisiTest
LIBS	      += VisiTest.lib CommunicationFPGA.lib
QT += widgets
