#include "config.h"

void initialise_ui(void);
void ui_init_weather(void);
void ui_destroy_weather(void);
void destroy_ui(void);
void ui_pushStack(void);
void ui_popStack(void);
  
//buff below must be static with terminator
void ui_setTempTo(char *buff);
void ui_setDayTo(char *buff);
void ui_setDateTo(char *buff);
void ui_setTimeTo(char *buff);
void ui_setBattTo(char *buff);
void ui_setUserTextTo(char *buff);
void ui_setUserText2To(char *buff);
void ui_setWeatherTo(uint8_t id);
void ui_setAllColors(uint32_t background, uint32_t foreground, uint32_t text);
void ui_fitToRound();