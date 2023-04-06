#include <iostream>
#include "System.h"


double field(double r, double eps=1.73466e-21, double sig=0.3345e-9)
{
    return (-24 * eps * pow(sig, 6) * (pow(r, 6) - 2 * pow(sig, 6))) / pow(r, 13);
}

int main(int argc, const char * argv[]) {
    System system("/Users/lukelele/Documents/Scientific Computing/Year 2/Assessments/Assessment4/FinalAssessment/FinalAssessment/test.txt");

    float simulationTime = 8e-13;
    float dt = simulationTime / 200;
    system.Simulate(simulationTime, dt);
}
