#include "TrGEMDetectorConstruction.hh"
#include "GasGapSensitiveDetector.hh"

#include "G4NistManager.hh"
#include "G4SDManager.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4GeometryManager.hh"
//#include "G4PhysicalVolumeStore.hh"
//#include "G4LogicalVolumeStore.hh"
//#include "G4SolidStore.hh"
#include "G4VisAttributes.hh"
#include "G4PVPlacement.hh"
#include "G4UnitsTable.hh"

TrGEMDetectorConstruction::TrGEMDetectorConstruction() :
   fG10Mat(0), fGasMat(0), fEmptyMat(0), fGasDetectorCuts(0),
   tripleGemThinBase(0), tripleGemLargeBase(0), tripleGemHeight(0)
{

   tripleGemThinBase  = 220.0*mm ;
   tripleGemLargeBase = 445.0*mm ;
   tripleGemHeight    = 990.0*mm ;

   G4double cut = 1*mm ;
   fGasDetectorCuts = new G4ProductionCuts() ;
   fGasDetectorCuts->SetProductionCut(cut,"gamma") ;
   fGasDetectorCuts->SetProductionCut(cut,"e-") ;
   fGasDetectorCuts->SetProductionCut(cut,"e+") ;
   fGasDetectorCuts->SetProductionCut(cut,"proton") ;

}

TrGEMDetectorConstruction::~TrGEMDetectorConstruction() {

   delete fGasDetectorCuts ;

}

void TrGEMDetectorConstruction::DefineMaterials() {

   G4NistManager* manager = G4NistManager::Instance() ;
   // define Elements
   G4Element* elC  = manager->FindOrBuildElement(6);
   G4Element* elF  = manager->FindOrBuildElement(9);

   // define Materials
   G4Material *H  = G4NistManager::Instance()->FindOrBuildMaterial("G4_H") ;
   G4Material *C  = G4NistManager::Instance()->FindOrBuildMaterial("G4_C") ;
   G4Material *O  = G4NistManager::Instance()->FindOrBuildMaterial("G4_O") ;
   G4Material *Si = G4NistManager::Instance()->FindOrBuildMaterial("G4_Si") ;

   G4Material *g10Material = new G4Material("G10", 1.9*g/cm3, 4) ;
   g10Material->AddMaterial(C,0.1323) ;
   g10Material->AddMaterial(H,0.03257) ;
   g10Material->AddMaterial(O,0.48316) ;
   g10Material->AddMaterial(Si,0.35194) ;
   fG10Mat = g10Material ;

   // gases at STP conditions 
   G4Material* Argon = manager->FindOrBuildMaterial("G4_Ar");
   G4Material* CarbonDioxide = manager->FindOrBuildMaterial("G4_CARBON_DIOXIDE");
   G4Material* empty = manager->FindOrBuildMaterial("G4_Galactic");
   fEmptyMat = empty ;

   // CF4 must be defined by hand
   G4int numel(0) ;
   G4double density(0.), temperature(0.), pressure(0.) ;
   G4String name, symbol ;
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

   // Choice of the gas
   fGasMat = ArCO2CF4 ;

}

