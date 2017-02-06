#ifndef TRGEMSTACKINACTION_H
#define TRGEMSTACKINACTION_H 1

#include "globals.hh"
#include "G4UserStackingAction.hh"


class G4Track;

class TrGEMStackingAction : public G4UserStackingAction {

   public:
      // Constructor & Destructor
      TrGEMStackingAction();
      virtual ~TrGEMStackingAction();

      virtual G4ClassificationOfNewTrack ClassifyNewTrack( const G4Track* aTrack );
};

#endif

