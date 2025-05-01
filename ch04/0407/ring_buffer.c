
#include <stdio.h>
#include "ring_buffer.h"

static int ring_buffer[ 10 ] ;
static int ring_buffer_index = 0 ;

void ring_buffer_init() 
{
    for( int i = 0 ; i < 10 ; i++ ) {
        ring_buffer[ i ] = 0 ;
    }
    ring_buffer_index = 0 ;
}
void ring_buffer_push( int value ) 
{
    ring_buffer[ ring_buffer_index ] = value ;
    ring_buffer_index ++ ;
    ring_buffer_index = ring_buffer_index  % 10 ;
}

int ring_buffer_get( int index ) 
{
    return ring_buffer[ index % 10 ] ;
}

int ring_buffer_pop() 
{
    ring_buffer_index --;
    ring_buffer_index = ring_buffer_index  % 10 ;
    int value = ring_buffer[ ring_buffer_index ] ;
    ring_buffer[ ring_buffer_index ] = 0 ;
    return value ;
}

int ring_buffer_shift()
{
    int value = ring_buffer[ 0 ] ;
    for( int i = 0 ; i < ring_buffer_size() - 1 ; i++ ) {
        ring_buffer[ i ] = ring_buffer[ i + 1 ] ;
    }
    ring_buffer[ ring_buffer_size() - 1 ] = 0 ;
    return value ;
}

void ring_buffer_clear() 
{
    for( int i = 0 ; i < 10 ; i++ ) {
        ring_buffer[ i ] = 0 ;
    }
    ring_buffer_index = 0 ;
}

int ring_buffer_size() 
{
    return sizeof( ring_buffer ) / sizeof( ring_buffer[ 0 ] ) ;
}

void ring_buffer_print() 
{
    for( int i = 0 ; i < ring_buffer_size() ; i++ ) {
        printf( "%d ", ring_buffer[ i ] ) ;
    }
    printf( "\n" ) ;
}