G4VPhysicalVolume* TrGEMDetectorConstruction::Construct() {


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

   G4double worldSizeX = 10*m;
   G4double worldSizeY = 10*m;
   G4double worldSizeZ = 10*m;

   // World definition and placement
   G4Box* worldBox = new G4Box("WorldBox", worldSizeX, worldSizeY, worldSizeZ) ;
   G4LogicalVolume* worldLog = new G4LogicalVolume(worldBox, fEmptyMat, "WorldLog") ;
   // Set visual attributes
   G4VisAttributes *worldAttributes = new G4VisAttributes ;
   worldAttributes->SetVisibility(true) ;
   worldLog->SetVisAttributes(worldAttributes) ;
   G4VPhysicalVolume* worldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLog, "WorldSpace", 0, false, 0) ;

   // Rotation Matrix for layers
   G4RotationMatrix* rotationPlacement = new G4RotationMatrix() ;
   rotationPlacement->rotateY(M_PI / 2.0) ;
   rotationPlacement->rotateX(M_PI / 2.0) ;

   // Visual attributes
   G4VisAttributes *cathodeAttributes = new G4VisAttributes(G4Color::Grey()) ;
   cathodeAttributes->SetForceWireframe(true) ;
   G4VisAttributes *g10Attributes = new G4VisAttributes(G4Color::White()) ;
   g10Attributes->SetForceWireframe(true) ;
   G4VisAttributes *gasAttributes = new G4VisAttributes(G4Color::Red()) ;
   gasAttributes->SetForceWireframe(true) ;
   G4VisAttributes *gemAttributes = new G4VisAttributes(G4Color::Green()) ;
   gemAttributes->SetForceWireframe(true) ;

   
   G4Trd* cathode = Trapezoid("Cathode", 1.*mm) ;
   G4LogicalVolume* cathodeLog = new G4LogicalVolume(cathode, G4NistManager::Instance()->FindOrBuildMaterial("G4_Al"), "CathodeLog") ;
   cathodeLog->SetVisAttributes(new G4VisAttributes(*cathodeAttributes)) ;
   trdCollection.push_back(cathode) ;
   trdLogCollection.push_back(cathodeLog) ;

   // Drift cathode foil
   G4Trd* kapton0 = Trapezoid("kapton0", 200.*um) ;
   G4LogicalVolume* kapton0Log = new G4LogicalVolume(kapton0, G4NistManager::Instance()->FindOrBuildMaterial("G4_KAPTON"), "kapton0Log") ;
   kapton0Log->SetVisAttributes(new G4VisAttributes(*gemAttributes)) ;
   trdCollection.push_back(kapton0) ;
   trdLogCollection.push_back(kapton0Log) ;

   G4Trd* g10_1 = Trapezoid("g10_1", 3.*mm) ;
   G4LogicalVolume* g10_1Log = new G4LogicalVolume(g10_1, fG10Mat, "G10_1Log") ;
   g10_1Log->SetVisAttributes(new G4VisAttributes(*g10Attributes)) ;
   trdCollection.push_back(g10_1) ;
   trdLogCollection.push_back(g10_1Log) ;
   

   G4Trd* gasGap1 = Trapezoid("GasGap1", 3.*mm) ;
   G4LogicalVolume* gasGap1Log = new G4LogicalVolume(gasGap1, fGasMat, "gasGap1Log") ; 
   gasGap1Log->SetVisAttributes(new G4VisAttributes(*gasAttributes)) ;
   trdCollection.push_back(gasGap1) ;
   trdLogCollection.push_back(gasGap1Log) ;
   GasGapSensitiveDetector* sensitive = new GasGapSensitiveDetector("/GasGap") ;
   sdman->AddNewDetector(sensitive) ;
   gasGap1Log->SetSensitiveDetector(sensitive) ;

   
   // First GEM Foil - beginning
   G4Trd* copper11 = Trapezoid("Copper11", 5*um) ;
   G4LogicalVolume* copper11Log = new G4LogicalVolume(copper11, G4NistManager::Instance()->FindOrBuildMaterial("G4_Cu"), "copper11Log") ; 
   copper11Log->SetVisAttributes(new G4VisAttributes(*gemAttributes)) ;
   trdCollection.push_back(copper11) ;
   trdLogCollection.push_back(copper11Log) ;

   G4Trd* kapton1 = Trapezoid("Kapton1", 50.*um) ;
   G4LogicalVolume* kapton1Log = new G4LogicalVolume(kapton1, G4NistManager::Instance()->FindOrBuildMaterial("G4_KAPTON"), "kapton1Log") ;
   kapton1Log->SetVisAttributes(new G4VisAttributes(*gemAttributes)) ;
   trdCollection.push_back(kapton1) ;
   trdLogCollection.push_back(kapton1Log) ;

   G4Trd* copper12 = Trapezoid("Copper12",5.*um) ;
   G4LogicalVolume* copper12Log = new G4LogicalVolume(copper12, G4NistManager::Instance()->FindOrBuildMaterial("G4_Cu"), "copper12Log") ;
   copper12Log->SetVisAttributes(new G4VisAttributes(*gemAttributes)) ;
   trdCollection.push_back(copper12) ;
   trdLogCollection.push_back(copper12Log) ;
   // First GEM Foil - end

   G4Trd* gasGap2 = Trapezoid("GasGap2", 1.*mm) ;
   G4LogicalVolume* gasGap2Log = new G4LogicalVolume(gasGap2, fGasMat, "gasGap2Log") ;
   gasGap2Log->SetVisAttributes(new G4VisAttributes(*gasAttributes)) ;
   trdCollection.push_back(gasGap2) ;
   trdLogCollection.push_back(gasGap2Log) ;
   gasGap2Log->SetSensitiveDetector(sensitive) ;

   G4Trd* copper21 = Trapezoid("Copper21", 5.*um) ;
   G4LogicalVolume* copper21Log = new G4LogicalVolume(copper21, G4NistManager::Instance()->FindOrBuildMaterial("G4_Cu"), "copper21Log") ;
   copper21Log->SetVisAttributes(new G4VisAttributes(*gemAttributes)) ;
   trdCollection.push_back(copper21) ;
   trdLogCollection.push_back(copper21Log) ;

   G4Trd* kapton2 = Trapezoid("Kapton2", 50.*um) ;
   G4LogicalVolume* kapton2Log = new G4LogicalVolume(kapton2, G4NistManager::Instance()->FindOrBuildMaterial("G4_KAPTON"), "kapton2Log") ;
   kapton2Log->SetVisAttributes(new G4VisAttributes(*gemAttributes)) ;
   trdCollection.push_back(kapton2) ;
   trdLogCollection.push_back(kapton2Log) ;

   G4Trd* copper22 = Trapezoid("Copper22", 5.*um) ;
   G4LogicalVolume* copper22Log = new G4LogicalVolume(copper22, G4NistManager::Instance()->FindOrBuildMaterial("G4_Cu"), "copper22Log") ;
   copper22Log->SetVisAttributes(new G4VisAttributes(*gemAttributes)) ;
   trdCollection.push_back(copper22) ;
   trdLogCollection.push_back(copper22Log) ;

   G4Trd* gasGap3 = Trapezoid("GasGap3", 2.*mm) ;
   G4LogicalVolume* gasGap3Log = new G4LogicalVolume(gasGap3, fGasMat, "GasGap3Log") ;
   gasGap3Log->SetVisAttributes(new G4VisAttributes(*gasAttributes)) ;
   trdCollection.push_back(gasGap3) ;
   trdLogCollection.push_back(gasGap3Log) ;

   G4Trd* copper31 = Trapezoid("Copper31", 5.*um) ;
   G4LogicalVolume* copper31Log = new G4LogicalVolume(copper31, G4NistManager::Instance()->FindOrBuildMaterial("G4_Cu"), "copper31Log") ;
   copper31Log->SetVisAttributes(new G4VisAttributes(*gemAttributes)) ;
   trdCollection.push_back(copper31) ;
   trdLogCollection.push_back(copper31Log) ;

   G4Trd* kapton3 = Trapezoid("Kapton3", 50.*um) ;
   G4LogicalVolume* kapton3Log = new G4LogicalVolume(kapton3, G4NistManager::Instance()->FindOrBuildMaterial("G4_KAPTON"), "kapton3Log") ;
   kapton3Log->SetVisAttributes(new G4VisAttributes(*gemAttributes)) ;
   trdCollection.push_back(kapton3) ;
   trdLogCollection.push_back(kapton3Log) ;

   G4Trd* copper32 = Trapezoid("Copper32", 5.*um) ;
   G4LogicalVolume* copper32Log = new G4LogicalVolume(copper32, G4NistManager::Instance()->FindOrBuildMaterial("G4_Cu"), "copper32Log") ;
   copper32Log->SetVisAttributes(new G4VisAttributes(*gemAttributes)) ;
   trdCollection.push_back(copper32) ;
   trdLogCollection.push_back(copper32Log) ;

   G4Trd* gasGap4 = Trapezoid("GasGap4", 1.*mm) ;
   G4LogicalVolume* gasGap4Log = new G4LogicalVolume(gasGap4, fGasMat, "gasGap4Log") ;
   gasGap4Log->SetVisAttributes(new G4VisAttributes(*gasAttributes)) ;
   trdCollection.push_back(gasGap4) ;
   trdLogCollection.push_back(gasGap4Log) ;

   // Readout strips
   G4Trd* copper4 = Trapezoid("Copper4", 5.*um) ;
   G4LogicalVolume* copper4Log = new G4LogicalVolume(copper4, G4NistManager::Instance()->FindOrBuildMaterial("G4_Cu"), "copper4Log") ;
   copper4Log->SetVisAttributes(new G4VisAttributes(*gemAttributes)) ;
   trdCollection.push_back(copper4) ;
   trdLogCollection.push_back(copper4Log) ;

   // Readout Board
   G4Trd* g10_2 = Trapezoid("g10_2", 3.*mm) ;
   G4LogicalVolume* g10_2Log = new G4LogicalVolume(g10_2, fG10Mat, "g10_2Log") ; // was G4_BAKELITE
   g10_2Log->SetVisAttributes(new G4VisAttributes(*g10Attributes)) ;
   trdCollection.push_back(g10_2) ;
   trdLogCollection.push_back(g10_2Log) ;

   G4Trd* kapton4 = Trapezoid("kapton4", 200.*um) ;
   G4LogicalVolume* kapton4Log = new G4LogicalVolume(kapton4, G4NistManager::Instance()->FindOrBuildMaterial("G4_KAPTON"), "kapton4Log") ;
   kapton4Log->SetVisAttributes(new G4VisAttributes(*gemAttributes)) ;
   trdCollection.push_back(kapton4) ;
   trdLogCollection.push_back(kapton4Log) ;

   // Spacer (air/void)
   G4Trd* spacer = Trapezoid("spacer", 1.8*mm) ;
   G4LogicalVolume* spacerLog = new G4LogicalVolume(spacer, fEmptyMat, "spacerLog") ;
   spacerLog->SetVisAttributes(new G4VisAttributes(*gemAttributes)) ;
   trdCollection.push_back(spacer) ;
   trdLogCollection.push_back(spacerLog) ;

   // GEM cover (1 mm)
   G4Trd* readout = Trapezoid("Readout", 1.*mm) ;
   G4LogicalVolume* readoutLog = new G4LogicalVolume(readout, G4NistManager::Instance()->FindOrBuildMaterial("G4_Al"), "readoutLog") ;
   readoutLog->SetVisAttributes(new G4VisAttributes(*cathodeAttributes)) ;
   trdCollection.push_back(readout) ;
   trdLogCollection.push_back(readoutLog) ;
   

   PlaceGeometry(rotationPlacement,G4ThreeVector(0.,0.,0.),worldLog) ;

   return worldPhys ;

}

