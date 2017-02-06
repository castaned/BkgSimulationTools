#include "RPCDetectorConstruction.hh"
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
#include "G4Tubs.hh"

RPCDetectorConstruction::RPCDetectorConstruction() :
   fG10Mat(0), fGraphiteMat(0), fBakeliteMat(0), fGasMat(0), fEmptyMat(0), fGasDetectorCuts(0),
   tripleGemPx(0), tripleGemPy(0)
{

   // Squared shape dimensions
   tripleGemPx = 200.*mm ;
   tripleGemPy = 200.*mm ;

   G4double cut = 1*mm ;
   fGasDetectorCuts = new G4ProductionCuts() ;
   fGasDetectorCuts->SetProductionCut(cut,"gamma") ;
   fGasDetectorCuts->SetProductionCut(cut,"e-") ;
   fGasDetectorCuts->SetProductionCut(cut,"e+") ;
   fGasDetectorCuts->SetProductionCut(cut,"proton") ;

}

RPCDetectorConstruction::~RPCDetectorConstruction() {

   delete fGasDetectorCuts ;

}

void RPCDetectorConstruction::DefineMaterials() {

   G4NistManager* manager = G4NistManager::Instance() ;
   // define Elements
   G4Element* elH  = manager->FindOrBuildElement(1);
   G4Element* elC  = manager->FindOrBuildElement(6);
   G4Element* elO  = manager->FindOrBuildElement(8);
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
   G4Material* empty  = manager->FindOrBuildMaterial("G4_Galactic");
   fEmptyMat = empty ;

   // CF4 must be defined by hand
   G4int numel(0), natoms(0) ;
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

   //RPCgas
   G4double fractionMass(0.) ;
   density = 3.569*mg/cm3;
   G4Material* RPCgas = new G4Material(name = "RPCGas", density, numel=2) ;
   RPCgas->AddMaterial(isobutane, fractionMass = 3.* perCent) ;
   RPCgas->AddMaterial(C2H2F4, fractionMass = 97.* perCent) ;

   // Choice of the gas
   fGasMat = RPCgas ;

   // Graphite
   G4int z(0) ;
   G4double a(0.) ;
   G4Material* graphite = new G4Material("graphite", z=6, a= 12.0107*g/mole, density= 2.2*g/cm3);
   fGraphiteMat = graphite ;

   // Bakelite
   G4Material* bakelite = new G4Material("bakelite", density = 1.4*g/cm3, numel=3) ;
   bakelite->AddElement(elC, natoms=1) ;
   bakelite->AddElement(elH, natoms=4) ;
   bakelite->AddElement(elO, natoms=2) ;
   fBakeliteMat = bakelite ;

}

