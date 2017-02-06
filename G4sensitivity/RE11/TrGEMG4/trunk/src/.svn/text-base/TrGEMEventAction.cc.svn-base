#include "TrGEMEventAction.hh"
#include "TrGEMAnalysis.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"

TrGEMEventAction::TrGEMEventAction()
{}

TrGEMEventAction::~TrGEMEventAction()
{}

void TrGEMEventAction::BeginOfEventAction(const G4Event* anEvent)
{

   G4int event_id = anEvent->GetEventID();
   if (event_id % 100000 == 0) 
      G4cout << "Starting Event: " << anEvent->GetEventID() << G4endl ;

   TrGEMAnalysis::GetInstance()->PrepareNewEvent(anEvent) ;
}

void TrGEMEventAction::EndOfEventAction(const G4Event* anEvent)
{
   // get number of stored trajectories
   G4TrajectoryContainer* trajectoryContainer = anEvent->GetTrajectoryContainer();
   G4int n_trajectories = 0;
   if(trajectoryContainer) n_trajectories = trajectoryContainer->entries();

   // periodic printing
   //

   /*if (event_id < 100 || event_id%100 == 0) {
     G4cout << ">>> Event " << anEvent->GetEventID() << G4endl;
     G4cout << "    " << n_trajectories 
     << " trajectories stored in this event." << G4endl;
     }*/

   TrGEMAnalysis::GetInstance()->EndOfEvent(anEvent) ;
}
