#pragma once
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QFileDialog>
#include <QSlider>
#include <QLabel>
#include <QToolBar>

#include "project_assets.h"
#include "core/play.h"
#include "fx_control.h"
#include "timeline.h"
#include "render_window.h"
#include "core/import.h"

class FOEMainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit FOEMainWindow(QWidget *parent = nullptr);
    void setupUI();
    void setupMenu();
    void setupToolbar();

private slots:
    void importVideoAction();
    void onZoomChanged(int value);
    void onPlayPause();

private:
    ProjectAssets *projectAssets;
    RenderWindow *renderWindow;
    PlayEngine *playEngine;
    FxControl *fxControl;
    Timeline *timeline;
    ImportManager *importManager;

    QToolBar *toolbar;
    QAction *playAction;
    QAction *pauseAction;
    QSlider *zoomSlider;
    QLabel *zoomLabel;
};

