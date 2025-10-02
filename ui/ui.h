#pragma once
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include "project_assets.h"
#include "core/framebuffer.h"
#include "core/play.h"
class FOEMainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit FOEMainWindow(QWidget *parent = nullptr);
    void setupUI();
private:
    ProjectAssets *projAssets;
    QWidget *previewWidget;
    QLabel *previewArea;
    QPushButton *playButton;
    VideoClip currentClip;
    PlayEngine *playEngine;
};

