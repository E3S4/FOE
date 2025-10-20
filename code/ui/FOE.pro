QT       += core gui widgets opengl
CONFIG   += c++17 console
CONFIG   -= app_bundle
TARGET = FOE
TEMPLATE = app
SOURCES += \
    main.cpp \
    ui.cpp \
    render_window.cpp \
    timeline.cpp \
    fx_control.cpp \
    effects_panel.cpp \
    top_panel.cpp \
    project_assets.cpp \
    core/add_fx.cpp \
    core/import.cpp \
    core/play.cpp \
    core/render.cpp
HEADERS += \
    ui.h \
    render_window.h \
    timeline.h \
    fx_control.h \
    effects_panel.h \
    top_panel.h \
    project_assets.h \
    core/add_fx.h \
    core/import.h \
    core/play.h \
    core/render.h \
    core/framebuffer.h
RESOURCES += qmake_qmake_immediate.qrc
INCLUDEPATH += /usr/include/opencv4
LIBS += -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio
INCLUDEPATH += /usr/include
LIBS += -lavformat -lavcodec -lavutil -lswscale
unix {
    LIBS += -lpthread
}
DISTFILES += qss
QMAKE_CXXFLAGS += -Wno-overloaded-virtual

