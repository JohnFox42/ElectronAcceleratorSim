#include "PhysicsList.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4StepLimiterPhysics.hh"
#include "G4LeptonConstructor.hh"
#include "G4BosonConstructor.hh"

namespace BasicDetector
{
    PhysicsList::PhysicsList()
    {
        //Register leptons and bosons
        G4LeptonConstructor LeptonConstructor;
        LeptonConstructor.ConstructParticle();
        G4BosonConstructor BosonConstructor;
        BosonConstructor.ConstructParticle();

        RegisterPhysics(new G4StepLimiterPhysics());
        RegisterPhysics(new G4EmPenelopePhysics());
    }
} 
