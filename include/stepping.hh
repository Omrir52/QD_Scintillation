#ifndef STEPPING_HH
#define STEPPING_HH

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"

#include "CalorimeterSD.hh"
#include "EventAction.hh"

class MySteppingAction : public G4UserSteppingAction
{
public:
    MySteppingAction();
    ~MySteppingAction();

    virtual void UserSteppingAction(const G4Step*);

private:
    //EventAction *fEventAction;
};


#endif