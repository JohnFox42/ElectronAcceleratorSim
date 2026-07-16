/// \file SteppingAction.hh
/// \brief Definition for BasicDetector::SteppingAction class

#ifndef BasicDetectorSteppingAction_h
#define BasicDetectorSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"

namespace BasicDetector
{
    class EventAction;
    class RunAction;

    class SteppingAction : public G4UserSteppingAction
    { 
        public:
        SteppingAction(EventAction* eventAction,RunAction* runAction);
        SteppingAction() = default;
        ~SteppingAction() override = default;
        void UserSteppingAction(const G4Step* step) override; 

        private:
        EventAction* fEventAction = nullptr;
        RunAction* fRunAction = nullptr;
    };
}

#endif
