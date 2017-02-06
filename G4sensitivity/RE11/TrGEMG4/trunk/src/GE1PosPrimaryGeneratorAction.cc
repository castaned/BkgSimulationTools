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

#include "GE1PosPrimaryGeneratorAction.hh"

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
G4double PosCosXB[17],PosCosYB[17],PosCosXBmax,PosCosYBmax;
G4double PosValXB[17],PosValYB[17],PosValXBmax,PosValYBmax;
//front
G4double PosCosXF[17],PosCosYF[17],PosCosXFmax,PosCosYFmax;
G4double PosValXF[17],PosValYF[17],PosValXFmax,PosValYFmax;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GE1PosPrimaryGeneratorAction::GE1PosPrimaryGeneratorAction(
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
  G4ParticleDefinition* particlen = particleTable -> FindParticle("e+");
 fParticleGun  = new G4ParticleGun(particlen,n_particle);
   
// set energy
 
  fParticleGun->SetParticleEnergy(energy);
  
 G4double CosXtemp,ValXtemp;
 G4double CosYtemp,ValYtemp;
 
  	std::ifstream inX;
	inX.open("/home/alice/RE11/TrGEMG4/trunk/UserData/GE11_e_angx_back.out");

 
		inX >> PosCosXBmax >> PosValXBmax ;
	for(G4int i=0; i<17;i++){
		inX >> CosXtemp >> ValXtemp ;
	PosCosXB[i]=CosXtemp;        
	PosValXB[i]=ValXtemp;        
	}

     inX.close();   
   
   	std::ifstream inXF;
 	inXF.open("/home/alice/RE11/TrGEMG4/trunk/UserData/GE11_e_angx_front.out");


		inXF >> PosCosXFmax >> PosValXFmax ;
	for(G4int i=0; i<17;i++){
		inXF >> CosXtemp >> ValXtemp ;
	PosCosXF[i]=CosXtemp;        
	PosValXF[i]=ValXtemp;        
	}

     inXF.close();   
 
  	std::ifstream inY;
 	inY.open("/home/alice/RE11/TrGEMG4/trunk/UserData/GE11_e_angy_back.out");


		inY >> PosCosYBmax >> PosValYBmax ;
	for(G4int i=0; i<17;i++){
		inY >> CosYtemp >> ValYtemp ;
	PosCosYB[i]=CosYtemp;        
	PosValYB[i]=ValYtemp;        
	}

     inY.close();   
 
   	std::ifstream inYF;
 	inYF.open("/home/alice/RE11/TrGEMG4/trunk/UserData/GE11_e_angy_front.out");


		inYF >> PosCosYFmax >> PosValYFmax ;
	for(G4int i=0; i<17;i++){
		inYF >> CosYtemp >> ValYtemp ;
	PosCosYF[i]=CosYtemp;        
	PosValYF[i]=ValYtemp;        
	}

     inYF.close();   
        
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GE1PosPrimaryGeneratorAction::~GE1PosPrimaryGeneratorAction()
{
  delete fParticleGun;
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GE1PosPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{    

    //set direction
     G4double cosx,cosy;
     G4double valx,valy;
     G4double segnoZ;
     G4int  ifuncX=-1,ifuncY=-1 ;
     CX=0;CY=0;CZ=0;
     G4double fracBehind=0.46;   //fraction of particles coming from behind
     
     segnoZ=G4UniformRand();
     if (segnoZ<fracBehind)  {  //il neutrone viene da dietro nel 6i% dei casi
       
     while (1){
        cosx=-1+G4UniformRand()*2;
        valx=G4UniformRand()*PosValXBmax;

        for(G4int i=0; i<17;i++){
           if(cosx<PosCosXB[i]) {ifuncX=i;break;}
         }
 
         if(valx<PosValXB[ifuncX]) break;

       }

    CX = cosx; 
   
 
     while (1){
        cosy=-1+G4UniformRand()*2;
        valy=G4UniformRand()*PosValYBmax;

        for(G4int i=0; i<17;i++){
           if(cosy<PosCosYB[i]) {ifuncY=i;break;}
         }
         if(valy<PosValYB[ifuncY]  && (cosy*cosy+CX*CX)<1) break;

       }

       CY = cosy; 
       CZ = -sqrt(1-CX*CX-CY*CY);
 }
else {
     while (1){
        cosx=-1+G4UniformRand()*2;
        valx=G4UniformRand()*PosValXFmax;

        for(G4int i=0; i<17;i++){
           if(cosx<PosCosXF[i]) {ifuncX=i;break;}
         }
 
         if(valx<PosValXF[ifuncX]) break;

       }

    CX = cosx; 
   
 
     while (1){
        cosy=-1+G4UniformRand()*2;
        valy=G4UniformRand()*PosValYFmax;

        for(G4int i=0; i<17;i++){
           if(cosy<PosCosYF[i]) {ifuncY=i;break;}
         }
         if(valy<PosValYF[ifuncY]  && (cosy*cosy+CX*CX)<1) break;

       }

       CY = cosy; 
       CZ = sqrt(1-CX*CX-CY*CY);
}

   
  
   fParticleGun->SetParticleMomentumDirection((G4ThreeVector(+CX,+CY,+CZ))); 
  
//Uniform generation on the detector surface
 gX=0;
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
  //create vertex
  //   
  fParticleGun->SetParticlePosition(G4ThreeVector(gX,gY,gZ));
  fParticleGun->GeneratePrimaryVertex(anEvent);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
