############################################################
# Project file for autotest for file qfocusframe.h
############################################################

CONFIG += testcase
CONFIG += parallel_test
TARGET = tst_qfocusframe
QT += widgets testlib
SOURCES += tst_qfocusframe.cpp


DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0
