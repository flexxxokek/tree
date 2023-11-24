#include "tree.h"

#define _MARK_ printf( "||||!MARK!||||, %s, %s, %d  \n", __FILE__, __PRETTY_FUNCTION__, __LINE__  );

#define SMTH_IS_NULL( smth ) printf( "in %s" #smth "is NULL\n", __PRETTY_FUNCTION__ );

void TreeCtor( Tree* tree )
{
    if( !tree )
    {
        SMTH_IS_NULL( tree );

        return;
    }

    tree->size = 0;

    tree->depth = 0;

    tree->root = NULL;

    //printf( "successfuly created tree\n" );
}

void TreeDtor( Tree* tree )
{
    if( !tree )
    {
        SMTH_IS_NULL( tree );

        return;
    }

    DelSubTree( tree->root );

    tree->depth = 0;

    tree->size = 0;

    tree->root = NULL;
}

void DelSubTree( Node* node )
{
    if( !node )
    {
        return;
    }

    DelSubTree( node->left );

    DelSubTree( node->right );

    free( node );
}

Tree* NewTree()
{
    Tree* tree = ( Tree* ) calloc( 1, sizeof( Tree ) );

    TreeCtor( tree );

    return tree;
}

void NodeCtor( Node* node )
{
    if( !node )
    {
        SMTH_IS_NULL( node );

        return;
    }

    node->data = ( char* ) calloc( 1, sizeof( char ) * BUFF_SIZE );

    node->left = NULL;

    node->right = NULL;
}

Node* NewNode()
{
    Node* node = ( Node* ) calloc( 1, sizeof( Node ) );

    NodeCtor( node );

    return node;
}

void OutTreePreOrder( Tree* tree, FILE* fp )
{
    if( !fp )
    {
        SMTH_IS_NULL( fp );

        return;
    }

    if( !tree )
    {
        SMTH_IS_NULL( tree );

        return;
    }

    OutSubTreePreOrder( tree->root, fp );

    putchar( '\n' );
}

void OutSubTreePreOrder( Node* node, FILE* fp )
{
    if( !node )
    {
        fprintf( fp, "nil\n" );

        return;
    }
    
    fprintf( fp, " (\n" );

    fputs( node->data, fp );

    putc( '\n', fp );

    OutSubTreePreOrder( node->left, fp );

    OutSubTreePreOrder( node->right, fp );

    fprintf( fp, " )\n" );
}

void FreadPreOrder( FILE* fp, Tree* tree )
{
    if( !fp )
    {
        SMTH_IS_NULL( fp );

        return;
    }

    if( !tree )
    {
        SMTH_IS_NULL( tree );

        return;
    }

    char buff[BUFF_SIZE] = {};

    if( !tree->root )
    {
        fgets( buff, BUFF_SIZE, fp );

        *strchr( buff, '\n' ) = '\0';

        if( !strcmp( buff, " (" ) )
        {
            tree->root = NewNode();

            fgets( buff, BUFF_SIZE, fp );

            *strchr( buff, '\n' ) = '\0';

            strncpy( tree->root->data, buff, BUFF_SIZE );
        }
        else
        {
            return;
        }
    }

    NodeFreadPreOrder( fp, tree->root, buff );
}

void NodeFreadPreOrder( FILE* fp, Node* node, char* buff )
{
    do
    {
        fgets( buff, BUFF_SIZE, fp );
    }
    while( buff[0] == '\n' );

    *strchr( buff, '\n' ) = '\0';

    if( !strcmp( buff, "nil" ) )
    {
        node->left = NULL;
    }
    else if( !strcmp( buff, " (" ) )
    {
        node->left = NewNode();

        fgets( node->left->data, BUFF_SIZE, fp );

        *strchr( node->left->data, '\n' ) = '\0';

        NodeFreadPreOrder( fp, node->left, buff );
    }
    
    fgets( buff, BUFF_SIZE, fp );

    *strchr( buff, '\n' ) = '\0';

    if( !strcmp( buff, "nil" ) )
    {
        node->right = NULL;
    }
    else if( !strcmp( buff, " (" ) )
    {
        node->right = NewNode();

        fgets( node->right->data, BUFF_SIZE, fp );

        *strchr( node->right->data, '\n' ) = '\0';

        NodeFreadPreOrder( fp, node->right, buff );
    }

    fgets( buff, BUFF_SIZE, fp );
}

