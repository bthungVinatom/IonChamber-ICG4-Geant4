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
/// \file analysis/shared/src/DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class
//
//
// $Id: DetectorConstruction.cc 77256 2013-11-22 10:10:23Z gcosmo $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "DetectorConstruction.hh"
#include "Field.hh"
#include "DetectorSD.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4CutTubs.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4AutoDelete.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4ElectricField.hh"
#include "G4UniformElectricField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4EqMagElectricField.hh"

#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"

#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
:G4VUserDetectorConstruction(),
 //field(0),
 fSolidWorld(0),fLogicWorld(0),fPhysiWorld(0),
 fwindow(0), fLogicwin(0), fPhysiwin(0),
 fwingap(0), fLogicwgap(0), fPhysiwgap(0),
 fgap(0),
 fSoliddE(0),fLogicdE(0),fPhysidE(0),
 cyl(0), subtraction1(0),
 fSolidwire(0),fPhysiwire(0),
 fDefaultMaterial(0),fDetectorMessenger(0),
 fCheckOverlaps(true)
{
  fWorldSizeXY = 25*cm;
  fWorldSizeZ = 20*cm;
  fgapSizeZ = 1.83*cm;
  fdESizeZ = 1*mm;
  fdESizeXY = 13.6652*cm;
  ComputeCalorParameters();
  DefineMaterials();
  //field = new Field();
  inter = 1.83*cm;
  wireR = 0.002032*cm;
  wingapH = 2*cm;
  wingappos = -fWorldSizeZ+wingapH;
  winpos = wingappos+wingapH+5.08/2*um;
  detpos1 = (winpos+inter);
  gappos = (winpos+detpos1)/2;
  ngap = 17;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{ //delete fDetectorMessenger;
  //delete field;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  return ConstructCalorimeter();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{ 
// use G4-NIST materials data base
//
const G4double expTemp=CLHEP::STP_Temperature+25.*kelvin;//25C

G4NistManager* man = G4NistManager::Instance();
G4bool isotopes =false;

G4Element* Si = man->FindOrBuildElement("Si", isotopes);
G4Element* He = man->FindOrBuildElement("He", isotopes);
G4Element* H = man->FindOrBuildElement("H", isotopes);
G4Element* C = man->FindOrBuildElement("C", isotopes);
G4Element* O = man->FindOrBuildElement("O", isotopes);
G4Element* F = man->FindOrBuildElement("F", isotopes);
G4Element* Au = man->FindOrBuildElement("Au", isotopes);

//G4double density, z, a;

//G4Material* Tungsten = new G4Material("Tungsten", z=74., a=183.85*g/mole, density = 19.30*g/cm3);
//G4Material* Gold = new G4Material("Gold", z=79., a=196.97*g/mole, density = 19.32*g/cm3);

G4Material* Silicon = new G4Material("Silicon", 2.3290*g/cm3, 1);
Silicon->AddElement(Si, 1);

G4Material* Helium = new G4Material("Helium", 0.0001786*g/cm3, 1);
Helium->AddElement(He, 1);

G4Material* Gold = new G4Material("Gold", 19.32*g/cm3, 1);
Gold->AddElement(Au, 1);

G4Material* Mylar = new G4Material("Mylar", 1.390*g/cm3, 3);
Mylar->AddElement(H, 8);
Mylar->AddElement(C, 10);
Mylar->AddElement(O, 4);

G4cout<<"Temp:"<<expTemp<<G4endl;
G4Material* CF4 = new G4Material("CF4", 4.7332e-4*g/cm3, 2);
CF4->AddElement(C, 1);
CF4->AddElement(F, 4);

// print table
//
G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::ConstructCalorimeter()
{

  // Clean old geometry, if any
  //
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();
 

  // complete the Calor parameters definition
  ComputeCalorParameters();
  
  // Gamma detector Parameters
  //
    G4NistManager* nist = G4NistManager::Instance();
	fDefaultMaterial = nist->FindOrBuildMaterial("CF4");
	G4Material* detec_mat = nist->FindOrBuildMaterial("G4_Galactic");
	G4Material* wire_mat   = nist->FindOrBuildMaterial("Gold");
	G4Material* window_mat   = nist->FindOrBuildMaterial("Mylar");
  
  
  //     
  // World
  //
  fSolidWorld = new G4Tubs("World",                         //its name
                   0,fWorldSizeXY,fWorldSizeZ,0,CLHEP::twopi);  			//its size
                         
  fLogicWorld = new G4LogicalVolume(fSolidWorld,            //its solid
                                   fDefaultMaterial,        //its material
                                   "World");                //its name
                                   
  fPhysiWorld = new G4PVPlacement(0,                        //no rotation
                                 G4ThreeVector(),           //at (0,0,0)
                                 fLogicWorld,             	//its logical volume
                                 "World",                   //its name
                                 0,                         //its mother  volume
                                 false,                  	//no boolean operation
                                 0,                         // copy number
                                 true);                     //copy number
  


	  G4RotationMatrix Ra;
	  Ra.rotateX(-30*deg);
  //
  // Window gap
  //
  //G4double wingappos = fWorldSize+2;
  //G4double wingapH = 2;

	 fwingap = new G4CutTubs("wingap", 0, 5.87*cm, wingapH, 0, CLHEP::twopi,G4ThreeVector(0,0,0),G4ThreeVector(0,0.5*cm,0.87*cm));

	 fLogicwgap = new G4LogicalVolume(fwingap,
	 								 detec_mat,
									 "wingap");
	 fPhysiwgap = new G4PVPlacement(0,
	 								G4ThreeVector(0,0,wingappos),
	 							   fLogicwgap,
								   "wingap",
								   fLogicWorld,
								   false,
								   fCheckOverlaps);

  
  //
  // Window-Mylar
  //
	  G4ThreeVector Ta2; //Window
	  Ta2.setX(0); Ta2.setY(0); Ta2.setZ(winpos);

	 fwindow = new G4Tubs("window", 0,5.87*cm,5.08/2*um,0,CLHEP::twopi);
	 fLogicwin = new G4LogicalVolume(fwindow,
	 								 window_mat,
									 "win");
	 fPhysiwin = new G4PVPlacement(G4Transform3D(Ra,Ta2),
	 							   fLogicwin,
								   "win",
								   fLogicWorld,
								   false,
								   fCheckOverlaps);

  //
  //gap
  //

  	
	fgap = new G4Box("gap",fdESizeXY/2,fdESizeXY/2, fgapSizeZ/2);
  	
	

	  G4double detz = (inter-fdESizeZ)/2;
  for(G4int igap=0;igap<ngap;igap++){
		char fName[16];
		
		sprintf(fName, "gap%d", igap);
		fLogicgap[igap] = new G4LogicalVolume(fgap,
										fDefaultMaterial,
										fName,
										0,
										0,
										0);

		G4double mgappos = gappos + inter*igap;

		G4ThreeVector Ga;
		Ga.setX(0); Ga.setY(0), Ga.setZ(mgappos);
		
		fPhysigap = new G4PVPlacement(G4Transform3D(Ra,Ga),
									  fLogicgap[igap],
									  fName,
									  fLogicWorld,
									  false,
									  0,
									  0);


	 //
	 // Detector
	 //

      fSoliddE = new G4Box("dE",                			//its name
                    fdESizeXY/2,fdESizeXY/2,fdESizeZ/2);	//size
	  cyl = new G4Tubs("cylin",0,5.87*cm,1*mm,0,CLHEP::twopi);
	  
	  subtraction1 = new G4SubtractionSolid("Box-cylin1",fSoliddE,cyl);
      
	  fLogicdE = new G4LogicalVolume(   subtraction1,        	//its solid
                                        fDefaultMaterial,   		//its material
                                        "dE",
										0,
										0,
										0);     			//its name
      
	  G4double	dEpos = detz;

	  fPhysidE = new G4PVPlacement(  0,						 // rotation
	  								 G4ThreeVector(0,0,dEpos),//translation
                                     fLogicdE,           	//its logical volume
                                     "dE",         			//its name
                                     fLogicgap[igap],       //its mother  volume
                                     0,					//copy number
                                     fCheckOverlaps);       //copy number
	  //
	  // Wire
	  // 

	  fSolidwire = new G4Tubs("Wire", 0, wireR,5.87*cm,0,CLHEP::twopi);
	  
	  fLogicwire[igap] = new G4LogicalVolume(fSolidwire,
											   wire_mat,
											   "Wire");

			for(G4int iwire=0;iwire<120;iwire++){
			  G4RotationMatrix Ta;
			  Ta.rotateX(-90*deg);
			  G4ThreeVector Wa;
			  G4double wirex = -5.87+iwire*0.1;
			  G4double wirepos = detz-wireR;
			  Wa.setX(wirex*cm), Wa.setY(0), Wa.setZ(wirepos);
			  fPhysiwire = new G4PVPlacement(G4Transform3D(Ta,Wa),
											fLogicwire[igap],
											 "Wire",
											 fLogicgap[igap],
											 false,
											 iwire,
											 0);

		}// for loop iwire

  
  //                                        
  // Visualization attributes
  //
  
  G4VisAttributes* visdE = new G4VisAttributes(true, G4Colour(1.,0.,1.));
  fLogicdE->SetVisAttributes(visdE);
  
  G4VisAttributes* viswire = new G4VisAttributes(true, G4Colour(1.,1.,0.));
  viswire -> SetForceSolid(true);
  fLogicwire[igap]->SetVisAttributes(viswire);

  G4VisAttributes* viswin = new G4VisAttributes(true, G4Colour(0.,1.,1));
  viswin -> SetForceSolid(true);
  fLogicwin->SetVisAttributes(viswin);

  //fLogicwgap->SetVisAttributes(G4VisAttributes::Invisible);
  	fLogicgap[igap]->SetVisAttributes(G4VisAttributes::Invisible);

}// for loop igap
   
  if(0.0== fDefaultMaterial->GetIonisation()->GetMeanEnergyPerIonPair()){
	SetPairEnergy(35*eV);
  }
	 

  PrintCalorParameters();     
  ConstructField();

  //
  //always return the physical World
  //
 
 return fPhysiWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::PrintCalorParameters()
{

}

void DetectorConstruction::ConstructField()
{
	G4SDManager* SDman = G4SDManager::GetSDMpointer();
	G4String SDname;
	G4String SDname17 = "/MylarSD";
	
//	DetectorSD* MylarSD = new DetectorSD(SDname17);
//	SDman->AddNewDetector(MylarSD);
//	fLogicwin->SetSensitiveDetector(MylarSD);
	
	DetectorSD* detecSD[17];
	for(G4int igap=0; igap<17; igap++){
		char name[16];
		sprintf(name, "/detecSD%02d", igap);
		SDname = name;
		detecSD[igap] = new DetectorSD(SDname);
		SDman->AddNewDetector(detecSD[igap]);
		fLogicgap[igap]->SetSensitiveDetector(detecSD[igap]);
	}


//Field

//	field = new Field();


/*
if (!fEmFieldSetup.Get()){
	Field* fieldSetup = new Field();
	G4AutoDelete::Register(fieldSetup);
	fEmFieldSetup.Put(fieldSetup);
}

	G4bool allLocal = true;
	fLogicwire->SetFieldManager(fEmFieldSetup.Get()->GetLocalFieldManager(), allLocal);
	//fLogicgap1->SetFieldManager(fEmFieldSetup.Get()->GetLocalFieldManager(), allLocal);
*/
}

void DetectorConstruction::SetPairEnergy(G4double val)
{
	if(val > 0.0) {
	  fDefaultMaterial->GetIonisation()->SetMeanEnergyPerIonPair(val);
	}
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
