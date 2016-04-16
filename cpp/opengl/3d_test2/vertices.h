#ifndef VERTICES_H
#define VERTICES_H

#include "irenderable.h"
#include "vertice.h"
#include <QOpenGLFunctions>

class Vertices : public IRenderable
{
public:
    Vertices(const Vertice *vertices, const int verticeNumber);
    ~Vertices();

    void init();
    virtual void render();

protected:
    QOpenGLFunctions func;
    Vertice *m_vertices;
    int m_verticesNumber;
    uint VAO;
    uint VBO;
};

#endif // VERTICES_H
