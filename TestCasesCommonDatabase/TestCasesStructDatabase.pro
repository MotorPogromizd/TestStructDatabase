QT += testlib sql
QT -= gui

CONFIG += c++1z qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \ 
    main.cpp \
    tst_database.cpp \
    tst_databasedetail.cpp \
    tst_benchdatabase.cpp \
    tst_testmultitabledatabase.cpp

INCLUDEPATH += ../CommonDatabaseProject

HEADERS += \
    tst_database.h \
    tst_databasedetail.h \
    tst_benchdatabase.h \
    tst_testmultitabledatabase.h
