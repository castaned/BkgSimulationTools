#include "RE11DetectorConstruction.hh"
#include "GasGapSensitiveDetector.hh"

#include "G4NistManager.hh"
#include "G4SDManager.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Torus.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4GeometryManager.hh"
//#include "G4PhysicalVolumeStore.hh"
//#include "G4LogicalVolumeStore.hh"
//#include "G4SolidStore.hh"
#include "G4VisAttributes.hh"
#include "G4PVPlacement.hh"
#include "G4UnitsTable.hh"

RE11DetectorConstruction::RE11DetectorConstruction() :
   fFR4Mat(0), fGasMat(0), fEmptyMat(0), fAirMat(0),
   fCuMat(0),fKAPTONMat(0),fWaterMat(0),fAlMat(0),fMylarMat(0),fHPLMat(0),
   tripleGemThinBase(0), tripleGemLargeBase(0), tripleGemHeight(0)
    
{

   tripleGemThinBase  = 271.0*mm ;
   tripleGemLargeBase = 453.0*mm ;
   tripleGemHeight    = 1007.0*mm ;

//    G4double cut = 1*mm ;
//    fGasDetectorCuts = new G4ProductionCuts() ;
//    fGasDetectorCuts->SetProductionCut(cut,"gamma") ;
//    fGasDetectorCuts->SetProductionCut(cut,"e-") ;
//    fGasDetectorCuts->SetProductionCut(cut,"e+") ;
//    fGasDetectorCuts->SetProductionCut(cut,"proton") ;

}

RE11DetectorConstruction::~RE11DetectorConstruction() {

 //  delete fGasDetectorCuts ;

}

