HEADERS     = slidersgroup.h \
              window.h
SOURCES     = main.cpp \
              slidersgroup.cpp \
              window.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/sliders
INSTALLS += target

QT += widgets

simulator: warning(This example might not fully work on Simulator platform)
