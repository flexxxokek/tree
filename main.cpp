#include "main.h"

int main()
{
    Tree tree = NewTree();

    FILE* fp = fopen( "treelog", "r" );

    /*TreeInsert( &tree, 499 );

    for( int i = 0; i < 1000; i++ )
    {
        TreeInsert( &tree, i % 500 );
    }

    TreeOrder( &tree );

    TreeDtor( &tree );

    TreeCtor( &tree );

    if( !fp )
        printf( "fp is null\n" );
    //FreadSeq( fp, &tree );

    TreeOrder( &tree );

    fclose( fp );*/

    FreadPreOrder( fp, &tree );

    OutTreePreOrder( &tree );

    return 0;
}
