#include "render_window.h"
#include <QPainter>

RenderWindow::RenderWindow(QWidget *p) : QOpenGLWidget(p) {}

void RenderWindow::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.1f, 0.1f, 0.1f, 1.f);
}

void RenderWindow::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    QPainter painter(this);
    if (!currentImg.isNull()) {
        painter.drawImage(rect(), currentImg);
    }
}

void RenderWindow::updateFrame(const QImage &frame) {
    currentImg = frame;
    update();
}

QImage RenderWindow::currentFrame() const {
    return currentImg;
}

