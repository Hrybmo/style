#include <pebble.h>
#include "ui.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GBitmap *s_res_image_bg1;
static GFont s_res_bitham_42_bold;
static GBitmap *s_res_image_bt;
static GFont s_res_gothic_14;
static GFont s_res_gothic_18_bold;
static GFont s_res_gothic_24;
static GFont s_res_gothic_28_bold;
static GBitmap *s_res_image_w_partly_cloudy;
static BitmapLayer *s_bitmaplayer_bg;
static TextLayer *s_textlayer_time;
static BitmapLayer *s_bitmaplayer_BT;
static TextLayer *s_textlayer_batt;
static TextLayer *s_textlayer_date;
static TextLayer *s_textlayer_day;
static TextLayer *s_textlayer_w_temp;
static BitmapLayer *s_bitmaplayer_weather;
static TextLayer *s_textlayer_bot_user;

void initialise_ui(void) {
  s_window = window_create();
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, 1);
  #endif
  
  s_res_image_bg1 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG1);
  s_res_bitham_42_bold = fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD);
  s_res_image_bt = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BT);
  s_res_gothic_14 = fonts_get_system_font(FONT_KEY_GOTHIC_14);
  s_res_gothic_18_bold = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
  s_res_gothic_24 = fonts_get_system_font(FONT_KEY_GOTHIC_24);
  s_res_gothic_28_bold = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
  s_res_image_w_partly_cloudy = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_W_PARTLY_CLOUDY);
  // s_bitmaplayer_bg
  s_bitmaplayer_bg = bitmap_layer_create(GRect(0, 0, 144, 168));
  bitmap_layer_set_bitmap(s_bitmaplayer_bg, s_res_image_bg1);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_bg);
  
  // s_textlayer_time
  s_textlayer_time = text_layer_create(GRect(0, 23, 144, 55));
  text_layer_set_background_color(s_textlayer_time, GColorClear);
  text_layer_set_text(s_textlayer_time, "12:42");
  text_layer_set_text_alignment(s_textlayer_time, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_time, s_res_bitham_42_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_time);
  
  // s_bitmaplayer_BT
  s_bitmaplayer_BT = bitmap_layer_create(GRect(0, 3, 18, 18));
  bitmap_layer_set_bitmap(s_bitmaplayer_BT, s_res_image_bt);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_BT);
  
  // s_textlayer_batt
  s_textlayer_batt = text_layer_create(GRect(121, 1, 21, 15));
  text_layer_set_background_color(s_textlayer_batt, GColorClear);
  text_layer_set_text_color(s_textlayer_batt, GColorWhite);
  text_layer_set_text(s_textlayer_batt, "100");
  text_layer_set_text_alignment(s_textlayer_batt, GTextAlignmentRight);
  text_layer_set_font(s_textlayer_batt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_batt);
  
  // s_textlayer_date
  s_textlayer_date = text_layer_create(GRect(29, 74, 83, 24));
  text_layer_set_background_color(s_textlayer_date, GColorClear);
  text_layer_set_text(s_textlayer_date, "01-01-2015");
  text_layer_set_text_alignment(s_textlayer_date, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_date, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_date);
  
  // s_textlayer_day
  s_textlayer_day = text_layer_create(GRect(0, 1, 144, 28));
  text_layer_set_background_color(s_textlayer_day, GColorClear);
  text_layer_set_text(s_textlayer_day, "Wed");
  text_layer_set_text_alignment(s_textlayer_day, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_day, s_res_gothic_24);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_day);
  
  // s_textlayer_w_temp
  s_textlayer_w_temp = text_layer_create(GRect(26, 128, 63, 28));
  text_layer_set_background_color(s_textlayer_w_temp, GColorClear);
  text_layer_set_text(s_textlayer_w_temp, "-10°F");
  text_layer_set_text_alignment(s_textlayer_w_temp, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_w_temp, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_w_temp);
  
  // s_bitmaplayer_weather
  s_bitmaplayer_weather = bitmap_layer_create(GRect(91, 130, 26, 26));
  bitmap_layer_set_bitmap(s_bitmaplayer_weather, s_res_image_w_partly_cloudy);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_weather);
  
  // s_textlayer_bot_user
  s_textlayer_bot_user = text_layer_create(GRect(7, 101, 128, 28));
  text_layer_set_background_color(s_textlayer_bot_user, GColorClear);
  text_layer_set_text(s_textlayer_bot_user, "John Hryb");
  text_layer_set_text_alignment(s_textlayer_bot_user, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_bot_user, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_bot_user);
}

 void destroy_ui(void) {
  window_destroy(s_window);
  bitmap_layer_destroy(s_bitmaplayer_bg);
  text_layer_destroy(s_textlayer_time);
  bitmap_layer_destroy(s_bitmaplayer_BT);
  text_layer_destroy(s_textlayer_batt);
  text_layer_destroy(s_textlayer_date);
  text_layer_destroy(s_textlayer_day);
  text_layer_destroy(s_textlayer_w_temp);
  bitmap_layer_destroy(s_bitmaplayer_weather);
  text_layer_destroy(s_textlayer_bot_user);
  gbitmap_destroy(s_res_image_bg1);
  gbitmap_destroy(s_res_image_bt);
  gbitmap_destroy(s_res_image_w_partly_cloudy);
}
// END AUTO-GENERATED UI CODE

//------------------------------------------------------------------------
void ui_pushStack(void){
  window_stack_push(s_window, true);
}
//------------------------------------------------------------------------
void ui_popStack(void){
  window_stack_push(s_window, true);
}
//------------------------------------------------------------------------
void ui_setTempTo(char *buff){
  text_layer_set_text(s_textlayer_w_temp, buff);
}
//---------------------------------------------------------------------
void ui_setDayTo(char *buff){
  text_layer_set_text(s_textlayer_day, buff);
}
//--------------------------------------------------------------------
void ui_setDateTo(char *buff){
  text_layer_set_text(s_textlayer_date, buff);
}
//---------------------------------------------------------------------
void ui_setTimeTo(char *buff){
  text_layer_set_text(s_textlayer_time, buff);
}
//------------------------------------------------------------------------
void ui_setBattTo(char *buff){
  text_layer_set_text(s_textlayer_batt, buff);
}
//----------------------------------------------------------
void ui_setBluetoothTo(bool isBluetooth){
	//todo show/hide bluetooth bitmap
}
//-----------------------------------------------------------------
void ui_setUserTextTo(char *buff){
	text_layer_set_text(s_textlayer_bot_user,buff);
}