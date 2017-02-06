#include "GasGapHit.hh"
#include "G4UnitsTable.hh"

// -- one more nasty trick for new and delete operator overloading:
G4Allocator<GasGapHit> GasGapHitAllocator;

//Does just initialization of the two members: layerID and energy
GasGapHit::GasGapHit(const G4int layer) :
  layerNumber(layer),
  eDep(0)
{;}

GasGapHit::~GasGapHit()
{;}

void GasGapHit::Print()
{
  //---------------------
  // Exercise 2 of task 5b
  //---------------------
  //Add some print out on screen: layer number and energy deposited
  //
  G4cout<<"GasGapHit: Layer="<<layerNumber<<" Edep="<<G4BestUnit(eDep,"Energy")<<G4endl;
}
