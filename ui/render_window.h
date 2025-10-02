#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class RenderWindow : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT
public:
    RenderWindow(QWidget *parent=nullptr);

protected:
    void initializeGL() override;
    void paintGL() override;
};

