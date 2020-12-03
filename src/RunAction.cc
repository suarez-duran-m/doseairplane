
// Geant4 Libraries
//
#include "G4Timer.hh"
#include "G4Run.hh"
#include "g4root.hh"
#include "G4AccumulableManager.hh"
#include "DetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"


// Root Libraries
//
#include <TFile.h> 


// Local Libraries
//
#include "RunAction.hh"


RunAction::RunAction()
 : G4UserRunAction(),
  fEdep(0.),
  fEdep2(0.),
  fTimer(0)
{
  G4cout << "...RunAction..." << G4endl;
  fTimer = new G4Timer;

  // -----------------------
  // Histogram for One Pulse
  analysisManager->CreateH1("0","Time at Pmt", 1000, 0., 1000.);
  startCerenkValid();

  cerVali = new CerenkovValidation();

  if(cervaliOk)
    histCerVali = new CerValHistograms();

  if( histRunOk )
  {
    histRun = new histosRun();
    histRun->initHistos();
  }

  const G4double milligray = 1.e-3*gray;
  const G4double microgray = 1.e-6*gray;
  const G4double nanogray  = 1.e-9*gray;               
  const G4double picogray  = 1.e-12*gray;              
                                                       
  new G4UnitDefinition(
      "milligray", "milliGy" , "Dose", milligray
      );
  new G4UnitDefinition(
      "microgray", "microGy" , "Dose", microgray
      );
  new G4UnitDefinition(
      "nanogray" , "nanoGy"  , "Dose", nanogray
      );
  new G4UnitDefinition(
      "picogray" , "picoGy"  , "Dose", picogray
      );
}


RunAction::~RunAction()
{
  if(cervaliOk)
    histCerVali->~CerValHistograms();

//  if(coulombOk)
//    scatter->~coulombScattering();

  delete fTimer;
}


void RunAction::BeginOfRunAction(const G4Run* aRun)
{
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
  fTimer->Start();

  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Merge();

  if(cervaliOk)
    histCerVali->creatingHist(aRun->GetRunID());


//  if(coulombOk)
//    scatter->creatingHist();

  // ---------------------------
  // Root File for Pulses On PMT
  
//  G4String rootFile = "rootPulsesOnPMT";
//  analysisManager->OpenFile(rootFile);
}


void RunAction::EndOfRunAction(const G4Run* aRun)
{
  fTimer->Stop();
  G4cout << "number of event = " 
    << aRun->GetNumberOfEvent()
    << " " 
    << *fTimer 
    << G4endl;

  G4int nofEvents = aRun->GetNumberOfEvent();
  if (nofEvents == 0) return;

  const DetectorConstruction* detectorConstruction 
    = static_cast<const DetectorConstruction*>
    (G4RunManager::GetRunManager()->GetUserDetectorConstruction());

  G4double mass 
    = detectorConstruction->GetScoringVolume()->GetMass();

  G4double edep  = fEdep.GetValue();
  G4double edep2 = fEdep2.GetValue();

  G4double rms = edep2 - edep*edep/nofEvents;
  if (rms > 0.) rms = std::sqrt(rms); else rms = 0.;

  G4double dose = edep/mass;
  G4double rmsDose = rms/mass;

  G4cout << "Doses deposited into Lung: "
    << G4BestUnit(dose,"Dose") 
    << " rms = " 
    << G4BestUnit(rmsDose,"Dose")
    << " "
    << nofEvents
    << " "
    << edep2
    << " mass: "
    << mass
    << G4endl;

  closeCerenkValid();
  histRun->~histosRun();
}


void RunAction::startCerenkValid()
{
  analysisManager->CreateH1("1","PhotoElectrons", 500, 0, 500);
  analysisManager->OpenFile("rootCerenkValid");
}


void RunAction::closeCerenkValid()
{
  analysisManager->Write();
  analysisManager->CloseFile();
}


void RunAction::startCoulombValid()
{
  analysisManager->CreateH1("1","CoulombSomeThing", 500, 0, 500);
  analysisManager->OpenFile("rootCoulombValid");
}


void RunAction::closeCoulombValid()
{
  analysisManager->Write();
  analysisManager->CloseFile();
}


void RunAction::fillHistPhoVcm()
{
  histCerVali->doHistCerPhoCm(cerVali->nphoVcm);
}


void RunAction::AddEdep(G4double edep)
{
  fEdep += edep;
  fEdep2 += edep*edep;
}
