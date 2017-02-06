#include "G4TouchableHistory.hh"
#include "G4Step.hh"
#include "G4HCofThisEvent.hh"
#include "G4HCtable.hh"
#include "G4UnitsTable.hh"

#include "TrGEMAnalysis.hh"
#include "GasGapSensitiveDetector.hh"
#include "GasGapHit.hh"

   GasGapSensitiveDetector::GasGapSensitiveDetector(G4String SDname)
: G4VSensitiveDetector(SDname),
   driftDep(0.),
   transferDep(0.),
   globalTime(0.),
   pdgCode(0),
   kineticEnergy(0.),
   positionX(0.),
   positionY(0.),
   positionZ(0.),
   momentumX(0.),
   momentumY(0.),
   momentumZ(0.),
   momentumDirectionX(0.),
   momentumDirectionY(0.),
   momentumDirectionZ(0.),
   charge(0),
   neutSensitive(false)

{
   G4cout << "*************************************" << G4endl ;
   G4cout << "*** Creating SD with name: "<< SDname << " ***" << G4endl ;  
   G4cout << "*************************************" << G4endl ;

   // Declaration of the hit collection name
   G4String myCollectionName = "GasGapHitCollection" ;
   collectionName.insert( myCollectionName) ;

}


GasGapSensitiveDetector::~GasGapSensitiveDetector()
{}

G4bool GasGapSensitiveDetector::ProcessHits(G4Step *step, G4TouchableHistory *)
{
   //This method is called every time a G4Step is performed in the logical volume
   //to which this SD is attached: the GAS GAP.

   //To identify where the step is we use the touchable navigation,
   //Remember we need to use PreStepPoint!
   G4TouchableHandle touchable = step->GetPreStepPoint()->GetTouchableHandle();
   G4int copyNo = touchable->GetVolume(0)->GetCopyNo();
   G4int layerIndex = copyNo;
   G4String volName = touchable->GetVolume(0)->GetName();
   //We get now the energy deposited by this step
   G4double edep = step->GetTotalEnergyDeposit() ;

   if(volName == "GasGap1") {
      // we're in drift gap
      driftDep += edep ;

      // if any particle makes a 1st step inside Drift Gap
      G4StepPoint* point1 = step->GetPreStepPoint() ;
      //if(point1->GetStepStatus() == fGeomBoundary) 
      // special algorithm for neutron sensitivity
      charge = step->GetTrack()->GetParticleDefinition()->GetPDGCharge() ;
      if(charge != 0) neutSensitive = true ;
   }

   if(volName == "GasGap2") {
      // we're in transfer1 gap
      transferDep += edep ;
      // special algorithm for neutron sensitivity
      charge = step->GetTrack()->GetParticleDefinition()->GetPDGCharge() ; 
      if(charge != 0) neutSensitive = true ;
   }

   //This line is used to store in Analysis class the energy deposited in this layer
   //The Analysis class will sum up this edep to the current event total energy in this layer
   //Pass the number directly to the Analysis manager. No Hits objects are created in 
   //this case
   //Analysis::GetInstance()->AddEDepHad(layerIndex,edep);


   //check if edep is from primary or secondary:
   G4String isPri = step->GetTrack()->GetTrackID() == 1 ? "Yes" : "No";

   // Tricks to implement hits 
   hitMap_t::iterator it = hitMap.find(layerIndex) ;
   GasGapHit* aHit = 0 ;
   if( it != hitMap.end() ) {
      aHit = it->second ;
   }
   else {
      aHit = new GasGapHit(layerIndex) ;
      hitMap.insert( std::make_pair(layerIndex, aHit) ) ;
      hitCollection->insert(aHit) ;
   }
   aHit->AddEdep(edep) ;

   return true;
   }

   void GasGapSensitiveDetector::Initialize(G4HCofThisEvent* HCE)
   {
      hitCollection = new GasGapHitCollection(GetName(), collectionName[0]) ;
      static G4int HCID = -1 ;
      if(HCID<0) HCID = GetCollectionID(0) ; // <<-- this is to get an ID for collectionName[0]
      HCE->AddHitsCollection(HCID, hitCollection) ;

      // Reset map of hits
      hitMap.clear() ;
   }

   void GasGapSensitiveDetector::EndOfEvent(G4HCofThisEvent*)
   {
      G4double ionizationPotential = 0.45*26*eV + 0.15*33*eV + 0.4*54*eV ; // Ar:CO2:CF4 (45:15:40)
      // Updated peer-reviewed values. Effective energy to generate a pair. (Sauli '77, Sharma)  
      // G4double ionizationPotential = 0.45*15.8*eV + 0.15*13.78*eV + 0.4*15.9*eV ; // Ar:CO2:CF4 (45:15:40)
      // These are values previously used. They represent the minimum ionization potential.
      G4int factor = 5 ;
      if(driftDep > factor*ionizationPotential) {
	 TrGEMAnalysis::GetInstance()->SetDriftSensitivity(driftDep) ;
	 //G4cout << "The Drift Gap is sensitive (" << G4BestUnit(driftDep,"Energy") << ")" << G4endl ; 
      }
      else if(transferDep > factor*ionizationPotential) { 
	 TrGEMAnalysis::GetInstance()->SetTransferSensitivity(transferDep) ;
	 //G4cout << "The Transfer Gap 1 is sensitive (" << G4BestUnit(transferDep,"Energy") << ")" << G4endl ;
      }

      driftDep = 0. ;
      transferDep = 0. ;

      //hitCollection->PrintAllHits() ;

      TrGEMAnalysis::GetInstance()->SetNeutronSensitivity(neutSensitive) ;
      // resetting neutron sensitivity
      neutSensitive = false ;

   }

