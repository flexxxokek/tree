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
        printf( "NULL pointer recieved in function TreeDtor()" );

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

Tree NewTree()
{
    Tree buff = {};

    TreeCtor( &buff );

    return buff;
}

Node* TreeInsert( Tree* tree, TreeElem elem )
{
    if( tree->root == NULL )
    {
        tree->root = ( Node* ) calloc( 1, sizeof( Node ) );

        tree->root->data = elem;

        tree->root->left = NULL;

        tree->root->right = NULL;

        return tree->root;
    }

    Node* node = tree->root;

    while( true )
    {
        if( elem <= node->data )
        {
            if( node->left == NULL )
            {
                node->left = ( Node* ) calloc( 1, sizeof( Node ) );

                node->left->data = elem;

                node->left->left = NULL;

                node->left->right = NULL;

                return node->left;
            }

           node = node->left; 
        }
        
        if( elem > node->data )
        {
            if( node->right == NULL )
            {
                node->right = ( Node* ) calloc( 1, sizeof( Node ) );

                node->right->data = elem;

                node->right->left = NULL;

                node->right->right = NULL;

                return node->right;
            }

           node = node->right; 
        }
    }
}

void OutTreePreOrder( Tree* tree )
{
    SubTreePreOrder( tree->root );

    putchar( '\n' );
}

void SubTreePreOrder( Node* node )
{
    if( !node )
    {
        printf( " nil" );

        return;
    }
    
    printf( " ( " );

    printf( "%lld", node->data );

    SubTreePreOrder( node->left );

    SubTreePreOrder( node->right );

    printf( " )" );
}

void OutTreePostOrder( Tree* tree )
{
    SubTreePostOrder( tree->root );

    putchar( '\n' );
}

void SubTreePostOrder( Node* node )
{
    if( !node )
    {
        printf( " nil" );

        return;
    }
    
    printf( " ( " );

    SubTreePostOrder( node->left );

    SubTreePostOrder( node->right );

    printf( "%lld", node->data );

    printf( " )" );
}

void OutTreeInOrder( Tree* tree )
{
    SubTreePostOrder( tree->root );

    putchar( '\n' );
}

void SubTreeInOrder( Node* node )
{
    if( !node )
    {
        printf( " nil" );

        return;
    }
    
    printf( " ( " );

    SubTreeInOrder( node->left );

    printf( "%lld", node->data );

    SubTreeInOrder( node->right );

    printf( " )" );
}

void TreeDelElem( Tree* tree, TreeElem elem )
{
    if( tree == NULL )
    {
        printf( "in %s: tree is NULL\n", __PRETTY_FUNCTION__);
    }

    SubTreeDelElem( tree->root, elem );
}

void SubTreeDelElem( Node* node, TreeElem elem )
{
    if( node == NULL )
    {        
        return;
    }

    if( elem == node->data )
    {
        Node* swapnode = SubTreeExtractMin( node );

        return;
    }

    if( elem <= node->data )
        SubTreeDelElem( node->left, elem );

    if( elem > node->data )
        SubTreeDelElem( node->right, elem );
}

Node* TreeSearch( Tree* tree, TreeElem elem )
{
    if( tree == NULL )
    {
        printf( "NULL pointer recieved in function TreeSearch()\n" );
    }

    return SubTreeSearch( tree->root, elem );
}

Node* SubTreeSearch( Node* node, TreeElem elem )
{
    if( node == NULL )
    {        
        return NULL;
    }

    if( elem == node->data )
        return node;

    if( elem <= node->data )
        return SubTreeSearch( node->right, elem );

    if( elem > node->data )
        return SubTreeSearch( node->left, elem );

    return NULL;
}

void FreadPreOrder( FILE* fp, Tree* tree )
{
    if( !fp )
        return;

    if( !tree )
        return;

    char buff[21] = {};

    int temp = 0;

    long long delta = 0;

    while( ( temp = fscanf( fp, "%20s", buff ) ) != EOF && temp != 0 && buff[0] != '\n' )
    {
        /*puts( buff );

        printf( "buff is %d\n", isNum( buff ) );*/

        if( delta < 0 )
        {
            printf( "Invalid tree sequence \n" );

            return;
        }

        if( !strcmp( buff, "nil" ) )
            continue;

        if( !strcmp( buff, "(" ) )
        {
            ++delta;
        }

        else if( !strcmp( buff, ")" ) )
        {
            --delta;
        }
        
        else if( isNum( buff ) == 1 )
        {
            _MARK_;

            TreeInsert( tree, StrToNum( buff ) );
        }

        else
        {
            printf( "Invalid tree sequence \n" );

            return;
        }
    }
}

Node* SubTreeSearchMin( Node* node )
{
    if( !node )
    {
        SMTH_IS_NULL( node );

        return NULL;
    }

    Node* curpos = node->right;

    while( curpos->left )
    {
        curpos = curpos->left;
    }

    return curpos;
}

Node* SubTreeExtractMin( Node* node )
{
    if( !node )
    {
        SMTH_IS_NULL( node );

        return NULL;
    }

    Node* curpos = node->right;

    Node* res = NULL;

    while( curpos->left->left )
    {
        curpos = curpos->left;
    }

    res = curpos->left;

    curpos->left = NULL;

    return res;
}

