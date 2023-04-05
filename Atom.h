#pragma once

#include "Vector3.h"



class Atom
{
public:
    Atom();
    Atom(Vector3 Position, Vector3 Velocity, Vector3 Acceleration);
    
    void SetPosition(Vector3 inputPosition);
    Vector3 GetPosition();
    void SetVelocity(Vector3 inputVelocity);
    Vector3 GetVelocity();
    void SetAcceleration(Vector3 inputAcceleration);
    Vector3 GetAcceleration();
    void SetMass(double inputMass);
    double GetMass();
private:
    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;
    double mass;
};
