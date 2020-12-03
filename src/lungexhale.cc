// Database of materials:
// http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/BackupVersions/V9.3/html/apas09.html


// Geant4 Libraries
//
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"



// Local Libraries
//
#include "lungexhale.hh"


lungexhale::lungexhale()
{
  G4cout << "...Creating Lung Geometry..." << G4endl;
}


lungexhale::~lungexhale()
{}


void lungexhale::DefineMaterials()
{

  G4NistManager* nist = G4NistManager::Instance();
  G4double density = 0.495*g/cm3;
  lungexhale_mat 
    = nist->BuildMaterialWithNewDensity(
        "Lung_0495", 
        "G4_LUNG_ICRP", 
        density
        );
}


void lungexhale::buildDetector(G4double posZ, G4LogicalVolume* log_mother, G4bool* overLaps)
{
  G4double pxSemiAxis = 5.*cm; // Volume ~418 cm^3
  G4double pySemiAxis = 5.*cm;
  G4double pzSemiAxis = 4.*cm;
  G4double pzBottomCut = -pzSemiAxis;
  G4double pzTopCut = 4.*cm;

  lungexhale_geo
    = new G4Ellipsoid("lung_geo",
        pxSemiAxis,
        pySemiAxis,
        pzSemiAxis,
        pzBottomCut,
        pzTopCut
        );

  lungexhale_log
    = new G4LogicalVolume(
        lungexhale_geo,
        lungexhale_mat,
        lungexhale_geo->GetName()
        );

  lungexhale_phys 
    = new G4PVPlacement(
        0,
        G4ThreeVector(posZ, 0.*m, 0*m),
        lungexhale_log,
        lungexhale_geo->GetName(),
        log_mother,
        false,
        0,
        overLaps
        );
}


G4VPhysicalVolume* lungexhale::getPhysVolume()
{
  return lungexhale_phys;
}


G4LogicalVolume* lungexhale::getLogVolume()
{
  return lungexhale_log;
}
