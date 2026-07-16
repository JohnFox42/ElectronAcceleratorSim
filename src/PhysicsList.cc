#include "PhysicsList.hh"
#include "G4EmPenelopePhysics.hh"

namespace BasicDetector
{
    PhysicsList::PhysicsList()
    {
        RegisterPhysics(new G4EmPenelopePhysics());
    }
} 
