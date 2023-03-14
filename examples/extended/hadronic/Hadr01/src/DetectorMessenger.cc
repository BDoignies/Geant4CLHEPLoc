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
/// \file hadronic/Hadr01/src/DetectorMessenger.cc
/// \brief Implementation of the DetectorMessenger class
//
//
/////////////////////////////////////////////////////////////////////////
//
// DetectorMessenger
//
// Created: 31.01.03 V.Ivanchenko
//
// Modified:
// 04.06.2006 Adoptation of Hadr01 (V.Ivanchenko)
// 16.11.2006 Add beamCmd (V.Ivanchenko)
//
////////////////////////////////////////////////////////////////////////
//

#include "DetectorMessenger.hh"

#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4HadronicParameters.hh"
#include "HistoManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::DetectorMessenger(DetectorConstruction * Det)
: G4UImessenger(), fDetector(Det),
  fTestDir(0),
  fMatCmd(0),
  fMat1Cmd(0),
  fRCmd(0),
  fLCmd(0),
  fEdepCmd(0),
  fBinCmd(0),
  fNOfAbsCmd(0),
  fVerbCmd(0),
  fBeamCmd(0)
{
  fTestDir = new G4UIdirectory("/testhadr/");
  fTestDir->SetGuidance(" Hadronic Extended Example.");

  fMatCmd = new G4UIcmdWithAString("/testhadr/TargetMat",this);
  fMatCmd->SetGuidance("Select Material for the target");
  fMatCmd->SetParameterName("tMaterial",false);
  fMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fMat1Cmd = new G4UIcmdWithAString("/testhadr/WorldMat",this);
  fMat1Cmd->SetGuidance("Select Material for world");
  fMat1Cmd->SetParameterName("wMaterial",false);
  fMat1Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fRCmd = new G4UIcmdWithADoubleAndUnit("/testhadr/TargetRadius",this);
  fRCmd->SetGuidance("Set radius of the target");
  fRCmd->SetParameterName("radius",false);
  fRCmd->SetUnitCategory("Length");
  fRCmd->SetRange("radius>0");
  fRCmd->AvailableForStates(G4State_PreInit);

  fLCmd = new G4UIcmdWithADoubleAndUnit("/testhadr/TargetLength",this);
  fLCmd->SetGuidance("Set length of the target");
  fLCmd->SetParameterName("length",false);
  fLCmd->SetUnitCategory("Length");
  fLCmd->SetRange("length>0");
  fLCmd->AvailableForStates(G4State_PreInit);

  fBinCmd = new G4UIcmdWithAnInteger("/testhadr/NumberOfBinsE",this);
  fBinCmd->SetGuidance("Set number of bins for Energy");
  fBinCmd->SetParameterName("NEbins",false);
  fBinCmd->AvailableForStates(G4State_PreInit);

  fNOfAbsCmd = new G4UIcmdWithAnInteger("/testhadr/NumberDivZ",this);
  fNOfAbsCmd->SetGuidance("Set number of slices");
  fNOfAbsCmd->SetParameterName("NZ",false);
  fNOfAbsCmd->AvailableForStates(G4State_PreInit);

  fEdepCmd = new G4UIcmdWithADoubleAndUnit("/testhadr/MaxEdep",this);
  fEdepCmd->SetGuidance("Set max energy in histogram");
  fEdepCmd->SetParameterName("edep",false);
  fEdepCmd->SetUnitCategory("Energy");
  fEdepCmd->SetRange("edep>0");
  fEdepCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fBeamCmd = new G4UIcmdWithABool("/testhadr/DefaultBeamPosition",this);
  fBeamCmd->SetGuidance("Use default beam position");
  fBeamCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fVerbCmd = new G4UIcmdWithAnInteger("/testhadr/Verbose",this);
  fVerbCmd->SetGuidance("Set verbose for ");
  fVerbCmd->SetParameterName("verb",false);
  fVerbCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fBCCmd = new G4UIcmdWithABool("/testhadr/BCParticles",this);
  fBCCmd->SetGuidance("Enable b-, c- hadronic physics");
  fBCCmd->SetParameterName("BCparticles",false);
  fBCCmd->AvailableForStates(G4State_PreInit);

  fHNCmd = new G4UIcmdWithABool("/testhadr/HyperNuclei",this);
  fHNCmd->SetGuidance("Enable hyper-nuclei hadronic physics");
  fHNCmd->SetParameterName("HyperNuclei",false);
  fHNCmd->AvailableForStates(G4State_PreInit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::~DetectorMessenger()
{
  delete fMatCmd;
  delete fMat1Cmd;
  delete fRCmd;
  delete fLCmd;
  delete fBinCmd;
  delete fNOfAbsCmd;
  delete fTestDir;
  delete fBeamCmd;
  delete fVerbCmd;
  delete fEdepCmd;
  delete fBCCmd;
  delete fHNCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  HistoManager* h = HistoManager::GetPointer();
  if( command == fMatCmd ) {
    fDetector->SetTargetMaterial(newValue);
  } else if( command == fMat1Cmd ) {
    fDetector->SetWorldMaterial(newValue);
  } else if( command == fRCmd ) {
    h->SetTargetRadius(fRCmd->GetNewDoubleValue(newValue));
  } else if( command == fLCmd ) {
    h->SetTargetLength(fLCmd->GetNewDoubleValue(newValue));
  } else if( command == fNOfAbsCmd ) {
    h->SetNumberOfSlices(fNOfAbsCmd->GetNewIntValue(newValue));
  } else if( command == fBinCmd ) {
    h->SetNumberOfBinsE(fBinCmd->GetNewIntValue(newValue));
  } else if( command == fVerbCmd ) {
    h->SetVerbose(fVerbCmd->GetNewIntValue(newValue));
  } else if (command == fBeamCmd) {
    h->SetDefaultBeamPositionFlag(fBeamCmd->GetNewBoolValue(newValue));
  } else if (command == fEdepCmd) {
    h->SetMaxEnergyDeposit(fEdepCmd->GetNewDoubleValue(newValue));
  } else if( command == fBCCmd ) {
    G4HadronicParameters::Instance()->SetEnableBCParticles(fBCCmd->GetNewBoolValue(newValue));
  } else if( command == fHNCmd ) {
    G4HadronicParameters::Instance()->SetEnableHyperNuclei(fHNCmd->GetNewBoolValue(newValue));
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

