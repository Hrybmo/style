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
  s_textlayer_batt = text_layer_create(GRect(110, 88, 27, 15));
  text_layer_set_background_color(s_textlayer_batt, GColorClear);
  text_layer_set_text(s_textlayer_batt, "100");
  text_layer_set_text_alignment(s_textlayer_batt, GTextAlignmentCenter);
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
  s_textlayer_w_temp = text_layer_create(GRect(29, 130, 63, 28));
  text_layer_set_background_color(s_textlayer_w_temp, GColorClear);
  text_layer_set_text(s_textlayer_w_temp, "-10°F");
  text_layer_set_text_alignment(s_textlayer_w_temp, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_w_temp, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_w_temp);
  
  // s_bitmaplayer_weather_01
  s_bitmaplayer_weather_01 = bitmap_layer_create(GRect(86, 130, 26, 26));
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
//---------------------------------------------------------
void ui_setWeatherTo(uint8_t id){
	switch (id){
		gbitmap_destroy(s_res_image_01);
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
	bitmap_layer_set_bitmap(s_bitmaplayer_weather_01, s_res_image_01);
}

//-----------------------------------------------------------------------'
//much easier than seperate fuctions because of color overlapping
void ui_setAllColors(uint32_t background, uint32_t foreground, uint32_t text){
	static bool isFirstCall = true;
	//static GColor oldTextColor;
	static GColor oldForegroundColor;
	static GColor oldBackgroundColor;
	int num_palette_items;
	GColor *current_palette;
	
	int index1 = 0;
	int index2 = 0;
	
	if(isFirstCall){
		oldForegroundColor = GColorWhite;
		oldBackgroundColor = GColorBlack;
		//oldTextColor = GColorBlack;
		isFirstCall = false;
	}
	
	//first do background image
	num_palette_items = get_num_palette_colors(s_res_image_bg1);
	current_palette = gbitmap_get_palette(s_res_image_bg1);
	for(int i = 0; i < num_palette_items; i++){
		if ((oldForegroundColor.argb & 0x3F)==(current_palette[i].argb & 0x3F)){
			index1 = i;
		}
	}
	for(int i = 0; i < num_palette_items; i++){
		if ((oldBackgroundColor.argb & 0x3F)==(current_palette[i].argb & 0x3F)){
			index2 = i;
		}
	}
	
	current_palette[index1].argb = (current_palette[index1].argb & 0xC0)| 
																 (GColorFromHEX(foreground).argb & 0x3F);
	current_palette[index2].argb = (current_palette[index2].argb & 0xC0)|
																 (GColorFromHEX(background).argb & 0x3F);

	//now do weather
	num_palette_items = get_num_palette_colors(s_res_image_01);
	current_palette = gbitmap_get_palette(s_res_image_01);
	for(int i = 0; i < num_palette_items; i++){
		if ((GColorWhite.argb & 0x3F)==(current_palette[i].argb & 0x3F)){
			index1 = i;
		}
	}
	for(int i = 0; i < num_palette_items; i++){
		if ((GColorBlack.argb & 0x3F)==(current_palette[i].argb & 0x3F)){
			index2 = i;
		}
	}
	
	current_palette[index1].argb = (current_palette[index1].argb & 0xC0)|
																 (GColorFromHEX(foreground).argb & 0x3F);
	current_palette[index2].argb = (current_palette[index2].argb & 0xC0)|
																 (GColorFromHEX(text).argb & 0x3F);
	
	//set for round
	window_set_background_color(s_window, GColorFromHEX(background));
	
	//now finish the text
	text_layer_set_text_color(s_textlayer_time, GColorFromHEX(text));
	text_layer_set_text_color(s_textlayer_batt, GColorFromHEX(text));
	text_layer_set_text_color(s_textlayer_date, GColorFromHEX(text));
	text_layer_set_text_color(s_textlayer_day, GColorFromHEX(text));
	text_layer_set_text_color(s_textlayer_w_temp, GColorFromHEX(text));
	text_layer_set_text_color(s_textlayer_bot_user, GColorFromHEX(text));
	
	//and save for next time
	oldForegroundColor = GColorFromHEX(foreground);
	oldBackgroundColor = GColorFromHEX(background);
	//oldTextColor = GColorFromHEX(text);
}
//----------------------------------------------------------------------
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

GRect roundOffset(GRect r){
	return GRect((r.origin.x + 18), r.origin.y + 7, r.size.w, r.size.h);
}		

void ui_fitToRound(){
	Layer *layer; 
	GRect frame;
	
	layer = bitmap_layer_get_layer(s_bitmaplayer_bg);
	frame = layer_get_frame(layer);
	layer_set_frame(layer, roundOffset(frame));
	
	layer = bitmap_layer_get_layer(s_bitmaplayer_weather_01);
	frame = layer_get_frame(layer);
	layer_set_frame(layer, roundOffset(frame));
	
	layer = text_layer_get_layer(s_textlayer_time);
	frame = layer_get_frame(layer);
	layer_set_frame(layer, roundOffset(frame));
	
	layer = text_layer_get_layer(s_textlayer_batt);
	frame = layer_get_frame(layer);
	layer_set_frame(layer, roundOffset(frame));

	layer = text_layer_get_layer(s_textlayer_date);
	frame = layer_get_frame(layer);
	layer_set_frame(layer, roundOffset(frame));

	layer = text_layer_get_layer(s_textlayer_day);
	frame = layer_get_frame(layer);
	layer_set_frame(layer, roundOffset(frame));
	
	layer = text_layer_get_layer(s_textlayer_w_temp);
	frame = layer_get_frame(layer);
	layer_set_frame(layer, roundOffset(frame));
	
  layer = text_layer_get_layer(s_textlayer_bot_user);
	frame = layer_get_frame(layer);
	layer_set_frame(layer, roundOffset(frame));
}
									
							