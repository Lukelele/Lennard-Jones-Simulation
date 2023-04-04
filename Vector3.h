#pragma once
#include <cmath>


class Vector3
{
public:
    double x;
    double y;
    double z;
    
    
    Vector3(double inputX, double inputY, double inputZ);
    Vector3();
    
    Vector3 operator+(Vector3 otherVector);
    Vector3 operator-(Vector3 otherVector);
    Vector3 operator*(double scalar);
    Vector3 operator/(double scalar);
    double Dot(Vector3 &otherVector);
    double Magnitude();
    Vector3 Normalise();
};
