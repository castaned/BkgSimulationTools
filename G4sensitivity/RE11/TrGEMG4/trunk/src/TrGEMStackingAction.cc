#include "TrGEMStackingAction.hh"
#include "TrGEMAnalysis.hh"

#include "G4ClassificationOfNewTrack.hh"
#include "G4Track.hh"

TrGEMStackingAction::TrGEMStackingAction()
{}

TrGEMStackingAction::~TrGEMStackingAction() 
{}

G4ClassificationOfNewTrack TrGEMStackingAction::ClassifyNewTrack( const G4Track * aTrack ) 
{
   // always "urgent" in current applications
   G4ClassificationOfNewTrack result( fUrgent );

   if ( aTrack->GetParentID() > 0 ) // This is a secondary
   {
      TrGEMAnalysis::GetInstance()->AddSecondary(aTrack->GetDefinition());
      //G4String orTouch = aTrack->GetOriginTouchable()->GetVolume()->GetName() ;
      //G4String GasGaps[4] = {"GasGap1", "GasGap2", "GasGap3", "GasGap4"} ;
      //for(G4int i = 0; i < 4; i++) {
      //if(orTouch == GasGaps[i]) // This is a secondary born in GasGap #i 
      //TrGEMAnalysis::GetInstance()->AddGapSecondary(aTrack->GetDefinition(), i);
   }
   else // This is primary
   {
      TrGEMAnalysis::GetInstance()->SetBeam(aTrack->GetDefinition(), aTrack->GetKineticEnergy());
   }


   return result;

}

