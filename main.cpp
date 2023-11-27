#include <stdio.h>
#include <string.h>

#include "tree.h"
#include "akinator.h"

int main()
{
    int type = AkinatorHelloMsg();

    Tree* tree = NewTree();

    FILE* fp = fopen( "./logs/akinatorlog", "r+" );

    if( !fp )
    {
        perror( "fp is null" );
    }

    FreadPreOrder( fp, tree );

    switch( type )
    {
        case 1:
        {
            StartAkinator( tree );

            break;
        }

        case 2:
        {
            char buff[BUFF_SIZE] = {};
            
            printf( "print the name of the object: " );

            if( fgets( buff, BUFF_SIZE, stdin ) == NULL )
            {
                puts( HELP_MESSAGE );

                return 0;
            }

            char* p = strchr( buff, '\n' );

            if( p )
                *p = '\0';

            putchar( '\n' );

            AkinatorDescribe( tree, buff );

            break;
        }

        case 3:
        {
            char buff1[BUFF_SIZE] = {};
            
            printf( "print the name of the first object: " );

            if( fgets( buff1, BUFF_SIZE, stdin ) == NULL )
            {
                puts( HELP_MESSAGE );

                return 0;
            }

            char* p = strchr( buff1, '\n' );

            if( p )
                *p = '\0';

            putchar( '\n' );

            char buff2[BUFF_SIZE] = {};
            
            printf( "print the name of the second object: " );

            if( fgets( buff2, BUFF_SIZE, stdin ) == NULL )
            {
                puts( HELP_MESSAGE );

                return 0;
            }

            p = strchr( buff2, '\n' );

            if( p )
                *p = '\0';

            AkinatorCompare( tree, buff1, buff2 );

            putchar( '\n' );

            break;
        }

        case 4:
        {
            VIS_TREE_DUMP( tree );

            break;
        }

        case 0:
        {
            puts( HELP_MESSAGE );

            return 0;
        }

        default:
        {
            break;
        }
    }

    fseek( fp, 0L, SEEK_SET );

    OutTreePreOrder( tree, fp );

    fclose( fp );

    TreeDtor( tree );

    return 0;
}
