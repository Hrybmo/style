#include <pebble.h>
#include "ui.h"
#include "callback.h"
  
/*
This module controls all and is responsable for starting and
shutting down other modules.
tweak this module after setting up the UI
- stay on minute ticks, update weather whenever called back.
*/

//globals
static char user_text[] = "-----------";
static char time_text[] = "12:12";
static char day_text[] = "tue";
static char date_text[] = "12-30-2015";
static char batt_text[] = "100";
static BatteryChargeState charge_state;
static int temperatureUnits;
static int temperature;
static int temperatureIncoming;
static char temperature_buffer[8];
static int uiColor;

//prototypes
static void handle_minute_tick(struct tm* tick_time, TimeUnits units_changed);


//-------------------------------------------
int main(void) {
  handle_init(); //start app
  app_event_loop(); //wait until exit
  handle_deinit(); //cleanup
}
/-------------------------------------------------
	
void handle_init(void) {
  static struct tm *current_time;
 
  ui_init(); 
  CallBack_init();
  uiColor = CallBack_isInvertUiColor();
  //setup events
  tick_timer_service_subscribe(MINUTE_UNIT , &handle_minute_tick);
  //show the ui
  ui_pushStack();
	//force first event
	handle_minute_tick(current_time, MINUTE_UNIT);
}

void handle_deinit(void) {
  destroy_ui();
}
//------------------------------------------------------------------------------
// update time, date, and battery every minute
static void handle_minute_tick(struct tm* tick_time, TimeUnits units_changed) {
  
  //change color if needed
  if(CallBack_isInvertUiColor()){
		ui_invert();
  }
	
  //is weather update time?
  if((tick_time->tm_min == 0) && (tick_time->tm_sec == 0)) {
    CallBack_sendWeatherMessage();
  }
  
  //get current time
	if(clock_is_24h_style()){ 
		strftime(time_text, sizeof(time_text), "%H:%M", tick_time);
	} 
	else{
    strftime(time_text, sizeof(time_text), "%I:%M", tick_time);
  }
	ui_setTimeTo(time_text);
	
	//day
	strftime(day_text, sizeof(day_text), "%a", tick_time); //short day of week
	ui_setDayTo(day_text);

	//date
	strftime(date_text, sizeof(date_text), "%m-%d-%Y", tick_time);
	ui_setDateTo(date_text);

	//battery
	charge_state = battery_state_service_peek();
	snprintf(batt_text,sizeof(batt_text), "%d", charge_state.charge_percent);
	ui_setBattTo(batt_text);

	if(CallBack_isWeatherDataAvailable()) {  
		temperatureUnits = CallBack_getTemperatureUnits();
		temperatureIncoming = CallBack_getTemperature();
		//convert temp from K
		if(temperatureUnits == 'F')
			{
			temperature = (((temperatureIncoming - 273.15)*1.8)+32);
			snprintf(temperature_buffer, sizeof(temperature_buffer), "%d°F", temperature);
		}
		else
			{
			temperature = (temperatureIncoming - 273.15);
			snprintf(temperature_buffer, sizeof(temperature_buffer), "%d°C", temperature);
		}
		ui_setTempTo(temperature_buffer);
		}
	ui_setUserTextTo(user_text);
}


