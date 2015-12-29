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
static int temperature_hi = 0;
static int temperature_lo = 0;
static int uiColor = 0;
static int isWeatherDataAvailable = 0;
static int isGPS = 1;
static char sLatitude[20] = "1";
static char sLongitude[20] = "1";
static char sZipCode[20] = "1";
static char sVersion[] = "1.2";
static char isFirstWeather = 1;
//-----------public start--------------------------------
int CallBack_getTemperature(void)
  {
  return temperature;
}

int CallBack_getTemperatureHigh(void)
  {
  return temperature_hi;
}

int CallBack_getTemperatureLow(void)
  {
  return temperature_lo;
}

int CallBack_getTemperatureUnits(void)
  {
  return temperatureUnits;
}

int CallBack_isWeatherDataAvailable(void)
  {
  return isWeatherDataAvailable;
}

int CallBack_isInvertUiColor(void)
  {
  return uiColor;
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
    dict_write_uint32(iter, KEY_INVERT_UI, uiColor);
    dict_write_end(iter);
    // Send the message!
    app_message_outbox_send();
}
//------------------------------------------------
void CallBack_refreshPersistance(void)
  {
  //set color
  if (persist_exists(KEY_INVERT_UI))
    {
       uiColor = persist_read_int(KEY_INVERT_UI);
  }
  else
  {
    persist_write_int(KEY_INVERT_UI,uiColor);
  }
  
  //set temperature units
  if (persist_exists(KEY_TEMP_UNITS))
    {
       temperatureUnits = persist_read_int(KEY_TEMP_UNITS);
  }
  else
    {
     persist_write_int(KEY_TEMP_UNITS,temperatureUnits);
  }
  
  if (persist_exists(KEY_IS_GPS))
    {
       isGPS = persist_read_int(KEY_IS_GPS);
  }
  else{
      persist_write_int(KEY_IS_GPS,isGPS);
  }
  
  if (persist_exists(KEY_LATITUDE))
    {
      persist_read_string((KEY_LATITUDE),sLatitude,sizeof(sLatitude));
  }
  else
    {
    persist_write_string(KEY_LATITUDE,sLatitude);
  }
  
   if (persist_exists(KEY_LONGITUDE))
    {
      persist_read_string((KEY_LONGITUDE),sLongitude,sizeof(sLongitude));
  }
  else
    {
    persist_write_string(KEY_LONGITUDE,sLongitude);
  }
  else
    {
    persist_write_string(KEY_ZIP_CODE,sZipCode);
  }
  
    if (persist_exists(KEY_VERSION))
    {
      persist_read_string((KEY_VERSION),sVersion,sizeof(sVersion));
  }
  else
    {
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
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
  if(isFirstWeather)
    {
    isFirstWeather = 0;
    CallBack_sendWeatherMessage();
  }
}

//----------------------------------------------------------------
static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  
  char incomming[10];
  
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
      //snprintf(conditions_buffer, sizeof(conditions_buffer), "%s", t->value->cstring);
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
      
      case KEY_INVERT_UI:
        memcpy(incomming,(t->value->cstring),sizeof(incomming));
        if(strcmp(incomming,"b") == 0)
        {
         persist_write_int(KEY_INVERT_UI,1);
         uiColor = 1;
        }
        else{
           persist_write_int(KEY_INVERT_UI,0);
           uiColor = 0;
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