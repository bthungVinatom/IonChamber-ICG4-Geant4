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
/// \file analysis/shared/include/DetectorConstruction.hh
/// \brief Definition of the DetectorConstruction class
//
//
// $Id: DetectorConstruction.hh 77256 2013-11-22 10:10:23Z gcosmo $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4ElectricField.hh"
#include "G4UniformElectricField.hh"
#include "G4FieldManager.hh"
#include "G4Cache.hh"

class G4Box;
class G4Tubs;
class G4CutTubs;
class G4SubtractionSolid;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4VSensitiveDetector;
class G4GenericMessenger;

class G4Material;
class G4FieldManager;
class G4EqMagElectricField;

class Field;
class DetectorSD;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
  
    DetectorConstruction();
    virtual ~DetectorConstruction();

     virtual G4VPhysicalVolume* Construct();
  
     void PrintCalorParameters(); 
     virtual void ConstructField();

     const G4VPhysicalVolume* GetphysiWorld() {return fPhysiWorld;};
	 G4VPhysicalVolume* GetdE() {return fPhysidE;};

	 void SetPairEnergy(G4double);
  protected:
  	 G4FieldManager*	GetGlobalFieldManager();
  
  private:
	G4Cache<Field*> fEmFieldSetup;
	// Field*				field;

     G4int              fNbOfLayers;
     
     G4double           fdESizeXY;
     G4double           fdESizeZ;
     G4double			fgapSizeZ;

     G4double           fWorldSizeXY;
     G4double           fWorldSizeZ;
 
	 G4double			inter;
	 G4double			wireR;
	 G4double 			wingapH;
	 G4double			wingappos;
	 G4double 			winpos;
	 G4double			detpos1;
	 G4double			gappos;
	 G4int				ngap;

     G4Tubs*            fSolidWorld;    //pointer to the solid World 
     G4LogicalVolume*   fLogicWorld;    //pointer to the logical World
     G4VPhysicalVolume* fPhysiWorld;    //pointer to the physical World

	 G4Tubs*			fwindow;
	 G4LogicalVolume* 	fLogicwin;
	 G4VPhysicalVolume*	fPhysiwin;

	 G4CutTubs*			fwingap;
	 G4LogicalVolume* 	fLogicwgap;
	 G4VPhysicalVolume*	fPhysiwgap;
	 
	 G4Box*				fgap;
	 G4LogicalVolume*	fLogicgap[17];
	 G4VPhysicalVolume*	fPhysigap;

	 G4Box*             fSoliddE;    //pointer to the solid Calor 
     G4LogicalVolume*   fLogicdE;    //pointer to the logical Calor
     G4VPhysicalVolume* fPhysidE;    //pointer to the physical Calor
     
	 G4Tubs*			cyl;
	 G4SubtractionSolid* subtraction1;

	 G4Tubs* 			fSolidwire;
	 G4LogicalVolume*	fLogicwire[17];
	 G4VPhysicalVolume*	fPhysiwire;

	 G4Material*		fDefaultMaterial;

	 G4GenericMessenger* fDetectorMessenger;  //pointer to the Messenger

	 G4bool	fCheckOverlaps;
  private:
    
     void DefineMaterials();
     void ComputeCalorParameters();
     G4VPhysicalVolume* ConstructCalorimeter();     
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void DetectorConstruction::ComputeCalorParameters()
{
  // Compute derived parameters of the calorimeter
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

