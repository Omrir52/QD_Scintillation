#include "stepping.hh"

MySteppingAction::MySteppingAction()
{
    
}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step *step)
{
   // G4int pdg = step->GetTrack()->GetParticleDefinition()->GetPDGEncoding();
    //if (pdg == -22){
      //  step->GetTrack()->SetTrackStatus(fStopAndKill);
    //}
}
