#include "Atom.h"


Atom::Atom()
:position(Vector3(0,0,0)), velocity(Vector3(0,0,0)), acceleration(Vector3(0,0,0)), mass(6.6335209e-26)
{
    
}


Atom::Atom(Vector3 Position, Vector3 Velocity, Vector3 Acceleration)
:position(Position), velocity(Velocity), acceleration(Acceleration), mass(6.6335209e-26)
{
    
}


void Atom::SetPosition(Vector3 inputPosition)
{
    position = inputPosition;
}

Vector3 Atom::GetPosition()
{
    return position;
}

void Atom::SetVelocity(Vector3 inputVelocity)
{
    velocity = inputVelocity;
}

Vector3 Atom::GetVelocity()
{
    return velocity;
}

void Atom::SetAcceleration(Vector3 inputAcceleration)
{
    acceleration = inputAcceleration;
}

Vector3 Atom::GetAcceleration()
{
    return acceleration;
}

void Atom::SetMass(double inputMass)
{
    mass = inputMass;
}

double Atom::GetMass()
{
    return mass;
}
