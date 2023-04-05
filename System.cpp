#include "System.h"



System::System(int NumAtoms)
{
    atoms.reserve(NumAtoms);
    for (int i = 0; i < NumAtoms; i++) {
        atoms.push_back(Atom());
    }
}


System::System(const char* filepath)
{
    ReadFromTXT(filepath);
}


void System::Add(Atom &atom)
{
    atoms.push_back(atom);
}


// Reads initial condition variables of all the atoms in a system and loads in to the atom object
// TXT files are used because .csv UTF encoding strings at the start of the file which makes it harder to parse, the .txt files here use the same comma separated format as .csv
void System::ReadFromTXT(const char* filepath)
{
    //open the text file
    ifstream file;
    file.open(filepath);
    
    //check if the file is open, if not exit the function
    if (!file.is_open()) {
        cout << "file cannot be opened" << std::endl;
        return;
    }
    
    string initialConditionString;
    
    //read the entire file line by line, each line represents a single atom, and contains data for its position, velocity and acceleration
    while (getline(file, initialConditionString)) {
        string initialConditionParameterString;
        vector <double> initialConditionParametersDouble;
        vector <Vector3> initialConditionParameters;
        
        //create a stringstream for the current atom
        stringstream sstr(initialConditionString);
        
        //parse the stringstream into initialConditionParameterString, which contains the current attribute of the current atom, it does it by splitting the sstr at every comma
        while (getline(sstr, initialConditionParameterString, ',')) {
            string str = initialConditionParameterString.substr();
            initialConditionParametersDouble.push_back(stod(str));
        }
        //every 3 attributes forms either position, velocity or acceleration, the initialConditionParameters is a list of these 3 Vector3 objects
        for (int i = 0; i < 3; i++) {
            initialConditionParameters.push_back(Vector3(initialConditionParametersDouble[i*3], initialConditionParametersDouble[i*3 + 1], initialConditionParametersDouble[i*3 + 2]));
        }
        //assign the position, velocity and acceleration to the atom object
        atoms.push_back(Atom(initialConditionParameters[0], initialConditionParameters[1], initialConditionParameters[2]));
    }
    
    //close the file to free up memory
    file.close();
}




void System::Simulate(float duration, float dt)
{
    ofstream savefile;
    savefile.open("/Users/lukelele/Documents/Scientific Computing/Year 2/Assessments/Assessment4/FinalAssessment/FinalAssessment/output.csv");
    if (!savefile.is_open()) {
        cout << "save file cannot be opened" << endl;
        return;
    }
    
    
    for (int i = 0; i < atoms.size(); i++) {
        savefile << "atom" << i << "_x" << ',';
        savefile << "atom" << i << "_y" << ',';
        savefile << "atom" << i << "_z" << ',';
        savefile << "atom" << i << "_vx" << ',';
        savefile << "atom" << i << "_vy" << ',';
        savefile << "atom" << i << "_vz" << ',';
        savefile << "atom" << i << "_ax" << ',';
        savefile << "atom" << i << "_ay" << ',';
        savefile << "atom" << i << "_az";
    }
    
    savefile << endl;
    
    for (float t = 0; t < duration; t += dt) {
        for (int i = 0; i < atoms.size(); i++) {
            Vector3 currentPosition = atoms[i].GetPosition();
            Vector3 currentVelocity = atoms[i].GetVelocity();
            Vector3 currentAcceleration = atoms[i].GetAcceleration();
            atoms[i].SetVelocity(currentVelocity + currentAcceleration * (0.5 * dt));
            atoms[i].SetPosition(currentPosition + currentVelocity * dt);
            updateAcceleration();
            atoms[i].SetVelocity(atoms[i].GetVelocity() + atoms[i].GetAcceleration() * (0.5 * dt));

            savefile << to_string(atoms[i].GetPosition().x) << ',';
            savefile << to_string(atoms[i].GetPosition().y) << ',';
            savefile << to_string(atoms[i].GetPosition().z) << ',';
            savefile << to_string(atoms[i].GetVelocity().x) << ',';
            savefile << to_string(atoms[i].GetVelocity().y) << ',';
            savefile << to_string(atoms[i].GetVelocity().z) << ',';
            savefile << to_string(atoms[i].GetAcceleration().x) << ',';
            savefile << to_string(atoms[i].GetAcceleration().y) << ',';
            savefile << to_string(atoms[i].GetAcceleration().z);

        }
        savefile << endl;
    }
    
    savefile.close();
}




void System::updateAcceleration()
{
    for (int i = 0; i < atoms.size(); i++) {
        //initialise the acceleration vector to zero with each new atom
        Vector3 acc(0,0,0);

        //for each atom, loop through all other atoms in the system except for itself to calculate the acceleration
        for (int j = 0; j < atoms.size(); j++) {
            if (i != j) {
                Vector3 deltaR = atoms[j].GetPosition() - atoms[i].GetPosition();
                //deltaR.normalise() gives the direction of the force, multiplied by the magnitude of the force given by the field
                acc = acc + deltaR.Normalise() * field(deltaR.Magnitude());
            }
        }
        //update the acceleration at the end of the i loop
        atoms[i].SetAcceleration(acc / atoms[i].GetMass());
        cout << acc.x << "   " << acc.y << "   " << acc.z << endl;
    }
}



void System::verlet()
{
    
}



double System::potential(double r, double eps, double sig)
{
    return 4 * eps * (pow(sig/r, 12) - pow(sig/r, 6));
}

double System::field(double r, double eps, double sig)
{
    return -4 * eps * ((6 * pow(sig, 6) / pow(r, 7)) - (12 * pow(sig, 12) / pow(r, 13)));
}
