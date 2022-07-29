
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
/// \file analysis/AnaEx02/AnaEx02.cc
/// \brief Main program of the analysis/AnaEx02 example
//
//
// $Id: AnaEx02.cc 68015 2013-03-13 13:27:27Z gcosmo $
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "StackingAction.hh"
#include "HistoManager.hh"
#include "ActionInitialization.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{     
  // Construct the default run manager
  //
  G4RunManager * runManager = new G4RunManager;

  // Set mandatory initialization classes
  //
  DetectorConstruction* det = new DetectorConstruction;
  runManager->SetUserInitialization(det);
  //
  PhysicsList* phys = new PhysicsList;
  runManager->SetUserInitialization(phys);
 
  // set an HistoManager
  //
  HistoManager*  histo = new HistoManager();
      
  // Set user action classes
  //
  PrimaryGeneratorAction* kin = 
                          new PrimaryGeneratorAction(det);
  runManager->SetUserAction(kin);
  //
  EventAction* event = new EventAction();
  runManager->SetUserAction(event);
  //
  RunAction* run = new RunAction(event);  
  runManager->SetUserAction(run);
  //
  SteppingAction* stepping =
                    new SteppingAction();
  runManager->SetUserAction(stepping);
  //
  StackingAction* stacking = new StackingAction();
  runManager->SetUserAction(stacking);
  // Initialize G4 kernel
  //
  runManager->Initialize();

  // Get the pointer to the User Interface manager
  //
  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  
  if (argc!=1)   // batch mode
    {
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UImanager->ApplyCommand(command+fileName);    
    }
  else
    {  // interactive mode : define visualization and UI terminal
#ifdef G4VIS_USE
      G4VisManager* visManager = new G4VisExecutive;
      visManager->Initialize();
#ifdef G4UI_USE
      G4UIExecutive* ui = new G4UIExecutive(argc, argv);
#endif
      UImanager->ApplyCommand("/control/execute vis.mac");     
#endif

#ifdef G4UI_USE
      ui->SessionStart();
      delete ui;
#endif

#ifdef G4VIS_USE
      delete visManager;
#endif
    }
  
  // Job termination
  delete histo;                
  delete runManager;

  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
