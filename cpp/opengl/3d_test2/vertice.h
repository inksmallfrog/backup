#ifndef VERTICES_H
#define VERTICES_H

#include "vector3.h"

class Vertice
{
public:
    Vertice();
    Vertice(const Vector3 &position, const Vector3 &color);
    const Vertice& operator=(const Vertice &vertice);

    const Vector3& getPosition()const{
        return m_position;
    }

    const Vector3& getColor()const{
        return m_color;
    }

protected:
    Vector3 m_position;
    Vector3 m_color;
};

#endif // VERTICES_H
