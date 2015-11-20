/** \file keyb.h
 * Header file containing keyboard function prototypes.
 */
#ifndef __KEYB_H__
#define __KEYB_H__

#include "fxlib.h"
#include "timer.h"

int read_string( char **result, int max_length, int x_start, int y_start );

void cursor_on();
void cursor_off();
void cursor_handler();
void move_cursor( int x, int y );
void move_cursor_cr( int column, int row );

#endif
