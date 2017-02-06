#ifndef TrGEMHolesParameterisation_h
#define TrGEMHolesParameterisation_h 1

#include "G4VPVParameterisation.hh"

class G4VPhysicalVolume;
class G4Tubs;

// Dummy declarations to get rid of warnings ...
class G4Trd;
class G4Box;
class G4Trap;
class G4Cons;
class G4Orb;
class G4Sphere;
class G4Torus;
class G4Para;
class G4Hype;
class G4Polycone;
class G4Polyhedra;

class TrGEMHolesParameterisation : public G4VPVParameterisation
{
   public:
      TrGEMHolesParameterisation(
	    G4int noHoles,
	    G4double startX,
	    G4double startY,
	    G4double spacingX,
	    G4double spacingY);
      virtual ~TrGEMHolesParameterisation() ;
      void ComputeTransformation
	 (const G4int copyNo, G4VPhysicalVolume* physVol) const ;
      void ComputeDimensions
	 (G4Tubs& hole, const G4int copyNo, const G4VPhysicalVolume*) const ;

   private:  // Dummy declarations to get rid of warnings ...

      void ComputeDimensions (G4Box&,const G4int,const G4VPhysicalVolume*) const {}
      void ComputeDimensions (G4Trd&,const G4int,const G4VPhysicalVolume*) const {}
      void ComputeDimensions (G4Trap&,const G4int,const G4VPhysicalVolume*) const {}
      void ComputeDimensions (G4Cons&,const G4int,const G4VPhysicalVolume*) const {}
      void ComputeDimensions (G4Sphere&,const G4int,const G4VPhysicalVolume*) const {}
      void ComputeDimensions (G4Orb&,const G4int,const G4VPhysicalVolume*) const {}
      void ComputeDimensions (G4Torus&,const G4int,const G4VPhysicalVolume*) const {}
      void ComputeDimensions (G4Para&,const G4int,const G4VPhysicalVolume*) const {}
      void ComputeDimensions (G4Hype&,const G4int,const G4VPhysicalVolume*) const {}
      void ComputeDimensions (G4Polycone&,const G4int,const G4VPhysicalVolume*) const {}
      void ComputeDimensions (G4Polyhedra&,const G4int,const G4VPhysicalVolume*) const {}

   private:

      G4int    fNoHoles ;
      G4double fStartX ;
      G4double fStartY ;
      G4double fSpacingX ;
      G4double fSpacingY ;
      G4double fWidthHole ;

};

#endif
