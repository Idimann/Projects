#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"

Block_List_t parser_from_tokens(const Token_List_t input) {
    Block_List_t returning = {
        .size = input.size, 
        .type = COLLECTION, 
        .token = INVALID,
        .blocks = malloc(sizeof(Block_List_t) * input.size)
    };

    for(size_t i = 0; i < returning.size; i++) {
        returning.blocks[i].size = 0;
        returning.blocks[i].type = TOKEN;
        returning.blocks[i].token = input.list[i];
        returning.blocks[i].blocks = NULL;
    }

    return returning;
}

static size_t recursive_bracket_collection(Block_List_t* input, size_t begin, size_t end) {
    size_t bracketBegin = 0;
    size_t bracketCount = 0;

    size_t returning = 0;

    for(size_t i = begin; i < end; i++) {
        if(input->blocks[i].type != TOKEN)
            return returning; //This can't happen

        if(input->blocks[i].token.type == LBRACKET) {
            if(!bracketCount)
                bracketBegin = i;

            ++bracketCount;
        }
        else if(input->blocks[i].token.type == RBRACKET) {
            --bracketCount;

            if(!bracketCount) {
                i -= recursive_bracket_collection(input, bracketBegin + 1, i);

                const size_t numOfNewTokens = i - bracketBegin - 1;
                input->blocks[bracketBegin].type = COLLECTION;

                //Resetting the token
                input->blocks[bracketBegin].token.type = INVALID;
                input->blocks[bracketBegin].token.size = 0;
                input->blocks[bracketBegin].token.string = NULL;

                //Opening the token list
                input->blocks[bracketBegin].size = numOfNewTokens;
                input->blocks[bracketBegin].blocks = malloc(sizeof(Block_List_t) * numOfNewTokens);

                //Filling the token list
                for(size_t j = 0; j < numOfNewTokens; j++)
                    input->blocks[bracketBegin].blocks[j] = input->blocks[bracketBegin + j + 1];

                //Removing tokens from our list
                Block_List_t* newBlocks = malloc(sizeof(Block_List_t) * 
                        (input->size - numOfNewTokens - 1));

                //Actually removing the tokens
                size_t counter = 0;
                for(size_t j = 0; j < (input->size); j++) {
                    if(bracketBegin < j && j <= i)
                        continue;

                    newBlocks[counter] = input->blocks[j];
                    ++counter;
                }

                free(input->blocks);
                input->blocks = newBlocks;
                input->size -= numOfNewTokens + 1;
                returning += numOfNewTokens + 1;
            }
        }
    }

    return returning;
}

void parser_collect_brackets(Block_List_t* input) {
    recursive_bracket_collection(input, 0, input->size);
}

void parser_collect_breaks(Block_List_t* input) {
    size_t foundAt = 0;

    for(size_t i = 0; i < (input->size); i++) {
        if(input->blocks[i].type != TOKEN)
            continue;

        if(input->blocks[i].token.type != BREAK)
            continue;

        const size_t numOfNewTokens = i - foundAt - 1;
        const Block_List_t token = input->blocks[foundAt];
        input->blocks[foundAt].type = COLLECTION;

        //Resetting the token
        input->blocks[foundAt].token.type = INVALID;
        input->blocks[foundAt].token.size = 0;
        input->blocks[foundAt].token.string = NULL;

        //Opening the token list
        input->blocks[foundAt].size = numOfNewTokens + 1;
        input->blocks[foundAt].blocks = malloc(sizeof(Block_List_t) * (numOfNewTokens + 1));

        //Inputting the first one
        input->blocks[foundAt].blocks[0] = token;

        //Filling the token list
        for(size_t j = 1; j < numOfNewTokens; j++)
            input->blocks[foundAt].blocks[j] = input->blocks[foundAt + j];

        //Removing tokens from our list
        Block_List_t* newBlocks = malloc(sizeof(Block_List_t) * 
                (input->size - numOfNewTokens - 1));

        //Actually removing the tokens
        size_t counter = 0;
        for(size_t j = 0; j < (input->size); j++) {
            if(foundAt < j && j <= i)
                continue;

            newBlocks[counter] = input->blocks[j];
            ++counter;
        }

        free(input->blocks);
        input->blocks = newBlocks;
        input->size -= numOfNewTokens + 1;
        i -= numOfNewTokens;
        foundAt = i + 1;
    }
}

void parser_print(const Block_List_t* list, const size_t indentation) {
    for(size_t i = 0; i < (list->size); i++) {
        for(size_t j = 0; j < indentation; j++)
            printf("\t");

        if(list->blocks[i].type == TOKEN) {
            printf("Token \t=> ");

            switch(list->blocks[i].token.type) {
                case INVALID:
                    printf("Invalid!!");
                case BREAK:
                    printf("Break");
                    break;
                case LBRACKET:
                    printf("L-Bracket");
                    break;
                case RBRACKET:
                    printf("R-Bracket");
                    break;
                case LCURLY:
                    printf("L-Curly");
                    break;
                case RCURLY:
                    printf("R-Curly");
                    break;
                case LCORNER:
                    printf("L-Corner");
                    break;
                case RCORNER:
                    printf("R-Corner");
                    break;
                case COMMA:
                    printf("Comma");
                    break;
                case BAR:
                    printf("Bar");
                    break;
                case HASHTAG:
                    printf("Hashtag");
                    break;
                case ARROW:
                    printf("Arrow");
                    break;
                case CONDITION_ARROW:
                    printf("Condition");
                    break;
                case DEFINE:
                    printf("Definition");
                    break;
                case DECLARE:
                    printf("Declaration");
                    break;
                case KEY_FROM:
                    printf("Key-\"from\"");
                    break;
                case KEY_MODULE:
                    printf("Key-\"module\"");
                    break;
                case KEY_WITH:
                    printf("Key-\"with\"");
                    break;
                case NAME:
                    printf("Name");
                    break;
            }

            if(list->blocks[i].token.size > 0) {
                printf("(");
                for(size_t j = 0; j < (list->blocks[i].token.size); j++)
                    printf("%c", list->blocks[i].token.string[j]);
                printf(")\n");
            }
            else
                printf("\n");
        }
        else if(list->blocks[i].type == COLLECTION) {
            printf("Block \t=>\n");

            parser_print(&list->blocks[i], indentation + 1);
        }
    }
}
