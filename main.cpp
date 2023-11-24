#include "main.h"

int main()
{
    Tree* tree = NewTree();

    FILE* fp = fopen( "./logs/akinatorlog", "r+" );

    if( !fp )
    {
        perror( "fp is null" );
    }

    FreadPreOrder( fp, tree );

    StartAkinator( tree );

    fseek( fp, 0L, SEEK_SET );

    OutTreePreOrder( tree, fp );

    VIS_TREE_DUMP( tree );

    fclose( fp );

    return 0;
}
