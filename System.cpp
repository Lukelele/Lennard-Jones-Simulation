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




void System::Simulate(float duration, float dt, Vector3 simulationBox)
{
    //Opening a file for output data
    ofstream savefile;
    //stringstream to combine file path with the simulation metadata
    stringstream oss;
    oss << "/Users/lukelele/Documents/Scientific Computing/Year 2/Assessments/Assessment4/FinalAssessment/FinalAssessment/Output/" << atoms.size() << '_' << simulationBox.x << ".csv";
    savefile.open(oss.str().c_str());

    if (!savefile.is_open()) {
        cout << "save file cannot be opened" << endl;
        return;
    }
    
    createSimulationHeader(savefile);
    
    for (float t = 0; t < duration; t += dt) {
        savefile << t << ',';
        //initialise system wide variables
        pressureFrame = Vector3(0,0,0);
        temperature = 0;
        kineticEnergy = 0;
        potentialEnergy = 0;
        
        //Verlet integration algorithm
        //|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
        for (int i = 0; i < atoms.size(); i++) {
            Vector3 currentPosition = atoms[i].GetPosition();
            Vector3 currentVelocity = atoms[i].GetVelocity();
            Vector3 currentAcceleration = atoms[i].GetAcceleration();

            atoms[i].SetVelocity(currentVelocity + currentAcceleration * 0.5 * dt);
            //check if the particle is out of the boudaries before setting the position
            updateOnRebound(simulationBox, i, dt);
            atoms[i].SetPosition(currentPosition + atoms[i].GetVelocity() * dt);
            
            kineticEnergy += 0.5 * atoms[i].GetMass() * pow(atoms[i].GetVelocity().Magnitude(), 2);

            //log the particle data into a .csv file
            logSimulationData(savefile, i);
        }
        
        temperature = (double)(2.0f / 3.0f) * kineticEnergy / (atoms.size() * 1.38e-23);
        calculatePotential();
        calculatePressure(dt, simulationBox);
        updateAcceleration();
        
        
        for (int i = 0; i < atoms.size(); i++) {
            atoms[i].SetVelocity(atoms[i].GetVelocity() + atoms[i].GetAcceleration() * 0.5 * dt);
        }
        //|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
        
        savefile << pressureFrame.x << ',' << pressureFrame.y << ',' << pressureFrame.z << ',' << potentialEnergy << ',' << kineticEnergy << ',' << temperature;
        
        //cout << pressureFrame.x << "  " << pressureFrame.y << "  " << pressureFrame.z << endl;
        
        savefile << endl;
    }
    
    savefile.close();
}



void System::updateAcceleration()
{
    //loop through every body
    for (int i = 0; i < atoms.size(); i++) {
        //initialise the acceleration vector to zero with each new body
        Vector3 acc(0,0,0);

        //for each body, loop through all other bodies except for itself to calculate the acceleration according to equation1
        for (int j = 0; j < atoms.size(); j++) {
            if (i != j) {
                acc = acc + (atoms[i].GetPosition() - atoms[j].GetPosition()).Normalise() * (field((atoms[i].GetPosition() - atoms[j].GetPosition()).Magnitude()));
            }
        }
        //update the acceleration at the end of the i loop
        atoms[i].SetAcceleration(acc / atoms[i].GetMass());
    }
}

void System::calculatePotential()
{
    // loop through the system twice, for each body, add all the potential contribution from other bodies
    for (int i = 0; i < atoms.size(); i++) {
        for (int j = 0; j < atoms.size(); j++) {
            // if the body is not itself, do calculatiom shown in equation 7 and update the gpe variable each time
            if (i != j) {
                potentialEnergy += potential((atoms[i].GetPosition() - atoms[j].GetPosition()).Magnitude());
            }
        }
    }
}


