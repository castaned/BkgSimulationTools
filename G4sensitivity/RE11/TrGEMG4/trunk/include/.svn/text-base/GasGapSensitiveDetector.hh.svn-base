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
      G4double driftDep ;
      G4double transferDep ;
      // GARFIELD quantities
      G4double globalTime ;
      G4int    pdgCode ;
      G4double kineticEnergy ;
      G4double positionX ;
      G4double positionY ;
      G4double positionZ ;
      G4double momentumX ;
      G4double momentumY ;
      G4double momentumZ ;
      G4double momentumDirectionX ;
      G4double momentumDirectionY ;
      G4double momentumDirectionZ ;
      G4int    charge ;
      G4bool   neutSensitive ;

      typedef std::map<G4int,GasGapHit*> hitMap_t; //< Helper mapping layer number with hit
      hitMap_t hitMap;
      GasGapHitCollection* hitCollection;          //< Collection of calorimetric hits

};

#endif
