static int status_red = 0 ;
static int status_green = 0 ;
static int status_blue = 0 ;

void set_red( int value ) 
{
    status_red = value ;
}
void set_green( int value ) 
{
    status_green = value ;
}
void set_blue( int value ) 
{
    status_blue = value ;
}

int get_red( void ) 
{
    return status_red ;
}
int get_green( void ) 
{
    return status_green ;
}
int get_blue( void ) 
{
    return status_blue ;
}

int get_status_red_or_green( void ) 
{
    return ( status_red | status_green ) ;
}
int get_status_green_or_blue( void ) 
{
    return ( status_green | status_blue ) ;
}
int get_status_yellow( void ) 
{
    if ( status_red == 1 && status_green == 1 && status_blue == 0 ) {
        return 1 ;
    }
    else {
        return 0 ;
    }
}
int get_status_cyan( void ) 
{
    if ( status_red == 0 && status_green == 1 && status_blue == 1 ) {
        return 1 ;
    }
    else {
        return 0 ;
    }
}
int get_status_magenta( void ) 
{
    if ( status_green == 0  && status_red == 1 && status_blue == 1 ) {
        return 1 ;
    }
    else {
        return 0 ;
    }
}
int get_status_black( void ) 
{
    if ( status_red == 0 && status_green == 0 && status_blue == 0 ) {
        return 1 ;
    }
    else {
        return 0 ;
    }
}
int get_status_white( void ) 
{
    if ( status_red == 1 && status_green == 1 && status_blue == 1 ) {
        return 1 ;
    }
    else {
        return 0 ;
    }
}

void color_init( void ) 
{
    status_red = 0 ;
    status_green = 0 ;
    status_blue = 0 ;
}
void color_clear( void ) 
{
    status_red = 0 ;
    status_green = 0 ;
    status_blue = 0 ;
}
