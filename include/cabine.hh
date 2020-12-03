#ifndef cabine_h
#define cabine_h 1


// Geant4 Libraries
//
#include "G4Element.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4SystemOfUnits.hh" 


// Local Libraries
//


class cabine
{
  public:
    cabine();
    ~cabine();

    void DefineMaterials();
    void buildDetector(G4double grd_size, G4LogicalVolume* log_mother, G4bool* overLaps);

    G4VPhysicalVolume* getPhysVolume();
    G4LogicalVolume* getLogVolume();


  private:
    G4Material* cabine_mat;

    G4Tubs* cabine_geo;
    G4LogicalVolume* cabine_log;
    G4VPhysicalVolume* cabine_phys;
};
#endif
