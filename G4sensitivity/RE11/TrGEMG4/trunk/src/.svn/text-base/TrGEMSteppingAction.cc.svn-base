#include "TrGEMSteppingAction.hh"
#include "TrGEMAnalysis.hh"

#include "G4SteppingManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrGEMSteppingAction::TrGEMSteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrGEMSteppingAction::UserSteppingAction(const G4Step* aStep)
{

   const G4VTouchable* touchable = aStep->GetPreStepPoint()->GetTouchable();
   //G4int volCopyNum = touchable->GetVolume()->GetCopyNo();
   G4String volName = touchable->GetVolume()->GetName() ;

   G4String processName = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() ;

   G4int parentID = aStep->GetTrack()->GetParentID() ;
   //G4cout << "Non si capisce niente " << parentID << G4endl ;

   if(parentID == 0 /*aStep->IsFirstStepInVolume()*/ && (processName == "compt" || processName == "phot" )) {
      if(processName == "compt") G4int procNo = 1 ;
      if(processName == "phot") G4int procNo = 2 ;
      //TrGEMAnalysis::GetInstance()->SaveStepProcess(procNo,volName) ;
      //G4cout << "ParentID is " << parentID << G4endl ;
      //G4cout << "PDG code is " << aStep->GetTrack()->GetParticleDefinition()->GetPDGEncoding() << G4endl ;
      //G4cout << G4endl ;
   }

   G4double edep(0.) ;
   edep = aStep->GetTotalEnergyDeposit() ;
   if(edep == 0.0) { return; }

   //G4cout << "This is the VolCopyNum: " << volCopyNum << " (" << volName << ")" << G4endl ;

   // Find out position along axis Z as a random point 
   // between pre- and post step points.
   // This randomisation allows to smooth histogram profile independently
   // on histogram binning
   G4double z1 = aStep->GetPreStepPoint()->GetPosition().z() ;
   G4double z2 = aStep->GetPostStepPoint()->GetPosition().z() ;
   G4double z  = z1 + G4UniformRand()*(z2 - z1) ;
   //G4cout << "z coordinate " << z << G4endl ;

   // Save energy deposition 
   TrGEMAnalysis::GetInstance()->AddEDep(edep, z) ;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

