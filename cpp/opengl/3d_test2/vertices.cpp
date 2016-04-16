#include "vertices.h"
#include <QtOpenGL>


Vertices::Vertices(const Vertice *vertices, const int verticeNumber) :
    m_verticesNumber(verticeNumber),
    func(QOpenGLContext::currentContext())
{
    m_vertices = new Vertice[m_verticesNumber];
    for(int i = 0; i < verticeNumber; ++i){
        m_vertices[i] = vertices[i];
    }
    init();
}

Vertices::~Vertices(){
    delete m_vertices[];
    m_vertices = NULL;
}

void Vertices::init(){
    func.glGenBuffers(1, &VBO);
    func.glBindBuffer(GL_ARRAY_BUFFER, VBO);
    func.glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);
}

void Vertices::render(){
    func.glBindBuffer(GL_ARRAY_BUFFER, VBO);
    func.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    func.glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 12, 0);
    func.glEnableVertexAttribArray(0);
    func.glEnableVertexAttribArray(1);
    func.glDrawArrays(GL_TRIANGLES, 0, m_verticesNumber);
    func.glDisableVertexAttribArray(1);
    func.glDisableVertexAttribArray(0);
}