void RE11DetectorConstruction::DefineMaterials() {

   G4NistManager* manager = G4NistManager::Instance() ;
   // define Elements
   G4Element* elC  = manager->FindOrBuildElement(6);
   G4Element* elF  = manager->FindOrBuildElement(9);
   G4Element* elSi = manager->FindOrBuildElement(14);
   G4Element* elO  = manager->FindOrBuildElement(8);
   G4Element* elH  = manager->FindOrBuildElement(1);
   G4Element* elS  = manager->FindOrBuildElement(16);

   // define Materials
   G4Material *Cu = G4NistManager::Instance()->FindOrBuildMaterial("G4_Cu") ;
   G4Material *Al = G4NistManager::Instance()->FindOrBuildMaterial("G4_Al") ;
   G4Material *KAPTON = G4NistManager::Instance()->FindOrBuildMaterial("G4_KAPTON");
   G4Material* Mylar = G4NistManager::Instance()->FindOrBuildMaterial("G4_MYLAR");
   fCuMat = Cu;
   fKAPTONMat = KAPTON;
   fAlMat = Al;
   fMylarMat= Mylar;
   
   G4int numel(0), natoms(0) ;
   G4double density(0.), temperature(0.), pressure(0.), fractionMass(0.)  ;
   G4String name, symbol ;
   
   G4Material* SiO2 =  new G4Material("quartz",density= 2.200*g/cm3, numel=2);
   SiO2->AddElement(elSi, natoms=1);
   SiO2->AddElement(elO , natoms=2);

   //from http://www.physi.uni-heidelberg.de/~adler/TRD/TRDunterlagen/RadiatonLength/tgc2.htm
  //Epoxy (for FR4 )
   density = 1.2*g/cm3;
   G4Material* Epoxy = new G4Material("Epoxy" , density, numel=2);
   Epoxy->AddElement(elH, natoms=2);
   Epoxy->AddElement(elC, natoms=2);
  
   //FR4 (Glass + Epoxy)
   density = 1.86*g/cm3; 
   G4Material* FR4 = new G4Material("FR4"  , density, numel=2);
   FR4->AddMaterial(Epoxy, fractionMass=0.472);
   FR4->AddMaterial(SiO2, fractionMass=0.528);
   fFR4Mat = FR4;

   //High Pressure Laminate HPL   
   G4Material* HPL = new G4Material(name = "HPL", density= 1.4*g/cm3, numel=3);
   HPL->AddMaterial(G4NistManager::Instance()->FindOrBuildMaterial("G4_H"), fractionMass = 5.74*perCent);
   HPL->AddMaterial(G4NistManager::Instance()->FindOrBuildMaterial("G4_C"), fractionMass = 77.46*perCent);
   HPL->AddMaterial(G4NistManager::Instance()->FindOrBuildMaterial("G4_O"), fractionMass = 16.8*perCent);
   fHPLMat = HPL ;

   //Air   
   G4Material* Air = new G4Material(name = "Air", density= 1.29*mg/cm3, numel=2);
    Air->AddMaterial(G4NistManager::Instance()->FindOrBuildMaterial("G4_N"), fractionMass = 70.*perCent);
    Air->AddMaterial(G4NistManager::Instance()->FindOrBuildMaterial("G4_O"), fractionMass = 30.*perCent);
   fAirMat = Air ;

   // gases at STP conditions 
   G4Material* Argon = manager->FindOrBuildMaterial("G4_Ar");
   G4Material* CarbonDioxide = manager->FindOrBuildMaterial("G4_CARBON_DIOXIDE");
   G4Material* empty = manager->FindOrBuildMaterial("G4_Galactic");
   fEmptyMat = empty ;

   // CF4 must be defined by hand
   //G4int numel(0) ;
   //G4double density(0.), temperature(0.), pressure(0.) ;
   //G4String name, symbol ;
   G4Material* CF4 = new G4Material(name="CF4", density=0.003884*g/cm3, numel=2, kStateGas, temperature = 273.15*kelvin, pressure=1.0*atmosphere);
   CF4->AddElement(elC, 1) ;
   CF4->AddElement(elF, 4) ; 

   // Ar:CO2 (70:30) @ STP conditions
   G4double mixtureDensity = (Argon->GetDensity() * 70/100.0 + CarbonDioxide->GetDensity() * 30/100.0) ;
   G4Material *ArCO2 = new G4Material("Ar/CO2",mixtureDensity,2) ;
   ArCO2->AddMaterial(Argon, 0.7) ;
   ArCO2->AddMaterial(CarbonDioxide, 0.3) ;

   // Ar:CO2:CF4 (45:15:40) @ STP conditions
   mixtureDensity = (Argon->GetDensity() * 45/100.0 + CarbonDioxide->GetDensity() * 15/100.0 + CF4->GetDensity() * 40/100.0) ;
   G4Material *ArCO2CF4 = new G4Material("Ar/CO2/CF4",mixtureDensity,3) ;
   ArCO2CF4->AddMaterial(Argon, 0.45) ;
   ArCO2CF4->AddMaterial(CarbonDioxide,0.15) ;
   ArCO2CF4->AddMaterial(CF4,0.40) ;



  // RPC mixture gas components
   // iso-Butane (methylpropane), STP
   density = 2.67*mg/cm3;
   G4Material* isobutane = new G4Material(name = "isoC4H10", density, numel=2) ;
   isobutane->AddElement(elC,4);
   isobutane->AddElement(elH,10);

   // Freon
   density = 4.55*mg/cm3;
   G4Material* C2H2F4 = new G4Material(name = "Freon", density, numel=3) ;
   C2H2F4->AddElement(elC, natoms=2);
   C2H2F4->AddElement(elH, natoms=2);
   C2H2F4->AddElement(elF, natoms=4);
 
   // esafluoruro di zolfo SF6
   density = 6.14*mg/cm3;
   G4Material* SF6 = new G4Material(name = "SF6", density, numel=2) ;
   SF6->AddElement(elS, natoms=1);
   SF6->AddElement(elF, natoms=6);


    density = 3.569*mg/cm3;
   G4Material* RPCgas = new G4Material(name = "RPCGas", density, numel=3) ;
   RPCgas->AddMaterial(isobutane, fractionMass = 4.5* perCent) ;
   RPCgas->AddMaterial(C2H2F4, fractionMass = 95.2* perCent) ;
   RPCgas->AddMaterial(SF6, fractionMass = 0.3* perCent) ;

   // Choice of the gas
   fGasMat = RPCgas ;
  
  density = 1.000*g/cm3;
  G4Material* H2O = new G4Material(name="Water",density,2);
  H2O->AddElement(elH, natoms=2);
  H2O->AddElement(elO, natoms=1);
  fWaterMat=H2O;
}

