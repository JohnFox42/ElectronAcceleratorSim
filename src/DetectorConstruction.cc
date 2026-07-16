#include "DetectorConstruction.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"
#include "G4VPhysicalVolume.hh"

namespace BasicDetector
{
G4VPhysicalVolume* DetectorConstruction::Construct()
{
    //Defining the world space parameters
    G4double world_hx = 0.5*m;
    G4double world_hy = 0.5*m;
    G4double world_hz = 0.5*m;
    
    //Creating the world space
    G4Box* worldBox = new G4Box("World",world_hx,world_hy,world_hz);
    
    //Creating a vaccum property from NIST
    auto nist = G4NistManager::Instance();
    G4Material* worldMat = nist->FindOrBuildMaterial("G4_Galactic");

    //Creating the world logical volume
    G4LogicalVolume* worldLog = new G4LogicalVolume(worldBox,worldMat,"World");
    
    //Defining the silicon detector geometric parameters
    G4double SiInnerRadius = 0.*m;
    G4double SiOuterRadius = 2*cm;
    G4double SiHz = 1.*mm;
    G4double SiStartAngle = 0.*deg;
    G4double SiSpanningAngle = 360.*deg;
    
    //Building the silicon detector
    G4Tubs* SiDetectorTube = new G4Tubs("SiDetector",SiInnerRadius,SiOuterRadius,SiHz,SiStartAngle,SiSpanningAngle);
    
    //Creating Silicon
    G4Material* Si = nist->FindOrBuildMaterial("G4_Si");

    //Creating the logical detector volume and filling with silicon
    G4LogicalVolume* SiDetectorLog = new G4LogicalVolume(SiDetectorTube,Si,"SiDetector");

    //Dimensions for the germanium detector
    G4double GeOuterRadius = 4.*cm;
    G4double GeInnerRadius = 0.*cm; 
    G4double GeHz = 3.5*cm;
    G4double GeStartAngle = 0.*deg;
    G4double GeSpanningAngle = 360.*deg;

    //Building the germanium detector
    G4Tubs* GeDetectorTube = new G4Tubs("GeDetector",GeInnerRadius,GeOuterRadius,GeHz,GeStartAngle,GeSpanningAngle);

    //Creating germanium
    G4Material* Ge = nist->FindOrBuildMaterial("G4_Ge");

    //Creating the logical germanium detector and filling with germanium
    G4LogicalVolume* GeDetectorLog = new G4LogicalVolume(GeDetectorTube,Ge,"GeDetector");

    //Assigning a detector volume to germanium
    fGeDetector = GeDetectorLog;

    //Assiging a detector volume to silicon
    fSiDetector = SiDetectorLog; 
    

    //Placing the world volume
    G4VPhysicalVolume* worldPhys = new G4PVPlacement(0,G4ThreeVector(0,0,0),worldLog,"World",nullptr,false,0);
    
    //Placing the silicon detector at the origin
    G4VPhysicalVolume* SiDetectorPhys = new G4PVPlacement(0,G4ThreeVector(0,0,0),SiDetectorLog,"SiDetector",worldLog,false,0);

    //Placing the germanium detector 
    G4VPhysicalVolume* GeDetectorPhys = new G4PVPlacement(0,G4ThreeVector(0,0,-13.55*cm),GeDetectorLog,"GeDetector",worldLog,false,0);

    return worldPhys;
}
}
