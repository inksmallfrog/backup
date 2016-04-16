#ifndef VECTORY3_H
#define VECTORY3_H

#include <cmath>

class Vector3
{
public:
    Vector3();
    Vector3(float _x, float _y, float _z);
    Vector3(const Vector3 &vectory);

    void normalize(){
        x /= length;
        y /= length;
        z /= length;
        length = 1;
    }

    Vector3& operator=(const Vector3 &vector){
        x = vector.getX();
        y = vector.getY();
        z = vector.getZ();
        length = vector.getLength();
    }

    Vector3 operator+(const Vector3 &vector){
        return Vector3(x + vector.getX(), y + vector.getY(), z + vector.getZ());
    }

    Vector3 operator*(const float scale){
        return Vector3(x * scale, y * scale, z * scale);
    }

    const float getX()const{
        return x;
    }

    const float getY()const{
        return y;
    }

    const float getZ()const{
        return z;
    }

    const float getLength()const{
        return length;
    }

protected:
    float x;
    float y;
    float z;
    float length;

private:
    void calculateLength(){
        length = sqrt(x * x + y * y + z * z);
    }
};

#endif // VECTORY3_H
