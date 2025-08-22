/***********************************************************************\
 * This software is licensed under the terms of the GNU General Public *
 * License version 3 or later. See G4CMP/LICENSE for the full license. *
\***********************************************************************/

// $Id$
// File:  RISQTutorialConfigMessenger.cc
//
// Description:	Macro command defitions to set user configuration in
//		RISQTutorialConfigManager.
//
// 20170816  Michael Kelsey

#include "RISQTutorialConfigMessenger.hh"
#include "RISQTutorialConfigManager.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"


// Constructor and destructor

RISQTutorialConfigMessenger::RISQTutorialConfigMessenger(RISQTutorialConfigManager* mgr)
  : G4UImessenger("/g4cmp/", "User configuration for G4CMP phonon example"),
    theManager(mgr), hitsCmd(nullptr), primaryCmd(nullptr), fileCmd(nullptr),
    voltageCmd(nullptr), escaleCmd(nullptr), qAbsProbCmd(nullptr), qReflProbCmd(nullptr) {
  hitsCmd = CreateCommand<G4UIcmdWithAString>("HitsFile",
    "Set filename for output of phonon hit locations");
  primaryCmd = CreateCommand<G4UIcmdWithAString>("PrimaryFile",
    "Set filename for output of phonon hit locations");
  fileCmd = CreateCommand<G4UIcmdWithAString>("PotentialFile",
    "Set filename for Ramo potential ASCII data file with columns (x,y,z,V)");
  voltageCmd = CreateCommand<G4UIcmdWithADoubleAndUnit>("Voltage",
    "Set voltage for uniform electric field");
  voltageCmd->SetUnitCategory("Electric potential");
  voltageCmd->SetGuidance("Voltage across chip (E=V/d where d=dp_housingDimZ).");
  escaleCmd = CreateCommand<G4UIcmdWithADouble>("scaleEPot",
		"Set a scale factor for voltages in EPot electric field file");
  qAbsProbCmd = CreateCommand<G4UIcmdWithADouble>("qAbsProb",
    "Set probability to absorb charge carrier");
  qReflProbCmd = CreateCommand<G4UIcmdWithADouble>("qReflProb",
    "Set probability to reflect charge carrier");
}


RISQTutorialConfigMessenger::~RISQTutorialConfigMessenger() {
  delete hitsCmd; hitsCmd=nullptr;
  delete primaryCmd; primaryCmd=nullptr;
  delete fileCmd; fileCmd=nullptr;
  delete voltageCmd; voltageCmd=nullptr;
  delete escaleCmd; escaleCmd=nullptr;
  delete qAbsProbCmd; qAbsProbCmd=nullptr;
  delete qReflProbCmd; qReflProbCmd=nullptr;
}


// Parse user input and add to configuration

void RISQTutorialConfigMessenger::SetNewValue(G4UIcommand* cmd, G4String value) {
  if (cmd == hitsCmd) theManager->SetHitOutput(value);
  if (cmd == primaryCmd) theManager->SetPrimaryOutput(value);
  if (cmd == fileCmd) theManager->SetEPotFile(value);
  if (cmd == voltageCmd) theManager->SetVoltage(voltageCmd->GetNewDoubleValue(value));
  if (cmd == escaleCmd) theManager->SetEPotScale(escaleCmd->GetNewDoubleValue(value));
  if (cmd == qAbsProbCmd) theManager->SetQAbsProb(qAbsProbCmd->GetNewDoubleValue(value));
  if (cmd == qReflProbCmd) theManager->SetQReflProb(qReflProbCmd->GetNewDoubleValue(value));
}
