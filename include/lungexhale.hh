#ifndef lungexhale_h
#define lungexhale_h 1


// Geant4 Libraries
//
#include "G4Element.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Ellipsoid.hh"
#include "G4SystemOfUnits.hh" 


// Local Libraries
//


class lungexhale 
{
  public:
    lungexhale();
    ~lungexhale();

    void DefineMaterials();
    void buildDetector(G4double posZ, G4LogicalVolume* log_mother, G4bool* overLaps);

    G4VPhysicalVolume* getPhysVolume();
    G4LogicalVolume* getLogVolume();


  private:
    G4Material* lungexhale_mat;

    G4Ellipsoid* lungexhale_geo;
    G4LogicalVolume* lungexhale_log;
    G4VPhysicalVolume* lungexhale_phys;
};
#endif
