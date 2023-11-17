#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mystring.h"

typedef long long TreeElem;

const long long DEAD_TREE_ELEM = ( 1ull << 63 ) - 1;

struct Node 
{
    TreeElem data;

    Node* left;

    Node* right;
};

struct Tree
{
    Node* root;

    size_t size;

    size_t depth;
};

void TreeCtor( Tree* );

void DelSubTree( Node* node );

void TreeDtor( Tree* tree );

Tree NewTree();

Node* TreeInsert( Tree* tree, TreeElem elem );

void OutTreePreOrder( Tree* tree );

void SubTreePreOrder( Node* node );

void OutTreePostOrder( Tree* tree );

void SubTreePostOrder( Node* node );

void OutTreeInOrder( Tree* tree );

void SubTreeInOrder( Node* node );

Node* TreeSearch( Tree* tree, TreeElem elem );

Node* SubTreeSearch( Node* node, TreeElem elem );

void FreadPreOrder( FILE* fp, Tree* tree );

Node* SubTreeExtractMin( Node* node );
