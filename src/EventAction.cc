//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file analysis/shared/src/EventAction.cc
/// \brief Implementation of the EventAction class
//
//
// $Id: EventAction.cc 68015 2013-03-13 13:27:27Z gcosmo $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "EventAction.hh"
#include "Analysis.hh"

#include "RunAction.hh"
#include "HistoManager.hh"
#include "DetectorHit.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction()
:G4UserEventAction()
{
 fHistoManager = HistoManager::GetPointer();
 G4RunManager::GetRunManager()->SetPrintProgress(1);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event* )
{
  fHistoManager->InitEnergy();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* evt)
{
 // Get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  
 G4double nclu = fHistoManager->GetEnergy();
 Totnclu += nclu;
 G4cout << "Total Number of electron cluster is "<<Totnclu << G4endl;
 G4cout << "Number of electron cluster each event is "<<nclu << G4endl;

  analysisManager->FillNtupleDColumn(27, nclu);

  G4SDManager* sdManager = G4SDManager::GetSDMpointer();
 
  DetectorHitsCollection* detec1HC[17];
  for(G4int id=0;id<17;id++){
  char name[16];
  sprintf(name, "detecSD%02d/deltaE", id);
  SDname = name;
  fHHC1ID[id] = sdManager->GetCollectionID(SDname);
  G4HCofThisEvent* hce = evt->GetHCofThisEvent();
  detec1HC[id]=0;
  
  if(hce){
	detec1HC[id] = (DetectorHitsCollection*)(hce->GetHC(fHHC1ID[id]));
  }
  
  
	int n_hit1 = detec1HC[id]->entries();

  totgE[id]=0;
  if(detec1HC[id]) {
	for (int i=0; i<n_hit1; i++)
	{
		totgE[id] += (*detec1HC[id])[i]->GetEdep();
 	}	
  }
  char gapname[16];
  sprintf(gapname,"Total energy deposition in gap%02d",id);
  G4cout << gapname << " : " << totgE[id]/MeV << "MeV" << G4endl;


}  

  G4double detec1 = totgE[0]+totgE[1];
  G4double detec2 = totgE[2]+totgE[3];
  G4double detec3 = totgE[4]+totgE[5];
  G4double detec4 = totgE[6]+totgE[7];
  G4double detec5 = totgE[8]+totgE[9];
  G4double detec6 = totgE[10]+totgE[11];
  G4double detec7 = totgE[12]+totgE[13];
  G4double detec8 = totgE[14]+totgE[15];
  G4double detec9 = totgE[16];
  
  G4double totalE = detec1+detec2+detec3+detec4+detec5+detec6+detec7+detec8+detec9;
  G4cout << "The Total Energy Deposit : " << totalE/MeV << "MeV" << G4endl;

  analysisManager->FillNtupleDColumn(0, totgE[0]);
  analysisManager->FillNtupleDColumn(1, totgE[1]);
  analysisManager->FillNtupleDColumn(2, totgE[2]);
  analysisManager->FillNtupleDColumn(3, totgE[3]);
  analysisManager->FillNtupleDColumn(4, totgE[4]);
  analysisManager->FillNtupleDColumn(5, totgE[5]);
  analysisManager->FillNtupleDColumn(6, totgE[6]);
  analysisManager->FillNtupleDColumn(7, totgE[7]);
  analysisManager->FillNtupleDColumn(8, totgE[8]);
  analysisManager->FillNtupleDColumn(9, totgE[9]);
  analysisManager->FillNtupleDColumn(10, totgE[10]);
  analysisManager->FillNtupleDColumn(11, totgE[11]);
  analysisManager->FillNtupleDColumn(12, totgE[12]);
  analysisManager->FillNtupleDColumn(13, totgE[13]);
  analysisManager->FillNtupleDColumn(14, totgE[14]);
  analysisManager->FillNtupleDColumn(15, totgE[15]);
  analysisManager->FillNtupleDColumn(16, totgE[16]);

  analysisManager->FillNtupleDColumn(17, detec1);
  analysisManager->FillNtupleDColumn(18, detec2);
  analysisManager->FillNtupleDColumn(19, detec3);
  analysisManager->FillNtupleDColumn(20, detec4);
  analysisManager->FillNtupleDColumn(21, detec5);
  analysisManager->FillNtupleDColumn(22, detec6);
  analysisManager->FillNtupleDColumn(23, detec7);
  analysisManager->FillNtupleDColumn(24, detec8);
  analysisManager->FillNtupleDColumn(25, detec9);
  analysisManager->FillNtupleDColumn(26, totalE);
  analysisManager->AddNtupleRow();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
