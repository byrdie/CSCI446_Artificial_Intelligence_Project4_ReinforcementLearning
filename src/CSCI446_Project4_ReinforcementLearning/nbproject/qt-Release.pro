# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Release/GNU-Linux
TARGET = CSCI446_Project4_ReinforcementLearning
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += release 
PKGCONFIG +=
QT = core gui widgets
SOURCES += QLearn.cpp agent.cpp engine.cpp main.cpp qt_world.cpp rand_agent.cpp typedef.cpp value_it.cpp world_gen.cpp
HEADERS += QLearn.h agent.h engine.h main.h qt_world.h rand_agent.h typedef.h value_it.h world_gen.h
FORMS +=
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Release/GNU-Linux
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = c++
DEFINES += 
INCLUDEPATH += 
LIBS += 
