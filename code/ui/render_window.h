#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QImage>

class RenderWindow : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT
public:
    explicit RenderWindow(QWidget *parent = nullptr);

    void updateFrame(const QImage &frame);
    QImage currentFrame() const;

protected:
    void initializeGL() override;
    void paintGL() override;

private:
    QImage currentImg;
};

