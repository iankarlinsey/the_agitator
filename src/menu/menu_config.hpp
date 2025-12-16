// menu_model.hpp
#pragma once

#include <Arduino.h>
#include <avr/pgmspace.h>
#include "menu_defs.hpp"
#include "menu_settings.hpp"

// menu_config.hpp
// This file defines the entire menu and configuration surface.
// Edit THIS file to change the UI or settings.
// No logic should be added here.

/*
MENU_PAGES[]                            MENU_ITEMS[]
-----------                            -----------
[page] --> (firstItemIdx,itemCount) --->  [i] label
                                           type
                                           target  -------------------+
                                           valueId ----------------+  |
                                           param ---------------+  |  |
                                                                |  |  |
                                                                v  v  v
                                                               (A)(B)(C)

(A) target goes to ONE of:
    - MenuPageId   (if type = MENU_SUBMENU or MENU_ENUM_SUB)
    - ActionId     (if type = MENU_ACTION)
    - SettingId    (if type = MENU_SETTING_OP)

(B) valueId goes to ONE of:
    - SettingId    (if type = MENU_SUBMENU or MENU_ENUM_SUB)  [display / edit]
    - SettingOp    (if type = MENU_SETTING_OP)                 [OP_PRESET / OP_ENTER_EDITOR]
    - unused       (if type = MENU_ACTION)

(C) param goes to:
    - presetIndex  (if type = MENU_SETTING_OP and valueId = OP_PRESET)
    - unused/other (otherwise)


SettingId  --->  SETTING_DEFINITIONS[SettingId]  --->  storage (cfg.*)
                         |
                         +--> presets[] (SettingPreset[])
*/

/* ===============================
   Strings (PROGMEM)
   =============================== */
static const char STR_MAIN[]    PROGMEM = "Main Menu";
static const char STR_PARAMS[]  PROGMEM = "Parameters";
static const char STR_MANUAL[]  PROGMEM = "Manual";
static const char STR_MODESEL[] PROGMEM = "Select Mode";
static const char STR_TIMESEL[] PROGMEM = "Set Timer";
static const char STR_SPEEDSEL[] PROGMEM = "Set Speed";
static const char STR_DWELLSEL[] PROGMEM = "End Dwell";
static const char STR_ACCELSEL[] PROGMEM = "Acceleration";
static const char STR_FWDSEL[]   PROGMEM = "Fwd Speed";
static const char STR_REVSEL[]   PROGMEM = "Rev Speed";
static const char STR_BIASSEL[]  PROGMEM = "Bias";
static const char STR_VAMPSEL[]  PROGMEM = "Vib Amp";
static const char STR_VFREQSEL[] PROGMEM = "Vib Freq";
static const char STR_VBURSTSEL[] PROGMEM = "Vib Burst";

/* ---- Main labels ---- */
static const char STR_LBL_MODE[]   PROGMEM = "Mode";
static const char STR_LBL_PARAMS[] PROGMEM = "Parameters";
static const char STR_LBL_TIMER[]  PROGMEM = "Timer";
static const char STR_LBL_RUN[]    PROGMEM = "Run";
static const char STR_LBL_MANUAL[] PROGMEM = "Manual";

/* ---- Parameter labels ---- */
static const char STR_LBL_SPEED[]  PROGMEM = "Speed";
static const char STR_LBL_DWELL[]  PROGMEM = "End Dwell";
static const char STR_LBL_ACCEL[]  PROGMEM = "Accel";
static const char STR_LBL_FWD[]    PROGMEM = "Fwd Speed";
static const char STR_LBL_REV[]    PROGMEM = "Rev Speed";
static const char STR_LBL_BIAS[]   PROGMEM = "Bias";
static const char STR_LBL_VAMP[]   PROGMEM = "Vib Amp";
static const char STR_LBL_VFREQ[]  PROGMEM = "Vib Freq";
static const char STR_LBL_VBURST[] PROGMEM = "Vib Burst";

/* ---- Manual labels ---- */
static const char STR_MAN_LEFT[]  PROGMEM = "Move Left";
static const char STR_MAN_RIGHT[] PROGMEM = "Move Right";
static const char STR_MAN_VIB[]   PROGMEM = "Vibrate";
static const char STR_MAN_OFF[]   PROGMEM = "Motor Off";

