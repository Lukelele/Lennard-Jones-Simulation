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
    void Simulate();
private:
    float dt = 0.01;
    vector<Atom> atoms;
    
    void updateAcceleration();
    void verlet();
    double potential(double r, double eps=1.73466e-21, double sig=0.03345e-9);
    double field(double r, double eps=1.73466e-21, double sig=0.03345e-9);
};

