#include <iostream>
#include "System.h"


double field(double r, double eps=1.73466e-21, double sig=0.3345e-9)
{
    return (-24 * eps * pow(sig, 6) * (pow(r, 6) - 2 * pow(sig, 6))) / pow(r, 13);
}

int main(int argc, const char * argv[]) {
    System system("FinalAssessment/input.txt");

    float simulationTime = 3e-11;
    float dt = simulationTime / 1000;
    system.Simulate(simulationTime, dt, Vector3(1e-9, 1e-9, 1e-9));
}
