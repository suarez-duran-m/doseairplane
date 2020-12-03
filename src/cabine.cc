// Database of materials:
// http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/BackupVersions/V9.3/html/apas09.html


// Geant4 Libraries
//
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"



// Local Libraries
//
#include "cabine.hh"


cabine::cabine()
{
  G4cout << "...Creating Ground..." << G4endl;
}


cabine::~cabine()
{}


void cabine::DefineMaterials()
{

  G4NistManager* nist = G4NistManager::Instance();
  
  cabine_mat = nist->FindOrBuildMaterial("G4_AIR");
}


void cabine::buildDetector(G4double plane_size, G4LogicalVolume* log_mother, G4bool* overLaps)
{
  G4double cab_rad = 2.64*m; // Airbus330-200
  G4double cab_lar = 5.*m;
  G4double posZ = 0.*m;

  cabine_geo
    = new G4Tubs(
        "cabine_geo",
        0.*m,
        cab_rad,
        cab_lar,
        0.*deg,
        360.*deg
        );

  cabine_log
    = new G4LogicalVolume(
        cabine_geo,
        cabine_mat,
        cabine_geo->GetName()
        );

  cabine_phys 
    = new G4PVPlacement(
        0,
        G4ThreeVector(0.*m, 0.*m, -posZ),
        cabine_log,
        cabine_geo->GetName(),
        log_mother,
        false,
        0,
        overLaps
        ); 
}


G4VPhysicalVolume* cabine::getPhysVolume()
{
  return cabine_phys;
}


G4LogicalVolume* cabine::getLogVolume()
{
  return cabine_log;
}
