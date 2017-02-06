#ifndef RE11DetectorConstruction_hh
#define RE11DetectorConstruction_hh

class G4LogicalVolume ;
class G4PhysicalVolume ;


// Standard includes
#include <list>
#include <string>
#include <cmath>

// Geant4 includes
#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"
#include "G4ProductionCuts.hh"
#include "G4Region.hh"
#include "G4Trd.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Torus.hh"

class RE11DetectorConstruction : public G4VUserDetectorConstruction
{
   public :
      // Constructor
      RE11DetectorConstruction() ;
      // Destructor
      ~RE11DetectorConstruction() ;

      void DefineMaterials() ;
      G4VPhysicalVolume* Construct() ;
      G4Trd* Trapezoid(G4String name, G4double width) ;
      void PlaceGeometry(G4RotationMatrix *pRot, G4ThreeVector tlate, G4LogicalVolume *pMotherLogical) ; 

   private :
      G4Material*        fFR4Mat;
      G4Material*        fGasMat;
      G4Material*        fEmptyMat;
      G4Material*        fAirMat;
      G4Material*        fCuMat;
      G4Material*        fKAPTONMat;
      G4Material*        fWaterMat;
      G4Material*	 fAlMat;
      G4Material*	 fMylarMat;
      G4Material*	 fHPLMat;
 //     G4ProductionCuts*  fGasDetectorCuts;
      G4double           tripleGemThinBase; 
      G4double           tripleGemLargeBase;
      G4double           tripleGemHeight;
     
      G4Trd* 			    TrdStrati[21];
      G4LogicalVolume*		    logicStrati[21];
      std::vector<G4Trd*>           trdCollection ;
      std::vector<G4LogicalVolume*> trdLogCollection ;
     
      std::vector<G4Box*>           FebCollection ;
      std::vector<G4LogicalVolume*> FebLogCollection ;
      std::vector<G4Box*>           FebAlCollection ;
      std::vector<G4LogicalVolume*> FebAlLogCollection ;
      std::vector<G4Box*>           FebCapCollection ;
      std::vector<G4LogicalVolume*> FebCapLogCollection ;
      std::vector<G4Box*>           crossBarCollection ;
      std::vector<G4LogicalVolume*> crossBarLogCollection ;

     
      G4Tubs*			    CuTube1;
      G4LogicalVolume*		    CuTube1Log;
      G4Tubs*			    H2OTube1;
      G4LogicalVolume*		    H2OTube1Log;
      G4Tubs*			    CuTube2;
      G4LogicalVolume*		    CuTube2Log;
      G4Tubs*			    H2OTube2;
      G4LogicalVolume*		    H2OTube2Log;
      G4Torus*			    CuTorus;
      G4LogicalVolume*		    CuTorusLog;
      G4Torus*			    H2OTorus;
      G4LogicalVolume*		    H2OTorusLog;
 
      G4Trd*			    AlCover;
      G4LogicalVolume*		    AlCoverLog;
 
      G4Trd*			    FakeBottom;
      G4LogicalVolume*		    FakeBottomLog;
      G4Trd*			    FakeTop;
      G4LogicalVolume*		    FakeTopLog;

};

#endif

