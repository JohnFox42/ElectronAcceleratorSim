#include "EventAction.hh"
#include "RunAction.hh"
#include "G4RootAnalysisManager.hh"
#include "G4Event.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4ios.hh"

namespace BasicDetector
{
    EventAction::EventAction(RunAction* runAction): fRunAction(runAction)
    {
    }

    void EventAction::BeginOfEventAction(const G4Event*)
    {
        SiEdep = 0.;
    }

    void EventAction::AddSiEdep(G4double edep)
    {
        SiEdep += edep; 
    }

    void EventAction::EndOfEventAction(const G4Event* event)
    {
        //Record the energy deposition in the Ge detector and output to a root file
        auto analysisManager = G4RootAnalysisManager::Instance();
        G4double TotalDeposit = 0;
        for (auto const& [key,deposit] : fPhotonEdep)
        {
            analysisManager->FillH1(1,deposit);
            TotalDeposit += deposit;
        }
        G4double CoincidenceE = TotalDeposit + SiEdep;
        if (TotalDeposit!= 0 && CoincidenceE>=380*keV && CoincidenceE<= 401*keV && TotalDeposit>=70*keV && TotalDeposit<= 130*keV)
        {
            fRunAction->IterateCoinCount();
        } 
        fPhotonEdep.clear();

        //Fill SiEdep histogram
        analysisManager->FillH1(3,SiEdep);
        
        auto eventID = event->GetEventID();
        if (eventID % 100000 == 0)
        {
            G4cout << "Event: " << eventID << G4endl;
        }
        
    }
}
