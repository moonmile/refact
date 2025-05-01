#include <stdio.h>

/**
 * 組み合わせテストのサンプルコード
 */

#include <stdio.h>
#include "color.h"
int main( void ) 
{
    puts( "色のサンプル" ) ;
    color_init() ;
    set_red( 1 ) ;
    set_green( 1 ) ;
    set_blue( 1 ) ;
    printf( "red = %d\n", get_red() ) ;
    printf( "green = %d\n", get_green() ) ;
    printf( "blue = %d\n", get_blue() ) ;
    printf( "yellow = %d\n", get_status_red_or_green() ) ;
    printf( "white = %d\n", get_status_white() ) ;
    printf( "black = %d\n", get_status_black() ) ;
    color_clear() ;

    return 0;
}