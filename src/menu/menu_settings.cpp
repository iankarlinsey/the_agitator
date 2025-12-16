#include "menu_settings.hpp"
#include "menu_config.hpp"
#include <avr/pgmspace.h>
#include <stdio.h>

/* ===============================
   Descriptor table
   ===============================

   IMPORTANT:
   - This table MUST match SettingId enum order
   - Storage pointers come from the model
   - This is the ONLY place behavior is defined
*/
extern const SettingDefinition SETTING_DESCS[];

/* ===============================
   Formatting helpers
   =============================== */

static char fmtBuf[20];

/* ===============================
   Public API
   =============================== */

const char *menuGetSettingValueString(SettingId id)
{
  if (id >= SET_COUNT)
    return nullptr;

  const SettingDefinition &d = SETTING_DEFINITIONS[id];

  switch (d.type) {
    case SETTYPE_ENUM: {
      uint8_t v = *(uint8_t *)d.storage;
      if (v >= d.aux) return "?";

      const char *const *tbl = (const char *const *)d.data; // PROGMEM table
      PGM_P p = (PGM_P)pgm_read_ptr(&tbl[v]);
      strcpy_P(fmtBuf, p);
      return fmtBuf;
    }

    case SETTYPE_UINT8:
      snprintf(fmtBuf, sizeof(fmtBuf), "%u",
               *(uint8_t *)d.storage);
      return fmtBuf;

    case SETTYPE_UINT16:
      snprintf(fmtBuf, sizeof(fmtBuf), "%u",
               *(uint16_t *)d.storage);
      return fmtBuf;

    case SETTYPE_TIME: 
    {
      uint16_t sec = *(uint16_t *)d.storage;
      uint8_t mm = sec / 60;
      uint8_t ss = sec % 60;
      snprintf(fmtBuf, sizeof(fmtBuf), "%02u:%02u", mm, ss);
      return fmtBuf;
    }

    case SETTYPE_STRING:
      return (const char *)d.storage;
  }

  return "?";
}

void menuBeginSettingEdit(SettingId)
{
  // Editor dispatch will live here
}

void menuCommitSettingEdit(void)
{
  // no-op for now
}

void menuCancelSettingEdit(void)
{
  // no-op for now
}

uint8_t menuGetSettingValue(SettingId id)
{
  const SettingDefinition &d = SETTING_DEFINITIONS[id];

  switch (d.type)
  {
    case SETTYPE_ENUM:
    case SETTYPE_UINT8:
      return *(uint8_t *)d.storage;

    case SETTYPE_TIME:
      // cursor/index not meaningful → return 0
      return 0;

    default:
      return 0;
  }
}

void menuSetSetting(SettingId id, uint8_t value)
{
  const SettingDefinition &d = SETTING_DEFINITIONS[id];
  *(uint8_t*)d.storage = value;
}
