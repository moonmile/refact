#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "sleep_demo.h"

void sleep_init( void ) 
{
    time_t t = time( NULL ) ;
    srand( t ) ;
}


int sleep_seconds( int seconds ) 
{
    sleep( seconds ) ;
    return 0 ;
}
int sleep_random( int seconds ) 
{
    int n = rand() % seconds + 1 ;
    sleep( n ) ;
    return 0 ;
}
int sleep_random_range( int min, int max ) 
{
    int n = rand() % ( max - min + 1 ) + min ;
    sleep( n ) ;
    return 0 ;
}
int sleep_longtime( int seconds ) 
{
    sleep( seconds * 10) ;
    return 0 ;
}
