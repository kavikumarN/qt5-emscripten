SOURCES += main.cpp fademessage.cpp
HEADERS += fademessage.h
RESOURCES += fademessage.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/effects/fademessage
INSTALLS += target

QT += widgets
simulator: warning(This example might not fully work on Simulator platform)
