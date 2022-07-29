#ifndef DetectorSD_h
#define DetectorSD_h 1

#include "G4VSensitiveDetector.hh"
#include "DetectorHit.hh"
#include "globals.hh"

class G4HCofThisEvent;
class G4Step;
class G4TouchableHistory;
class HistoManager;

class DetectorSD : public G4VSensitiveDetector
{
  public:

	DetectorSD(const G4String&);
	virtual ~DetectorSD();

	virtual void Initialize(G4HCofThisEvent*);
	virtual G4bool ProcessHits(G4Step*, G4TouchableHistory* );

  private:
    HistoManager* theHisto;
	DetectorHitsCollection* fHitsCollection;
	G4int fHCID;
	G4int* CellID;
	G4int numberOfCells;

};

#endif
