#include "Field.hh"

#include "G4UniformElectricField.hh"
#include "G4UniformMagField.hh"
#include "G4MagneticField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4EquationOfMotion.hh"
#include "G4EqMagElectricField.hh"
#include "G4Mag_UsualEqRhs.hh"
#include "G4MagIntegratorStepper.hh"
#include "G4MagIntegratorDriver.hh"
#include "G4ChordFinder.hh"

#include "G4ExplicitEuler.hh"
#include "G4ImplicitEuler.hh"
#include "G4SimpleRunge.hh"
#include "G4SimpleHeum.hh"
#include "G4ClassicalRK4.hh"
#include "G4HelixExplicitEuler.hh"
#include "G4HelixImplicitEuler.hh"
#include "G4HelixSimpleRunge.hh"
#include "G4CashKarpRKF45.hh"
#include "G4RKG3_Stepper.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

Field::Field()
: fFieldManager(0),
  fChordFinder(0),
  fEMfield(0),
  fStepper(0),
  fEquation(0),
  fIntgrDriver(0),
  fLocalFieldManager(0),
  fLocalChordFinder(0),
  fLocalEMfield(0),
  fLocalStepper(0),
  fLocalEquation(0),
  fLocalIntgrDriver(0),
  fLocalFieldManager1(0),
  fLocalChordFinder1(0),
  fLocalEMfield1(0),
  fLocalStepper1(0),
  fLocalEquation1(0),
  fLocalIntgrDriver1(0),
  fStepperType(4),
  fMinStep(0.0010*mm)
  {

	//G4ThreeVector FieldVector = G4ThreeVector(0,0,0);
	//G4ThreeVector FieldVector1 = G4ThreeVector(0,300*volt/cm,0);
	//G4ThreeVector FieldVector2 = G4ThreeVector(0,-300*volt/cm,0);
	//FieldVector1.rotateX(60*deg);
	//FieldVector2.rotateX(240*deg);

	//fEMfield	=	new G4UniformElectricField(FieldVector);
	//fLocalEMfield	=	new G4UniformElectricField(FieldVector1);
	//fLocalEMfield1	=	new G4UniformElectricField(FieldVector2);
	
	fEquation	=	new G4EqMagElectricField(this);
	//fLocalEquation	=	new G4EqMagElectricField(this);
	//fLocalEquation1	=	new G4EqMagElectricField(fLocalEMfield1);
	
	fFieldManager	=	G4TransportationManager::GetTransportationManager()->GetFieldManager();
	//fLocalFieldManager	=	new G4FieldManager();
	//fLocalFieldManager1	=	new G4FieldManager();

	SetStepper();

	//G4cout<<"The minimal step is equal to "<<fMinStep/mm<<"mm"<<G4endl;

	fFieldManager->SetDetectorField(this);
	//fLocalFieldManager->SetDetectorField(this);
	//fLocalFieldManager1->SetDetectorField(fLocalEMfield1);

    if (fChordFinder) delete fChordFinder;
    //if (fLocalChordFinder) delete fLocalChordFinder;
    //if (fLocalChordFinder1) delete fLocalChordFinder1;

	fIntgrDriver = new G4MagInt_Driver(fMinStep,
									   fStepper,
									   fStepper->GetNumberOfVariables());
	//fLocalIntgrDriver = new G4MagInt_Driver(fMinStep,
	//								   		fLocalStepper,
	//								   		fLocalStepper->GetNumberOfVariables());
	//fLocalIntgrDriver1 = new G4MagInt_Driver(fMinStep,
	//								   		fLocalStepper1,
	//								   		fLocalStepper1->GetNumberOfVariables());
	
	fChordFinder = new G4ChordFinder(fIntgrDriver);
	//fLocalChordFinder = new G4ChordFinder(fLocalIntgrDriver);
	//fLocalChordFinder1 = new G4ChordFinder(fLocalIntgrDriver1);

	fFieldManager->SetChordFinder(fChordFinder);
	//fLocalFieldManager->SetChordFinder(fLocalChordFinder);
	//fLocalFieldManager1->SetChordFinder(fLocalChordFinder1);
  }

Field::~Field()
{
  delete fEMfield;
  delete fStepper;
  delete fChordFinder;
  }