void VisTreeDump( Tree* tree, const char* s1 )
{
    if( !tree )
    {
        SMTH_IS_NULL( tree );

        return;
    }

    FILE* fp = fopen( "./logs/graphvislog", "w" );

    fprintf( fp, "digraph %s{\n", s1 );
    fprintf( fp, "    rankdir=\"TB\"\n" );
    fprintf( fp, "    node [ shape=\"record\"; color=yellow; style=filled; area=100 ]\n" );
    fprintf( fp, "    edge [  ]\n" );
    
    VisSubTreeDump( tree->root, 0, fp );

    fprintf( fp, "}\n" );

    fclose( fp );

    system( "/usr/bin/dot ./logs/graphvislog -T jpeg > ./logs/1.jpeg" );
}

void VisSubTreeDump( Node* node, int n, FILE* fp )
{
    if( !node )
        return;

    if( node->left || node->right )
        fprintf( fp, "node%d[ label=\"{ <data> ", n );
    else
        fprintf( fp, "node%d[ color=lightgreen label=\"{ <data> ", n );

    fputs( node->data, fp );

    if( !node->left )
        fprintf( fp, " | { <l> left:NULL" );
    else
        fprintf( fp, " | { <l> left:%p", node->left );

    if( !node->right )
        fprintf( fp, " | <r> right:NULL" );
    else
        fprintf( fp, " | <r> right:%p", node->right );

    fprintf( fp, " } } \" ]\n" );

    if( node->left )
        fprintf( fp, "node%d:l -> node%d\n", n, n * 2 + 1 );

    if( node->right ) 
        fprintf( fp, "node%d:r -> node%d\n", n, n * 2 + 2 );

    VisSubTreeDump( node->left, 2 * n + 1, fp );

    VisSubTreeDump( node->right, 2 * n + 2, fp );
}

void StartAkinator( Tree* tree )
{
    if( !tree )
    {
        SMTH_IS_NULL( tree );

        return;
    }

    if( !tree->root )
    {
        printf( "tree is empty\n" );

        return;
    }

    AkinatorCall( tree->root );
}

void AkinatorCall( Node* node )
{
    printf( "(Is/Does) your object ");

    puts( strcat( node->data, "?" ) );

    *strchr( node->data, '?' ) = '\0';

    printf( "Enter[y/n]: " );

    fflush( stdin );

    int ch = getchar();

    while( getchar() != '\n' )
        ;

    if( ch == 'y' )
    {
        putc( '\n', stdout );

        if( !node->right )
        {
            printf( "\nHAHAHAHA HUMANITY LOST AGAIN, BOZO GETTA FUK OUTA HERE\n" );

            return;
        }

        AkinatorCall( node->right );
    }
    else
    {
        putc( '\n', stdout );

        if( !node->left )
        {
            Node* newnodel = NewNode();

            Node* newnoder = NewNode();    //the past node can't conform the new condition, that's why it must be left 

            node->left = newnodel;

            node->right = newnoder;

            strncpy( node->left->data, node->data, BUFF_SIZE );

            printf( "Give a hint to the stupid computer, please.\n" );
            printf( "Who or What was your object?\n"
                    "-(He/She/It) is " );
            
            fgets( node->right->data, BUFF_SIZE, stdin );

            *strchr( node->right->data, '\n' ) = '\0';

            printf( "What's the difference between your object and " );

            fputs( strcat( node->left->data, "?" ), stdout );

            *strchr( node->left->data, '?' ) = '\0';

            printf( "-(He/She/It) (is/does) " );

            fgets( node->data, BUFF_SIZE, stdin );

            *strchr( node->data, '\n' ) = '\0';

            return;
        }

        fflush( stdin );

        AkinatorCall( node->left );
    }
}