#include "DetectorHit.hh"

#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4AttDef.hh"
#include "G4AttValue.hh"

#include <iomanip>

G4ThreadLocal G4Allocator<DetectorHit>* DetectorHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorHit::DetectorHit()
: G4VHit(),
  edep(0),
  fTrackLengthdE(0)
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
DetectorHit::DetectorHit(G4int z)
: G4VHit(),
  edep(0),
  fTrackLengthdE(0)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorHit::~DetectorHit()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorHit::DetectorHit(const DetectorHit& right)
: G4VHit()
{  
    fId     = right.fId;
    edep    = right.edep;
	fTrackLengthdE = right.fTrackLengthdE;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const DetectorHit& DetectorHit::operator=(const DetectorHit& right)
{
    fId     = right.fId;
  	edep    = right.edep;  
	fTrackLengthdE = right.fTrackLengthdE;

  	return *this;
}

G4int  DetectorHit::operator==(const DetectorHit& right) const
{
  return (fId == right.fId);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorHit::Print()
{
  G4cout
  	<< "Edep: "
	<< std::setw(7) << G4BestUnit(edep,"Energy")
	<< G4endl;
}
