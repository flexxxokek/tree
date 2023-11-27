#ifndef _TREE__
#define _TREE__

typedef char* TreeElem;

const long long DEAD_TREE_ELEM = ( 1ull << 63 ) - 1;

const long long MAX_TREE_ELEM_LEN = 64;

const size_t BUFF_SIZE = 100;

struct Node 
{
    TreeElem data;  //

    Node* left;

    Node* right;
};

struct Tree
{
    Node* root;

    size_t size;

    size_t depth;
};

enum TREE_ERRS
{
    TREE_OK = 0,
    LACK_OF_MEMORY = 1 << 0,
    TREE_IS_EMPTY = 1 << 1,
    FP_IS_NULL = 1 << 2,
    TREE_POINTER_IS_NULL = 1 << 3,
    INVALID_TREE_INPUT = 1 << 4,
    TREE_END_OF_IN = 1 << 5
};

#define VIS_TREE_DUMP( tree ) VisTreeDump( tree, #tree );

void NodeCtor( Node* node );

Node* NewNode();

void NodeDtor( Node* node );

void TreeCtor( Tree* );

void DelSubTree( Node* node );

void TreeDtor( Tree* tree );

Tree* NewTree();

void OutTreePreOrder( Tree* tree, FILE* fp );

void OutSubTreePreOrder( Node* node, FILE* fp );

TREE_ERRS FreadPreOrder( FILE* fp, Tree* tree );

TREE_ERRS NodeFreadPreOrder( FILE* fp, Node* node, char* buff );

void VisTreeDump( Tree* tree, const char* s1 );

void VisSubTreeDump( Node* node, int n, FILE* fp );

#endif