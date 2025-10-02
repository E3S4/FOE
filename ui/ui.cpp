#include "ui.h"
#include "core/import.h"
#include <QMenuBar>
#include <QDockWidget>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QToolBar>
#include <QDebug>

// -------------------- Constructor --------------------
FOEMainWindow::FOEMainWindow(QWidget *parent) : QMainWindow(parent) {
    // Initialize PlayEngine
    playEngine = new PlayEngine(this);

    // Setup UI
    setupUI();
}

// -------------------- Setup UI --------------------
void FOEMainWindow::setupUI() {
    setWindowTitle("FOE - Fusion of Effects");
    resize(1200, 800);

    // --- Project Assets Dock ---
    projAssets = new ProjectAssets(this);
    auto *dockAssets = new QDockWidget("Project Assets", this);
    dockAssets->setWidget(projAssets);
    addDockWidget(Qt::LeftDockWidgetArea, dockAssets);

    // --- Central Preview + Play Button ---
    previewWidget = new QWidget(this);
    auto *previewLayout = new QVBoxLayout(previewWidget);

    previewArea = new QLabel("Preview Window", this);
    previewArea->setAlignment(Qt::AlignCenter);
    previewArea->setStyleSheet("background:black; color:white; min-height:360px;");

    playButton = new QPushButton("▶ Play", this);

    previewLayout->addWidget(previewArea);
    previewLayout->addWidget(playButton);
    setCentralWidget(previewWidget);

    // --- Menu Bar: File → Import ---
    QMenu *fileMenu = menuBar()->addMenu("File");
    QAction *importAct = new QAction("Import...", this);
    fileMenu->addAction(importAct);

    connect(importAct, &QAction::triggered, this, [this]() {
        QString filePath = QFileDialog::getOpenFileName(this, "Import Media", "",
            "Videos (*.mp4 *.avi *.mov);;Images (*.png *.jpg *.jpeg);;Audio (*.mp3 *.wav)");
        if (!filePath.isEmpty()) {
            QString name = QFileInfo(filePath).baseName();
            if (filePath.endsWith(".mp4") || filePath.endsWith(".avi") || filePath.endsWith(".mov"))
                projAssets->addAsset(name, "Video", filePath);
            else if (filePath.endsWith(".png") || filePath.endsWith(".jpg"))
                projAssets->addAsset(name, "Image", filePath);
            else
                projAssets->addAsset(name, "Audio", filePath);
        }
    });

    // --- Asset double-click → Preview ---
    connect(projAssets, &ProjectAssets::assetDoubleClicked, this, [this](AssetItem asset) {
        if(asset.type == "Video") {
            currentClip = importVideo(asset.path);
            if(!currentClip.frames.empty()) {
                playEngine->startPreview(currentClip, [this](const QImage &frame){
                    previewArea->setPixmap(QPixmap::fromImage(frame).scaled(
                        previewArea->size(),
                        Qt::KeepAspectRatio,
                        Qt::SmoothTransformation
                    ));
                });
            }
        }
        // TODO: handle Image / Audio
    });

    // --- Play Button ---
    connect(playButton, &QPushButton::clicked, this, [this]() {
        if(!currentClip.frames.empty()) {
            playEngine->startPreview(currentClip, [this](const QImage &frame){
                previewArea->setPixmap(QPixmap::fromImage(frame).scaled(
                    previewArea->size(),
                    Qt::KeepAspectRatio,
                    Qt::SmoothTransformation
                ));
            });
        }
    });
}

