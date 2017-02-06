#ifndef GasGapSensitiveDetector_h
#define GasGapSensitiveDetector_h 1

/**
 * @file
 * @brief Defines GasGapSensitiveDetector class.
 */

#include "GasGapHit.hh"
#include "G4VSensitiveDetector.hh"

class G4Step;
class G4TouchableHistory;


/*!
 * \brief Defines sensitve part of HAD calo detector geometry.
 * 
 * Mandatory method
 * /sa ProcessHits()
 * is inkoved at each step in the logical volume
 * to which this SD is attached: the HAD calo.
 */
class GasGapSensitiveDetector : public G4VSensitiveDetector
{
   public:
      /// Constructor
      GasGapSensitiveDetector(G4String SDname);
      /// Destructor
      ~GasGapSensitiveDetector();

   public:
      /// @name methods from base class G4VSensitiveDetector
      //@{
      /// Mandatory base class method : it must to be overloaded:
      G4bool ProcessHits(G4Step *step, G4TouchableHistory *ROhist);

      /// (optional) method of base class G4VSensitiveDetector
      void Initialize(G4HCofThisEvent* HCE);
      /// (optional) method of base class G4VSensitiveDetector
      void EndOfEvent(G4HCofThisEvent* HCE);
      //@}

   private:
      G4double driftDep[9] ;
      G4double driftDepI[9] ;

      G4double transferDep[9] ;
      G4double transferDepI[9] ;
 
      G4double transfer2Dep[9] ;
      G4double transfer2DepI[9] ;

      G4double inductionDep[9] ;
      G4double inductionDepI[9] ;
 
 //for the second TripleGEM in the super chamber
     
      G4double driftDep_B[9] ;
      G4double driftDepI_B[9] ;

      G4double transferDep_B[9] ;
      G4double transferDepI_B[9] ;
 
      G4double transfer2Dep_B[9] ;
      G4double transfer2DepI_B[9] ;

      G4double inductionDep_B[9] ;
      G4double inductionDepI_B[9] ;
 
//     // GARFIELD quantities
//       G4double globalTime ;
//       G4int    pdgCode ;
//       G4double kineticEnergy ;
//       G4double positionX ;
//       G4double positionY ;
//       G4double positionZ ;
//       G4double momentumX ;
//       G4double momentumY ;
//       G4double momentumZ ;
//       G4double momentumDirectionX ;
//       G4double momentumDirectionY ;
//       G4double momentumDirectionZ ;
      G4int    charge ;
      G4bool   neutSensitive ;
      G4bool   elegap ;
      G4bool   chargegap ;
      G4bool   elegap_B ;
      G4bool   chargegap_B ;
      G4double primaryene ;
      G4double primaryposx ;
       G4double primaryposy ;
     G4double primaryposz ;
      G4double zinteraction ;
      G4int    contaPrimary;
      G4int    contaInteraction;
      G4int    contaSec;
      G4int    contaSec_B;
      G4int    contaTrack;
      G4int    contaGar;
     
      std::vector<G4int>  ttTrack;
      std::vector<G4int>  ttTrack_B;
      std::vector<G4int>  ttTrack_Gar;
      std::vector<G4int>  postTrack;

      typedef std::map<G4int,GasGapHit*> hitMap_t; //< Helper mapping layer number with hit
      hitMap_t hitMap;
      GasGapHitCollection* hitCollection;          //< Collection of calorimetric hits

};

#endif
