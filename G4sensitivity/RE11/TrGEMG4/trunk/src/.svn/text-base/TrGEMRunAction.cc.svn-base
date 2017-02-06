#include "TrGEMRunAction.hh"
#include "TrGEMAnalysis.hh"

#include "G4Run.hh"

TrGEMRunAction::TrGEMRunAction()
{}

TrGEMRunAction::~TrGEMRunAction()
{}

void TrGEMRunAction::BeginOfRunAction(const G4Run* aRun)
{
   G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl ;
   TrGEMAnalysis::GetInstance()->PrepareNewRun(aRun) ;
}

void TrGEMRunAction::EndOfRunAction(const G4Run* aRun)
{
   TrGEMAnalysis::GetInstance()->EndOfRun(aRun) ;
}