/* ---- Mode value strings ---- */
static const char STR_MODE_SWEEP[]     PROGMEM = "Sweep";
static const char STR_MODE_RESONANT[]  PROGMEM = "Resonant";
static const char STR_MODE_MICROVIB[]  PROGMEM = "Micro Vib";
static const char STR_MODE_HYBRID[]    PROGMEM = "Hybrid";

/* ---- Timer preset strings ---- */
static const char STR_TMR_2M[]  PROGMEM = "02:00";
static const char STR_TMR_5M[]  PROGMEM = "05:00";
static const char STR_TMR_10M[] PROGMEM = "10:00";
static const char STR_TMR_15M[] PROGMEM = "15:00";
static const char STR_TMR_20M[] PROGMEM = "20:00";

/* ---- Accel strings ---- */
static const char STR_ACCEL_SOFT[] PROGMEM = "Soft";
static const char STR_ACCEL_FAST[] PROGMEM = "Fast";

/* ---- Speed preset strings ---- */
static const char STR_SPD_80[]  PROGMEM = "80";
static const char STR_SPD_120[] PROGMEM = "120";
static const char STR_SPD_160[] PROGMEM = "160";
static const char STR_SPD_200[] PROGMEM = "200";
static const char STR_SPD_240[] PROGMEM = "240";

/* ---- Dwell preset strings ---- */
static const char STR_DWL_0[]   PROGMEM = "0ms";
static const char STR_DWL_100[] PROGMEM = "100ms";
static const char STR_DWL_200[] PROGMEM = "200ms";
static const char STR_DWL_500[] PROGMEM = "500ms";

/* ---- Bias preset strings ---- */
static const char STR_BIAS_0[]  PROGMEM = "0";
static const char STR_BIAS_1[]  PROGMEM = "1";
static const char STR_BIAS_2[]  PROGMEM = "2";
static const char STR_BIAS_3[]  PROGMEM = "3";

/* ---- Vib presets ---- */
static const char STR_VAMP_1[] PROGMEM = "1";
static const char STR_VAMP_2[] PROGMEM = "2";
static const char STR_VAMP_3[] PROGMEM = "3";
static const char STR_VAMP_4[] PROGMEM = "4";

static const char STR_VFREQ_5[]  PROGMEM = "5Hz";
static const char STR_VFREQ_10[] PROGMEM = "10Hz";
static const char STR_VFREQ_20[] PROGMEM = "20Hz";
static const char STR_VFREQ_30[] PROGMEM = "30Hz";

static const char STR_VBURST_OFF[] PROGMEM = "Off";
static const char STR_VBURST_ON[]  PROGMEM = "On";

static const char STR_CUSTOM[] PROGMEM = "Custom";

/* ===============================
   Page IDs
   =============================== */
enum MenuPageId : uint8_t {
  PAGE_MAIN = 0,
  PAGE_PARAMS,
  PAGE_MANUAL,

  PAGE_MODE_SELECT,
  PAGE_TIMER_MENU,   // <-- timer submenu (presets + custom)
  PAGE_TIMER_EDIT,   // <-- custom editor

  PAGE_SPEED_SELECT,
  PAGE_DWELL_SELECT,
  PAGE_ACCEL_SELECT,
  PAGE_FWD_SELECT,
  PAGE_REV_SELECT,
  PAGE_BIAS_SELECT,
  PAGE_VAMP_SELECT,
  PAGE_VFREQ_SELECT,
  PAGE_VBURST_SELECT,

  PAGE_COUNT
};


/* ===============================
   Setting IDs
   =============================== */
enum SettingId : uint8_t {
  SET_NONE = 0,
  SET_MODE,
  SET_TIMER_SECONDS,

  SET_SPEED,
  SET_END_DWELL,
  SET_ACCEL,

  SET_FWD_SPEED,
  SET_REV_SPEED,
  SET_BIAS,

  SET_VIB_AMP,
  SET_VIB_FREQ,
  SET_VIB_BURST,

