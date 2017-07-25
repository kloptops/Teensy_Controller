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
 * For more information, please refer to <http://unlicense.org>
 * This code is based on code written by Sota from the Sudomod forums.
 * It contains autocalibration code by Helder + wermy.
 * 
 * I may at somepoint make it so autocalibration can be disabled and
 * your own variables can be plugged in.
 * 
 */


#ifndef __AXIS_H__
#define __AXIS_H__

#ifndef AXIS_COUNT
# define AXIS_COUNT 0
#endif

#ifndef AXIS_DEADZONE
# define AXIS_DEADZONE 5
#endif

#ifdef AXIS_NO_AUTOCALIBATION
/* TODO: support manual calibration. */
# error "Currently unsupported"
#endif

////////////////////////////////////////////////////////////////////////////////
#if AXIS_COUNT > 0 // AXIS 1
# define AXIS_1

# ifdef AXIS_INVERT_X1
#  define AXIS_X1_F1 +127
#  define AXIS_X1_F2 -127
# else
#  define AXIS_X1_F1 -127
#  define AXIS_X1_F2 +127
# endif

# ifdef AXIS_INVERT_Y1
#  define AXIS_Y1_F1 +127
#  define AXIS_Y1_F2 -127
# else
#  define AXIS_Y1_F1 -127
#  define AXIS_Y1_F2 +127
# endif

// -- Autocalibration variables
int axis_x1_zero = 0;
int axis_y1_zero = 0;
int axis_x1_max = 0;
int axis_x1_min = 0;
int axis_y1_max = 0;
int axis_y1_min = 0;

// -- Autocalibration temporary variables
int     __axis_x1, __axis_y1;
int16_t __axis_x1_final, __axis_y1_final;
float   __axis_x1s_max, __axis_y1s_max;

# define AXIS_X1_CMD X
# define AXIS_Y1_CMD Y

# ifndef AXIS_1_DEADZONE
#  define AXIS_1_DEADZONE AXIS_DEADZONE
# endif
#endif
////////////////////////////////////////////////////////////////////////////////
#if AXIS_COUNT > 1 // AXIS 2
# define AXIS_2
# ifdef AXIS_INVERT_X2
#  define AXIS_X2_F1 +127
#  define AXIS_X2_F2 -127
# else
#  define AXIS_X2_F1 -127
#  define AXIS_X2_F2 +127
# endif

# ifdef AXIS_INVERT_Y2
#  define AXIS_Y2_F1 +127
#  define AXIS_Y2_F2 -127
# else
#  define AXIS_Y2_F1 -127
#  define AXIS_Y2_F2 +127
# endif

// -- Autocalibration variables
int axis_x2_zero = 0;
int axis_y2_zero = 0;
int axis_x2_max = 0;
int axis_x2_min = 0;
int axis_y2_max = 0;
int axis_y2_min = 0;

// -- Autocalibration temporary variables
int     __axis_x2, __axis_y2;
int16_t __axis_x2_final, __axis_y2_final;
float   __axis_x2s_max, __axis_y2s_max;

# define AXIS_X2_CMD Z
# define AXIS_Y2_CMD Zrotate

# ifndef AXIS_2_DEADZONE
#  define AXIS_2_DEADZONE AXIS_DEADZONE
# endif
#endif
////////////////////////////////////////////////////////////////////////////////
#if AXIS_COUNT > 2 // AXIS 3
# define AXIS_3
# ifdef AXIS_INVERT_X3
#  define AXIS_X3_F1 +127
#  define AXIS_X3_F2 -127
# else
#  define AXIS_X3_F1 -127
#  define AXIS_X3_F2 +127
# endif

# ifdef AXIS_INVERT_Y3
#  define AXIS_Y3_F1 +127
#  define AXIS_Y3_F2 -127
# else
#  define AXIS_Y3_F1 -127
#  define AXIS_Y3_F2 +127
# endif

// -- Autocalibration variables
int axis_x3_zero = 0;
int axis_y3_zero = 0;
int axis_x3_max = 0;
int axis_x3_min = 0;
int axis_y3_max = 0;
int axis_y3_min = 0;

// -- Autocalibration temporary variables
int     __axis_x3, __axis_y3;
int16_t __axis_x3_final, __axis_y3_final;
float   __axis_x3s_max, __axis_y3s_max;

# define AXIS_X3_CMD sliderLeft
# define AXIS_Y3_CMD sliderRight

# ifndef AXIS_3_DEADZONE
#  define AXIS_3_DEADZONE AXIS_DEADZONE
# endif
#endif
////////////////////////////////////////////////////////////////////////////////


#define AXIS_LOOP_CODE(ZZ) \
    __axis_x##ZZ = analogRead(AXIS_X##ZZ##_PIN) - axis_x##ZZ##_zero;           \
    __axis_y##ZZ = analogRead(AXIS_Y##ZZ##_PIN) - axis_y##ZZ##_zero;           \
                                                                               \
    /* Deal with deadzones */                                                  \
    if (abs(__axis_x##ZZ) < AXIS_##ZZ##_DEADZONE)                              \
        __axis_x##ZZ = 0;                                                      \
    if (abs(__axis_y##ZZ) < AXIS_##ZZ##_DEADZONE)                              \
        __axis_y##ZZ = 0;                                                      \
                                                                               \
    /* Autocalibrate the maximum and minimum values */                         \
    /* X axis */                                                               \
    if (__axis_x##ZZ > 0 && __axis_x##ZZ > axis_x##ZZ##_max)                   \
        axis_x##ZZ##_max = __axis_x##ZZ;                                       \
    if (__axis_x##ZZ < 0 && __axis_x##ZZ < axis_x##ZZ##_min)                   \
        axis_x##ZZ##_min = __axis_x##ZZ;                                       \
                                                                               \
    /* Y axis */                                                               \
    if (__axis_y##ZZ > 0 && __axis_y##ZZ > axis_y##ZZ##_max)                   \
        axis_y##ZZ##_max = __axis_y##ZZ;                                       \
    if (__axis_y##ZZ < 0 && __axis_y##ZZ < axis_y##ZZ##_min)                   \
        axis_y##ZZ##_min = __axis_y##ZZ;                                       \
                                                                               \
    /* Scale the axis values to the maximum/minimum values */                  \
    /* X axis */                                                               \
    __axis_x##ZZ##s_max = abs(axis_x##ZZ##_max);                               \
    if (__axis_x##ZZ < 0)                                                      \
        __axis_x##ZZ##s_max = abs(axis_x##ZZ##_min);                           \
    __axis_x##ZZ##_final = (((float)__axis_x##ZZ / __axis_x##ZZ##s_max) * 127);\
                                                                               \
    /* Y axis */                                                               \
    __axis_y##ZZ##s_max = abs(axis_y##ZZ##_max);                               \
    if (__axis_y##ZZ < 0)                                                      \
        __axis_y##ZZ##s_max = abs(axis_y##ZZ##_min);                           \
                                                                               \
    __axis_y##ZZ##_final = (((float)__axis_y##ZZ / __axis_y##ZZ##s_max) * 127);\
                                                                               \
    /* Map the axis outputs and output the results */                          \
    Joystick.AXIS_X##ZZ##_CMD(                                                 \
        map(__axis_x##ZZ##_final, AXIS_X##ZZ##_F1, AXIS_X##ZZ##_F2, 0, 255));  \
    Joystick.AXIS_Y##ZZ##_CMD(                                                 \
        map(__axis_y##ZZ##_final, AXIS_Y##ZZ##_F1, AXIS_Y##ZZ##_F2, 0, 255));  \



#endif // __AXIS_H__

