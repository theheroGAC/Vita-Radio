#ifndef TOUCH_H
#define TOUCH_H

void init_touch();
void update_touch();
bool is_touch_swipe_left();
bool is_touch_swipe_right();
bool is_touch_swipe_up();
bool is_touch_swipe_down();
void cleanup_touch();

#endif // TOUCH_H
