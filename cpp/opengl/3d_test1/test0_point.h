#ifndef TRIANGLEWINDOW_H
#define TRIANGLEWINDOW_H

#include "openglwindow.h"
#include <QOpenGLShaderProgram>

class Test0_Point : public OpenGLWindow
{
public:
    Test0_Point();
    ~Test0_Point();

    void initialize() Q_DECL_OVERRIDE;
    void render() Q_DECL_OVERRIDE;

private:
    uint VBO;
};

#endif // TRIANGLEWINDOW_H
