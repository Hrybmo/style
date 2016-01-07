#include <pebble.h>
#include "ui.h"
int get_num_palette_colors(GBitmap *b);
// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GBitmap *s_res_image_bg1;
static GFont s_res_bitham_42_bold;
static GFont s_res_gothic_14;
static GFont s_res_gothic_24_bold;
static GFont s_res_gothic_28_bold;
static GBitmap *s_res_image_01;
static BitmapLayer *s_bitmaplayer_bg;
static TextLayer *s_textlayer_time;
static TextLayer *s_textlayer_batt;
static TextLayer *s_textlayer_date;
static TextLayer *s_textlayer_day;
static TextLayer *s_textlayer_w_temp;
static BitmapLayer *s_bitmaplayer_weather_01;
static TextLayer *s_textlayer_bot_user;

void initialise_ui(void) {
  s_window = window_create();
  
  s_res_image_bg1 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG1);
  s_res_bitham_42_bold = fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD);
  s_res_gothic_14 = fonts_get_system_font(FONT_KEY_GOTHIC_14);
  s_res_gothic_24_bold = fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD);
  s_res_gothic_28_bold = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
  s_res_image_01 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_01);
  // s_bitmaplayer_bg
  s_bitmaplayer_bg = bitmap_layer_create(GRect(0, 0, 144, 168));
  bitmap_layer_set_bitmap(s_bitmaplayer_bg, s_res_image_bg1);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_bg);
  
  // s_textlayer_time
  s_textlayer_time = text_layer_create(GRect(0, 21, 144, 55));
  text_layer_set_background_color(s_textlayer_time, GColorClear);
  text_layer_set_text(s_textlayer_time, "12:42");
  text_layer_set_text_alignment(s_textlayer_time, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_time, s_res_bitham_42_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_time);
  
  // s_textlayer_batt
  s_textlayer_batt = text_layer_create(GRect(121, 153, 21, 15));
  text_layer_set_background_color(s_textlayer_batt, GColorClear);
  text_layer_set_text_color(s_textlayer_batt, GColorWhite);
  text_layer_set_text(s_textlayer_batt, "100");
  text_layer_set_text_alignment(s_textlayer_batt, GTextAlignmentRight);
  text_layer_set_font(s_textlayer_batt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_batt);
  
  // s_textlayer_date
  s_textlayer_date = text_layer_create(GRect(0, 62, 144, 28));
  text_layer_set_background_color(s_textlayer_date, GColorClear);
  text_layer_set_text(s_textlayer_date, "01-01-2015");
  text_layer_set_text_alignment(s_textlayer_date, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_date, s_res_gothic_24_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_date);
  
  // s_textlayer_day
  s_textlayer_day = text_layer_create(GRect(0, -2, 144, 28));
  text_layer_set_background_color(s_textlayer_day, GColorClear);
  text_layer_set_text(s_textlayer_day, "Wed");
  text_layer_set_text_alignment(s_textlayer_day, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_day, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_day);
  
  // s_textlayer_w_temp
  s_textlayer_w_temp = text_layer_create(GRect(34, 130, 63, 28));
  text_layer_set_background_color(s_textlayer_w_temp, GColorClear);
  text_layer_set_text(s_textlayer_w_temp, "-10°F");
  text_layer_set_text_alignment(s_textlayer_w_temp, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_w_temp, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_w_temp);
  
  // s_bitmaplayer_weather_01
  s_bitmaplayer_weather_01 = bitmap_layer_create(GRect(91, 130, 26, 26));
  bitmap_layer_set_bitmap(s_bitmaplayer_weather_01, s_res_image_01);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_weather_01);
  
  // s_textlayer_bot_user
  s_textlayer_bot_user = text_layer_create(GRect(0, 98, 144, 35));
  text_layer_set_background_color(s_textlayer_bot_user, GColorClear);
  text_layer_set_text(s_textlayer_bot_user, "It's working");
  text_layer_set_text_alignment(s_textlayer_bot_user, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_bot_user, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_bot_user);
}

void destroy_ui(void) {
  window_destroy(s_window);
  bitmap_layer_destroy(s_bitmaplayer_bg);
  text_layer_destroy(s_textlayer_time);
  text_layer_destroy(s_textlayer_batt);
  text_layer_destroy(s_textlayer_date);
  text_layer_destroy(s_textlayer_day);
  text_layer_destroy(s_textlayer_w_temp);
  bitmap_layer_destroy(s_bitmaplayer_weather_01);
  text_layer_destroy(s_textlayer_bot_user);
  gbitmap_destroy(s_res_image_bg1);
  gbitmap_destroy(s_res_image_01);
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
//-----------------------------------------------------------------
void ui_setUserTextTo(char *buff){
	text_layer_set_text(s_textlayer_bot_user,buff);
}

void ui_setWeatherTo(uint8_t id){
	switch (id){
		case 1:
			s_res_image_01 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_01);
			break;
		case 2:
			s_res_image_01 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_02);
			break;
		case 3: case 4:
			s_res_image_01 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_03_04);
			break;
		case 9:
			s_res_image_01 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_09);
			break;
		case 10:
			s_res_image_01 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_10);
			break;
		case 11:
			s_res_image_01 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_11);
			break;
		case 13:
			s_res_image_01 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_13);
			break;
		case 50:
			s_res_image_01 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_50);
			break;
	}
}

void ui_setForegroundColorTo(GColor color){
	int num_palette_items = get_num_palette_colors(s_res_image_bg1);
	GColor *current_palette = gbitmap_get_palette(s_res_image_bg1);
	for(int i = 0; i < num_palette_items; i++){
		if ((GColorWhite.argb & 0x3F)==(current_palette[i].argb & 0x3F)){
			current_palette[i].argb = (current_palette[i].argb & 0xC0)| (color.argb & 0x3F);
		}
	}
	num_palette_items = get_num_palette_colors(s_res_image_01);
	current_palette = gbitmap_get_palette(s_res_image_01);
	for(int i = 0; i < num_palette_items; i++){
		if ((GColorWhite.argb & 0x3F)==(current_palette[i].argb & 0x3F)){
			current_palette[i].argb = (current_palette[i].argb & 0xC0)| (color.argb & 0x3F);
		}
	}
}

void ui_setBackgroundColorTo(GColor color){
	int num_palette_items = get_num_palette_colors(s_res_image_bg1);
	GColor *current_palette = gbitmap_get_palette(s_res_image_bg1);
	for(int i = 0; i < num_palette_items; i++){
		if ((GColorBlack.argb & 0x3F)==(current_palette[i].argb & 0x3F)){
			current_palette[i].argb = (current_palette[i].argb & 0xC0)| (color.argb & 0x3F);
		}
	}
}

int get_num_palette_colors(GBitmap *b){
	GBitmapFormat format = gbitmap_get_format(b);
	switch (format) {
		case GBitmapFormat1Bit: return 0;
		case GBitmapFormat8Bit: return 0;
		case GBitmapFormat1BitPalette: return 2;
		case GBitmapFormat2BitPalette: return 4;
		case GBitmapFormat4BitPalette: return 16;
		default: return 0;
	}

}