  SET_COUNT
};


/* ---- Mode value strings ---- */
static const char *const MODE_STRINGS[] PROGMEM = 
{
  STR_MODE_SWEEP,
  STR_MODE_RESONANT,
  STR_MODE_MICROVIB,
  STR_MODE_HYBRID
};

/* ===============================
   Action IDs
   =============================== */
enum ActionId : uint8_t {
  ACTION_NONE = 0,
  // Main actions
  ACTION_RUN,

  // Manual actions
  ACTION_MAN_LEFT,
  ACTION_MAN_RIGHT,
  ACTION_MAN_VIB,
  ACTION_MAN_OFF,

  // Timer preset actions (write SET_TIMER_PRESET and return)
  ACTION_SET_TMR_2M,
  ACTION_SET_TMR_5M,
  ACTION_SET_TMR_10M,
  ACTION_SET_TMR_15M,
  ACTION_SET_TMR_20M,

  // Speed preset actions (write SET_SPEED and return)
  ACTION_SET_SPD_80,
  ACTION_SET_SPD_120,
  ACTION_SET_SPD_160,
  ACTION_SET_SPD_200,
  ACTION_SET_SPD_240,

  // Dwell preset actions (write SET_END_DWELL and return)
  ACTION_SET_DWL_0,
  ACTION_SET_DWL_100,
  ACTION_SET_DWL_200,
  ACTION_SET_DWL_500,

  // Fwd speed preset actions (write SET_FWD_SPEED and return)
  ACTION_SET_FWD_120,
  ACTION_SET_FWD_160,
  ACTION_SET_FWD_200,
  ACTION_SET_FWD_240,

  // Rev speed preset actions (write SET_REV_SPEED and return)
  ACTION_SET_REV_120,
  ACTION_SET_REV_160,
  ACTION_SET_REV_200,
  ACTION_SET_REV_240,

  // Bias preset actions (write SET_BIAS and return)
  ACTION_SET_BIAS_0,
  ACTION_SET_BIAS_1,
  ACTION_SET_BIAS_2,
  ACTION_SET_BIAS_3,

  // Vib preset actions (write SET_VIB_AMP / SET_VIB_FREQ / SET_VIB_BURST and return)
  ACTION_SET_VAMP_1,
  ACTION_SET_VAMP_2,
  ACTION_SET_VAMP_3,
  ACTION_SET_VAMP_4,

  ACTION_SET_VFREQ_5,
  ACTION_SET_VFREQ_10,
  ACTION_SET_VFREQ_20,
  ACTION_SET_VFREQ_30,
};

static const char *const VBURST_STRINGS[] PROGMEM = {
  STR_VBURST_OFF,
  STR_VBURST_ON
};


// What concrete values are valid for this setting?
struct SettingPreset 
{
  uint16_t raw;        // opaque value (seconds, fixed-point, enum idx)
  const char *label;   // PROGMEM
};

static const SettingPreset TIMER_PRESETS[] PROGMEM = {
  { 120, STR_TMR_2M  },
  { 300, STR_TMR_5M  },
  { 600, STR_TMR_10M },
  { 900, STR_TMR_15M },
  {1200, STR_TMR_20M },
};

static const SettingPreset SPEED_PRESETS[] PROGMEM = {
  {  80, STR_SPD_80  },
  { 120, STR_SPD_120 },
  { 160, STR_SPD_160 },
  { 200, STR_SPD_200 },
  { 240, STR_SPD_240 },
};

static const SettingPreset DWELL_PRESETS[] PROGMEM = {
  {   0, STR_DWL_0   },
  { 100, STR_DWL_100 },
  { 200, STR_DWL_200 },
  { 500, STR_DWL_500 },
};

static const SettingPreset FWD_SPEED_PRESETS[] PROGMEM = {
  { 120, STR_SPD_120 },
  { 160, STR_SPD_160 },
  { 200, STR_SPD_200 },
  { 240, STR_SPD_240 },
};

static const SettingPreset REV_SPEED_PRESETS[] PROGMEM = {
  { 120, STR_SPD_120 },
  { 160, STR_SPD_160 },
  { 200, STR_SPD_200 },
  { 240, STR_SPD_240 },
};