void Field::SetStepper()
   {
   // Set stepper according to the stepper type
   
     G4int nvar = 8;
   
     if (fStepper) delete fStepper;
   
     switch ( fStepperType )
     {
       case 0:
         fStepper = new G4ExplicitEuler( fEquation, nvar );
         fLocalStepper = new G4ExplicitEuler( fLocalEquation, nvar );
         fLocalStepper1 = new G4ExplicitEuler( fLocalEquation1, nvar );
         G4cout<<"G4ExplicitEuler is calledS"<<G4endl;
         break;
       case 1:
         fStepper = new G4ImplicitEuler( fEquation, nvar );
         fLocalStepper = new G4ImplicitEuler( fLocalEquation, nvar );
         fLocalStepper1 = new G4ImplicitEuler( fLocalEquation1, nvar );
         G4cout<<"G4ImplicitEuler is called"<<G4endl;
         break;
       case 2:
         fStepper = new G4SimpleRunge( fEquation, nvar );
         fLocalStepper = new G4SimpleRunge( fLocalEquation, nvar );
         fLocalStepper1 = new G4SimpleRunge( fLocalEquation1, nvar );
         G4cout<<"G4SimpleRunge is called"<<G4endl;
         break;
       case 3:
         fStepper = new G4SimpleHeum( fEquation, nvar );
         fLocalStepper = new G4SimpleHeum( fLocalEquation, nvar );
         fLocalStepper1 = new G4SimpleHeum( fLocalEquation1, nvar );
         G4cout<<"G4SimpleHeum is called"<<G4endl;
         break;
       case 4:
         fStepper = new G4ClassicalRK4( fEquation, nvar );
         fLocalStepper = new G4ClassicalRK4( fLocalEquation, nvar );
         fLocalStepper1 = new G4ClassicalRK4( fLocalEquation1, nvar );
         G4cout<<"G4ClassicalRK4 (default) is called"<<G4endl;
         break;
       case 5:
         fStepper = new G4CashKarpRKF45( fEquation, nvar );
         fLocalStepper = new G4CashKarpRKF45( fLocalEquation, nvar );
         fLocalStepper1 = new G4CashKarpRKF45( fLocalEquation1, nvar );
         G4cout<<"G4CashKarpRKF45 is called"<<G4endl;
         break;
       case 6:
         fStepper = 0; // new G4RKG3_Stepper( fEquation, nvar );
         fLocalStepper = 0; // new G4RKG3_Stepper( fEquation, nvar );
         fLocalStepper1 = 0; // new G4RKG3_Stepper( fEquation, nvar );
         G4cout<<"G4RKG3_Stepper is not currently working for Electric Field"
               <<G4endl;
         break;
       case 7:
         fStepper = 0; // new G4HelixExplicitEuler( fEquation );
         fLocalStepper = 0; // new G4HelixExplicitEuler( fEquation );
         fLocalStepper1 = 0; // new G4HelixExplicitEuler( fEquation );
         G4cout<<"G4HelixExplicitEuler is not valid for Electric Field"<<G4endl;
         break;
       case 8:
         fStepper = 0; // new G4HelixImplicitEuler( fEquation );
         fLocalStepper = 0; // new G4HelixImplicitEuler( fEquation );
         fLocalStepper1 = 0; // new G4HelixImplicitEuler( fEquation );
         G4cout<<"G4HelixImplicitEuler is not valid for Electric Field"<<G4endl;
		 break;
		      default: fStepper = 0;
		    }
		  }

void Field::GetFieldValue(const G4double Point[3], G4double* Efield) const
{

const G4double Er = -300*volt/cm;

G4double Ey, Ez;

G4double posR = std::sqrt(std::pow(Point[1],2) + std::pow(Point[2],2));
G4double cos_theta, sin_theta;

if (posR>0){
	cos_theta = Point[1]/(G4double)posR;
	sin_theta = Point[2]/(G4double)posR;
	Ey = -1*Er*cos_theta;
	Ez = -1*Er*sin_theta;
} else{
	Ey=0;
	Ez=0;
}

Efield[0]=0;
Efield[1]=0;
Efield[2]=10*cm;

Efield[3]=0;
Efield[4]=Ey;
Efield[5]=Ez;


//G4cout << "Point y = :" << Point[1] << G4endl;
//G4cout << "Point z = :" << Point[2] << G4endl;
//G4cout << "electric field at y axis = :" << Ey << G4endl;
//G4cout << "electric field at z axis = :" << Ez << G4endl;


return;


}



