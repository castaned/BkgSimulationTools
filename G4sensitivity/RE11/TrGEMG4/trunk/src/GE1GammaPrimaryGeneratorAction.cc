//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file radioactivedecay/rdecay01/src/IsoPrimaryGeneratorActionScan.cc
/// \brief Implementation of the IsoPrimaryGeneratorActionScan class
//
//
// $Id$
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 

#include "GE1GammaPrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4Geantino.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "TrGEMAnalysis.hh"

#include "G4ParticleGun.hh"
#include "G4Event.hh"
#include <fstream>

//back
G4double GammaCosXB[100],GammaCosYB[100],GammaCosXBmax,GammaCosYBmax;
G4double GammaValXB[100],GammaValYB[100],GammaValXBmax,GammaValYBmax;
//front
G4double GammaCosXF[100],GammaCosYF[100],GammaCosXFmax,GammaCosYFmax;
G4double GammaValXF[100],GammaValYF[100],GammaValXFmax,GammaValYFmax;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GE1GammaPrimaryGeneratorAction::GE1GammaPrimaryGeneratorAction(
      const G4String& particleName,
      G4double energy,
      G4ThreeVector position,
      G4ThreeVector momentumDirection) :
   G4VUserPrimaryGeneratorAction(),
   fParticleGun(0)
{
  G4int n_particle = 1;
//  fParticleGun  = new G4ParticleGun(n_particle);
 G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particlen = particleTable -> FindParticle("gamma");
 fParticleGun  = new G4ParticleGun(particlen,n_particle);
   
// set energy
 
  fParticleGun->SetParticleEnergy(energy);
     
 G4double CosXtemp,ValXtemp;
 G4double CosYtemp,ValYtemp;
 
  	std::ifstream inX;
 	inX.open("/home/alice/RE11/TrGEMG4/trunk/UserData/GE11_ph_angx_back.out");

 
		inX >> GammaCosXBmax >> GammaValXBmax ;
	for(G4int i=0; i<84;i++){
		inX >> CosXtemp >> ValXtemp ;
	GammaCosXB[i]=CosXtemp;        
	GammaValXB[i]=ValXtemp;        
	}

     inX.close();   
   
   	std::ifstream inXF;
	inXF.open("/home/alice/RE11/TrGEMG4/trunk/UserData/GE11_ph_angx_front.out");


		inXF >> GammaCosXFmax >> GammaValXFmax ;
	for(G4int i=0; i<84;i++){
		inXF >> CosXtemp >> ValXtemp ;
	GammaCosXF[i]=CosXtemp;        
	GammaValXF[i]=ValXtemp;        
	}

     inXF.close();   
 
  	std::ifstream inY;
 	inY.open("/home/alice/RE11/TrGEMG4/trunk/UserData/GE11_ph_angy_back.out");


		inY >> GammaCosYBmax >> GammaValYBmax ;
	for(G4int i=0; i<84;i++){
		inY >> CosYtemp >> ValYtemp ;
	GammaCosYB[i]=CosYtemp;        
	GammaValYB[i]=ValYtemp;        
	}

     inY.close();   
 
   	std::ifstream inYF;
	inYF.open("/home/alice/RE11/TrGEMG4/trunk/UserData/GE11_ph_angy_front.out");


		inYF >> GammaCosYFmax >> GammaValYFmax ;
	for(G4int i=0; i<84;i++){
		inYF >> CosYtemp >> ValYtemp ;
	GammaCosYF[i]=CosYtemp;        
	GammaValYF[i]=ValYtemp;        
	}

     inYF.close();   
        
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GE1GammaPrimaryGeneratorAction::~GE1GammaPrimaryGeneratorAction()
{
  delete fParticleGun;
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GE1GammaPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{    

 
     //set direction
     G4double cosx,cosy;
     G4double valx,valy;
     G4double segnoZ;
     G4int  ifuncX=-1,ifuncY=-1 ;
     CX=0;CY=0;CZ=0;
     G4double fracBehind=0.56;   //fraction of particles coming from behind
     
     segnoZ=G4UniformRand();
     if (segnoZ<fracBehind)  {  
       
     while (1){
        cosx=-1+G4UniformRand()*2;
        valx=G4UniformRand()*GammaValXBmax;

        for(G4int i=0; i<84;i++){
           if(cosx<GammaCosXB[i]) {ifuncX=i;break;}
         }
 
         if(valx<GammaValXB[ifuncX]) break;

       }

    CX = cosx; 
   
 
     while (1){
        cosy=-1+G4UniformRand()*2;
        valy=G4UniformRand()*GammaValYBmax;

        for(G4int i=0; i<84;i++){
           if(cosy<GammaCosYB[i]) {ifuncY=i;break;}
         }
         if(valy<GammaValYB[ifuncY]  && (cosy*cosy+CX*CX)<1) break;

       }

       CY = cosy; 
       CZ = -sqrt(1-CX*CX-CY*CY);
 }
else {
     while (1){
        cosx=-1+G4UniformRand()*2;
        valx=G4UniformRand()*GammaValXFmax;

        for(G4int i=0; i<84;i++){
           if(cosx<GammaCosXF[i]) {ifuncX=i;break;}
         }
 
         if(valx<GammaValXF[ifuncX]) break;

       }

    CX = cosx; 
   
 
     while (1){
        cosy=-1+G4UniformRand()*2;
        valy=G4UniformRand()*GammaValYFmax;

        for(G4int i=0; i<84;i++){
           if(cosy<GammaCosYF[i]) {ifuncY=i;break;}
         }
         if(valy<GammaValYF[ifuncY]  && (cosy*cosy+CX*CX)<1) break;

       }

       CY = cosy; 
       CZ = sqrt(1-CX*CX-CY*CY);
}

   
  
   fParticleGun->SetParticleMomentumDirection((G4ThreeVector(+CX,+CY,+CZ))); 

//Uniform generation on the detector surface
 gX = 0;
 gY = 0;
 gZ = 0;
 G4double gXtemp=99999; 
 G4double gYtemp=99999; 
  
 while(1){
  
  gYtemp = G4UniformRand()*1007-503.5;
  gXtemp = G4UniformRand()*453-226.5;  
   if(fabs(gXtemp)<(gYtemp+2002.93)/11.066) break; 
 
 }
 gX=gXtemp;
 gY=gYtemp;


if(segnoZ<fracBehind){ gZ=36.393;}
else {gZ=-1;}
//G4cout<<gX<<"	"<<gY<<G4endl;

  //create vertex
  //   
  fParticleGun->SetParticlePosition(G4ThreeVector(gX,gY,gZ));
  fParticleGun->GeneratePrimaryVertex(anEvent);

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
