#include <pebble.h>
#include "callback.h"
  
static void inbox_dropped_callback(AppMessageResult reason, void *context);
static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context);
static void outbox_sent_callback(DictionaryIterator *iterator, void *context);
static void inbox_received_callback(DictionaryIterator *iterator, void *context);
static void CallBack_refreshPersistance(void);

// Store incoming information
static int temperatureUnits = 'F';
static int temperature = 0;
static int isWeatherDataAvailable = 0;
static int isGPS = 1;
static char sLatitude[20] = "1";
static char sLongitude[20] = "1";
static char sVersion[] = "1";
static char isFirstWeather = 1;
static char user_text[20] = {""};
static uint8_t conditions = 1;
//-----------public start--------------------------------
int CallBack_getTemperature(void){
  return temperature;
}

int CallBack_getTemperatureUnits(void){
  return temperatureUnits;
}

int CallBack_isWeatherDataAvailable(void){
  return isWeatherDataAvailable;
}

uint8_t CallBack_getConditions(void){
  return conditions;
}


void *CallBack_getUserTextPtr(void){
	return user_text;
}

//----------------------------------------------
void CallBack_sendWeatherMessage(void)
  {// Begin dictionary
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
  
    // Add a key-value pair
    dict_write_uint32(iter, KEY_WEATHER_MESSAGE, 1);
    dict_write_end(iter);
    // Send the message!
    app_message_outbox_send();
}
//----------------------------------------------
void CallBack_sendPersistantMessage(void){
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
    // Add a key-value pair
    dict_write_uint32(iter, KEY_PERSISTANT_MESSAGE, 1);
    dict_write_uint32(iter, KEY_IS_GPS, isGPS);
    dict_write_cstring(iter, KEY_LATITUDE, sLatitude);
    dict_write_cstring(iter, KEY_LONGITUDE, sLongitude);
    dict_write_end(iter);
    // Send the message!
    app_message_outbox_send();
}
//------------------------------------------------
void CallBack_refreshPersistance(void)
  {
  //set temperature units
  if (persist_exists(KEY_TEMP_UNITS)){
  	temperatureUnits = persist_read_int(KEY_TEMP_UNITS);
  }
  else{
    persist_write_int(KEY_TEMP_UNITS,temperatureUnits);
  }
	
	 if (persist_exists(KEY_USER_TEXT)){
		persist_read_string((KEY_USER_TEXT),user_text,sizeof(user_text));
  }
  else{
		 persist_write_string(KEY_USER_TEXT,user_text);
  }
  
  if (persist_exists(KEY_IS_GPS)){
 	 isGPS = persist_read_int(KEY_IS_GPS);
  }
  else{
      persist_write_int(KEY_IS_GPS,isGPS);
  }
  
  if (persist_exists(KEY_LATITUDE)){
		persist_read_string((KEY_LATITUDE),sLatitude,sizeof(sLatitude));
  }
  else{
    persist_write_string(KEY_LATITUDE,sLatitude);
  }
  
  if (persist_exists(KEY_LONGITUDE)){
  	persist_read_string((KEY_LONGITUDE),sLongitude,sizeof(sLongitude));
  }
  else{
    persist_write_string(KEY_LONGITUDE,sLongitude);
  }
  
	if (persist_exists(KEY_VERSION)){
		persist_read_string((KEY_VERSION),sVersion,sizeof(sVersion));
	}
  else{
    persist_write_string(KEY_VERSION,sVersion);
  }
}

void CallBack_init(void)
  {
  CallBack_refreshPersistance();
  // Register callbacks
  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback); 
  
  // Open AppMessage
  app_message_open(100,100);
}


//----------------private start----------------------
static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  //APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  //APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  //APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
  if(isFirstWeather)
    {
    isFirstWeather = 0;
    CallBack_sendWeatherMessage();
  }
}

//----------------------------------------------------------------
static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  
  char incomming[20];
  
  // Read first item
  Tuple *t = dict_read_first(iterator);

  // For all items
  while(t != NULL) {
    // Which key was received?
    switch(t->key) {
      
    case KEY_TEMPERATURE:
      temperature = (int)t->value->int32;
			//APP_LOG(APP_LOG_LEVEL_INFO, "temperature -callback- %i",temperature);
      isWeatherDataAvailable = 1;
      break;
      
    case KEY_CONDITIONS:
      snprintf(incomming, sizeof(incomming), "%s", t->value->cstring);
			if(memcmp("01",incomming,3) == 0){
				conditions = 1;
			}
			else if(memcmp("02",incomming,3) == 0){
				conditions = 2;
			}
			else if(memcmp("03",incomming,3) == 0){
				conditions = 3;
			}
			else if(memcmp("04",incomming,3) == 0){
				conditions = 4;
			}
			else if(memcmp("09",incomming,3) == 0){
				conditions = 9;
			}
			else if(memcmp("10",incomming,3) == 0){
				conditions = 10;
			}
			else if(memcmp("13",incomming,3) == 0){
				conditions = 13;
			}
			else if(memcmp("50",incomming,3) == 0){
				conditions = 50;
			}
			//APP_LOG(APP_LOG_LEVEL_INFO, "conditions - callback = %d",conditions);
      break;

    case KEY_TEMP_UNITS:        
       memcpy(incomming,(t->value->cstring),sizeof(incomming));
       if(strcmp(incomming,"F") == 0)
       {
         persist_write_int(KEY_TEMP_UNITS,'F');
         temperatureUnits = 'F';
       }
       else{
         persist_write_int(KEY_TEMP_UNITS,'C');
         temperatureUnits = 'C';
       }
      break;
      
      case KEY_IS_GPS:
      memcpy(incomming,(t->value->cstring),sizeof(incomming));
      if(strcmp(incomming,"GPS") == 0){
        //APP_LOG(APP_LOG_LEVEL_INFO,"KEY_IS_GPS persistance saved as 1");
        persist_write_int(KEY_IS_GPS,1);
        isGPS = 1;
      }        
      else{
        persist_write_int(KEY_IS_GPS,0);
        //APP_LOG(APP_LOG_LEVEL_INFO,"KEY_IS_GPS persistance saved as 0");
        isGPS = 0;
      }
      break;
      
      case KEY_LATITUDE:
      memcpy(sLatitude,(t->value->cstring),(t->length));
      //APP_LOG(APP_LOG_LEVEL_INFO, "lat = %s",sLatitude);
      persist_write_string(KEY_LATITUDE,sLatitude);
      break;
      
      case KEY_LONGITUDE:
      memcpy(sLongitude,(t->value->cstring),(t->length));
      persist_write_string(KEY_LONGITUDE,sLongitude);
      break;
			
			case KEY_USER_TEXT:
      memcpy(user_text,(t->value->cstring),(t->length));
      persist_write_string(KEY_USER_TEXT,user_text);
      break;

      case KEY_JS_READY:
      //APP_LOG(APP_LOG_LEVEL_INFO, "KEY_JS_READY received");
      CallBack_sendPersistantMessage();
      break;
      
    default:
      break;
    }
    // Look for next item
    t = dict_read_next(iterator);
  }
} 