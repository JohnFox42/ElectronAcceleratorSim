#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "SteppingAction.hh"
#include "EventAction.hh"
#include "RunAction.hh"
#include <typeinfo>

namespace BasicDetector
{
void ActionInitialization::Build() const
{
    auto runAction = new RunAction();
    SetUserAction(runAction);
    auto eventAction = new EventAction(runAction);
    SetUserAction(eventAction);
    SetUserAction(new PrimaryGeneratorAction()); 
    SetUserAction(new SteppingAction(eventAction,runAction));
}

void ActionInitialization::BuildForMaster() const
{
    SetUserAction(new RunAction());
}
}
