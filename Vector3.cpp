#include "Vector3.h"


Vector3::Vector3(double inputX, double inputY, double inputZ)
:x(inputX), y(inputY), z(inputZ)
{
    
}


Vector3::Vector3()
{
    
}


double Vector3::Magnitude() {
    return (sqrt(x * x + y * y + z * z));
}


Vector3 Vector3::operator+(Vector3 otherVector) {
    return Vector3(x + otherVector.x, y + otherVector.y, z + otherVector.z);
}

Vector3 Vector3::operator-(Vector3 otherVector) {
    return Vector3(x - otherVector.x, y - otherVector.y, z - otherVector.z);
}

Vector3 Vector3::operator*(double scalar){
    return Vector3(x * scalar, y * scalar, z * scalar);
}

Vector3 Vector3::operator/(double scalar) {
    return Vector3(x / scalar, y / scalar, z / scalar);
}

double Vector3::Dot(Vector3 &otherVector) {
    return x * otherVector.x + y * otherVector.y + z * otherVector.z;
}

Vector3 Vector3::Normalise() {
    double mag = Magnitude();
    return Vector3(x / mag, y / mag, z / mag);
}