static const SettingPreset BIAS_PRESETS[] PROGMEM = {
  { 0, STR_BIAS_0 },
  { 1, STR_BIAS_1 },
  { 2, STR_BIAS_2 },
  { 3, STR_BIAS_3 },
};

static const SettingPreset VAMP_PRESETS[] PROGMEM = {
  { 1, STR_VAMP_1 },
  { 2, STR_VAMP_2 },
  { 3, STR_VAMP_3 },
  { 4, STR_VAMP_4 },
};

static const SettingPreset VFREQ_PRESETS[] PROGMEM = {
  {  5, STR_VFREQ_5  },
  { 10, STR_VFREQ_10 },
  { 20, STR_VFREQ_20 },
  { 30, STR_VFREQ_30 },
};

static const char *const ACCEL_STRINGS[] PROGMEM = {
  STR_ACCEL_SOFT,
  STR_ACCEL_FAST
};

/* ===============================
   Menu items (flat list)
   What rows exist, in what order, and what happens when I press ENTER?
   =============================== */
static const MenuItemDesc MENU_ITEMS[] PROGMEM = {
  
  /* ---- Main Menu ---- */
  //label          |type             |target             |valueId          |param |
  { STR_LBL_MODE,   MENU_ENUM_SUB,   PAGE_MODE_SELECT,    SET_MODE,         OP_NONE }, //0
  { STR_LBL_PARAMS, MENU_SUBMENU,    PAGE_PARAMS,         SET_NONE,         OP_NONE },
  { STR_LBL_TIMER,  MENU_SUBMENU,    PAGE_TIMER_MENU,     SET_TIMER_SECONDS,OP_NONE },

  { STR_LBL_RUN,    MENU_ACTION,     ACTION_RUN,          SET_NONE,         OP_NONE },
  { STR_LBL_MANUAL, MENU_SUBMENU,    PAGE_MANUAL,         SET_NONE,         OP_NONE },

  { STR_LBL_SPEED,  MENU_SUBMENU,    PAGE_SPEED_SELECT,   SET_SPEED,        OP_NONE },
  { STR_LBL_DWELL,  MENU_SUBMENU,    PAGE_DWELL_SELECT,   SET_END_DWELL,    OP_NONE },
  { STR_LBL_ACCEL,  MENU_ENUM_SUB,   PAGE_ACCEL_SELECT,   SET_ACCEL,        OP_NONE },
 
  { STR_LBL_FWD,    MENU_SUBMENU,    PAGE_FWD_SELECT,     SET_FWD_SPEED,    OP_NONE },
  { STR_LBL_REV,    MENU_SUBMENU,    PAGE_REV_SELECT,     SET_REV_SPEED,    OP_NONE },
  { STR_LBL_BIAS,   MENU_SUBMENU,    PAGE_BIAS_SELECT,    SET_BIAS,         OP_NONE }, //10
 
  { STR_LBL_VAMP,   MENU_SUBMENU,    PAGE_VAMP_SELECT,    SET_VIB_AMP,      OP_NONE },
  { STR_LBL_VFREQ,  MENU_SUBMENU,    PAGE_VFREQ_SELECT,   SET_VIB_FREQ,     OP_NONE },
  { STR_LBL_VBURST, MENU_ENUM_SUB,   PAGE_VBURST_SELECT,  SET_VIB_BURST,    OP_NONE },

  /* ---- Manual ---- */
  //label          |type             |target             |valueId          |param |
  { STR_MAN_LEFT,   MENU_ACTION,      ACTION_MAN_LEFT,    SET_NONE,         OP_NONE }, //14
  { STR_MAN_RIGHT,  MENU_ACTION,      ACTION_MAN_RIGHT,   SET_NONE,         OP_NONE },
  { STR_MAN_VIB,    MENU_ACTION,      ACTION_MAN_VIB,     SET_NONE,         OP_NONE },
  { STR_MAN_OFF,    MENU_ACTION,      ACTION_MAN_OFF,     SET_NONE,         OP_NONE },

  /* ---- Select Mode ---- */
  //label          |type             |target             |valueId          |param |
  { STR_MODE_SWEEP,    MENU_LABEL,    ACTION_NONE,        SET_NONE,         OP_NONE }, //18
  { STR_MODE_RESONANT, MENU_LABEL,    ACTION_NONE,        SET_NONE,         OP_NONE },
  { STR_MODE_MICROVIB, MENU_LABEL,    ACTION_NONE,        SET_NONE,         OP_NONE },
  { STR_MODE_HYBRID,   MENU_LABEL,    ACTION_NONE,        SET_NONE,         OP_NONE },

  /* ---- Timer Menu ---- */
  //label          |type             |target             |valueId          |param |
  { STR_TMR_2M,     MENU_SETTING_OP,  SET_TIMER_SECONDS,  SET_TIMER_SECONDS, 0      }, //22
  { STR_TMR_5M,     MENU_SETTING_OP,  SET_TIMER_SECONDS,  SET_TIMER_SECONDS, 1      },
  { STR_TMR_10M,    MENU_SETTING_OP,  SET_TIMER_SECONDS,  SET_TIMER_SECONDS, 2      },
  { STR_TMR_15M,    MENU_SETTING_OP,  SET_TIMER_SECONDS,  SET_TIMER_SECONDS, 3      },
  { STR_TMR_20M,    MENU_SETTING_OP,  SET_TIMER_SECONDS,  SET_TIMER_SECONDS, 4      },
  { STR_CUSTOM,     MENU_SETTING_OP,  SET_TIMER_SECONDS,  SET_TIMER_SECONDS, 0      },

  /* ---- Set Speed ---- */
  //label          |type             |target             |valueId          |param |
  { STR_SPD_80,     MENU_SETTING_OP,  SET_SPEED,          SET_SPEED,         0      }, //28
  { STR_SPD_120,    MENU_SETTING_OP,  SET_SPEED,          SET_SPEED,         1      },
  { STR_SPD_160,    MENU_SETTING_OP,  SET_SPEED,          SET_SPEED,         2      },
  { STR_SPD_200,    MENU_SETTING_OP,  SET_SPEED,          SET_SPEED,         3      },
  { STR_SPD_240,    MENU_SETTING_OP,  SET_SPEED,          SET_SPEED,         4      },

  /* ---- End Dwell ---- */
  //label          |type             |target             |valueId          |param |
  { STR_DWL_0,      MENU_SETTING_OP,  SET_END_DWELL,      SET_END_DWELL,     0      }, //33
  { STR_DWL_100,    MENU_SETTING_OP,  SET_END_DWELL,      SET_END_DWELL,     1      },
  { STR_DWL_200,    MENU_SETTING_OP,  SET_END_DWELL,      SET_END_DWELL,     2      },
  { STR_DWL_500,    MENU_SETTING_OP,  SET_END_DWELL,      SET_END_DWELL,     3      },

  /* ---- Acceleration ---- */
  //label          |type             |target             |valueId          |param |
  { STR_ACCEL_SOFT, MENU_LABEL,       ACTION_NONE,        SET_NONE,         OP_NONE }, //37
  { STR_ACCEL_FAST, MENU_LABEL,       ACTION_NONE,        SET_NONE,         OP_NONE },

  /* ---- Fwd Speed ---- */
  //label          |type             |target             |valueId          |param |
  { STR_SPD_120,    MENU_SETTING_OP,  SET_FWD_SPEED,      SET_FWD_SPEED,     0      }, //39
  { STR_SPD_160,    MENU_SETTING_OP,  SET_FWD_SPEED,      SET_FWD_SPEED,     1      },
  { STR_SPD_200,    MENU_SETTING_OP,  SET_FWD_SPEED,      SET_FWD_SPEED,     2      },
  { STR_SPD_240,    MENU_SETTING_OP,  SET_FWD_SPEED,      SET_FWD_SPEED,     3      },

  /* ---- Rev Speed ---- */
  //label          |type             |target             |valueId          |param |
  { STR_SPD_120,    MENU_SETTING_OP,  SET_REV_SPEED,      SET_REV_SPEED,     0      }, //43
  { STR_SPD_160,    MENU_SETTING_OP,  SET_REV_SPEED,      SET_REV_SPEED,     1      },
  { STR_SPD_200,    MENU_SETTING_OP,  SET_REV_SPEED,      SET_REV_SPEED,     2      },
  { STR_SPD_240,    MENU_SETTING_OP,  SET_REV_SPEED,      SET_REV_SPEED,     3      },

  /* ---- Bias ---- */
  //label          |type             |target             |valueId          |param |
  { STR_BIAS_0,     MENU_SETTING_OP,  SET_BIAS,           SET_BIAS,          0      }, //47
  { STR_BIAS_1,     MENU_SETTING_OP,  SET_BIAS,           SET_BIAS,          1      },
  { STR_BIAS_2,     MENU_SETTING_OP,  SET_BIAS,           SET_BIAS,          2      },
  { STR_BIAS_3,     MENU_SETTING_OP,  SET_BIAS,           SET_BIAS,          3      },

  /* ---- Vib Amp ---- */
  //label          |type             |target             |valueId          |param |
  { STR_VAMP_1,     MENU_SETTING_OP,  SET_VIB_AMP,        SET_VIB_AMP,       0      }, //51
  { STR_VAMP_2,     MENU_SETTING_OP,  SET_VIB_AMP,        SET_VIB_AMP,       1      },
  { STR_VAMP_3,     MENU_SETTING_OP,  SET_VIB_AMP,        SET_VIB_AMP,       2      },
  { STR_VAMP_4,     MENU_SETTING_OP,  SET_VIB_AMP,        SET_VIB_AMP,       3      },

  /* ---- Vib Freq ---- */
  //label          |type             |target             |valueId          |param |
  { STR_VFREQ_5,    MENU_SETTING_OP,  SET_VIB_FREQ,       SET_VIB_FREQ,      0      }, //55
  { STR_VFREQ_10,   MENU_SETTING_OP,  SET_VIB_FREQ,       SET_VIB_FREQ,      1      },
  { STR_VFREQ_20,   MENU_SETTING_OP,  SET_VIB_FREQ,       SET_VIB_FREQ,      2      },
  { STR_VFREQ_30,   MENU_SETTING_OP,  SET_VIB_FREQ,       SET_VIB_FREQ,      3      },

  /* ---- Vib Burst ---- */
  //label          |type             |target             |valueId          |param |
  { STR_VBURST_OFF, MENU_LABEL,       ACTION_NONE,        SET_NONE,         OP_NONE }, //59
  { STR_VBURST_ON,  MENU_LABEL,       ACTION_NONE,        SET_NONE,         OP_NONE }
};