void System::updateOnRebound(Vector3 boundaryVector, int i, double dt)
{
    Vector3 currentPosition = atoms[i].GetPosition();
    Vector3 currentVelocity = atoms[i].GetVelocity();
    
    if (currentPosition.x > boundaryVector.x) {
        // if the particle goes out of bounds in between frames, it means it must rebound in the time between frames and have already travelled back a distance, simply reversing the velocity does not address the problem that the particle has travelled extra distance, therefore this extra distance has to be offset in the opposite direction before the next frame
        atoms[i].SetPosition(Vector3(boundaryVector.x - (currentPosition.x - boundaryVector.x), currentPosition.y, currentPosition.z));
        atoms[i].SetVelocity(Vector3(-currentVelocity.x, currentVelocity.y, currentVelocity.z));
    }
    else if (currentPosition.x < -boundaryVector.x) {
        atoms[i].SetPosition(Vector3(-boundaryVector.x - (currentPosition.x + boundaryVector.x), currentPosition.y, currentPosition.z));
        atoms[i].SetVelocity(Vector3(-currentVelocity.x, currentVelocity.y, currentVelocity.z));
    }
    
    if (currentPosition.y > boundaryVector.y) {
        atoms[i].SetPosition(Vector3(currentPosition.x, boundaryVector.y - (currentPosition.y - boundaryVector.y), currentPosition.z));
        atoms[i].SetVelocity(Vector3(currentVelocity.x, -currentVelocity.y, currentVelocity.z));
     }
    else if (currentPosition.y < -boundaryVector.y) {
        atoms[i].SetPosition(Vector3(currentPosition.x, -boundaryVector.y - (currentPosition.y + boundaryVector.y), currentPosition.z));
        atoms[i].SetVelocity(Vector3(currentVelocity.x, -currentVelocity.y, currentVelocity.z));
     }

    if (currentPosition.z > boundaryVector.z) {
        atoms[i].SetPosition(Vector3(currentPosition.x, currentPosition.y, boundaryVector.z - (currentPosition.z - boundaryVector.z)));
        atoms[i].SetVelocity(Vector3(currentVelocity.x, currentVelocity.y, -currentVelocity.z));
     }
    else if (currentPosition.z < -boundaryVector.z) {
        atoms[i].SetPosition(Vector3(currentPosition.x, currentPosition.y, -boundaryVector.z - (currentPosition.z + boundaryVector.z)));
        atoms[i].SetVelocity(Vector3(currentVelocity.x, currentVelocity.y, -currentVelocity.z));
     }
}

void System::calculatePressure(double dt, Vector3 boundary)
{
    //loop through all atoms, 3 imagineary surfaces are set up around the origin, if the atom crosses any of the surfaces, a pressure has been exerted on that surface
    for (int i = 0; i < atoms.size(); i++) {
        // if the current position multiplied by the position in the next frame is negative it must mean the atom has crossed the origin
        if ((atoms[i].GetPosition().x + atoms[i].GetVelocity().x * dt) * atoms[i].GetPosition().x < 0) {
            pressureFrame.x +=  abs(atoms[i].GetVelocity().x) * atoms[i].GetMass() / (2 * boundary.x * boundary.x + 2 * boundary.y * boundary.y + 2 * boundary.z + boundary.z * dt);
        }
        if ((atoms[i].GetPosition().y + atoms[i].GetVelocity().y * dt) * atoms[i].GetPosition().y < 0) {
            pressureFrame.y +=  abs(atoms[i].GetVelocity().y) * atoms[i].GetMass() / (2 * boundary.x * boundary.x + 2 * boundary.y * boundary.y + 2 * boundary.z + boundary.z * dt);
        }
        if ((atoms[i].GetPosition().z + atoms[i].GetVelocity().z * dt) * atoms[i].GetPosition().z < 0) {
            pressureFrame.z +=  abs(atoms[i].GetVelocity().z) * atoms[i].GetMass() / (2 * boundary.x * boundary.x + 2 * boundary.y * boundary.y + 2 * boundary.z + boundary.z * dt);
        }
    }
}


double System::potential(double r, double eps, double sig)
{
    return 4 * eps * (pow(sig/r, 12) - pow(sig/r, 6));
}

double System::field(double r, double eps, double sig)
{
    return -4 * eps * ((6 * pow(sig, 6)) / pow(r, 7) - 12 * pow(sig, 12) / pow(r, 13));
}

void System::createSimulationHeader(ofstream &savefile)
{
    savefile << "time" << ',';
    
    for (int i = 0; i < atoms.size(); i++) {
        savefile << "atom" << i << "_x" << ',';
        savefile << "atom" << i << "_y" << ',';
        savefile << "atom" << i << "_z" << ',';
        savefile << "atom" << i << "_vx" << ',';
        savefile << "atom" << i << "_vy" << ',';
        savefile << "atom" << i << "_vz" << ',';
        savefile << "atom" << i << "_ax" << ',';
        savefile << "atom" << i << "_ay" << ',';
        savefile << "atom" << i << "_az" << ',';
    }
    
    savefile << "pressure_x" << ',' << "pressure_y" << ',' << "pressure_z"  << ',' << "PE" << ',' << "KE" << ',' << "temperature";
    
    savefile << endl;
}

void System::logSimulationData(ofstream &savefile, int i)
{
    savefile << atoms[i].GetPosition().x << ',';
    savefile << atoms[i].GetPosition().y << ',';
    savefile << atoms[i].GetPosition().z << ',';
    savefile << atoms[i].GetVelocity().x << ',';
    savefile << atoms[i].GetVelocity().y << ',';
    savefile << atoms[i].GetVelocity().z << ',';
    savefile << atoms[i].GetAcceleration().x << ',';
    savefile << atoms[i].GetAcceleration().y << ',';
    savefile << atoms[i].GetAcceleration().z << ',';
}