G4Trd* TrGEMDetectorConstruction::Trapezoid(G4String name, G4double width) {
   G4Trd* shape = new G4Trd(name,
	 width/2, width/2,
	 tripleGemThinBase/2,
	 tripleGemLargeBase/2,
	 tripleGemHeight/2) ;
   return shape ;
}

void TrGEMDetectorConstruction::PlaceGeometry(G4RotationMatrix *pRot, G4ThreeVector tlate, G4LogicalVolume* pMotherLogical) {

   G4double XTranslation = 0 ;

   for(size_t i=0 ; i<trdCollection.size() ; i++) {
      // i counts as the copyNo
      XTranslation += trdCollection.at(i)->GetXHalfLength1() ;
      G4ThreeVector position = tlate + G4ThreeVector(XTranslation,0,0).transform(G4RotationMatrix(*pRot).inverse()) ;
      G4cout << "Volume (" << i << ") " << trdCollection.at(i)->GetName() << " the position is " << G4BestUnit(XTranslation,"Length") << G4endl ;
      new G4PVPlacement(pRot,
	    position,
	    trdLogCollection.at(i),
	    trdCollection.at(i)->GetName(),
	    pMotherLogical,
	    false,
	    i) ;
      XTranslation += trdCollection.at(i)->GetXHalfLength1() ;
   }
}

