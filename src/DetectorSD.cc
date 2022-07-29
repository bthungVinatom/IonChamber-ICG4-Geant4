#include "DetectorSD.hh"
#include "DetectorHit.hh"
#include "HistoManager.hh"
#include "globals.hh"

#include "G4TouchableHistory.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

DetectorSD::DetectorSD(const G4String& name)
: G4VSensitiveDetector(name), theHisto(HistoManager::GetPointer()),fHitsCollection(0),fHCID(-1)
{
    
	G4String dname = "deltaE";
	collectionName.insert(dname);
}

DetectorSD::~DetectorSD()
{;}

void DetectorSD::Initialize(G4HCofThisEvent* hce)
{
	fHitsCollection = new DetectorHitsCollection(SensitiveDetectorName,collectionName[0]);
	
	if (fHCID<0)
	{ fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);}
	hce->AddHitsCollection(fHCID, fHitsCollection);

}

G4bool DetectorSD::ProcessHits(G4Step* step, G4TouchableHistory* )
{
	G4double edep = step->GetTotalEnergyDeposit();
	theHisto->AddEnergy(edep, step);

	DetectorHit* detecHit = new DetectorHit();
	detecHit->SetEdep(edep);
	fHitsCollection->insert(detecHit);
 	
//	detecHit->Print();

  return true;
}
