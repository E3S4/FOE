#pragma once
#include <QWidget>
#include <QMenuBar>
#include <QToolBar>

class TopPanel : public QWidget {
    Q_OBJECT
public:
    TopPanel(QWidget *parent = nullptr);

private slots:
    void newProject() {}
    void openProject() {}
    void saveProject() {}

private:
    QMenuBar *m_menu;
    QToolBar *m_toolbar;
};


