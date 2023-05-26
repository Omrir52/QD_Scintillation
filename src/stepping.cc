#include "stepping.hh"

MySteppingAction::MySteppingAction()
{
    
}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step *step)
{
   /*G4int pdg = step->GetTrack()->GetParticleDefinition()->GetPDGEncoding();
   double energy = step->GetTrack()->GetKineticEnergy();
   double wavelength = 0.001247/energy;
    if (pdg == -22){
      if (wavelength < 300){
        step->GetTrack()->SetTrackStatus(fStopAndKill);
      }
    }*/
}
