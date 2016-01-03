#include <pebble.h>

/*
for time:
do (60 - minute) * 2 and shade that white
*/
static Window *window;
static Layer *bg_layer, *time_layer;

static void time_update_proc(Layer *layer, GContext *ctx) {
	time_t temp = time(NULL);
	struct tm *t = localtime(&temp);
	
	graphics_context_set_fill_color(ctx, GColorLightGray);
}

static void bg_create_proc(Layer *layer, GContext *ctx) {
	graphics_context_set_stroke_color(ctx, GColorLightGray);
	graphics_draw_rect(ctx, GRect(12, 23, 12, 120));
	graphics_draw_rect(ctx, GRect(36, 23, 12, 120));
	graphics_draw_rect(ctx, GRect(60, 23, 12, 120));

	for (int i = 0; i < 13; i++) {
		int y_pos;
		if (i == 12) {
			y_pos = (i * 10) + 22;
		} else {
			y_pos = (i * 10) + 23;
		}
		graphics_draw_line(ctx, GPoint(72, y_pos), GPoint(75, y_pos));

//		if (i == 15) {
	
	}

	graphics_draw_circle(ctx, GPoint(102 ,62), 7); //AM circle
	graphics_draw_circle(ctx, GPoint(124, 62), 7); //PM circle
	graphics_draw_circle(ctx, GPoint(102, 84), 7); //BT circle
	graphics_draw_rect(ctx, GRect(117, 77, 15, 15)); //Date rect
	
	graphics_draw_rect(ctx, GRect(95, 100, 37, 16)); // Day of week
}

static void main_window_load() {
	bg_layer = layer_create(GRect(0, 0, 144, 168));
	layer_set_update_proc(bg_layer, bg_create_proc);
	layer_add_child(window_get_root_layer(window), bg_layer);

	time_layer = layer_create(GRect(0, 0, 144, 168));
	layer_set_update_proc(time_layer, time_update_proc);
	layer_add_child(window_get_root_layer(window), time_layer);
}

static void main_window_unload() {
	layer_destroy(bg_layer);
}

static void init() {
	window = window_create();
	
	window_set_background_color(window, GColorBlack);

	window_set_window_handlers(window, (WindowHandlers) {
		.load = main_window_load,
		.unload = main_window_unload,
	});

	window_stack_push(window, true);
}

static void deinit() {
	window_destroy(window);
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}
