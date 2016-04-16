#include "test0_point.h"
#include "ui_trianglewindow.h"
#include <QScreen>

Test0_Point::Test0_Point() :
    VBO(0)
{
}

Test0_Point::~Test0_Point()
{
}

void Test0_Point::initialize(){

}

void Test0_Point::render(){
    GLfloat vertices[] = {
        0.0f, 2.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f
    };

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
}
