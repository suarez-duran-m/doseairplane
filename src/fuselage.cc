// Database of materials:
// http://geant4-userdoc.web.cern.ch/geant4-userdoc/UsersGuides/ForApplicationDeveloper/BackupVersions/V9.3/html/apas09.html


// Geant4 Libraries
//
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"



// Local Libraries
//
#include "fuselage.hh"


fuselage::fuselage()
{
  G4cout << "...Creating Ground..." << G4endl;
}


fuselage::~fuselage()
{}


void fuselage::DefineMaterials()
{

  G4NistManager* nist = G4NistManager::Instance();
  
  fuselage_mat = nist->FindOrBuildMaterial("G4_Al");
}


void fuselage::buildDetector(G4double plane_size, G4LogicalVolume* log_mother, G4bool* overLaps)
{
  G4double cab_radmin = 0.*m;
  G4double cab_radmax = 2.73*m; // Airbus330-200
  G4double cab_lar = 5.*m;
  G4double posZ = 0.*m;

  G4RotationMatrix* fusRot = new G4RotationMatrix();
  fusRot->rotateY(90.*deg);

  fuselage_geo
    = new G4Tubs(
        "fuselage_geo",
        cab_radmin,
        cab_radmax,
        cab_lar,
        0.*deg,
        360.*deg
        );

  fuselage_log
    = new G4LogicalVolume(
        fuselage_geo,
        fuselage_mat,
        fuselage_geo->GetName()
        );

  fuselage_phys 
    = new G4PVPlacement(
        fusRot,
        G4ThreeVector(0.*m, 0.*m, -posZ),
        fuselage_log,
        fuselage_geo->GetName(),
        log_mother,
        false,
        0,
        overLaps
        ); 
}


G4VPhysicalVolume* fuselage::getPhysVolume()
{
  return fuselage_phys;
}


G4LogicalVolume* fuselage::getLogVolume()
{
  return fuselage_log;
}
