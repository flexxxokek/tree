#include <stdio.h>
#include <assert.h>

#include "mystring.h"

int isNum( const char* ch )
{
    printf( "start:\t" );

    while( *ch )
    {
        putchar( *ch );

        if( *ch > '9' || *ch < '0' )
            return false;

        ch++;
    }
    
    return true;
}

long long StrToNum( const char* s )
{
    const char* start = s;

    long long num = 0;

    while( *s )
    {
        int temp = *s - '0';

        if( temp < 0 || temp > 9 )
        {
            printf( "str %s is not a number\n", start );

            return -1;
        }

        num = num * 10 + temp;

        s++;
    }

    return num;
}
