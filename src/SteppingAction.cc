#include "SteppingAction.hh"
#include "G4ios.hh"
#include "DetectorConstruction.hh"
#include "EventAction.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4VPhysicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4RunManager.hh"
#include "GlobalVariables.hh"
#include "RunAction.hh"
#include "G4RootAnalysisManager.hh"

namespace BasicDetector
{
    
    SteppingAction::SteppingAction(EventAction* eventAction,RunAction* runAction)
    : fEventAction(eventAction), fRunAction(runAction)
    {
    }
    

    void SteppingAction::UserSteppingAction(const G4Step* step)
    {
        auto analysisManager = G4RootAnalysisManager::Instance();
        const G4VProcess* process = step->GetPostStepPoint()->GetProcessDefinedStep();
        G4String processName = process->GetProcessName();
        if (process && processName == "eBrem")
        {
            //Get the secondaries
            const auto* secondaries = step->GetSecondaryInCurrentStep();
            for (const auto* secondary : *secondaries)
            {
                if (secondary->GetDefinition()->GetParticleName() == "gamma")
                {
                    if (secondary->GetCreatorProcess() && secondary->GetCreatorProcess()->GetProcessName() == "eBrem")
                    {
                        //fill the histogram with the energy
                        G4double kinE{secondary->GetKineticEnergy()};
                        analysisManager->FillH1(0,kinE);
                        //Iterate the bremcount based on the number of photons produced
                        fRunAction->IterateBremCount();
                    }
                }
            }
        }
        
        //getting the tracks
        auto* track = step->GetTrack();

        //Check the track
        if (track->GetDefinition()->GetParticleName() == "gamma")
        {
            if (track->GetCreatorProcess() && track->GetCreatorProcess()->GetProcessName()=="eBrem")
            {
                //Gets the detector construction
                auto detectorConstruction = static_cast<const DetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());

                //Gets the scoring volume i.e. the detector
                G4LogicalVolume* scoringVolume = detectorConstruction->GetScoringVolume();

                //Gets pre and post step volumes
                auto* preVolume = step->GetPreStepPoint()->GetPhysicalVolume();
                auto* postVolume = step->GetPostStepPoint()->GetPhysicalVolume();

                //Check to see if this is the photons first step within the Germanium
                if (preVolume != postVolume && postVolume && postVolume->GetLogicalVolume() == scoringVolume)
                {
                    fEventAction->fPhotonEdep[track->GetTrackID()] = 0;
                    analysisManager->FillH1(2,step->GetPreStepPoint()->GetKineticEnergy());
                }

                //Check the current volume and record the deposition energy
                if (preVolume && preVolume->GetLogicalVolume() == scoringVolume)
                {
                    auto it = fEventAction->fPhotonEdep.find(track->GetTrackID());
                    if (it != fEventAction->fPhotonEdep.end())
                    {
                        it->second += step->GetTotalEnergyDeposit(); 
                    } else {
                        G4Exception("Stepping Action","MissingPhotonRecord",JustWarning,"Photon deposited energy before being registered");
                        G4cout << "Track ID: " << track->GetTrackID() << G4endl;
                        G4cout << "Parent ID: " << track->GetParentID() << G4endl;
                        G4cout << "Creator Process: " << track->GetCreatorProcess()->GetProcessName() << G4endl;
                        G4cout << "CurrentStepNumber: " << track->GetCurrentStepNumber() << G4endl;
                        G4cout << "Pre Volume: " << preVolume->GetName() << G4endl;
                        G4cout << "Post Volume: " << postVolume->GetName() << G4endl;
                        G4cout << "Current Kinetic Energy: " << step->GetPreStepPoint()->GetKineticEnergy() << G4endl;
                        G4cout << "Current edep: " << step->GetTotalEnergyDeposit() << G4endl;
                    }
                }
            }
        }
    }
}
