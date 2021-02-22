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
/// \file SolenoidMagneticField.hh
/// \brief Definition of the SolenoidMagneticField class

#ifndef SolenoidMagneticField_h
#define SolenoidMagneticField_h 1

#include "globals.hh"
#include "G4MagneticField.hh"

class G4GenericMessenger;

/// Magnetic field

class SolenoidMagneticField : public G4MagneticField
{
  public:
    SolenoidMagneticField();
    virtual ~SolenoidMagneticField();
    
    virtual void GetFieldValue(const G4double point[4],double* field ) const;
    
    void SetField(G4double val) { magnetic_strength_z_ = val; }
    G4double GetField() const { return magnetic_strength_z_; }
    
  private:
    void DefineCommands();

    G4GenericMessenger* messenger_;
    G4double magnetic_strength_z_;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
