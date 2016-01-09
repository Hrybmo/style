#include "config.h"

void initialise_ui(void);
void destroy_ui(void);
void ui_invert(void);
void ui_pushStack(void);
void ui_popStack(void);
  
//buff below must be static with terminator
void ui_setTempTo(char *buff);
void ui_setDayTo(char *buff);
void ui_setDateTo(char *buff);
void ui_setTimeTo(char *buff);
void ui_setBattTo(char *buff);
void ui_setUserTextTo(char *buff);
void ui_setWeatherTo(uint8_t id);
void ui_setBackgroundColorTo(uint32_t color);
void ui_setForegroundColorTo(uint32_t color);
void ui_setTextColorTo(uint32_t color);
void ui_fitToRound();