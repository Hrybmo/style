#include <pebble.h>
#include "ui.h"
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

#define ACCEL_NUM_SAMPLES 10

//globals
//static char user_text[] = "SUPER JACK"; //max 11 charictors
static char time_text[] = "12:12";
static char day_text[] = "tue";
static char date_text[] = "12-30-2015";
static char batt_text[] = "100";
static char *userTextPtr = 0;
static BatteryChargeState charge_state;
static int temperatureUnits;
static int temperature;
static int temperatureIncoming;
static char temperature_buffer[8];
static bool isTimerMode = false;
bool isSleeping = false;

//prototypes
void handle_tick(struct tm* tick_time, TimeUnits units_changed);
static void data_handler(AccelData *data, uint32_t num_samples);
static void tap_handler(AccelAxisType axis, int32_t direction);
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
	userTextPtr = CallBack_getUserTextPtr();
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
  tick_timer_service_subscribe(SECOND_UNIT , handle_tick);
	accel_tap_service_subscribe(tap_handler);
  //show the ui
  ui_pushStack();
}

void handle_deinit(void) {
  destroy_ui();
	ui_destroy_weather();
}
//--------------------------------------------------
//for sleep mode wakeup
static void tap_handler(AccelAxisType axis, int32_t direction) {
	#define TENMS_SAMPLES_FOR_GUESTURE 5
	if(isSleeping){
		isSleeping = false;
		tick_timer_service_subscribe(SECOND_UNIT , handle_tick);
	}
	else{
    accel_data_service_subscribe(TENMS_SAMPLES_FOR_GUESTURE, data_handler);
    accel_service_set_sampling_rate(ACCEL_SAMPLING_10HZ);
	}
}

//-----------------------------------------------------------------
static void data_handler(AccelData *data, uint32_t num_samples) {
	#define TRIP_POINT -800
	static const uint32_t segments[] = {200, 200, 200, 200, 200};
	VibePattern vibrationPattern1 = {
  .durations = segments,
  .num_segments = ARRAY_LENGTH(segments),
	};
  //X+ = 1 button to 3 button sides out
	//Y+ = bottom link to top link
	//Z+ = coming out of the watch glass
	
	//see if we are vertical for stopwatch
	//APP_LOG(APP_LOG_LEVEL_INFO, "accel x = %d",data[num_samples - 1].x);
		if(data[num_samples - 1].x < TRIP_POINT){
			if(isTimerMode){
				vibes_enqueue_custom_pattern(vibrationPattern1);
				isTimerMode = false;
				light_enable_interaction();
				//APP_LOG(APP_LOG_LEVEL_INFO, "off");
			}
			else{
				vibes_short_pulse();
				isTimerMode = true;
				light_enable_interaction();
				//APP_LOG(APP_LOG_LEVEL_INFO, "on");
			}
		}
	accel_data_service_unsubscribe();
}

//------------------------------------------------------------------------------
void handle_tick(struct tm* tick_time, TimeUnits units_changed) {
	#define SLEEP_MODE_BUFFER_SIZE 30
	#define SLEEP_MODE_ACCEL_TOLERANCE 50
	static uint16_t secondsTickTimer = 0;
	static char timerBuffer[] = "00:00:00";
	uint8_t seconds = 0;
	uint8_t minutes = 0;
	uint8_t hours = 0;
	static int sleepModeBuffer[SLEEP_MODE_BUFFER_SIZE] = {0,-100,100};
	static uint8_t sleepModeBufferIndex = 0;
	int accelMax = -10000;
	int accelMin = 10000;
	AccelData accelData;
	
	//sleep mode check
	if(tick_time->tm_sec == 0){
		accel_service_peek(&accelData);
		if(sleepModeBufferIndex == SLEEP_MODE_BUFFER_SIZE){
			sleepModeBufferIndex = 0;
		}
		sleepModeBuffer[sleepModeBufferIndex] = accelData.x;
		sleepModeBufferIndex++;
		
		//check array for min max
		for(uint8_t a = 0; a < SLEEP_MODE_BUFFER_SIZE; a++){
			if(accelMin > sleepModeBuffer[a]){
				accelMin = sleepModeBuffer[a];
			}
			if(accelMax < sleepModeBuffer[a]){
				accelMax = sleepModeBuffer[a];
			}
		}
		
		#if 0
		for(uint8_t a = 0; a < SLEEP_MODE_BUFFER_SIZE; a++){
			APP_LOG(APP_LOG_LEVEL_INFO, "sleep buffer[%d] = %d",a,sleepModeBuffer[a]);
		}
		APP_LOG(APP_LOG_LEVEL_INFO, "MIN = %d MAX = %d",accelMin,accelMax);
		#endif
		
		if ((accelMax - accelMin) < SLEEP_MODE_ACCEL_TOLERANCE){
			//activate sleep mode
			isSleeping = true;
			tick_timer_service_unsubscribe();
			ui_setUserTextTo("");
			ui_setTimeTo("-- --");
			ui_setDayTo("");
			ui_setDateTo("<>");
			ui_setTempTo("");
			return;
		}
	}
	
	//stopwatch mode check
	if(isTimerMode){
		seconds = secondsTickTimer % 60;
		minutes = secondsTickTimer / 60;
		hours = secondsTickTimer / 3600;
		snprintf(timerBuffer, sizeof(timerBuffer), "%02d:%02d:%02d", hours, minutes, seconds);
		secondsTickTimer++;
		ui_setUserTextTo(timerBuffer);
	}
	else{
		secondsTickTimer = 0;
		ui_setUserTextTo(userTextPtr);
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
		//if there is a zero first then remove it
		if(!(memcmp(time_text,"0",1))){ 
			memcpy(time_text,(time_text + 1),sizeof(time_text)-1);
		}
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
	
	ui_setWeatherTo(CallBack_getConditions());
	
	ui_setAllColors(CallBack_getBackgroundColor(),
									CallBack_getForegroundColor(),
									CallBack_getTextColor());
									
}


