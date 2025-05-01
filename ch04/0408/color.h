#ifndef __COLOR_H__
#define __COLOR_H__

void color_init();
void set_red( int value );
void set_green( int value );
void set_blue( int value );
int get_red( void );
int get_green( void );
int get_blue( void );
int get_status_red_or_green( void );
int get_status_green_or_blue( void );
int get_status_yellow( void );
int get_status_cyan( void );
int get_status_magenta( void );
int get_status_black( void );
int get_status_white( void );
int color_clear( void );
#endif