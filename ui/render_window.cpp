#include "render_window.h"
RenderWindow::RenderWindow(QWidget *p): QOpenGLWidget(p){}
void RenderWindow::initializeGL(){
    initializeOpenGLFunctions();
    glClearColor(0.05f,0.05f,0.05f,1.f);
}
void RenderWindow::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);
}
