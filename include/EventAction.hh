/// \file EventAction.hh
/// \brief 

#ifndef BasicDetectorEventAction_h
#define BasicDetectorEventaction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "RunAction.hh"
#include <map>

namespace BasicDetector
{
    class RunAction;

    class EventAction : public G4UserEventAction
    {
        public:
        EventAction(RunAction* runAction);
        ~EventAction() override=default;

        void BeginOfEventAction(const G4Event*) override;
        void EndOfEventAction(const G4Event*) override;
        
        void AddSiEdep(G4double edep);
        void UpdateEscapeBool(bool escape);
        bool ReturnEscapeBool(){return EscapeBool;}

        std::map<G4int, G4double> fPhotonEdep {}; 

        protected:
        G4double SiEdep = 0.;
        G4bool EscapeBool = false;

        private:
        RunAction* fRunAction = nullptr;
    };
}

#endif 
