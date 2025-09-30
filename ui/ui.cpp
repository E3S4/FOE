#include <QApplication>
#include <QMainWindow>
#include <QDockWidget>
#include "top_panel.h"
#include "effects_panel.h"
#include "fx_control.h"
#include "timeline.h"
#include "render_window.h"
#include "project_materials.h"

int runFOE(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QMainWindow win;
    win.setWindowTitle("FOE – Fusion Of Effects");
    win.resize(1600, 900);

    // Menu/toolbar
    win.setMenuWidget(new TopPanel());

    // Dockable panels
    auto dockEffects  = new QDockWidget("Effects");
    dockEffects->setWidget(new EffectsPanel());
    win.addDockWidget(Qt::LeftDockWidgetArea, dockEffects);

    auto dockFxCtrl   = new QDockWidget("Effect Controls");
    dockFxCtrl->setWidget(new FxControl());
    win.addDockWidget(Qt::RightDockWidgetArea, dockFxCtrl);

    auto dockAssets   = new QDockWidget("Project Materials");
    dockAssets->setWidget(new ProjectMaterials());
    win.addDockWidget(Qt::LeftDockWidgetArea, dockAssets);

    auto dockTimeline = new QDockWidget("Timeline");
    dockTimeline->setWidget(new Timeline());
    win.addDockWidget(Qt::BottomDockWidgetArea, dockTimeline);

    // Central preview window
    win.setCentralWidget(new RenderWindow());

    // Style: dark mode with neon accent
    qApp->setStyleSheet(
        "QMainWindow { background:#202020; } "
        "QDockWidget { background:#2b2b2b; color:#ddd; } "
        "QMenuBar { background:#1e1e1e; color:#fff; } "
        "QToolBar { background:#1e1e1e; } "
    );

    win.show();
    return app.exec();
}

