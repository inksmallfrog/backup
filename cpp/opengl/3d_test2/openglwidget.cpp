#include "openglwidget.h"
#include <qopengl.h>

OpenGLWidget::OpenGLWidget(QWidget *parent) :
    QOpenGLWidget(parent)
{

}

OpenGLWidget::~OpenGLWidget(){

}

bool OpenGLWidget::init(){

}

void OpenGLWidget::render(){

}

void OpenGLWidget::clear(){

}

void OpenGLWidget::initializeGL(){

}

void OpenGLWidget::paintGL(){

}

void OpenGLWidget::resizeGL(int w, int h){
    glViewport(0, 0, w, h);
}

void OpenGLWidget::resizeEvent(QResizeEvent *event){

}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event){

}

void OpenGLWidget::keyPressEvent(QKeyEvent *event){

}
