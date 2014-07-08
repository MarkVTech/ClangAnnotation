greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = ClangAnnotation
INCLUDEPATH += . /usr/local/include/clang-c
config += debug

LIBS += -L/usr/local/lib -lclang

# Input
HEADERS += \
    ClangUtil.h
    #MainWindow.h

#FORMS += \
    #MainWindow.ui

SOURCES += \
    ClangUtil.cpp \
    main.cpp
