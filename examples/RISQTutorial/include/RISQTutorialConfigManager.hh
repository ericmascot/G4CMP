/***********************************************************************\
 * This software is licensed under the terms of the GNU General Public *
 * License version 3 or later. See G4CMP/LICENSE for the full license. *
\***********************************************************************/

#ifndef RISQTutorialConfigManager_hh
#define RISQTutorialConfigManager_hh 1

// $Id$
// File:  RISQTutorialConfigManager.hh
//
// Description:	Singleton container class for user configuration of G4CMP
//		phonon example. Looks for environment variables	at
//		initialization to set default values; active values may be
//		changed via macro commands (see RISQTutorialConfigMessenger).
//
// 20170816  M. Kelsey -- Extract hit filename from G4CMPConfigManager.

#include "globals.hh"

class RISQTutorialConfigMessenger;


class RISQTutorialConfigManager {
public:
  ~RISQTutorialConfigManager();	// Must be public for end-of-job cleanup
  static RISQTutorialConfigManager* Instance();   // Only needed by static accessors

  // Access current values
  static G4double GetVoltage() { return Instance()->voltage; }
  static G4double GetEPotScale() { return Instance()->epotScale; }
  static const G4String &GetEPotFile() { return Instance()->EPot_file; }
  static const G4String &GetHitOutput() { return Instance()->Hit_file; }
  static const G4String &GetPrimaryOutput() { return Instance()->Primary_file; }
  static G4double GetQAbsProb() { return Instance()->qAbsProb; }
  static G4double GetQReflProb() { return Instance()->qReflProb; }

  // Change values (e.g., via Messenger)
  static void SetHitOutput(const G4String& name)
    { Instance()->Hit_file=name; UpdateGeometry(); }
  static void SetPrimaryOutput(const G4String& name)
    { Instance()->Hit_file=name; UpdateGeometry(); }
  static void SetVoltage(G4double value)
    { Instance()->voltage = value; UpdateGeometry(); }
  static void SetEPotScale(G4double value)
    { Instance()->epotScale = value; UpdateGeometry(); }
  static void SetEPotFile(const G4String &name)
    { Instance()->EPot_file = name; UpdateGeometry(); }
  static void SetQAbsProb(G4double value)
    { Instance()->qAbsProb=value; UpdateGeometry(); }
  static void SetQReflProb(G4double value)
    { Instance()->qReflProb=value; UpdateGeometry(); }


  static void UpdateGeometry();

private:
  RISQTutorialConfigManager();		// Singleton: only constructed on request
  RISQTutorialConfigManager(const RISQTutorialConfigManager&) = delete;
  RISQTutorialConfigManager(RISQTutorialConfigManager&&) = delete;
  RISQTutorialConfigManager& operator=(const RISQTutorialConfigManager&) = delete;
  RISQTutorialConfigManager& operator=(RISQTutorialConfigManager&&) = delete;

  static RISQTutorialConfigManager* theInstance;

private:
  G4double voltage;      // Uniform field voltage ($G4CMP_VOLTAGE)
  G4double epotScale;    // Scale factor for EPot ($G4CMP_EPOT_SCALE)
  G4String EPot_file;    // Name of E-field file ($G4CMP_EPOT_FILE)
  G4String Hit_file;     // Output file of e/h hits ($G4CMP_HIT_FILE)
  G4String Primary_file; // Output file of primaries
  G4double qAbsProb;     // Absorption probability
  G4double qReflProb;    // Reflection probability

  RISQTutorialConfigMessenger* messenger;
};

#endif	/* RISQTutorialConfigManager_hh */
