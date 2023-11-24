#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mystring.h"

typedef char* TreeElem;

const long long DEAD_TREE_ELEM = ( 1ull << 63 ) - 1;

const long long MAX_TREE_ELEM_LEN = 64;

const size_t BUFF_SIZE = 24;

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

#define VIS_TREE_DUMP( tree ) VisTreeDump( tree, #tree );

void TreeCtor( Tree* );

void DelSubTree( Node* node );

void TreeDtor( Tree* tree );

Tree* NewTree();

void NodeCtor( Node* node );

Node* NewNode();

Node* TreeInsert( Tree* tree, TreeElem elem );

void OutTreePreOrder( Tree* tree, FILE* fp );

void OutSubTreePreOrder( Node* node, FILE* fp );

void FreadPreOrder( FILE* fp, Tree* tree );

void NodeFreadPreOrder( FILE* fp, Node* node, char* buff );

void StartAkinator( Tree* tree );

void AkinatorCall( Node* node );

void VisTreeDump( Tree* tree, const char* s1 );

void VisSubTreeDump( Node* node, int n, FILE* fp );
