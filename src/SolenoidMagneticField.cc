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
//
/// \file SolenoidMagneticField.cc
/// \brief Implementation of the SolenoidMagneticField class

#include "SolenoidMagneticField.hh"

#include "G4GenericMessenger.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SolenoidMagneticField::SolenoidMagneticField()
: G4MagneticField(), 
  messenger_(nullptr), magnetic_strength_z_(1.0*tesla)
{
  // define commands for this class
  DefineCommands();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SolenoidMagneticField::~SolenoidMagneticField()
{ 
  delete messenger_; 
}

void SolenoidMagneticField::GetFieldValue(const G4double [4],double *field) const
{
  field[0] = 0.;
  field[1] = 0.;
  field[2] = magnetic_strength_z_;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SolenoidMagneticField::DefineCommands()
{
  // Define /Solenoid/field command directory using generic messenger class
  messenger_ = new G4GenericMessenger(this, 
                                      "/Solenoid/field/", 
                                      "Field control");

  // fieldValue command 
  auto& valueCmd
    = messenger_->DeclareMethodWithUnit("value","tesla",
                                &SolenoidMagneticField::SetField, 
                                "Set field strength.");
  valueCmd.SetParameterName("field", true);
  valueCmd.SetDefaultValue("1.");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
