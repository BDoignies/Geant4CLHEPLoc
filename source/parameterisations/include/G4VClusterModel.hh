//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//
// $Id: G4VClusterModel.hh,v 1.1.4.1 2001/06/28 19:10:34 gunter Exp $
// GEANT4 tag $Name:  $
//
// 
///////////////////////////////////////////////////////////////////////////
// 
// Base class for 'fast' parametrisation models describing  ionisation clusters
// created in some G4Envelope. 
// 
// History:
// 14.07.00 V. Grichine first version 
//


#ifndef G4VClusterModel_h
#define G4VClusterModel_h 1


#include "globals.hh"
#include "templates.hh"
#include "G4PAIonisation.hh"
#include "G4VFastSimulationModel.hh"
#include "G4Step.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include <g4rw/tvordvec.h>


class G4VClusterModel : public G4VFastSimulationModel
{
public:

   G4VClusterModel (const G4String& modelName,G4LogicalVolume* anEnvelope);
   virtual  ~G4VClusterModel ();

  // Pure virtual functions from base class

  virtual G4bool IsApplicable(const G4ParticleDefinition&) = 0 ;
 
  virtual G4bool ModelTrigger(const G4FastTrack &) = 0 ;
 
  virtual void DoIt(const G4FastTrack&, G4FastStep&) = 0 ;

protected:

  void BuildDetectorResponse();

  void AssignClusterHit(const G4ThreeVector& position, G4double energy) ;

  void FillFakeStep(const G4ThreeVector& position, G4double energy) ;

protected:

  G4Step*         fFakeStep ;
  G4StepPoint*    fFakePreStepPoint ; 
  G4StepPoint*    fFakePostStepPoint ; 

  G4VTouchable*   fTouchable ;
  G4Navigator*    fNavigator ;
  G4bool          fNavigatorSetup ;

  G4RWTValOrderedVector<G4ThreeVector> fClusterPositionVector ; 
  G4RWTValOrderedVector<G4double>      fClusterEnergyVector ; 
};

#endif