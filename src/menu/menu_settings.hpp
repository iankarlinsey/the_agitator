#pragma once

#include <stdint.h>

/* ===============================
   Setting Types
   =============================== */
enum SettingType : uint8_t 
{
  SETTYPE_ENUM,
  SETTYPE_UINT8,
  SETTYPE_UINT16,
  SETTYPE_TIME,     // seconds -> MM:SS
  SETTYPE_STRING
};

struct SettingPreset;

struct SettingDefinition 
{
  SettingType type;
  void *storage;
  uint8_t aux;                    // enum count OR preset count
  const void *data;               // enum strings OR SettingPreset*
};

/* ===============================
   Public API used by menu system
   =============================== */

enum SettingId : uint8_t;

// Returns pointer to a static buffer or PROGMEM string
const char *menuGetSettingValueString(SettingId id);

// Begin editing a setting (editor dispatch later)
void menuBeginSettingEdit(SettingId id);

// Commit / cancel hooks (stubbed for now)
void menuCommitSettingEdit(void);
void menuCancelSettingEdit(void);

uint8_t menuGetSettingValue(SettingId id);
void    menuSetSetting(SettingId id, uint8_t value);

