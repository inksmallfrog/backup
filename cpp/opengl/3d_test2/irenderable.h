#ifndef IRENDERABLE_H
#define IRENDERABLE_H

#include <QMatrix>

class IRenderable
{
public:
    IRenderable();

    virtual void render() = 0;
    void setWorldMatrix(QMatrix4x4 worldMatrix){
        m_worldMatrix = worldMatrix;
    }

protected:
    QMatrix4x4 m_worldMatrix;
};

#endif // IRENDERABLE_H