G4VPhysicalVolume* RE11DetectorConstruction::Construct() {


   // Cleanup old geometry
   G4GeometryManager::GetInstance()->OpenGeometry();

   //G4GeometryManager::GetInstance()->OpenGeometry();
   //G4PhysicalVolumeStore::GetInstance()->Clean();
   //G4LogicalVolumeStore::GetInstance()->Clean();
   //G4SolidStore::GetInstance()->Clean();

   // Define all materials and set global variables
   DefineMaterials() ;

   // SD Manager 
   G4SDManager* sdman = G4SDManager::GetSDMpointer() ;

   G4double worldSizeX = 1.*m;
   G4double worldSizeY = 1.*m;
   G4double worldSizeZ = 1.*m;

   // Rotation Matrix for layers
   G4RotationMatrix* rotationPlacement = new G4RotationMatrix() ;
   rotationPlacement->rotateY(M_PI / 2.0) ;
   rotationPlacement->rotateX(M_PI / 2.0) ;

   // Visual attributes
   G4VisAttributes *cathodeAttributes = new G4VisAttributes(G4Color::Grey()) ;
   //cathodeAttributes->SetForceWireframe(true) ;
   G4VisAttributes *g10Attributes = new G4VisAttributes(G4Color::White()) ;
   //g10Attributes->SetForceWireframe(true) ;
   G4VisAttributes *gasAttributes = new G4VisAttributes(G4Color::Red()) ;
   //gasAttributes->SetForceWireframe(true) ;
   G4VisAttributes *gemAttributes = new G4VisAttributes(G4Color::Green()) ;
   //gemAttributes->SetForceWireframe(true) ;
   G4VisAttributes *insAttributes = new G4VisAttributes(G4Color::Blue()) ;
  //insAttributes->SetForceWireframe(true) ;


   // World definition and placement
   G4Box* worldBox = new G4Box("WorldBox", worldSizeX, worldSizeY, worldSizeZ) ;
   G4LogicalVolume* worldLog = new G4LogicalVolume(worldBox, fEmptyMat, "WorldLog") ;
   // Set visual attributes
   G4VisAttributes *worldAttributes = new G4VisAttributes ;
   worldAttributes->SetVisibility(false) ;
   worldLog->SetVisAttributes(worldAttributes) ;

   G4VPhysicalVolume* worldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLog, "WorldSpace", 0, false, 0) ;

// 
// //____________________________________________________________________________________________________________
 	        
		
	//CONTINOUS MATERIALS
		std::string NomeStrati[17]= 
		{
		"MylarElecIns1","totMylarHV1","CopperGND1",     
		"HPL1",					        		//HPL
		"GasGap1",							//GasGap1
		"HPL2",					       			//HPL
		"totMylarGND1","CuStrips","FR4Strips","totMylarGND2",		//Strips
		"HPL3",					        		//HPL
		"GasGap2",		                        		//GasGap2
		"HPL4",					        		//HPL
		"CopperGND2","totMylarHV2","MylarElecIns2",     		//Readout Board
		"AlPanel"  							//Aluminum Panel
		};
             
	        std::string NomeStratiLog[17];
		
		for(size_t A=0; A<17; A++) { 
		    NomeStratiLog[A]=NomeStrati[A]+"Log";
		}
		
		G4Material* MatStrati[17] = 
		{
		fMylarMat,fMylarMat,fCuMat,	
		fHPLMat, 	   		
		fGasMat,	
		fHPLMat, 	   		
		fMylarMat,fCuMat,fFR4Mat,fMylarMat,	
		fHPLMat, 	   		
		fGasMat,	
		fHPLMat, 	   		
		fCuMat,fMylarMat,fMylarMat,	
		fAlMat
		};
		
		G4double spessoreStrati[17]=
		{
		0.2*mm,0.4*mm,0.038*mm,	
		2*mm, 	   		
		2*mm,	
		2*mm, 	   		
		0.2*mm,0.017*mm,0.4*mm,0.2*mm,	
		2*mm, 	   		
		2*mm,	
		2*mm, 	   		
		0.038*mm,0.4*mm,0.2*mm,	
		5*mm
		};
		
		

		GasGapSensitiveDetector* sensitive = new GasGapSensitiveDetector("/GasGap") ;
		sdman->AddNewDetector(sensitive) ;
		
		G4Trd* strato; G4Box* box;
		G4LogicalVolume* logicStrato;
		
		for(G4int lyr=0;lyr<17;lyr++){
			
			strato=Trapezoid(NomeStrati[lyr], spessoreStrati[lyr]);
		        logicStrato = new G4LogicalVolume (strato, MatStrati[lyr],NomeStratiLog[lyr]);   
			logicStrato->SetVisAttributes(new G4VisAttributes(*gemAttributes)) ;
			trdCollection.push_back(strato) ;
		        trdLogCollection.push_back(logicStrato) ;
			trdLogCollection[lyr]->SetSensitiveDetector(sensitive) ;		       
}
 