/* ===============================
   Pages (index ranges into MENU_ITEMS)
   Which subset of rows are visible together?
   =============================== */
static const MenuPageDesc MENU_PAGES[] PROGMEM = {
  /* PAGE_MAIN */
  { STR_MAIN,     0,  5 },

  /* PAGE_PARAMS */
  { STR_PARAMS,   5,  9 },

  /* PAGE_MANUAL */
  { STR_MANUAL,  14,  4 },

  /* PAGE_MODE_SELECT */
  { STR_MODESEL, 18,  4 },

  /* PAGE_TIMER_MENU */
  { STR_TIMESEL, 22,  6 },

  /* PAGE_TIMER_EDIT */
  { STR_CUSTOM,   0,  0 },   // stub for now

  /* PAGE_SPEED_SELECT */
  { STR_SPEEDSEL, 28,  5 },

  /* PAGE_DWELL_SELECT */
  { STR_DWELLSEL, 33,  4 },

  /* PAGE_ACCEL_SELECT */
  { STR_ACCELSEL, 37,  2 },

  /* PAGE_FWD_SELECT */
  { STR_FWDSEL,   39,  4 },

  /* PAGE_REV_SELECT */
  { STR_REVSEL,   43,  4 },

  /* PAGE_BIAS_SELECT */
  { STR_BIASSEL,  47,  4 },

  /* PAGE_VAMP_SELECT */
  { STR_VAMPSEL,  51,  4 },

  /* PAGE_VFREQ_SELECT */
  { STR_VFREQSEL, 55,  4 },

  /* PAGE_VBURST_SELECT */
  { STR_VBURSTSEL, 59,  2 }
};

