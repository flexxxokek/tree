#include <string.h>

#include "akinator.h"

#define SMTH_IS_NULL( smth ) fprintf( stderr, "in %s" #smth "is NULL\n", __PRETTY_FUNCTION__ );

#define __AK_SPEECH__

int AkinatorHelloMsg()
{
    printf( "Mighty Akinator greets you!\n"
            "type: 1 to play guess game\n"
            "      2 to print description of an object\n"
            "      3 to compare objects\n"
            "      4 to generate visualisation of search tree( includes \"graphviz\" )\n" );

    int c = getchar();

    if( c == EOF )
    {
        puts( HELP_MESSAGE );

        return 0;
    }

    int temp = 0;

    while( ( temp = getchar() ) != EOF && temp != '\n' )
        ;

    if( temp == EOF )
    {
        puts( HELP_MESSAGE );

        return 0;
    }

    if( c <= '4' && c >= '1' )
    {
        return c - '0';
    }
    
    return 0;
}

AKINATOR_ERRS StartAkinator( Tree* tree )
{
    if( !tree )
    {
        SMTH_IS_NULL( tree );

        return AKINATOR_ERRS::TREE_ERR;
    }

    if( !tree->root )
    {
        fprintf( stderr, "\ntree is empty\n" );

        return AKINATOR_ERRS::TREE_ERR;
    }

    int err = AkinatorCall( tree->root );

    if( !err )
    {
        return AKINATOR_ERRS::AKINATOR_OK;
    }
    else if( err & AKINATOR_ERRS::INVALID_USER_INPUT )
    {
        fprintf( stderr, "\nInvalid user input\n" );

        return AKINATOR_ERRS::INVALID_USER_INPUT;
    }
    else if( err & AKINATOR_ERRS::TREE_ERR )
    {
        fprintf( stderr, "\nTree error\n" );

        return AKINATOR_ERRS::TREE_ERR;
    }
    else if( err & AKINATOR_ERRS::AKINATOR_END_OF_IN )
    {
        fprintf( stderr, "\nEnd of input in Akinator\n" );

        return AKINATOR_ERRS::TREE_ERR;
    }

    return AKINATOR_ERRS::AKINATOR_OK;
}

AKINATOR_ERRS AkinatorCall( Node* node )
{
    printf( "(Is/Does) your object %s?\n", node->data );

    printf( "Enter[y/n]: " );

    #ifdef __AK_SPEECH__

    FILE* fp = fopen( "speech.txt", "w" );

    fprintf( fp, "(Is/Does) your object %s?\n", node->data );

    fprintf( fp, "Enter[y/n]: \n" );

    fclose( fp );

    system( "espeak -f speech.txt" );

    system( "rm speech.txt" );

    #endif

    int ch = getchar();

    if( ch == EOF )
        return AKINATOR_ERRS::AKINATOR_END_OF_IN;

    char* p;

    int temp = 0;

    while( ( temp = getchar() ) != EOF && temp != '\n' )
        ;

    if( temp == EOF )
        return AKINATOR_ERRS::AKINATOR_END_OF_IN;

    char buff[BUFF_SIZE] = {};

    if( ch == 'y' )
    {
        putc( '\n', stdout );

        if( !node->right )
        {
            printf( "\nHAHAHAHA HUMANITY LOST AGAIN, BOZO GETTA FUK OUTA HERE\n" );

            #ifdef __AK_SPEECH__

            fp = fopen( "speech.txt", "w" );

            fprintf( fp, "\nHAHAHAHA HUMANITY LOST AGAIN, BOZO GETTA FUK OUTA HERE\n" );

            fclose( fp );

            system( "espeak -f speech.txt" );

            system( "rm speech.txt" );

            #endif

            return AKINATOR_ERRS::AKINATOR_OK;
        }

        return AkinatorCall( node->right );
    }
    else
    {
        putc( '\n', stdout );

        if( !node->left )
        {
            Node* newnodel = NewNode();

            if( !newnodel )
            {
                perror( "nullptr error" );

                return AKINATOR_ERRS::TREE_ERR;
            }

            Node* newnoder = NewNode();    //the past node can't conform the new condition, that's why it must be left 

            if( !newnoder )
            {
                perror( "nullptr error" );

                NodeDtor( newnodel );

                return AKINATOR_ERRS::TREE_ERR;
            }

            node->left = newnodel;

            node->right = newnoder;

            node->left->data = node->data;

            printf( "Give a hint to the stupid computer, please.\n" );
            printf( "Who or What was your object?\n"
                    "-(He/She/It/They) (is/are) " );

            #ifdef __AK_SPEECH__

            fp = fopen( "speech.txt", "w" );

            fprintf( fp, "Give a hint to the stupid computer, please.\n" );
            fprintf( fp, "Who or What was your object?\n" );

            fclose( fp );

            system( "espeak -f speech.txt" );

            system( "rm speech.txt" );

            #endif
            
            if( fgets( buff, BUFF_SIZE, stdin ) == NULL )
            {
                node->left = NULL;

                NodeDtor( node->left );

                NodeDtor( node->right );

                node->left = NULL;

                node->right = NULL;

                return AKINATOR_ERRS::AKINATOR_END_OF_IN;
            }

            p = strchr( buff, '\n' );

            if( p )
                *p = '\0';

            node->right->data = strdup( buff );

            printf( "What's the difference between your object and %s?\n", node->left->data );

            #ifdef __AK_SPEECH__

            fp = fopen( "speech.txt", "w" );

            fprintf( fp, "What's the difference between your object and %s?\n", node->left->data );
                    
            fclose( fp );

            system( "espeak -f speech.txt" );

            system( "rm speech.txt" );

            #endif

            printf( "-(He/She/It/They) (is/are/does/do) " );

            if( fgets( buff, BUFF_SIZE, stdin ) == NULL )
            {
                node->left = NULL;

                NodeDtor( node->left );

                NodeDtor( node->right );

                node->left = NULL;

                node->right = NULL;

                return AKINATOR_ERRS::AKINATOR_END_OF_IN;
            }

            p = strchr( buff, '\n' );

            if( p )
                *p = '\0';

            node->data = strdup( buff );

            return AKINATOR_ERRS::AKINATOR_OK;
        }

        return AkinatorCall( node->left );
    }
}