//FEB, FEB cooling caps & FEB Al Faraday cage

 G4double FebThick=1.6*mm;
 G4double FebAlThick=1*mm;
 G4double FebCapThick=2*mm;

//dimensioni aera feb
 G4double FebWidth[4]={200*mm, 200*mm,  200*mm, 108*mm};
 G4double FebEigth[4]={177*mm, 177*mm,  177*mm, 202*mm};

//dimensioni aera feb cap e faraday cage (alluminuo e rame)
 G4double FebCapWidth[4]={225.4*mm, 225.4*mm, 225.4*mm, 183*mm};
 G4double FebCapEigth[4]={130*mm, 130*mm, 130*mm, 208*mm};


//Nome dei volumi
 std::string NomeFeb[4]= {"Feb1","Feb2","Feb3","Feb4"};
 std::string NomeFebLog[4]= {"Feb1Log","Feb2Log","Feb3Log","Feb4Log"};
 std::string NomeFebCap[4];
 std::string NomeFebCapLog[4] ;
 std::string NomeFebAl[4];
 std::string NomeFebAlLog[4] ;
 for(size_t A=0; A<4; A++) { 
       NomeFebCap[A]=NomeFeb[A]+"Cap";
       NomeFebCapLog[A]=NomeFeb[A]+"CapLog";
       NomeFebAl[A]=NomeFeb[A]+"Al";
       NomeFebAlLog[A]=NomeFeb[A]+"AlLog";
 }
  
 //FEB Al Faraday cage
 for(G4int cool=0;cool<4;cool++){
        box= new G4Box(NomeFebAl[cool] , FebAlThick/2, FebCapWidth[cool]/2 , FebCapEigth[cool]/2) ;
 	logicStrato = new G4LogicalVolume(box, fAlMat,NomeFebAlLog[cool] ) ;
  	logicStrato->SetVisAttributes(new G4VisAttributes(*insAttributes)) ;
  	FebAlCollection.push_back(box) ;
  	FebAlLogCollection.push_back(logicStrato) ;
  	logicStrato->SetSensitiveDetector(sensitive) ;
  }
 //FEB Cu Caps
 for(G4int cool=0;cool<4;cool++){
        box= new G4Box(NomeFebCap[cool] , FebCapThick/2, FebCapWidth[cool]/2 , FebCapEigth[cool]/2) ;
 	logicStrato = new G4LogicalVolume(box, fCuMat,NomeFebCapLog[cool] ) ;
  	logicStrato->SetVisAttributes(new G4VisAttributes(*cathodeAttributes)) ;
  	FebCapCollection.push_back(box) ;
  	FebCapLogCollection.push_back(logicStrato) ;
  	logicStrato->SetSensitiveDetector(sensitive) ;
  }
 //FEB 
 for(G4int cool=0;cool<4;cool++){
        box= new G4Box(NomeFeb[cool] , FebThick/2, FebWidth[cool]/2 , FebEigth[cool]/2) ;
 	logicStrato = new G4LogicalVolume(box, fFR4Mat,NomeFebLog[cool] ) ;
  	logicStrato->SetVisAttributes(new G4VisAttributes(*gasAttributes)) ;
  	FebCollection.push_back(box) ;
  	FebLogCollection.push_back(logicStrato) ;
  	logicStrato->SetSensitiveDetector(sensitive) ;
  }


//AL cross bars

 G4double crossBarThick=5*mm;
 
//dimensioni aera
 G4double crossBarWidth[4]={440*mm, 380*mm, 332*mm, 310*mm};
 G4double crossBarEigth[4]={40*mm, 40*mm, 40*mm, 40*mm};


