#include "top_panel.h"
#include <QVBoxLayout>
#include <QApplication>
#include <QAction>

TopPanel::TopPanel(QWidget *parent) : QWidget(parent) {
    m_menu = new QMenuBar;
    auto *file = m_menu->addMenu("&File");
    file->addAction("New", this, &TopPanel::newProject);
    file->addAction("Open", this, &TopPanel::openProject);
    file->addAction("Save", this, &TopPanel::saveProject);
    file->addSeparator();
    file->addAction("Exit", []{ qApp->quit(); });

    m_toolbar = new QToolBar;
    m_toolbar->addAction("New", this, &TopPanel::newProject);
    m_toolbar->addAction("Open", this, &TopPanel::openProject);
    m_toolbar->addAction("Save", this, &TopPanel::saveProject);

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(m_menu);
    layout->addWidget(m_toolbar);
}


