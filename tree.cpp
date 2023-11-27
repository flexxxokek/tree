#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mystring.h"
#include "tree.h"

#define _MARK_ printf( "||||!MARK!||||, %s, %s, %d  \n", __FILE__, __PRETTY_FUNCTION__, __LINE__  );

#define SMTH_IS_NULL( smth ) fprintf( stderr, "in %s" #smth "is NULL\n", __PRETTY_FUNCTION__ );

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
    
    free( tree );
}

void DelSubTree( Node* node )
{
    if( !node )
    {
        return;
    }

    DelSubTree( node->left );

    DelSubTree( node->right );

    NodeDtor( node );
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

    node->data = NULL;

    node->left = NULL;

    node->right = NULL;
}

Node* NewNode()
{
    Node* node = ( Node* ) calloc( 1, sizeof( Node ) );

    NodeCtor( node );

    return node;
}

void NodeDtor( Node* node )
{
    if( !node )
    {
        SMTH_IS_NULL( node );

        return;
    }
    
    if( node->data )
        free( node->data );

    free( node );
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

TREE_ERRS FreadPreOrder( FILE* fp, Tree* tree )
{
    if( !fp )
    {
        SMTH_IS_NULL( fp );

        return TREE_ERRS::FP_IS_NULL;
    }

    if( !tree )
    {
        SMTH_IS_NULL( tree );

        return TREE_ERRS::TREE_POINTER_IS_NULL;
    }

    char buff[BUFF_SIZE] = {};

    if( !tree->root )
    {
        fgets( buff, BUFF_SIZE - 1, fp );

        *strchr( buff, '\n' ) = '\0';

        if( !strcmp( buff, " (" ) )
        {
            tree->root = NewNode();

            if( !tree->root )
            {
                perror( "nullptr error" );

                return TREE_ERRS::LACK_OF_MEMORY;
            }

            if( fgets( buff, BUFF_SIZE - 1, fp ) == NULL )
            {
                NodeDtor( tree->root );

                return TREE_ERRS::TREE_END_OF_IN;
            }

            *strchr( buff, '\n' ) = '\0';

            tree->root->data = strdup( buff );
        }
        else
        {
            return TREE_ERRS::INVALID_TREE_INPUT;
        }
    }

    return NodeFreadPreOrder( fp, tree->root, buff );
}

TREE_ERRS NodeFreadPreOrder( FILE* fp, Node* node, char* buff )
{
    do
    {
        fgets( buff, BUFF_SIZE - 1, fp );
    }
    while( buff[0] == '\n' );

    char* p = NULL;

    p = strchr( buff, '\n' );

    if( p )
        *p = '\0';

    if( !strcmp( buff, "nil" ) )
    {
        node->left = NULL;
    }
    else if( !strcmp( buff, " (" ) )
    {
        node->left = NewNode();

        if( !node->left )
        {
            perror( "nullptr error" );

            return TREE_ERRS::LACK_OF_MEMORY;
        }

        fgets( buff, BUFF_SIZE - 1, fp );

        p = strchr( buff, '\n' );

        if( p )
            *p = '\0';

        node->left->data = strdup( buff );

        NodeFreadPreOrder( fp, node->left, buff );
    }
    
    fgets( buff, BUFF_SIZE - 1, fp );

    p = strchr( buff, '\n' );

    if( p )
        *p = '\0';

    if( !strcmp( buff, "nil" ) )
    {
        node->right = NULL;
    }
    else if( !strcmp( buff, " (" ) )
    {
        node->right = NewNode();

        if( !node->right )
        {
            perror( "nullptr error" );

            return TREE_ERRS::LACK_OF_MEMORY;
        }

        fgets( buff, BUFF_SIZE - 1, fp );

        p = strchr( buff, '\n' );

        if( p )
            *p = '\0';

        node->right->data = strdup( buff );

        NodeFreadPreOrder( fp, node->right, buff );
    }

    fgets( buff, BUFF_SIZE - 1, fp );

    return TREE_ERRS::TREE_OK;
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
        fprintf( fp, "node%d[ label=\"{ <p> %p | <data> ", n, node );
    else
        fprintf( fp, "node%d[ color=lightgreen label=\"{ <p> %p | <data> ", n, node );

    if( node->data )
    {
        fputs( node->data, fp );
    }
    else
    {
        fputs( "NULL", fp );
    }

    if( !node->left )
        fprintf( fp, " | { <l> left:NULL" );
    else
        fprintf( fp, " | { <l> left" );

    if( !node->right )
        fprintf( fp, " | <r> right:NULL" );
    else
        fprintf( fp, " | <r> right" );

    fprintf( fp, " } } \" ]\n" );

    if( node->left )
        fprintf( fp, "node%d:l -> node%d\n", n, n * 2 + 1 );

    if( node->right ) 
        fprintf( fp, "node%d:r -> node%d\n", n, n * 2 + 2 );

    VisSubTreeDump( node->left, 2 * n + 1, fp );

    VisSubTreeDump( node->right, 2 * n + 2, fp );
}