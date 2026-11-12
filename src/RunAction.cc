#include "G4RootAnalysisManager.hh"
#include "G4Run.hh"
#include "RunAction.hh"
#include "G4SystemOfUnits.hh"
#include "GlobalVariables.hh"
#include "Randomize.hh"
#include "G4AccumulableManager.hh"
#include "G4Threading.hh"
#include <cmath>
#include <typeinfo>

namespace BasicDetector
{

RunAction::RunAction()
{
    //Create the analysis manager
    auto analysisManager = G4RootAnalysisManager::Instance();
    analysisManager->SetVerboseLevel(1);
    analysisManager->SetDefaultFileType("root");
    analysisManager->SetNtupleMerging(true);

    //Creating histograms
    analysisManager->CreateH1("SiKinE","Energy of Bremsstrahlung Photons",80,0,400*keV);
    analysisManager->CreateH1("Edep","Energy Deposited in Ge",80.,0.,400.*keV);
    analysisManager->CreateH1("GeKinE","Energy of Photons Impacting Ge Detector",400.,0.,400.*keV);
    analysisManager->CreateH1("SiEdep","Energy Deposited in Si",100.,0.,500.*keV);

    //Register accumulable to the accumulable manager
    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->Register(fBremCount);
    accumulableManager->Register(fCoinCount);
    accumulableManager->Register(fEscapeCount);
    accumulableManager->Register(fThreshCount);
}

void RunAction::BeginOfRunAction(const G4Run* run)
{
    //Run start verification
    if (IsMaster())
    {
        G4cout << "Run Started" << G4endl;
    }

    //Getting the analysis manager
    auto analysisManager = G4RootAnalysisManager::Instance();

    //Open an output file
    G4String fileName = "spectrum.root";
    analysisManager->OpenFile(fileName);

    //Reset accumulables to the initial values
    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->Reset();
}

void RunAction::IterateBremCount()
{
    ++fBremCount;
}

void RunAction::IterateCoinCount()
{
    ++fCoinCount;
}

void RunAction::IterateEscapeCount()
{
    ++fEscapeCount;
}

void RunAction::IterateThreshCount()
{
    ++fThreshCount;
}

void RunAction::EndOfRunAction(const G4Run* run)
{
    auto analysisManager = G4RootAnalysisManager::Instance();

    //Merge Accumulables
    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->Merge();

    //Get Total count of bremsstrahlung events
    const G4int TotalBremCount = fBremCount.GetValue();
    const G4int TotalCoinCount = fCoinCount.GetValue();
    const G4int TotalEscapeCount = fEscapeCount.GetValue();
    const G4int TotalThreshCount = fThreshCount.GetValue();

    //Output Statistics
    if (IsMaster())
    {
        //Silicon detector statistics
        G4cout << "The number of bremsstrahlug events was: " << TotalBremCount << '\n';
        G4double prob = static_cast<G4double>(TotalBremCount)/(run->GetNumberOfEvent());
        G4double sigma = sqrt(prob*(1-prob)/(run->GetNumberOfEvent()));
        G4cout << "The probability of an event was: " << prob*100 << '%' <<'\n';
        G4cout << "with standard deviation: " << sigma*100<< '%' << '\n';
        G4cout << "SEED = " << CLHEP::HepRandom::getTheSeed() << '\n';
        //Debugging code
        G4cout << "End of Run: Total Bremsstrahlung Events = " << analysisManager->GetH1(0)->entries() << '\n';

        //Germanium detector statistics 
        G4double GeCounts {static_cast<G4double>(analysisManager->GetH1(2)->entries())};
        G4cout << "End of Run: Ge Kinetic Energy Counts = " << GeCounts <<'\n';
        G4double GeProb = GeCounts/static_cast<G4double>(TotalBremCount);
        G4cout << "Probability of a hit = " << GeProb*100<< '%' << '\n';
        G4double GeSigma = sqrt(GeProb*(1-GeProb)/TotalBremCount);
        G4cout << "with standard deviation: " << GeSigma*100<< '%' << '\n';

        //Coincidence stats
        G4cout << "End of Run: Total Coincidence Count = " << TotalCoinCount << '\n';

        //Escape Stats
        G4cout << "End of Run: Total Escape Count = " << TotalEscapeCount << '\n';
        G4double EscapeProb = static_cast<G4double>(TotalEscapeCount)/static_cast<G4double>(run->GetNumberOfEvent());
        G4cout << "End of Run: Escape Probability = " << EscapeProb*100 << '%' << '\n';
        G4double EscapeSigma = sqrt(EscapeProb*(1-EscapeProb)/static_cast<G4double>(run->GetNumberOfEvent()));
        G4cout << "End of Run: with standard deviation = " << EscapeSigma*100 << '%' << '\n';

        //Threshold counts assuming 100% Ge Efficiency
        G4cout << "End of Run: Total Threshold Photons: " << TotalThreshCount << '\n';
        G4double ThreshProb = static_cast<G4double>(TotalThreshCount)/static_cast<G4double>(TotalEscapeCount);
        G4cout << "End of Run: Total Threshold Probability = " << ThreshProb*100 << '%' << '\n';
        G4double ThreshSigma = sqrt(ThreshProb*(1-ThreshProb)/static_cast<G4double>(TotalEscapeCount));
        G4cout << "End of Run: with standard deviation = " << ThreshSigma*100 << '%' <<'\n';
    }
    //write to the analysis file
    analysisManager->Write();
    analysisManager->CloseFile();

    if (IsMaster())
    {
        //run ended verification
        G4cout << "Run Finished" << G4endl;
    }
}
}
