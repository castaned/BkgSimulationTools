#include "TrGEMHolesParameterisation.hh"

#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4Tubs.hh"
#include "G4SystemOfUnits.hh"


TrGEMHolesParameterisation::TrGEMHolesParameterisation(
      G4int noHoles,
      G4double startX,
      G4double startY,
      G4double spacingX,
      G4double spacingY)
{

   fNoHoles = noHoles ;
   fStartX = startX ;
   fStartY = startY ;
   fSpacingX = spacingX ;
   fSpacingY = spacingY ;

   // I should add some G4Exception to check if dimensions are fine

}

TrGEMHolesParameterisation::~TrGEMHolesParameterisation()
{}

void TrGEMHolesParameterisation::ComputeTransformation
(const G4int copyNo, G4VPhysicalVolume* physVol) const
{
   // Note: copyNo will start with zero!
   G4double Xposition = fStartX + copyNo * fSpacingX;
   G4double Yposition = fStartY + fSpacingY ;
   G4ThreeVector origin(Xposition,Yposition,0);
   physVol->SetTranslation(origin);
   physVol->SetRotation(0);
}


void TrGEMHolesParameterisation::ComputeDimensions
(G4Tubs& hole, const G4int copyNo, const G4VPhysicalVolume*) const
{
   G4double rmax = sqrt((35*35+35*25+25*25)/3)*um; // to obtain an equivalent volume of the true gem hole
   hole.SetInnerRadius(0);
   hole.SetOuterRadius(rmax);
   hole.SetZHalfLength(50.*um/2);
   hole.SetStartPhiAngle(0.*deg);
   hole.SetDeltaPhiAngle(360.*deg);
}
