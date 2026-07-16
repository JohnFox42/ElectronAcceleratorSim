#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4EMPenelopePhysics.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "G4UImanager.hh"
#include "Randomize.hh"
#include <filesystem>
#include <ctime>

//I am commenting out visualization for increased performance
int main(int argc, char** argv)
{
    //Setting a random seed and by random I mean using the current time
    long seed = time(nullptr);
    CLHEP::HepRandom::setTheSeed(seed);

    //Setting up multthreaded run manager 
    auto runManager = G4RunManagerFactory::CreateRunManager();

    //set mandatory initialization classes
    runManager->SetUserInitialization(new BasicDetector::DetectorConstruction());
    runManager->SetUserInitialization(new BasicDetector::PhysicsList());
    runManager->SetUserInitialization(new BasicDetector::ActionInitialization());

    //initialize the G4 kernel
    runManager->Initialize();

    //Visualization Manager
    //G4VisManager* visManager = new G4VisExecutive();
    //visManager->Initialize();

    //Set up the UI
    //G4UIExecutive* ui  = new G4UIExecutive(argc,argv,"qt");
    
    //Execute visualization macro
    //G4UImanager::GetUIpointer()->ApplyCommand("/control/execute vis.mac");

    //Execute run macro
    G4UImanager::GetUIpointer()->ApplyCommand("/control/execute run.mac");

    //Start the UI session
    //ui->SessionStart();

    //job termination
    //delete ui;
    //delete visManager;
    delete runManager;
    return 0;
}
