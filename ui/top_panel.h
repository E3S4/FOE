#pragma once
#include <QMenuBar>
#include <QToolBar>

class TopPanel : public QWidget {
    Q_OBJECT
public:
    explicit TopPanel(QWidget *parent=nullptr);
    QMenuBar* menu() const { return m_menu; }
    QToolBar* toolbar() const { return m_toolbar; }

signals:
    void newProject();
    void openProject();
    void saveProject();

private:
    QMenuBar *m_menu;
    QToolBar *m_toolbar;
};

