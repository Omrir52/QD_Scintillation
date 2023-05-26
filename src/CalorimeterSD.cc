//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file CalorimeterSD.cc
/// \brief Implementation of the B4c::CalorimeterSD class

#include "CalorimeterSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"
#include "run.hh"
#include "EventAction.hh"

namespace B4c
{


CalorimeterSD::CalorimeterSD(const G4String& name,
                             const G4String& hitsCollectionName,
                             G4int nofCells)
 : G4VSensitiveDetector(name),
   fNofCells(nofCells)
{
  collectionName.insert(hitsCollectionName);
}



CalorimeterSD::~CalorimeterSD()
{}



void CalorimeterSD::Initialize(G4HCofThisEvent* hce)
{
  // Create hits collection
  fHitsCollection
    = new CalorHitsCollection(SensitiveDetectorName, collectionName[0]);

  // Add this collection in hce
  auto hcID
    = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection( hcID, fHitsCollection );

  // Create hits
  // fNofCells for cells + one more for total sums
  for (G4int i=0; i<fNofCells+1; i++ ) {
    fHitsCollection->insert(new CalorHit());
  }
}



G4bool CalorimeterSD::ProcessHits(G4Step* step,
                                     G4TouchableHistory*)
{
  auto analysisManager = G4AnalysisManager::Instance();
  G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
  G4int pdg = step->GetTrack()->GetParticleDefinition()->GetPDGEncoding();
  auto particlePDG = step->GetTrack()->GetDefinition()->GetPDGEncoding();
  // energy deposit
  auto edep = step->GetTotalEnergyDeposit();

  // step length
  G4double stepLength = 0.;
  if ( step->GetTrack()->GetDefinition()->GetPDGCharge() != 0. ) {
    stepLength = step->GetStepLength();
  }

  if ( edep==0. && stepLength == 0. ) return false;

  auto touchable = (step->GetPreStepPoint()->GetTouchable());

  // Get calorimeter cell id
  auto layerNumber = touchable->GetReplicaNumber(1);

  // Get hit accounting data for this cell
  auto hit = (*fHitsCollection)[layerNumber];
  if ( ! hit ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hit " << layerNumber;
    G4Exception("CalorimeterSD::ProcessHits()",
      "MyCode0004", FatalException, msg);
  }

  // Get hit for total accounting
  auto hitTotal
    = (*fHitsCollection)[fHitsCollection->entries()-1];

  // Add values
  double energy = step->GetTrack()->GetKineticEnergy();
  double wavelength = 0.001247/energy;
  double time;
  //G4cout << "Counter: " << counter << G4endl;
  time = step->GetPreStepPoint()->GetGlobalTime();
  if (pdg == -22){
    if (wavelength >= 300){
      event_counter++;
      
      analysisManager->FillNtupleDColumn(0,0,evt);
      analysisManager->FillNtupleDColumn(0,1,wavelength);
      //analysisManager->FillNtupleDColumn(2,energy);
      analysisManager->FillNtupleDColumn(0,2,time);
      analysisManager->AddNtupleRow(0);
      //G4cout << "Energy: " << energy << G4endl;
      //G4cout << "Wavelength: " << wavelength << G4endl;
    }
    else{
      step->GetTrack()->SetTrackStatus(fStopAndKill);
    }
  }
  


  //hit->Add(edep, stepLength, evt);
  //hitTotal->Add(edep, stepLength, evt);
  
  //G4cout << "Paricle PDG: " << pdg << G4endl;
  //G4cout << "Counter: " << counter << G4endl;
  //G4cout << "Energy: " << energy << G4endl;
  return true;
}



void CalorimeterSD::EndOfEvent(G4HCofThisEvent*)
{
}



}
