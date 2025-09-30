#pragma once
#include <QMainWindow>
#include <QDockWidget>
#include <QTreeWidget>
#include <QListWidget>
#include <QTableWidget>
#include <QSlider>
#include <QLabel>
#include <QGraphicsView>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QSplitter>

class FOEMainWindow : public QMainWindow {
    Q_OBJECT
public:
    FOEMainWindow(QWidget *parent = nullptr);

private:
    // Core preview
    QGraphicsView *previewView;

    // Panels
    QTreeWidget   *projectTree;
    QListWidget   *effectsList;
    QTableWidget  *propertiesTable;
    QSlider       *timelineSlider;
    QListWidget   *audioTracks;

    // Docks
    QDockWidget *projectDock;
    QDockWidget *effectsDock;
    QDockWidget *propertiesDock;
    QDockWidget *timelineDock;
    QDockWidget *audioDock;

    void setupDarkTheme();
    void setupUI();
    void setupMenu();
    void setupToolBar();
    void setupStatusBar();
};

