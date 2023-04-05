#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include "Atom.h"


using namespace std;


class System {
public:
    System(int NumAtoms=0);
    System(const char* filepath);
    
    void Add(Atom &atom);
    void ReadFromTXT(const char* filepath);
    void Simulate(float duration, float dt);
private:
    vector<Atom> atoms;
    
    void updateAcceleration();
    void verlet();
    double potential(double r, double eps=1.73466e-21, double sig=0.3345e-9);
    double field(double r, double eps=1.73466e-21, double sig=0.3345e-9);
};

