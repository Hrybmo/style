#include <pebble.h>
#include "ui.h"
#include "Handler.h"
#include "callback.h"
/*
This module controls all and is responsable for starting and
shutting down other modules.
tweak this module after setting up the UI
-=Functional requirenment specification=-
- stay on second ticks for quick ui response on change ex. clock 24 to 12
- stop watch guesture
- read from excel peek every minute, if 30 rolling samples are the same (within +/- x then goto sleep)
- if in sleep accelservice will auto wake
*/



//prototypes
void handle_init(void);
void handle_deinit(void);

//-------------------------------------------
int main(void) {
  handle_init(); //start app
  app_event_loop(); //wait until exit
  handle_deinit(); //cleanup
}
//-------------------------------------------------
	
void handle_init(void) {
  initialise_ui(); 
	ui_init_weather();
  CallBack_init();
	ui_setTempTo("");
	ui_setDayTo("");
	ui_setDateTo("");
	ui_setTimeTo("");
	ui_setBattTo("");
	ui_setUserTextTo("");
	
	#ifdef PBL_ROUND
	ui_fitToRound();
	#endif
	
  //setup events
	Handler_init();
	Handler_setEvent();
  //show the ui
  ui_pushStack();
}

void handle_deinit(void) {
  destroy_ui();
	ui_destroy_weather();
}

