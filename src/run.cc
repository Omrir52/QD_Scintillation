#include "run.hh"

MyRunAction::MyRunAction()
{}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run*)
{
    //G4AnalysisManager *man = G4AnalysisManager::Instance();

    //man->OpenFile("output.root");
    
    //man->CreateNtuple("Hits","Hits");
    //man->CreateNtupleIColumn("fEvent");
    //man->CreateNtupleIColumn("fEdep");
    //man->FinishNtuple();
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
    //G4AnalysisManager *man = G4AnalysisManager::Instance();

    //man->Write();
    //man->CloseFile();
}