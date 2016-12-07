# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Debug/GNU-Linux
TARGET = CSCI446_Project4_ReinforcementLearning
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui widgets
SOURCES += agent.cpp engine.cpp main.cpp qt_world.cpp reasoning_agent.cpp typedef.cpp world_gen.cpp
HEADERS += agent.h engine.h main.h qt_world.h reasoning_agent.h typedef.h world_gen.h
FORMS +=
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/GNU-Linux
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += 
LIBS += 