//Nome dei volumi
 std::string NomeCrossBar[4]= {"crossBar1","crossBar2","crossBar3","crossBar4"};
 std::string NomeCrossBarLog[4]= {"crossBar1Log","crossBar2Log","crossBar3Log","crossBar4Log"};
  
 for(G4int cool=0;cool<4;cool++){
        box= new G4Box(NomeCrossBar[cool] ,crossBarThick/2, crossBarWidth[cool]/2 , crossBarEigth[cool]/2) ;
 	logicStrato = new G4LogicalVolume(box, fAlMat, NomeCrossBarLog[cool] ) ;
  	logicStrato->SetVisAttributes(new G4VisAttributes(*insAttributes)) ;
  	crossBarCollection.push_back(box) ;
  	crossBarLogCollection.push_back(logicStrato) ;
  	logicStrato->SetSensitiveDetector(sensitive) ;
  }
  
  //COOLING PIPES
  
 CuTube1 = new G4Tubs("CuTube1",2.5*mm,3*mm,438.5*mm,0., 2*pi);
 CuTube1Log=new G4LogicalVolume(CuTube1, fCuMat,"CuTube1Log" ) ;    
 CuTube1Log->SetVisAttributes(new G4VisAttributes(*gasAttributes)) ;
 CuTube1Log->SetSensitiveDetector(sensitive) ;
 
 H2OTube1 = new G4Tubs("H2OTube1",0*mm,2.5*mm,438.5*mm,0., 2*pi);
 H2OTube1Log=new G4LogicalVolume(H2OTube1, fWaterMat,"H2OTube1Log" ) ;    
 H2OTube1Log->SetVisAttributes(new G4VisAttributes(*g10Attributes)) ;
 H2OTube1Log->SetSensitiveDetector(sensitive) ;

 CuTube2 = new G4Tubs("CuTube2",2.5*mm,3*mm,438.5*mm,0., 2*pi);
 CuTube2Log=new G4LogicalVolume(CuTube2, fCuMat,"CuTube2Log" ) ;    
 CuTube2Log->SetVisAttributes(new G4VisAttributes(*gasAttributes)) ;
 CuTube2Log->SetSensitiveDetector(sensitive) ;
 
 H2OTube2 = new G4Tubs("H2OTube2",0*mm,2.5*mm,438.5*mm,0., 2*pi);
 H2OTube2Log=new G4LogicalVolume(H2OTube2, fWaterMat,"H2OTube2Log" ) ;    
 H2OTube2Log->SetVisAttributes(new G4VisAttributes(*g10Attributes)) ;
 H2OTube2Log->SetSensitiveDetector(sensitive) ;
  
 CuTorus = new G4Torus("CuTorus",2.5*mm,3*mm, tripleGemThinBase/2-CuTube1->GetRMax()-70, 0, pi);
 CuTorusLog=new G4LogicalVolume(CuTorus, fCuMat,"CuTorusLog" ) ;    
 CuTorusLog->SetVisAttributes(new G4VisAttributes(*gasAttributes)) ;
 CuTorusLog->SetSensitiveDetector(sensitive) ;
 
 H2OTorus = new G4Torus("H2OTorus",0*mm,2.5*mm, tripleGemThinBase/2-H2OTube1->GetRMax()-70, 0, pi);
 H2OTorusLog=new G4LogicalVolume(H2OTorus, fWaterMat,"H2OTorusLog" ) ;    
 H2OTorusLog->SetVisAttributes(new G4VisAttributes(*g10Attributes)) ;
 H2OTorusLog->SetSensitiveDetector(sensitive) ;
 
 //Al Cover
 AlCover=Trapezoid("AlCover", 0.5*mm);
 AlCoverLog = new G4LogicalVolume (AlCover, fAlMat,"AlCoverLog");   
 AlCoverLog->SetVisAttributes(new G4VisAttributes(*g10Attributes)) ;
 AlCoverLog->SetSensitiveDetector(sensitive) ;

 //FAKE DETECTORS
 FakeBottom=Trapezoid("FakeBottom", 0.1*mm);
 FakeBottomLog = new G4LogicalVolume (FakeBottom, fAirMat,"FakeBottomLog");   
 FakeBottomLog->SetVisAttributes(new G4VisAttributes(*g10Attributes)) ;
 FakeBottomLog->SetSensitiveDetector(sensitive) ;

 FakeTop=Trapezoid("FakeTop", 0.1*mm);
 FakeTopLog = new G4LogicalVolume (FakeTop, fAirMat,"FakeTopLog");   
 FakeTopLog->SetVisAttributes(new G4VisAttributes(*g10Attributes)) ;
 FakeTopLog->SetSensitiveDetector(sensitive) ;
   
 PlaceGeometry(rotationPlacement,G4ThreeVector(0.,0.,0.),worldLog) ;

   return worldPhys ;

}

