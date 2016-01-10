#define KEY_VERSION 0  
#define KEY_JS_READY 1 
#define KEY_TEMPERATURE 2
#define KEY_CONDITIONS 3   
#define KEY_TEMP_UNITS 4  //0 is F
#define KEY_USER_TEXT 5
#define KEY_IS_GPS 6
#define KEY_LATITUDE 7 
#define KEY_LONGITUDE 8 
#define KEY_WEATHER_MESSAGE 9
#define KEY_PERSISTANT_MESSAGE 10
#define KEY_BACK_COLOR 11
#define KEY_FORE_COLOR 12
#define KEY_TEXT_COLOR 13

void CallBack_init(void);
void CallBack_sendWeatherMessage(void);
void CallBack_sendPersistantMessage(void);

int CallBack_isWeatherDataAvailable(void);
int CallBack_getTemperature(void);
int CallBack_getTemperatureUnits(void);
uint8_t CallBack_getConditions(void);
int CallBack_isInvertUiColor(void);
void *CallBack_getUserTextPtr(void);
uint32_t CallBack_getForegroundColor(void);
uint32_t CallBack_getBackgroundColor(void);
uint32_t CallBack_getTextColor(void);