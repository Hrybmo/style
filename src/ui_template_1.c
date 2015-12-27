/*
#include "ui_template_1.h"
#include <pebble.h>

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GBitmap *s_res_image_bg1;
static GFont s_res_bitham_42_bold;
static GBitmap *s_res_image_bt;
static GFont s_res_gothic_14;
static GFont s_res_gothic_18_bold;
static GFont s_res_gothic_24;
static GFont s_res_gothic_28_bold;
static GBitmap *s_res_image_w_sunny;
static GBitmap *s_res_image_w_thunderstorm;
static GBitmap *s_res_image_w_snow;
static GBitmap *s_res_image_w_chance_thunderstorm;
static GBitmap *s_res_image_w_partly_cloudy;
static BitmapLayer *s_bitmaplayer_bg;
static TextLayer *s_textlayer_time;
static BitmapLayer *s_bitmaplayer_BT;
static TextLayer *s_textlayer_batt;
static TextLayer *s_textlayer_date;
static TextLayer *s_textlayer_day;
static TextLayer *s_textlayer_w_temp;
static TextLayer *s_textlayer_w_hi;
static BitmapLayer *s_bitmaplayer_w1;
static BitmapLayer *s_bitmaplayer_w2;
static BitmapLayer *s_bitmaplayer_w3;
static BitmapLayer *s_bitmaplayer_w4;
static TextLayer *s_textlayer_w_lo;
static BitmapLayer *s_bitmaplayer_w5;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, true);
  
  s_res_image_bg1 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG1);
  s_res_bitham_42_bold = fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD);
  s_res_image_bt = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BT);
  s_res_gothic_14 = fonts_get_system_font(FONT_KEY_GOTHIC_14);
  s_res_gothic_18_bold = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
  s_res_gothic_24 = fonts_get_system_font(FONT_KEY_GOTHIC_24);
  s_res_gothic_28_bold = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
  s_res_image_w_sunny = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_W_SUNNY);
  s_res_image_w_thunderstorm = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_W_THUNDERSTORM);
  s_res_image_w_snow = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_W_SNOW);
  s_res_image_w_chance_thunderstorm = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_W_CHANCE_THUNDERSTORM);
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
  s_textlayer_w_temp = text_layer_create(GRect(13, 126, 63, 28));
  text_layer_set_background_color(s_textlayer_w_temp, GColorClear);
  text_layer_set_text_color(s_textlayer_w_temp, GColorWhite);
  text_layer_set_text(s_textlayer_w_temp, "-10°F");
  text_layer_set_text_alignment(s_textlayer_w_temp, GTextAlignmentRight);
  text_layer_set_font(s_textlayer_w_temp, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_w_temp);
  
  // s_textlayer_w_hi
  s_textlayer_w_hi = text_layer_create(GRect(80, 127, 40, 15));
  text_layer_set_background_color(s_textlayer_w_hi, GColorClear);
  text_layer_set_text_color(s_textlayer_w_hi, GColorWhite);
  text_layer_set_text(s_textlayer_w_hi, "-20");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_w_hi);
  
  // s_bitmaplayer_w1
  s_bitmaplayer_w1 = bitmap_layer_create(GRect(10, 100, 26, 26));
  bitmap_layer_set_bitmap(s_bitmaplayer_w1, s_res_image_w_sunny);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_w1);
  
  // s_bitmaplayer_w2
  s_bitmaplayer_w2 = bitmap_layer_create(GRect(40, 100, 26, 26));
  bitmap_layer_set_bitmap(s_bitmaplayer_w2, s_res_image_w_thunderstorm);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_w2);
  
  // s_bitmaplayer_w3
  s_bitmaplayer_w3 = bitmap_layer_create(GRect(70, 100, 26, 26));
  bitmap_layer_set_bitmap(s_bitmaplayer_w3, s_res_image_w_snow);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_w3);
  
  // s_bitmaplayer_w4
  s_bitmaplayer_w4 = bitmap_layer_create(GRect(100, 100, 26, 26));
  bitmap_layer_set_bitmap(s_bitmaplayer_w4, s_res_image_w_chance_thunderstorm);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_w4);
  
  // s_textlayer_w_lo
  s_textlayer_w_lo = text_layer_create(GRect(80, 139, 40, 15));
  text_layer_set_background_color(s_textlayer_w_lo, GColorClear);
  text_layer_set_text_color(s_textlayer_w_lo, GColorWhite);
  text_layer_set_text(s_textlayer_w_lo, "-10");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_w_lo);
  
  // s_bitmaplayer_w5
  s_bitmaplayer_w5 = bitmap_layer_create(GRect(100, 128, 26, 26));
  bitmap_layer_set_bitmap(s_bitmaplayer_w5, s_res_image_w_partly_cloudy);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_w5);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  bitmap_layer_destroy(s_bitmaplayer_bg);
  text_layer_destroy(s_textlayer_time);
  bitmap_layer_destroy(s_bitmaplayer_BT);
  text_layer_destroy(s_textlayer_batt);
  text_layer_destroy(s_textlayer_date);
  text_layer_destroy(s_textlayer_day);
  text_layer_destroy(s_textlayer_w_temp);
  text_layer_destroy(s_textlayer_w_hi);
  bitmap_layer_destroy(s_bitmaplayer_w1);
  bitmap_layer_destroy(s_bitmaplayer_w2);
  bitmap_layer_destroy(s_bitmaplayer_w3);
  bitmap_layer_destroy(s_bitmaplayer_w4);
  text_layer_destroy(s_textlayer_w_lo);
  bitmap_layer_destroy(s_bitmaplayer_w5);
  gbitmap_destroy(s_res_image_bg1);
  gbitmap_destroy(s_res_image_bt);
  gbitmap_destroy(s_res_image_w_sunny);
  gbitmap_destroy(s_res_image_w_thunderstorm);
  gbitmap_destroy(s_res_image_w_snow);
  gbitmap_destroy(s_res_image_w_chance_thunderstorm);
  gbitmap_destroy(s_res_image_w_partly_cloudy);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_ui_template_1(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_ui_template_1(void) {
  window_stack_remove(s_window, true);
}
*/