G4Trd* RE11DetectorConstruction::Trapezoid(G4String name, G4double width) {
   G4Trd* shape = new G4Trd(name,
	 width/2, width/2,
	 tripleGemThinBase/2,
	 tripleGemLargeBase/2,
	 tripleGemHeight/2) ;
   return shape ;
}

void RE11DetectorConstruction::PlaceGeometry(G4RotationMatrix *pRot, G4ThreeVector tlate, G4LogicalVolume* pMotherLogical) {
   
 //  G4double padEigth=51*mm;
   G4double XTranslation = 0 ;
   G4double space[4] = {70*mm,46.6*mm, 77.6*mm, 99.8*mm};  //space between FEBS
   G4double crossBarSpace[4] = {83.5*mm,310*mm,199*mm,149*mm};  //space between crossbars
   G4double ZTranslation = tripleGemHeight/2 - space[0] - FebCapCollection.at(0)->GetZHalfLength()/2;
   G4int cpN=0;
   G4ThreeVector position;
//---------------------------------------------------------------------------------fake bottom
      
       XTranslation += FakeBottom->GetXHalfLength1() ;
       position = tlate + G4ThreeVector(XTranslation,0,0).transform(G4RotationMatrix(*pRot).inverse()) ;
       G4cout << "Volume ( 0 ) " << FakeBottom->GetName() << " the position is " <<  G4BestUnit(XTranslation,"Length") << G4endl;
 	
       new G4PVPlacement(pRot,
       position,
       FakeBottomLog,
       "FakeBottom",
       pMotherLogical,
       false,
       cpN) ;
 	XTranslation += FakeBottom->GetXHalfLength1() ;
 	cpN++;
   
     //---------------------------------------------------------------------------------AlCover
     
     XTranslation += AlCover->GetXHalfLength1() ;
     position = tlate + G4ThreeVector(XTranslation,0,0).transform(G4RotationMatrix(*pRot).inverse()) ;
     G4cout << "Volume ( 0 ) " << AlCover->GetName() << " the position is " <<  G4BestUnit(XTranslation,"Length") << G4endl;
      
     new G4PVPlacement(pRot,
     position,
     AlCoverLog,
     "AlCover",
     pMotherLogical,
     false,
     cpN) ;
      XTranslation += AlCover->GetXHalfLength1() ;
      cpN++;
     
  
  //---------------------------------------------------------------------------------FEB Al Faraday Cage
      XTranslation += FebAlCollection.at(0)->GetXHalfLength() ;
      
      for(size_t i=0 ; i<FebAlCollection.size() ; i++) {
	G4ThreeVector position = tlate + G4ThreeVector(XTranslation,0, ZTranslation).transform(G4RotationMatrix(*pRot).inverse()) ;
       G4cout << "Volume (" << cpN << ") " << FebAlCollection.at(i)->GetName() << " the position is " <<  G4BestUnit(XTranslation,"Length") << G4endl ; 
      new G4PVPlacement(pRot,
      position,
      FebAlLogCollection.at(i),
      FebAlCollection.at(i)->GetName(),
      pMotherLogical,
      false,
      cpN) ;
      cpN++;
	if(i!=FebAlCollection.size()-1){ ZTranslation -= FebAlCollection.at(i)->GetZHalfLength() +
			FebAlCollection.at(i+1)->GetZHalfLength() +
		space[i+1];}
	else {ZTranslation=tripleGemHeight/2 - space[0] - FebCapCollection.at(0)->GetZHalfLength()/2;} 
   }
      XTranslation += FebAlCollection.at(0)->GetXHalfLength() ;
   //---------------------------------------------------------------------------------FEB 
     
      XTranslation += FebCollection.at(0)->GetXHalfLength() ;
      
      for(size_t i=0 ; i<FebCollection.size() ; i++) {
	G4ThreeVector position = tlate + G4ThreeVector(XTranslation,0, ZTranslation).transform(G4RotationMatrix(*pRot).inverse()) ;
       G4cout << "Volume (" << cpN << ") " << FebCollection.at(i)->GetName() << " the position is " <<  G4BestUnit(XTranslation,"Length") << G4endl ; 
      new G4PVPlacement(pRot,
      position,
      FebLogCollection.at(i),
      FebCollection.at(i)->GetName(),
      pMotherLogical,
      false,
      cpN) ;
      cpN++;
	if(i!=FebCollection.size()-1){ ZTranslation -= FebCapCollection.at(i)->GetZHalfLength() +
			FebCapCollection.at(i+1)->GetZHalfLength() +
		space[i+1];}
   //	else {ZTranslation=tripleGemHeight/2 - crossBarSpace[0] - crossBarCollection.at(0)->GetZHalfLength()/2;}       //prepare Ztranslation for crossbars
	else {ZTranslation=tripleGemHeight/2  - CuTube1->GetDz();}     //prepare Ztranslation for coolingpipe
   }
      XTranslation += FebCollection.at(0)->GetXHalfLength() ;
   //---------------------------------------------------------------------------------cooling pipes
     
     XTranslation += CuTube1->GetRMax() ;
     //COOLING PIPES
      G4double PipeY=-tripleGemThinBase/2+CuTube1->GetRMax()+70;
      G4cout << "Volume (  " << cpN <<" ) CuTube1" << " the position is " <<  G4BestUnit(XTranslation,"Length") << G4endl ; 
      position = tlate + G4ThreeVector(XTranslation,PipeY,ZTranslation).transform(G4RotationMatrix(*pRot).inverse()) ;
       new G4PVPlacement(pRot,
      position,
      CuTube1Log,
      "CuTube1",
      pMotherLogical,
      false,
      cpN) ;
       cpN++; 
      G4cout << "Volume (  " << cpN <<" )H2OTube1" << " the position is " <<  G4BestUnit(XTranslation,"Length") << G4endl ; 
       new G4PVPlacement(pRot,
      position,
      H2OTube1Log,
      "H2OTube1",
      pMotherLogical,
      false,
      cpN) ;
      cpN++; 
      G4cout << "Volume (  " << cpN <<" )CuTube2" << " the position is " <<	G4BestUnit(XTranslation,"Length") << G4endl ; 
    
       position = tlate + G4ThreeVector(XTranslation,-PipeY, ZTranslation).transform(G4RotationMatrix(*pRot).inverse()) ;
       new G4PVPlacement(pRot,
      position,
      CuTube2Log,
      "CuTube2",
      pMotherLogical,
      false,
      cpN) ;
      cpN++; 
       
      G4cout << "Volume (  " << cpN <<" )H2OTube2" << " the position is " <<  G4BestUnit(XTranslation,"Length") << G4endl ; 
       new G4PVPlacement(pRot,
      position,
      H2OTube2Log,
      "H2OTube2",
      pMotherLogical,
      false,
      cpN) ;
       cpN++; 
   
      G4RotationMatrix* rotationTorus = new G4RotationMatrix() ;
      //rotationPlacement->rotateZ(M_PI / 2.0) ;
      rotationTorus->rotateX(M_PI ) ;
    
       G4cout << "Volume (  " << cpN <<" )CuTorus" << " the position is " <<  G4BestUnit(XTranslation,"Length") << G4endl ; 
	position = tlate + G4ThreeVector(XTranslation,0, ZTranslation - CuTube1->GetDz()).transform(G4RotationMatrix(*pRot).inverse()) ;
       new G4PVPlacement(rotationTorus,
      position,
      CuTorusLog,
      "CuTorus",
      pMotherLogical,
      false,
      cpN) ;
       cpN++; 
	G4cout << "Volume (  " << cpN <<" )H2OTorus" << " the position is " <<  G4BestUnit(XTranslation,"Length") << G4endl ; 
	position = tlate + G4ThreeVector(XTranslation,0, ZTranslation- CuTube1->GetDz()).transform(G4RotationMatrix(*pRot).inverse()) ;
	new G4PVPlacement(rotationTorus,
      position,
      H2OTorusLog,
      "H2OTorus",
      pMotherLogical,
      false,
      cpN) ;
       XTranslation += CuTube1->GetRMax() ;
       ZTranslation=tripleGemHeight/2 - space[0] - FebCapCollection.at(0)->GetZHalfLength()/2;
       cpN++; 
   //---------------------------------------------------------------------------------FEB Cu cooling panel
      XTranslation += FebCapCollection.at(0)->GetXHalfLength() ;
 
      for(size_t i=0 ; i<FebCapCollection.size() ; i++) {
	G4ThreeVector position = tlate + G4ThreeVector(XTranslation,0, ZTranslation).transform(G4RotationMatrix(*pRot).inverse()) ;
       G4cout << "Volume (" << cpN << ") " << FebCapCollection.at(i)->GetName() << " the position is " <<  G4BestUnit(XTranslation,"Length") << G4endl ; 
      new G4PVPlacement(pRot,
      position,
      FebCapLogCollection.at(i),
      FebCapCollection.at(i)->GetName(),
      pMotherLogical,
      false,
      cpN) ;
      cpN++;
	if(i!=FebCapCollection.size()-1){ ZTranslation -= FebCapCollection.at(i)->GetZHalfLength() +
			FebCapCollection.at(i+1)->GetZHalfLength() +
		space[i+1];}
	else {         ZTranslation=tripleGemHeight/2 - crossBarSpace[0] - crossBarCollection.at(0)->GetZHalfLength()/2;
   }   
   }
      XTranslation += FebCapCollection.at(0)->GetXHalfLength() ;
   
  //  //---------------------------------------------------------------------------------CrossBar
     
     XTranslation += crossBarCollection.at(0)->GetXHalfLength() ;
    for(size_t i=0 ; i<crossBarCollection.size() ; i++) {
      G4ThreeVector position = tlate + G4ThreeVector(XTranslation,0, ZTranslation).transform(G4RotationMatrix(*pRot).inverse()) ;
     G4cout << "Volume (" << cpN << ") " << crossBarCollection.at(i)->GetName() << " the position is " <<  G4BestUnit(XTranslation,"Length") << G4endl ; 
       new G4PVPlacement(pRot,
       position,
       crossBarLogCollection.at(i),
       crossBarCollection.at(i)->GetName(),
       pMotherLogical,
       false,
       i+cpN) ;
       cpN++;
      if(i!=crossBarCollection.size()-1){ ZTranslation -= crossBarCollection.at(i)->GetZHalfLength() +
			 crossBarCollection.at(i+1)->GetZHalfLength() +
		 crossBarSpace[i+1];}
      else {ZTranslation=0;} 
 }
       XTranslation += crossBarCollection.at(0)->GetXHalfLength() ;
 
 //---------------------------------------------------------------------------------RPC
  
 
     for(size_t i=0 ; i<trdCollection.size() ; i++) {
       // i counts as the copyNo
       XTranslation += trdCollection.at(i)->GetXHalfLength1() ;
       position = tlate + G4ThreeVector(XTranslation,0,0).transform(G4RotationMatrix(*pRot).inverse()) ;
       G4cout << "Volume (" << cpN << ") " << trdCollection.at(i)->GetName() << " the position is " << G4BestUnit(XTranslation,"Length") << G4endl ;
       new G4PVPlacement(pRot,
	  position,
	  trdLogCollection.at(i),
	  trdCollection.at(i)->GetName(),
	  pMotherLogical,
	  false,
	  cpN) ;
       XTranslation += trdCollection.at(i)->GetXHalfLength1() ;
       cpN++;
    }
    
  
 //---------------------------------------------------------------------------------Fake Top
    XTranslation += FakeTop->GetXHalfLength1() ;
    position = tlate + G4ThreeVector(XTranslation,0,0).transform(G4RotationMatrix(*pRot).inverse()) ;
    G4cout << "Volume (" << cpN << ") " << FakeTop->GetName() << " the position is " <<  G4BestUnit(XTranslation,"Length") << G4endl;
     
       new G4PVPlacement(pRot,
	  position,
	  FakeTopLog,
	  "FakeTop",
	  pMotherLogical,
	  false,
	  cpN) ;

}

