#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sleep_demo.h"

int main( void )
{
    time_t t = time( NULL ) ;
    // yyyy-mm-dd hh:mm:ss 形式に直す
    struct tm *tm = localtime( &t ) ;
    printf( "%04d-%02d-%02d %02d:%02d:%02d\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec ) ;

    sleep_init();

    sleep_seconds( 5 ) ;
    t = time( NULL ) ;
    tm = localtime( &t ) ;
    printf( "%04d-%02d-%02d %02d:%02d:%02d\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec ) ;


    sleep_random_range( 10, 20 );
    t = time( NULL ) ;
    tm = localtime( &t ) ;
    printf( "%04d-%02d-%02d %02d:%02d:%02d\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec ) ;
}
