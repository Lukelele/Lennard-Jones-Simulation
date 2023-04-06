#include <iostream>
#include "System.h"


int main(int argc, const char * argv[]) {
    System system("/Users/lukelele/Documents/Scientific Computing/Year 2/Assessments/Assessment4/FinalAssessment/FinalAssessment/test.txt");

    float simulationTime = 3.46987e-13;
    float dt = simulationTime / 100;
    system.Simulate(simulationTime, dt);
}
