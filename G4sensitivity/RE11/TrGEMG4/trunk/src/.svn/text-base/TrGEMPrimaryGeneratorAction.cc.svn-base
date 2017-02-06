#include "TrGEMPrimaryGeneratorAction.hh"

#include "G4GeneralParticleSource.hh"


TrGEMPrimaryGeneratorAction::TrGEMPrimaryGeneratorAction(
      const G4String& particleName,
      G4double energy,
      G4ThreeVector position,
      G4ThreeVector momentumDirection) :
   G4VUserPrimaryGeneratorAction(),
   fParticleGun(0)
{

   /*
      G4int nofParticles = 1 ;
      fParticleGun = new G4ParticleGun(nofParticles) ;

   // default particle kinematic
   G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable() ;
   G4ParticleDefinition* particle = particleTable->FindParticle(particleName) ;
   fParticleGun->SetParticleDefinition(particle) ;
   fParticleGun->SetParticleEnergy(energy) ;
   fParticleGun->SetParticlePosition(position) ;
   fParticleGun->SetParticleMomentumDirection(momentumDirection) ;
   */

   G4GeneralParticleSource *gps = new G4GeneralParticleSource() ;

   gps->GetCurrentSource()->GetEneDist()->SetMonoEnergy(2.0*GeV);
   gps->GetCurrentSource()->GetPosDist()->SetCentreCoords(G4ThreeVector(0.0*cm, 0.0*cm, -5.0*cm));
   gps->GetCurrentSource()->GetAngDist()->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));

   gun = gps;

}


TrGEMPrimaryGeneratorAction::~TrGEMPrimaryGeneratorAction() {

   //delete fParticleGun ;
   delete gun ;

}

void TrGEMPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {

   //fParticleGun->GeneratePrimaryVertex(anEvent) ;
   gun->GeneratePrimaryVertex(anEvent) ;

}
