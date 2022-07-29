#ifndef DetectorHit_h
#define DetectorHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"

class DetectorHit : public G4VHit
{
  public:

	DetectorHit();
	DetectorHit(G4int z);
	virtual ~DetectorHit();
	DetectorHit(const DetectorHit&);

	const DetectorHit& operator=(const DetectorHit&);
	G4int operator==(const DetectorHit&) const;

	inline void* operator new(size_t);
	inline void  operator delete(void*);

	virtual void Print();

    void  SetID(G4int z) { fId = z; };
    G4int GetID() const { return fId; };


    void SetEdep(G4double de) { edep  = de; }
	void AddEdep(G4double de) { edep += de; }
	G4double GetEdep() const {return edep;}

  private:
    G4int    fId;
    G4double edep;
	G4double fTrackLengthdE;
	
};

typedef G4THitsCollection<DetectorHit> DetectorHitsCollection;

extern G4ThreadLocal G4Allocator<DetectorHit>* DetectorHitAllocator;

inline void* DetectorHit::operator new(size_t)
{
	if(!DetectorHitAllocator)
		DetectorHitAllocator = new G4Allocator<DetectorHit>;
	return (void*) DetectorHitAllocator->MallocSingle();

}

inline void DetectorHit::operator delete(void* aHit)
{
  if(!DetectorHitAllocator)
  	  DetectorHitAllocator = new G4Allocator<DetectorHit>;
  DetectorHitAllocator->FreeSingle((DetectorHit*) aHit);
}

#endif
