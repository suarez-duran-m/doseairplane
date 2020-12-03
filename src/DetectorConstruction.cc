
// Geant4 Libraries
//
#include "G4Material.hh"
#include "G4Element.hh"

#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4VPhysicalVolume.hh"

#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4UnitsTable.hh"
#include "G4PhysicalConstants.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4RunManager.hh"


// Local Libraries
//
//#include "PMTSD.hh"
#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "PMTSD.hh"
#include "world.hh"
#include "wcdLagoCont.hh"
#include "wcdLagoCalo.hh"
#include "wcdpmt.hh"
#include "worldGround.hh"
#include "cabine.hh"
#include "fuselage.hh"
#include "lungexhale.hh"


// C++ Libraries
//


DetectorConstruction::DetectorConstruction()
 : G4VUserDetectorConstruction(),
  fScoringVolume(0)
{
   G4cout << "...DetectorConstruction..." << G4endl;

  expHall = new world();
  groundBase = new worldGround();
  cabi = new cabine();
  fuse = new fuselage();
  lung = new lungexhale();

  wcdRadius = 9.*cm;
  wcdHight = 14.*cm; 

  checkOverlaps = true;

  detecMess = new DetectorMessenger(this);
}


DetectorConstruction::~DetectorConstruction()
{}

// *************************
// Doing Mechanical Detector
// ************************* 

G4VPhysicalVolume* DetectorConstruction::Construct()
{ 
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();
  G4LogicalSkinSurface::CleanSurfaceTable();
  G4LogicalBorderSurface::CleanSurfaceTable();

  return ConstructDetector();
}


G4VPhysicalVolume* DetectorConstruction::ConstructDetector()
{
  expHall->DefineMaterials();
  expHall->buildDetector(&checkOverlaps);

  groundBase->DefineMaterials();
  groundBase->buildDetector(expHall->getLogVolume(), &checkOverlaps);

  fuse->DefineMaterials();
  fuse->buildDetector(0., groundBase->getLogVolume(), &checkOverlaps);

  cabi->DefineMaterials();
  cabi->buildDetector(0., fuse->getLogVolume(), &checkOverlaps);

  lung->DefineMaterials();
  lung->buildDetector(1.2*m, cabi->getLogVolume(), &checkOverlaps);

  fScoringVolume = lung->getLogVolume();

  return expHall->getPhysVolume();
}


void DetectorConstruction::setWcdRadius( G4double wcdR )
{}


void DetectorConstruction::setWcdHight( G4double wcdH )
{}
