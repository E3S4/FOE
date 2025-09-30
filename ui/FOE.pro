QT += widgets opengl
CONFIG += c++17
TEMPLATE = app
TARGET = FOE

SOURCES += \
    main.cpp ui.cpp \
    top_panel.cpp effects_panel.cpp fx_control.cpp \
    timeline.cpp render_window.cpp project_materials.cpp

HEADERS += \
    top_panel.h effects_panel.h fx_control.h \
    timeline.h render_window.h project_materials.h

RESOURCES += qss/darktheme.qss