static_assert(
  PAGE_COUNT == (sizeof(MENU_PAGES) / sizeof(MENU_PAGES[0])),
  "MenuPageId enum and MENU_PAGES[] are out of sync"
);

/* ===============================
   Firmware configuration storage
   =============================== */
struct MachineConfig 
{
  uint8_t  mode;
  uint16_t timerSeconds;

  uint8_t  speed;
  uint16_t endDwellMs;
  uint8_t  accel;

  uint8_t  fwdSpeed;
  uint8_t  revSpeed;
  uint8_t  bias;

  uint8_t  vibAmp;
  uint8_t  vibFreq;
  uint8_t  vibBurst;
};

extern MachineConfig cfg;

/* ===============================
   Default machine configuration
   =============================== */
constexpr MachineConfig DEFAULT_CFG = {
  .mode         = 0,
  .timerSeconds = 120,

  .speed        = 160,
  .endDwellMs   = 100,
  .accel        = 0,

  .fwdSpeed     = 160,
  .revSpeed     = 160,
  .bias         = 0,

  .vibAmp       = 1,
  .vibFreq      = 10,
  .vibBurst     = 0
};

/* ===============================
   Setting descriptions
   Where is the data stored and how is it interpreted?
   =============================== */
const SettingDefinition SETTING_DEFINITIONS[] =
{
  /* SET_INVALID */
  { SETTYPE_UINT8,  nullptr,            0, nullptr },

  /* SET_MODE */
  { SETTYPE_ENUM, &cfg.mode, 4, MODE_STRINGS },

  /* SET_TIMER_SECONDS */
  { SETTYPE_TIME, &cfg.timerSeconds,
    sizeof(TIMER_PRESETS)/sizeof(TIMER_PRESETS[0]),
    TIMER_PRESETS },

  /* SET_SPEED */
  { SETTYPE_UINT8, &cfg.speed,
    sizeof(SPEED_PRESETS)/sizeof(SPEED_PRESETS[0]),
    SPEED_PRESETS },

  /* SET_END_DWELL */
  { SETTYPE_UINT16, &cfg.endDwellMs,
    sizeof(DWELL_PRESETS) / sizeof(DWELL_PRESETS[0]),
    DWELL_PRESETS },

  /* SET_ACCEL */
  { SETTYPE_ENUM, &cfg.accel, 2, ACCEL_STRINGS },

  /* SET_FWD_SPEED */
  { SETTYPE_UINT8, &cfg.fwdSpeed,
    sizeof(FWD_SPEED_PRESETS) / sizeof(FWD_SPEED_PRESETS[0]),
    FWD_SPEED_PRESETS },

  /* SET_REV_SPEED */
  { SETTYPE_UINT8, &cfg.revSpeed,
    sizeof(REV_SPEED_PRESETS) / sizeof(REV_SPEED_PRESETS[0]),
    REV_SPEED_PRESETS },

  /* SET_BIAS */
  { SETTYPE_UINT8, &cfg.bias,
    sizeof(BIAS_PRESETS) / sizeof(BIAS_PRESETS[0]),
    BIAS_PRESETS },

  /* SET_VIB_AMP */
  { SETTYPE_UINT8, &cfg.vibAmp,
    sizeof(VAMP_PRESETS) / sizeof(VAMP_PRESETS[0]),
    VAMP_PRESETS },

  /* SET_VIB_FREQ */
  { SETTYPE_UINT8, &cfg.vibFreq,
    sizeof(VFREQ_PRESETS) / sizeof(VFREQ_PRESETS[0]),
    VFREQ_PRESETS },

  /* SET_VIB_BURST */
  { SETTYPE_ENUM, &cfg.vibBurst, 2, VBURST_STRINGS },
};

static_assert(
  SET_COUNT == (sizeof(SETTING_DEFINITIONS) / sizeof(SETTING_DEFINITIONS[0])),
  "SettingId enum and SETTING_DEFINITIONS[] out of sync"
);

