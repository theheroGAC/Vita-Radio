#include "touch.h"
#include <psp2/touch.h>
#include <stdio.h>

void init_touch() {
    sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, SCE_TOUCH_SAMPLING_STATE_START);
    printf("Touch inizializzato\n");
}

void update_touch() {
    SceTouchData touch;
    sceTouchPeek(SCE_TOUCH_PORT_FRONT, &touch, 1);
    if (touch.reportNum > 0) {
        printf("Touch rilevato: x=%d, y=%d\n", touch.report[0].x, touch.report[0].y);
    }
}

void cleanup_touch() {
    sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, SCE_TOUCH_SAMPLING_STATE_STOP);
    printf("Touch pulito\n");
}
