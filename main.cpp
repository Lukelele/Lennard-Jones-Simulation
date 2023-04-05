#include <iostream>
#include "System.h"


int main(int argc, const char * argv[]) {
    System system("/Users/lukelele/Documents/Scientific Computing/Year 2/Assessments/Assessment4/FinalAssessment/FinalAssessment/test.txt");

    system.Simulate(10, 0.01);
}