G4VPhysicalVolume* RPCDetectorConstruction::Construct() {


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

   G4double worldSizeX = 10*m ;
   G4double worldSizeY = 10*m ;
   G4double worldSizeZ = 10*m ;

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
   //rotationPlacement->rotateY(M_PI / 2.0) ;
   rotationPlacement->rotateY(0) ;
   //rotationPlacement->rotateX(M_PI / 2.0) ;
   rotationPlacement->rotateX(0) ;

   // Visual attributes
   G4VisAttributes *cathodeAttributes = new G4VisAttributes(G4Color::Grey()) ;
   cathodeAttributes->SetForceWireframe(true) ;
   G4VisAttributes *insAttributes = new G4VisAttributes(G4Color::White()) ;
   insAttributes->SetForceWireframe(true) ;
   G4VisAttributes *gasAttributes = new G4VisAttributes(G4Color::Red()) ;
   gasAttributes->SetForceWireframe(true) ;
   G4VisAttributes *rpcAttributes = new G4VisAttributes(G4Color::Green()) ;
   rpcAttributes->SetForceWireframe(true) ;

   G4Box* aluminiumTop = RPCBox("aluminiumTop", 0.06*cm) ;
   G4LogicalVolume* aluminiumTopLog = new G4LogicalVolume(aluminiumTop, G4NistManager::Instance()->FindOrBuildMaterial("G4_Al"), "aluminiumTopLog") ;
   aluminiumTopLog->SetVisAttributes(new G4VisAttributes(*cathodeAttributes)) ;
   trdCollection.push_back(aluminiumTop) ;
   trdLogCollection.push_back(aluminiumTopLog) ;

   G4Box* pethylene0 = RPCBox("pethylene0", 0.01*cm) ;
   G4LogicalVolume* pethylene0Log = new G4LogicalVolume(pethylene0, G4NistManager::Instance()->FindOrBuildMaterial("G4_POLYETHYLENE"), "pethylene0Log") ;
   pethylene0Log->SetVisAttributes(new G4VisAttributes(*insAttributes)) ;
   trdCollection.push_back(pethylene0) ;
   trdLogCollection.push_back(pethylene0Log) ;

   G4Box* graphite0 = RPCBox("graphite0", 0.002*cm) ;
   G4LogicalVolume* graphite0Log = new G4LogicalVolume(graphite0, fGraphiteMat, "graphite0Log") ;
   graphite0Log->SetVisAttributes(new G4VisAttributes(*insAttributes)) ;
   trdCollection.push_back(graphite0) ;
   trdLogCollection.push_back(graphite0Log) ;

   G4Box* bakelite0 = RPCBox("bakelite0", 0.2*cm) ;
   G4LogicalVolume* bakelite0Log = new G4LogicalVolume(bakelite0, fBakeliteMat, "bakelite0Log") ; 
   bakelite0Log->SetVisAttributes(new G4VisAttributes(*insAttributes)) ;
   trdCollection.push_back(bakelite0) ;
   trdLogCollection.push_back(bakelite0Log) ;
   
   G4Box* gasGap1 = RPCBox("GasGap1", 0.2*cm) ;
   G4LogicalVolume* gasGap1Log = new G4LogicalVolume(gasGap1, fGasMat, "gasGap1Log") ; 
   gasGap1Log->SetVisAttributes(new G4VisAttributes(*rpcAttributes)) ;
   trdCollection.push_back(gasGap1) ;
   trdLogCollection.push_back(gasGap1Log) ;
   GasGapSensitiveDetector* sensitive = new GasGapSensitiveDetector("/GasGap") ;
   sdman->AddNewDetector(sensitive) ;
   gasGap1Log->SetSensitiveDetector(sensitive) ;

   G4Box* bakelite1 = RPCBox("bakelite1", 0.2*cm) ;
   G4LogicalVolume* bakelite1Log = new G4LogicalVolume(bakelite1, fBakeliteMat, "bakelite1Log") ; 
   bakelite1Log->SetVisAttributes(new G4VisAttributes(*insAttributes)) ;
   trdCollection.push_back(bakelite1) ;
   trdLogCollection.push_back(bakelite1Log) ;

   G4Box* graphite1 = RPCBox("graphite1", 0.002*cm) ;
   G4LogicalVolume* graphite1Log = new G4LogicalVolume(graphite1, fGraphiteMat, "graphite1Log") ;
   graphite1Log->SetVisAttributes(new G4VisAttributes(*insAttributes)) ;
   trdCollection.push_back(graphite1) ;
   trdLogCollection.push_back(graphite1Log) ;
   
   G4Box* pethylene1 = RPCBox("pethylene1", 0.01*cm) ;
   G4LogicalVolume* pethylene1Log = new G4LogicalVolume(pethylene1, G4NistManager::Instance()->FindOrBuildMaterial("G4_POLYETHYLENE"), "pethylene1Log") ;
   pethylene1Log->SetVisAttributes(new G4VisAttributes(*insAttributes)) ;
   trdCollection.push_back(pethylene1) ;
   trdLogCollection.push_back(pethylene1Log) ;

   G4Box* aluminiumStrips = RPCBox("aluminiumStrips", 0.01*cm) ;
   G4LogicalVolume* aluminiumStripsLog = new G4LogicalVolume(aluminiumStrips, G4NistManager::Instance()->FindOrBuildMaterial("G4_Al"), "aluminiumStripsLog") ;
   aluminiumStripsLog->SetVisAttributes(new G4VisAttributes(*cathodeAttributes)) ;
   trdCollection.push_back(aluminiumStrips) ;
   trdLogCollection.push_back(aluminiumStripsLog) ;

   G4Box* pethylene2 = RPCBox("pethylene2", 0.01*cm) ;
   G4LogicalVolume* pethylene2Log = new G4LogicalVolume(pethylene2, G4NistManager::Instance()->FindOrBuildMaterial("G4_POLYETHYLENE"), "pethylene2Log") ;
   pethylene2Log->SetVisAttributes(new G4VisAttributes(*insAttributes)) ;
   trdCollection.push_back(pethylene2) ;
   trdLogCollection.push_back(pethylene2Log) ;

   G4Box* graphite2 = RPCBox("graphite2", 0.002*cm) ;
   G4LogicalVolume* graphite2Log = new G4LogicalVolume(graphite2, fGraphiteMat, "graphite2Log") ;
   graphite2Log->SetVisAttributes(new G4VisAttributes(*insAttributes)) ;
   trdCollection.push_back(graphite2) ;
   trdLogCollection.push_back(graphite2Log) ;
   
   G4Box* bakelite2 = RPCBox("bakelite2", 0.2*cm) ;
   G4LogicalVolume* bakelite2Log = new G4LogicalVolume(bakelite2, fBakeliteMat, "bakelite2Log") ; 
   bakelite2Log->SetVisAttributes(new G4VisAttributes(*insAttributes)) ;
   trdCollection.push_back(bakelite2) ;
   trdLogCollection.push_back(bakelite2Log) ;

   G4Box* gasGap2 = RPCBox("GasGap2", 0.2*cm) ;
   G4LogicalVolume* gasGap2Log = new G4LogicalVolume(gasGap2, fGasMat, "gasGap2Log") ; 
   gasGap2Log->SetVisAttributes(new G4VisAttributes(*rpcAttributes)) ;
   trdCollection.push_back(gasGap2) ;
   trdLogCollection.push_back(gasGap2Log) ;
   gasGap2Log->SetSensitiveDetector(sensitive) ;

   G4Box* bakelite3 = RPCBox("bakelite3", 0.2*cm) ;
   G4LogicalVolume* bakelite3Log = new G4LogicalVolume(bakelite3, fBakeliteMat, "bakelite3Log") ; 
   bakelite3Log->SetVisAttributes(new G4VisAttributes(*insAttributes)) ;
   trdCollection.push_back(bakelite3) ;
   trdLogCollection.push_back(bakelite3Log) ;

   G4Box* graphite3 = RPCBox("graphite3", 0.002*cm) ;
   G4LogicalVolume* graphite3Log = new G4LogicalVolume(graphite3, fGraphiteMat, "graphite3Log") ;
   graphite3Log->SetVisAttributes(new G4VisAttributes(*insAttributes)) ;
   trdCollection.push_back(graphite3) ;
   trdLogCollection.push_back(graphite3Log) ;
   
   G4Box* pethylene3 = RPCBox("pethylene3", 0.01*cm) ;
   G4LogicalVolume* pethylene3Log = new G4LogicalVolume(pethylene3, G4NistManager::Instance()->FindOrBuildMaterial("G4_POLYETHYLENE"), "pethylene3Log") ;
   pethylene3Log->SetVisAttributes(new G4VisAttributes(*insAttributes)) ;
   trdCollection.push_back(pethylene3) ;
   trdLogCollection.push_back(pethylene3Log) ;

   G4Box* aluminiumBottom = RPCBox("aluminiumBottom", 0.06*cm) ;
   G4LogicalVolume* aluminiumBottomLog = new G4LogicalVolume(aluminiumBottom, G4NistManager::Instance()->FindOrBuildMaterial("G4_Al"), "aluminiumBottomLog") ;
   aluminiumBottomLog->SetVisAttributes(new G4VisAttributes(*cathodeAttributes)) ;
   trdCollection.push_back(aluminiumBottom) ;
   trdLogCollection.push_back(aluminiumBottomLog) ;

   PlaceGeometry(rotationPlacement,G4ThreeVector(0.,0.,0.),worldLog) ;

   return worldPhys ;

}

G4Box* RPCDetectorConstruction::RPCBox(G4String name, G4double width) {
   G4Box* shape = new G4Box(
	 name,
	 tripleGemPx/2,
	 tripleGemPy/2,
	 width/2) ;
   return shape ;

}

void RPCDetectorConstruction::PlaceGeometry(G4RotationMatrix *pRot, G4ThreeVector tlate, G4LogicalVolume* pMotherLogical) {

G4double ZTranslation = 0 ;

   for(size_t i=0 ; i<trdCollection.size() ; i++) {
      // i counts as the copyNo
      ZTranslation += trdCollection.at(i)->GetZHalfLength() ;
      G4ThreeVector position = tlate + G4ThreeVector(0,0,ZTranslation).transform(G4RotationMatrix(*pRot).inverse()) ;
      G4cout << "Volume (" << i << ") " << trdCollection.at(i)->GetName() << " the position is " << G4BestUnit(ZTranslation,"Length") << G4endl ;
      new G4PVPlacement(pRot,
	    position,
	    trdLogCollection.at(i),
	    trdCollection.at(i)->GetName(),
	    pMotherLogical,
	    false,
	    i) ;
      ZTranslation += trdCollection.at(i)->GetZHalfLength() ;
   }

}
