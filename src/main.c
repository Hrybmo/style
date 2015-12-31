#include <pebble.h>
#include "ui.h"
#include "callback.h"

/*
This module controls all and is responsable for starting and
shutting down other modules.
tweak this module after setting up the UI
-=Functional requirenment specification=-
- stay on second ticks for quick ui response on change ex. clock 24 to 12
- suscribe to accelservice, if triggered x amount of times within x amount 
of seconds then trigger timer start/stop, 1 vibration for start and 2 for finished
- read from excel peek every minute, if 30 rolling samples are the same (within +/- x then goto sleep)
- if in sleep accelservice will auto wake
*/

//globals
static char user_text[] = "SUPER JACK"; //max 11 charictors
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
static bool isTimerMode = false;

//prototypes
void handle_tick(struct tm* tick_time, TimeUnits units_changed);
static void data_handler(AccelData *data, uint32_t num_samples);
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
 const char ACCEL_NUM_SAMPLES = 10; //update every second
 
  initialise_ui(); 
  CallBack_init();
  //setup events
  tick_timer_service_subscribe(SECOND_UNIT , handle_tick);
	accel_data_service_subscribe(ACCEL_NUM_SAMPLES, data_handler);
	accel_service_set_sampling_rate(ACCEL_SAMPLING_10HZ);
  //show the ui
  ui_pushStack();
}

void handle_deinit(void) {
  destroy_ui();
}
//-----------------------------------------------------------------
static void data_handler(AccelData *data, uint32_t num_samples) {
	#define ACCEL_POS_IDLE_TOLERANCE 400
	#define ACCEL_NEG_IDLE_TOLERANCE -400
	#define ACCEL_BUFFER_SIZE 30
	#define ACCEL_NEG_THREASHOLD -600
	#define ACCEL_POS_THREASHOLD 600
	#define SEQUENCE_ITERATIONS_NEEDED 3
	static unsigned char bufferIndex = 0;
	static int xBuffer[ACCEL_BUFFER_SIZE] = {0};
	static int yBuffer[ACCEL_BUFFER_SIZE] = {0};
	static int zBuffer[ACCEL_BUFFER_SIZE] = {0};
	unsigned char searchSequenceTrigger = 0;
	unsigned char searchSequenceIteration = 0;
	unsigned char searchIndex = 0;
	unsigned char sample = 0;
	
	static const uint32_t segments[] = {200, 200, 200, 200, 200};
	VibePattern vibrationPattern1 = {
  .durations = segments,
  .num_segments = ARRAY_LENGTH(segments),
	};
	
	#if 0
	static uint8_t accelDebugSequence = 0;
	if((accelDebugSequence == 3)){
		APP_LOG(APP_LOG_LEVEL_INFO, "starting accel dump, bufferindex = %d",bufferIndex);
		for(uint8_t a = 0; a < ACCEL_BUFFER_SIZE; a++){
			APP_LOG(APP_LOG_LEVEL_INFO, "X= %d Y= %d Z= %d",xBuffer[a], yBuffer[a], zBuffer[a]);
		}				
		APP_LOG(APP_LOG_LEVEL_INFO, "accel dump end");								
	}
	accelDebugSequence++;	
	//APP_LOG(APP_LOG_LEVEL_INFO, "accel num_samples= %lu",num_samples);
	#endif

	//ring buffer time for the data
	for(uint8_t a = 0; a < num_samples; a++){
		if(bufferIndex == ACCEL_BUFFER_SIZE){
			bufferIndex = 0;
		}
		//APP_LOG(APP_LOG_LEVEL_INFO, "bufferIndex = %d",bufferIndex);		
		xBuffer[bufferIndex] = data[a].x;
		yBuffer[bufferIndex] = data[a].y;
		zBuffer[bufferIndex] = data[a].z;
		bufferIndex++;
	}
	
	//X+ = 1 button to 3 button sides out
	//Y+ = bottom link to top link
	//Z+ = coming out of the watch glass
	
	//look to see if we have a timer trigger
	for(char a = 0; a < ACCEL_BUFFER_SIZE; a++){
		//APP_LOG(APP_LOG_LEVEL_INFO, "buffer index = %d",bufferIndex);
		if(bufferIndex == ACCEL_BUFFER_SIZE){
			bufferIndex = 0;
		}
		switch(searchSequenceTrigger){
			//z is negative (upright) others are close to zero
			case 0:{ 
				if((zBuffer[bufferIndex] < ACCEL_NEG_THREASHOLD) &&
				   (yBuffer[bufferIndex] < ACCEL_POS_IDLE_TOLERANCE) &&
					 (yBuffer[bufferIndex] > ACCEL_NEG_IDLE_TOLERANCE) &&
					 (xBuffer[bufferIndex] < ACCEL_POS_IDLE_TOLERANCE) &&
					 (xBuffer[bufferIndex] > ACCEL_NEG_IDLE_TOLERANCE)){
					searchSequenceTrigger++;
					//APP_LOG(APP_LOG_LEVEL_INFO, "sequence 0 trigger");
				}
				break;
			}
			//Y is negative (tilted 90°) others are close to zero
			case 1:{
				if((yBuffer[bufferIndex] > ACCEL_POS_THREASHOLD) &&
				   (xBuffer[bufferIndex] < ACCEL_POS_IDLE_TOLERANCE) &&
					 (xBuffer[bufferIndex] > ACCEL_NEG_IDLE_TOLERANCE) &&
					 (zBuffer[bufferIndex] < ACCEL_POS_IDLE_TOLERANCE) &&
					 (zBuffer[bufferIndex] > ACCEL_NEG_IDLE_TOLERANCE)){
					searchSequenceTrigger = 0;
					searchSequenceIteration++;
					//APP_LOG(APP_LOG_LEVEL_INFO, "sequence 1 trigger");
				}
				break;
			}
		}																							
		bufferIndex++;
	}
	
	//clear y logs after trigger - vibration causes false trigger
	if(searchSequenceIteration >= SEQUENCE_ITERATIONS_NEEDED){
		if(isTimerMode){
			vibes_enqueue_custom_pattern(vibrationPattern1);
			isTimerMode = false;
			for(uint8_t a = 0; a < ACCEL_BUFFER_SIZE; a++){
				yBuffer[a] = 0;
			}
			//APP_LOG(APP_LOG_LEVEL_INFO, "off");
		}
		else{
			vibes_short_pulse();
			isTimerMode = true;
			for(uint8_t a = 0; a < ACCEL_BUFFER_SIZE; a++){
				yBuffer[a] = 0;
			}
			//APP_LOG(APP_LOG_LEVEL_INFO, "on");
		}
	}

}
//------------------------------------------------------------------------------
void handle_tick(struct tm* tick_time, TimeUnits units_changed) {
	static uint16_t secondsTickTimer = 0;
	static char timerBuffer[] = "00:00:00";
	uint8_t seconds = 0;
	uint8_t minutes = 0;
	uint8_t hours = 0;
  //change color if needed
	/*
  if(CallBack_isInvertUiColor()){
		ui_invert();
  }
	*/
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
		ui_setUserTextTo(user_text);
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
}


