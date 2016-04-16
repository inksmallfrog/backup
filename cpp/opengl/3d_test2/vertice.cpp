#include "vertice.h"

Vertice::Vertice() :
    m_position(),
    m_color(){
}

Vertice::Vertice(const Vector3 &position, const Vector3 &color) :
    m_position(position),
    m_color(color){
}

const Vertice& operator=(const Vertice &vertice){
    m_position = vertice.getPosition();
    m_color = vertice.getColor();
}
