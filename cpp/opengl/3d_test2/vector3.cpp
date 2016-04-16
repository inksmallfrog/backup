#include "vector3.h"
#include <cmath>

Vector3::Vector3() :
    x(0),
    y(0),
    z(0),
    length(0){
}

Vector3::Vector3(float _x, float _y, float _z) :
    x(_x),
    y(_y),
    z(_z){
    calculateLength();
}

Vector3::Vector3(const Vector3 &vector) :
    x(vector.getX()),
    y(vector.getY()),
    z(vector.getZ()){
    calculateLength();
}
