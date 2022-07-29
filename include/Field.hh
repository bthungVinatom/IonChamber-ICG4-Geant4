#ifndef Field_h
#define Field_h 1

#include "G4ElectricField.hh"
#include "G4UniformElectricField.hh"

class G4FieldManager;
class G4ChordFinder;
class G4EquationOfMotion;
class G4Mag_EqRhs;
class G4EqMagElectricField;
class G4MagIntegratorStepper;
class G4MagInt_Driver;

class Field : public G4ElectricField
{
  public:
	Field();
	 ~Field();

	void SetStepperType(G4int i){fStepperType = i;}

	void SetStepper();

	void SetMinStep(G4double s){fMinStep = s;}

	void GetFieldValue(const G4double Point[3], G4double* Efield) const;

	G4FieldManager* GetLocalFieldManager() {return fLocalFieldManager; }

  protected:
	G4FieldManager*			GetGlobalFieldManager();

	
  private: 

	G4FieldManager*			fFieldManager;
	G4FieldManager*			fLocalFieldManager;
	G4FieldManager*			fLocalFieldManager1;

	G4EqMagElectricField*	fEquation;
	G4EqMagElectricField*	fLocalEquation;
	G4EqMagElectricField*	fLocalEquation1;
	
	G4UniformElectricField*		fEMfield;
	G4UniformElectricField*		fLocalEMfield;
	G4UniformElectricField*		fLocalEMfield1;

	G4ChordFinder*			fChordFinder;
	G4ChordFinder*			fLocalChordFinder;
	G4ChordFinder*			fLocalChordFinder1;

	G4MagIntegratorStepper*	fStepper;
	G4MagIntegratorStepper*	fLocalStepper;
	G4MagIntegratorStepper*	fLocalStepper1;
	
	G4MagInt_Driver*		fIntgrDriver;
	G4MagInt_Driver*		fLocalIntgrDriver;
	G4MagInt_Driver*		fLocalIntgrDriver1;

	G4int					fStepperType;

	G4double				fMinStep;
};

#endif
