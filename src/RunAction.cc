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
/// \file analysis/shared/src/RunAction.cc
/// \brief Implementation of the RunAction class
//
//
// $Id: RunAction.cc 74272 2013-10-02 14:48:50Z gcosmo $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "RunAction.hh"
#include "HistoManager.hh"
#include "DetectorConstruction.hh"
#include "Analysis.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4EmCalculator.hh"
#include "G4Electron.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction(EventAction* evt)
: G4UserRunAction()
{
  fHistoManager = HistoManager::GetPointer();

  fevent = evt;
  //Create analysis manager
  G4AnalysisManager* analysisManager=G4AnalysisManager::Instance();
  G4cout << "Using" << analysisManager->GetType() << G4endl;

  // Default settings
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFileName("10B_80MeV");

  // Book histogram, ntuple
  //

  // Creating 1D histograms
  analysisManager -> CreateH1("detec1","Detecor 1 # Hits", 1000, 0, 10); // h1 Id = 0
  analysisManager -> CreateH1("detec1","Detecor 1 # Energydep", 800, 0, 10*CLHEP::keV); // h1 Id = 1
  analysisManager -> CreateH1("detec2","Detecor 2 # Hits", 1000, 0, 10); // h1 Id = 2
  analysisManager -> CreateH1("detec2","Detecor 2 # Energydep", 800, 0, 20*CLHEP::keV); // h1 Id = 3

  // Creating 2D histograms
  analysisManager -> CreateH2("Energy","deltaE vs E",800,0,10*CLHEP::keV,800,0,20*CLHEP::keV);

  // Creating ntuple
  analysisManager->CreateNtuple("ion", "Hits");
  analysisManager->CreateNtupleDColumn("gap0Edep"); // coulumn Id = 0
  analysisManager->CreateNtupleDColumn("gap1Edep"); // coulumn Id = 1
  analysisManager->CreateNtupleDColumn("gap2Edep"); // coulumn Id = 2
  analysisManager->CreateNtupleDColumn("gap3Edep"); // coulumn Id = 3
  analysisManager->CreateNtupleDColumn("gap4Edep"); // coulumn Id = 4
  analysisManager->CreateNtupleDColumn("gap5Edep"); // coulumn Id = 5
  analysisManager->CreateNtupleDColumn("gap6Edep"); // coulumn Id = 6
  analysisManager->CreateNtupleDColumn("gap7Edep"); // coulumn Id = 7
  analysisManager->CreateNtupleDColumn("gap8Edep"); // coulumn Id = 8
  analysisManager->CreateNtupleDColumn("gap9Edep"); // coulumn Id = 9
  analysisManager->CreateNtupleDColumn("gap10Edep"); // coulumn Id = 10
  analysisManager->CreateNtupleDColumn("gap11Edep"); // coulumn Id = 11
  analysisManager->CreateNtupleDColumn("gap12Edep"); // coulumn Id = 12
  analysisManager->CreateNtupleDColumn("gap13Edep"); // coulumn Id = 13
  analysisManager->CreateNtupleDColumn("gap14Edep"); // coulumn Id = 14
  analysisManager->CreateNtupleDColumn("gap15Edep"); // coulumn Id = 15
  analysisManager->CreateNtupleDColumn("gap16Edep"); // coulumn Id = 16
  
  analysisManager->CreateNtupleDColumn("detecE1"); // coulumn Id = 17
  analysisManager->CreateNtupleDColumn("detecE2"); // coulumn Id = 18
  analysisManager->CreateNtupleDColumn("detecE3"); // coulumn Id = 19
  analysisManager->CreateNtupleDColumn("detecE4"); // coulumn Id = 20
  analysisManager->CreateNtupleDColumn("detecE5"); // coulumn Id = 21
  analysisManager->CreateNtupleDColumn("detecE6"); // coulumn Id = 22
  analysisManager->CreateNtupleDColumn("detecE7"); // coulumn Id = 23
  analysisManager->CreateNtupleDColumn("detecE8"); // coulumn Id = 24
  analysisManager->CreateNtupleDColumn("detecE9"); // coulumn Id = 25
  analysisManager->CreateNtupleDColumn("totalEnergy"); // coulumn Id = 26
  analysisManager->CreateNtupleDColumn("NumberOfCluster"); // coulumn Id = 27
  analysisManager->FinishNtuple();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{
  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run* aRun)
{ 
  fHistoManager->InitCluster();
  fevent->InitTotn();
  // Get analysis manager
  G4AnalysisManager* analysisManager=G4AnalysisManager::Instance();
	
  // Open an output file
  analysisManager->OpenFile();

  /*
  //process counter
  fProcCounter = new ProcessesCount;
  
  //kinetic energy of charged secondary a creation
  //
  fEsecondary = fEsecondary2 = 0;
  fNbSec = 0;

  //total energy deposit in dE-E
  fEdepdetec = fEdepdetec2 = 0;
  fNbEventdetec = 0;
  fNbEventdetec2 = 0;
*/
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* aRun)
{
  //save histograms& ntuple
  //
  G4AnalysisManager* analysisManager=G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
  
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
