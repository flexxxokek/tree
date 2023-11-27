#ifndef __AKINATOR_
#define __AKINATOR_

#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

enum AKINATOR_ERRS
{
    AKINATOR_OK = 0,
    INVALID_USER_INPUT = 1 << 0,
    TREE_ERR = 1 << 1,
    AKINATOR_END_OF_IN = 1 << 2
};

const char* const HELP_MESSAGE = "\nfuck you dumbass nigga!\n";

int AkinatorHelloMsg();

AKINATOR_ERRS StartAkinator( Tree* tree );

AKINATOR_ERRS AkinatorCall( Node* node );

void AkinatorDescribe( Tree* tree, const char* name );

int AkinatorDescribe( Node* node, const char* name, char** buff, FILE* fp );

void AkinatorCompare( Tree* tree, const char* name1, const char* name2 );

#endif