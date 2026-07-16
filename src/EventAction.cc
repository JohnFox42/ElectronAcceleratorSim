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
    }

    void EventAction::EndOfEventAction(const G4Event* event)
    {
        //Record the energy deposition in the Ge detector and output to a root file
        auto analysisManager = G4RootAnalysisManager::Instance();
        for (auto const& [key,deposit] : fPhotonEdep)
        {
            analysisManager->FillH1(1,deposit);
        } 
        //debugging code
        /*
        if (fPhotonEdep.size()!=0)
        {
            G4cout << "End of event: map size = " << fPhotonEdep.size() << G4endl;
            G4cout << "End of event: Histogram size = " << analysisManager->GetH1(1)->entries() << G4endl;
        }
        */

        fPhotonEdep.clear();
        
        auto eventID = event->GetEventID();
        if (eventID % 100000 == 0)
        {
            G4cout << "Event: " << eventID << G4endl;
        }
        
    }
}