void AkinatorDescribe( Tree* tree, const char* name )
{
    char buff[BUFF_SIZE] = {};

    char* p = buff;

    if( AkinatorDescribe( tree->root, name, &p, stdout ) == 0 )
    {
        printf( "%s has not been found in tree\n", name );
    }

    //printf("%s\n", buff);
}

int AkinatorDescribe( Node* node, const char* name, char** buff, FILE* fp )
{
    int l = 0;

    int r = 0;

    if( node->left )
    {
        l = AkinatorDescribe( node->left, name, buff, fp );
    }
    
    if( node->right )
    {
        r = AkinatorDescribe( node->right, name, buff, fp );
    }

    if( !strcmp( node->data, name ) &&
        !node->left && !node->right )
    {
        if( fp )
        {
            fprintf( fp, "%s is\n", node->data );
        }

        return 1;
    }

    if( l )
    {
        if( buff )
        {
            **buff = '0';

            ++*buff;
        }

        if( fp )
        {
            fprintf( fp, "not %s \n", node->data );
        }

        return 1;
    }

    if( r )
    {
        if( buff )
        {
            **buff = '1';

            ++*buff;
        }

        if( fp )
        {
            fprintf( fp, "%s \n", node->data );
        }

        return 1;
    }

    return 0;
}

void AkinatorCompare( Tree* tree, const char* name1, const char* name2 )
{
    char buff1[BUFF_SIZE] = {};

    char* p1 = buff1;

    char buff2[BUFF_SIZE] = {};

    char* p2 = buff2;

    if( AkinatorDescribe( tree->root, name1, &p1, NULL ) == 0 )
    {
        printf( "error 404: %s was not found\n", name1 );

        return;
    }

    if( AkinatorDescribe( tree->root, name2, &p2, NULL ) == 0 )
    {
        printf( "error 404: %s was not found\n", name2 );

        return;
    }

    printf("%s|%s\n", buff1, buff2);

    printf( "similarities:\n" );

    Node* node = tree->root;

    for( ; p1 >= buff1 && p2 >= buff2; p1--, p2-- )
    {
        if( *p1 == *p2 )
        {
            if( *p1 == '0' )
            {
                printf( "not %s \n", node->data );

                node = node->left;
            }

            if( *p1 == '1' )
            {
                printf( "%s \n", node->data );

                node = node->right;
            }
        }
        else
        {
            printf( "the difference:\n"
                    "%s\n", node->data );

            break;
        }
    }
}

