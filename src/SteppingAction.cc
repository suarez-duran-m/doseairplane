
// Geant4 Libraries
//
#include "G4Step.hh"
#include "G4Track.hh"

#include "G4OpticalPhoton.hh"
#include "G4VProcess.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4SystemOfUnits.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "g4root.hh"
#include "G4SDManager.hh"
#include "G4TransportationManager.hh"
#include "G4SystemOfUnits.hh"


// Local Libraries
#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
#include "PMTSD.hh"
#include "CerenkovValidation.hh"
#include "EventAction.hh"
#include "PrimaryGeneratorAction.hh"



SteppingAction::SteppingAction(EventAction* eventAction)
  : G4UserSteppingAction(),
    fEventAction(eventAction)
{
  G4cout << "...SteppingAction..." << G4endl; 
  G4TransportationManager::GetTransportationManager()
    ->GetNavigatorForTracking()->SetPushVerbosity(0);
  
  fScintillationCounter = 0;
  lengthMaxOk = 0;
  fEventNumber = -1;
  initEner = 0.;
   pmtSD = new PMTSD;
 // cerValid = new CerenkovValidation;

  
  detectorConstruction 
     = static_cast < const DetectorConstruction* 
     > (G4RunManager::GetRunManager()
         ->GetUserDetectorConstruction());
}

SteppingAction::~SteppingAction()
{}


void SteppingAction::UserSteppingAction(const G4Step* step)
{
  // --------------------
  // Get G4Track variable 
  G4Track* track = step->GetTrack();
  volumName = step->GetPostStepPoint()->GetPhysicalVolume()->GetName();

  if( volumName == "lung_geo" )
  {
    fEventAction->fRunAction->AddEdep(step->GetTotalEnergyDeposit());
  }

  if ( volumName == "expHall" )
       track->SetTrackStatus(fStopAndKill);
}
