/// \file DetectorConstruction.hh
/// \brief Definition of BasicDetector::DetectorConstruction Class
#ifndef BasicDetectorDetectorConstruction_h
#define BasicDetectorDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

namespace BasicDetector
{
class DetectorConstruction : public G4VUserDetectorConstruction
{
    public:
    DetectorConstruction()= default;
    ~DetectorConstruction() override = default;

    G4VPhysicalVolume* Construct() override;

    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

    protected:
    G4LogicalVolume* fScoringVolume = nullptr;
};
}

#endif