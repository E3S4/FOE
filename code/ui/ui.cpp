#include "ui.h"
#include <QMenu>
#include <QAction>
#include <QFileInfo>
#include <QIcon>

FOEMainWindow::FOEMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
}

void FOEMainWindow::setupUI() {
    QWidget *central = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);
    setCentralWidget(central);

    projectAssets = new ProjectAssets(this);
    renderWindow = new RenderWindow(this);
    fxControl = new FxControl(this);
    playEngine = new PlayEngine(this);
    timeline = new Timeline(this);
    importManager = new ImportManager(this);

    // ---- Layouts ----
    QHBoxLayout *upperLayout = new QHBoxLayout;
    upperLayout->addWidget(projectAssets, 1);
    upperLayout->addWidget(renderWindow, 3);
    upperLayout->addWidget(fxControl, 2);

    mainLayout->addLayout(upperLayout, 4);
    mainLayout->addWidget(timeline, 1);

    setupMenu();
    setupToolbar();

    // === Connections ===

    // import → timeline
    connect(importManager, &ImportManager::clipsLoaded, timeline, &Timeline::onImportClipsLoaded);

    // file import trigger
    connect(projectAssets, &ProjectAssets::importRequested, this, &FOEMainWindow::importVideoAction);

    // timeline scrub → playback
    connect(timeline, &Timeline::playheadMoved, this, [this](int frame) {
        playEngine->seekToFrame(frame);
    });

    // playback → render preview
    connect(playEngine, &PlayEngine::frameDisplayed, renderWindow, &RenderWindow::updateFrame);

    resize(1280, 850);
    setWindowTitle("FrameOne Editor 🎬");
}

// === Menu Setup ===
void FOEMainWindow::setupMenu() {
    QMenu *fileMenu = menuBar()->addMenu("File");
    QAction *importAction = fileMenu->addAction("Import Video");
    QAction *exitAction = fileMenu->addAction("Exit");

    connect(importAction, &QAction::triggered, this, &FOEMainWindow::importVideoAction);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
}

// === Toolbar Setup ===
void FOEMainWindow::setupToolbar() {
    toolbar = addToolBar("Playback");
    toolbar->setMovable(false);

    playAction = toolbar->addAction(QIcon::fromTheme("media-playback-start"), "Play", this, &FOEMainWindow::onPlayPause);
    pauseAction = toolbar->addAction(QIcon::fromTheme("media-playback-pause"), "Pause", this, &FOEMainWindow::onPlayPause);

    toolbar->addSeparator();

    zoomLabel = new QLabel("Zoom: ");
    zoomSlider = new QSlider(Qt::Horizontal);
    zoomSlider->setRange(1, 500); // represents 0.1x to 5.0x
    zoomSlider->setValue(100);
    zoomSlider->setFixedWidth(150);

    QWidget *zoomWidget = new QWidget;
    QHBoxLayout *zoomLayout = new QHBoxLayout(zoomWidget);
    zoomLayout->setContentsMargins(0, 0, 0, 0);
    zoomLayout->addWidget(zoomLabel);
    zoomLayout->addWidget(zoomSlider);

    toolbar->addWidget(zoomWidget);

    connect(zoomSlider, &QSlider::valueChanged, this, &FOEMainWindow::onZoomChanged);
}

// === Import Functionality ===
void FOEMainWindow::importVideoAction() {
    QString filePath = QFileDialog::getOpenFileName(this, "Import Video", "", "Video Files (*.mp4 *.avi *.mov)");
    if (filePath.isEmpty()) return;

    VideoClip clip = importVideo(filePath);
    playEngine->loadClip(clip);

    QString name = QFileInfo(filePath).baseName();
    ClipItem item { name, 0, clip.totalFrames, QColor(0, 200, 255) };
    timeline->addClip(item.name, item.startFrame, item.length, item.color);
    projectAssets->addAsset(name, filePath, item.length);

    QList<ImportedClip> importedList;
    importedList.append({name, 0, clip.totalFrames});
    emit importManager->clipsLoaded(importedList); // trigger timeline sync
}

// === Playback ===
void FOEMainWindow::onPlayPause() {
    static bool playing = false;
    playing = !playing;
    if (playing) {
        playEngine->play();
    } else {
        playEngine->pause();
    }
}

// === Zoom Control ===
void FOEMainWindow::onZoomChanged(int value) {
    float zoom = value / 100.0f;
    timeline->setZoom(zoom);
}

