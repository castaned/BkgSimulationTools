#ifndef TrGEMEventAction_h
#define TrGEMEventAction_h 1

#include "G4UserEventAction.hh"

class G4Event;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TrGEMEventAction : public G4UserEventAction
{
   public:
      TrGEMEventAction();
      ~TrGEMEventAction();
      void BeginOfEventAction(const G4Event* anEvent);
      void EndOfEventAction(const G4Event* anEvent);

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


