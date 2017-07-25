/*
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 * 
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

/* 
 *  Teensy USB controller
 *  
 *  Has support for upto 32 buttons, and 3 anolog sticks.
 *  Contains auto calibration of the analog sticks.
 */


#include <Bounce2.h>

////////////////////////////////////////////////////////////////////////////////
// CHANGE THESE SETTINGS
#define AXIS_COUNT    2     // Number of analog axis (Maximum:  3)
#define BUTTON_COUNT 12     // Number of buttons     (Maximum: 32)

const int AXIS_X1_PIN = A0;
const int AXIS_Y1_PIN = A1;
const int AXIS_X2_PIN = A2;
const int AXIS_Y2_PIN = A3;
// const int AXIS_X3_PIN = A4;
// const int AXIS_Y3_PIN = A5;

#define AXIS_DEADZONE 5

const int BUTTON_PINS[BUTTON_COUNT] = {
     1,  2,  3,  4, // UP, DOWN, LEFT, RIGHT
     5,  6,  7,  8, // A, B, X, Y
     9, 10,         // START, SELECT
    11, 12,         // L1, R1
};

////////////////////////////////////////////////////////////////////////////////

#include "Axis.h"

Bounce BUTTON_BOUNCE[BUTTON_COUNT];

void setup() {
    int i;

    // Initialize axis pins/variables
#ifdef AXIS_1
    pinMode(AXIS_X1_PIN, INPUT);
    pinMode(AXIS_Y1_PIN, INPUT);

    // -- Set anolog stick to its zero position
    axis_x1_zero = analogRead(AXIS_X1_PIN);
    axis_y1_zero = analogRead(AXIS_Y1_PIN);
#endif
#ifdef AXIS_2
    pinMode(AXIS_X2_PIN, INPUT);
    pinMode(AXIS_Y2_PIN, INPUT);

    // -- Set anolog stick to its zero position
    axis_x2_zero = analogRead(AXIS_X2_PIN);
    axis_y2_zero = analogRead(AXIS_Y2_PIN);
#endif
#ifdef AXIS_3
    pinMode(AXIS_X3_PIN, INPUT);
    pinMode(AXIS_Y3_PIN, INPUT);

    // -- Set anolog stick to its zero position
    axis_x3_zero = analogRead(AXIS_X3_PIN);
    axis_y3_zero = analogRead(AXIS_Y3_PIN);
#endif

    // Initialize button pins/variables
    for (i=0; i < BUTTON_COUNT; i++) {
        pinMode(BUTTON_PINS[i], INPUT_PULLUP);
        BUTTON_BOUNCE[i].attach(BUTTON_PINS[i]);
        BUTTON_BOUNCE[i].interval(10);
    }

    Joystick.useManualSend(true);
}


void loop() {
    int i;

#ifdef AXIS_1
    AXIS_LOOP_CODE(1)
#endif
#ifdef AXIS_2
    AXIS_LOOP_CODE(2)
#endif
#ifdef AXIS_3
    AXIS_LOOP_CODE(3)
#endif

    // Update buttons
    for (i=0; i < BUTTON_COUNT; i++) {
        BUTTON_BOUNCE[i].update();
        if (BUTTON_BOUNCE[i].fallingEdge())
            Joystick.button(i + 1, 1);
        if (BUTTON_BOUNCE[i].risingEdge())
            Joystick.button(i + 1, 0);
    }

    Joystick.send_now();
  
    // a brief delay, so this runs 20 times per second
    delay(5);
}

