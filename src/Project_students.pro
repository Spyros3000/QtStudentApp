#-------------------------------------------------
#
# Project created by QtCreator 2018-05-20T14:11:37
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Project_students
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    database.cpp \
    student.cpp \
    lesson.cpp \
    enroll.cpp

HEADERS  += mainwindow.h \
    database.h \
    student.h \
    lesson.h \
    enroll.h

FORMS    += mainwindow.ui

RESOURCES +=
