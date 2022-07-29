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
/// \file analysis/shared/src/PrimaryGeneratorAction.cc
/// \brief Implementation of the PrimaryGeneratorAction class
//
//
// $Id: PrimaryGeneratorAction.cc 68015 2013-03-13 13:27:27Z gcosmo $
//
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "PrimaryGeneratorAction.hh"

#include "DetectorConstruction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ChargedGeantino.hh"
#include "G4IonTable.hh"
#include "G4SystemOfUnits.hh"

#include <CLHEP/Random/RandGauss.h>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction(DetectorConstruction* det)
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0),
  fDetector(det)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  //energy = CLHEP::RandGauss::shoot(30*MeV,1.0);
  //fParticleGun->SetParticleEnergy(energy);
  //G4cout << "Energy :" << energy << G4endl;
  // default particle kinematic

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle = particleTable->FindParticle("chargedgeantino");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1)); 

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{

  energy = CLHEP::RandGauss::shoot(80*MeV,5.0);
  fParticleGun->SetParticleEnergy(energy);
  fParticleGun->SetParticlePosition(G4ThreeVector(0*cm,0.*cm,-19.9*cm));
  G4cout << "Energy :" << energy << G4endl;

  G4ParticleDefinition* particle = fParticleGun->GetParticleDefinition();
  if (particle == G4ChargedGeantino::ChargedGeantino()) {
  	
	//Boron 10
	G4int Z = 5, A = 10;
  	G4double ionCharge   = 0.*eplus;
  	G4double excitEnergy = 0.*keV;

  	G4ParticleDefinition* ion
    	    = G4IonTable::GetIonTable()->GetIon(Z,A,excitEnergy);
  
  	fParticleGun->SetParticleDefinition(ion);
  	fParticleGun->SetParticleCharge(ionCharge);

  
  
}
 fParticleGun->GeneratePrimaryVertex(anEvent);
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
}
