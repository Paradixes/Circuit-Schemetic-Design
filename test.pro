QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

QT += opengl
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CircuitDesign/CircuitMainWindow.cpp \
    CircuitDesign/CircuitWidget.cpp \
    CircuitDesign/Compnent.cpp \
    CircuitDesign/Wire.cpp \
    CreateComp/CompMainWindow.cpp \
    CreateComp/PaintWidget.cpp \
    CreateComp/Shape/Ellipse.cpp \
    CreateComp/Shape/Line.cpp \
    CreateComp/Shape/Pin.cpp \
    CreateComp/Shape/Rect.cpp \
    CreateComp/Shape/SemiCircle.cpp \
    CreateComp/Shape/Shape.cpp \
    CreateComp/Shape/Text.cpp \
    main.cpp \
    welcomemenu.cpp

TRANSLATIONS += \
    test_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    CircuitDesign/CircuitMainWindow.h \
    CircuitDesign/CircuitWidget.h \
    CircuitDesign/Component.h \
    CircuitDesign/Wire.h \
    CreateComp/CompMainWindow.h \
    CreateComp/PaintWidget.h \
    CreateComp/Shape/Ellipse.h \
    CreateComp/Shape/Line.h \
    CreateComp/Shape/Pin.h \
    CreateComp/Shape/Rect.h \
    CreateComp/Shape/SemiCircle.h \
    CreateComp/Shape/Shape.h \
    CreateComp/Shape/Text.h \
    welcomemenu.h

RESOURCES +=

FORMS += \
    welcomemenu.ui

DISTFILES += \
    CreateComp/Lib/default.txt \
    CreateComp/default.txt
