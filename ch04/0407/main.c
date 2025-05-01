#include <stdio.h>
#include <stdlib.h>
#include "ring_buffer.h"

int main( void ) 
{
    puts( "シーケンスのサンプル" ) ;

    ring_buffer_init() ;
    ring_buffer_push( 1 ) ;
    ring_buffer_push( 2 ) ;
    ring_buffer_push( 3 ) ;
    ring_buffer_print() ;

    int n = ring_buffer_get( 0 ) ;
    printf( "ring_buffer_get( 0 ) = %d\n", n ) ;

    ring_buffer_pop() ;
    ring_buffer_pop() ;
    ring_buffer_push( 10 ) ;
    ring_buffer_push( 11 ) ;
    ring_buffer_push( 12 ) ;

    ring_buffer_print() ;

    return 0;
}