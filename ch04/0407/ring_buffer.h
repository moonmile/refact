#ifndef __RING_BUFFER_H__
#define __RING_BUFFER_H__

void ring_buffer_init();
void ring_buffer_push( int value );
int ring_buffer_get( int index );
int ring_buffer_pop() ;
int ring_buffer_shift();
int ring_buffer_size() ;
void ring_buffer_print() ;
void ring_buffer_clear() ;
int ring_buffer_seek();

#endif