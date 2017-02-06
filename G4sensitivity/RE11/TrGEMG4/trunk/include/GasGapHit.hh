#ifndef GasGapHit_h
#define GasGapHit_h 1

/**
 * @file
 * @brief Define user class GasGapHit.
 *
 * We define "our" hit content : the layer number and the energy deposited in the layer
 */

#include "G4VHit.hh"
#include "G4Allocator.hh"
#include "G4THitsCollection.hh"

/*!
 * \brief This class stores information of a hit.
 *
 * It contains
 *  - Hadronic calorimeter layer number
 *  - Deposited energy in layer
 */
class GasGapHit : public G4VHit {
public:
  /// Constructor
  GasGapHit(const G4int layer);
  /// Destructor
  ~GasGapHit();
  //! Print on screen a Hit
  void Print();
  
public:
  //! \name The new and delete operators are overloaded for performances reasons:
  /*! -- Tricky business here... :-(, but provided for you below */
  //@{
  inline void *operator    new(size_t);
  inline void  operator delete(void *aHit);
  //@}

public:
  //! \name  simple set and get methods
  //@{
  void          AddEdep(const double e){ eDep += e; }

  G4double      GetEdep()        const { return eDep;}
  G4int         GetLayerNumber() const { return layerNumber; }
  //@}

private:
  const G4int   layerNumber;
  G4double      eDep;
};

// Define the "hit collection" using the template class G4THitsCollection:
typedef G4THitsCollection<GasGapHit> GasGapHitCollection;


// -- new and delete overloaded operators:
extern G4Allocator<GasGapHit> GasGapHitAllocator;

inline void* GasGapHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) GasGapHitAllocator.MallocSingle();
  return aHit;
}
inline void GasGapHit::operator delete(void *aHit)
{
  GasGapHitAllocator.FreeSingle((GasGapHit*) aHit);
}

#endif
