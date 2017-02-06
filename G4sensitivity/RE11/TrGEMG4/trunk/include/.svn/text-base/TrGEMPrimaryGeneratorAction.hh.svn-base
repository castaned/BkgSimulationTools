#ifndef TrGEMPrimaryGeneratorAction_h
#define TrGEMPrimaryGeneratorAction_h

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4GeneralParticleSource.hh"

class TrGEMPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {

   public :
      TrGEMPrimaryGeneratorAction(
	    const G4String& particleName = "gamma",
	    G4double energy = 500*MeV,
	    G4ThreeVector position = G4ThreeVector(0,0,0),
	    G4ThreeVector momentumDirection = G4ThreeVector(0,0,1)) ;
      
      ~TrGEMPrimaryGeneratorAction() ;

      // methods
      void GeneratePrimaries(G4Event*) ;

   private :
      // data members
      G4ParticleGun* fParticleGun; // pointer to a G4 service class
      G4GeneralParticleSource *gun ;

};

#endif
