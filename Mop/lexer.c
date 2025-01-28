#include <stdlib.h>
#include <string.h>
#include "lexer.h"

typedef enum {
    NONE,
    NORMAL,
    NEWLINE
} Whitespace_Type;

static Whitespace_Type is_whitespace(char data) {
    switch(data) {
        case ' ':
        case '\t':
            return NORMAL;
        case '\n':
        case '\r':
            return NEWLINE;
    }

    return NONE;
}

static size_t skip_whitespace(char** data, Token_Type* optional) {
    size_t returning = 0;
    Whitespace_Type type = is_whitespace((*data)[0]);

    while(type) {
        ++returning;
        ++(*data);
       
        if(type == NEWLINE) {
            type = is_whitespace((*data)[0]);

            if(!type)
                *optional = BREAK;
        }
        else
            type = is_whitespace((*data)[0]);
    }

    return returning;
}

static int wasBackslash = 0;
static int allowWhitespace = 0;
static size_t currentSize = 0;
static char* currentToken;

static int compareToCurrent(const char* input) {
    if(strlen(input) != currentSize)
        return 0;

    for(size_t i = 0; i < currentSize; i++) {
        if(currentToken[i] != input[i])
            return 0;
    }

    return 1;
}

static void end_token(Token_List_t* list, char* newCurrent) {
    if(!currentSize) {
        currentToken = newCurrent;
        return;
    }

    Token_t* newList = malloc(sizeof(Token_t) * (list->size + 1));
    if(list->size)
        memcpy(newList, list->list, sizeof(Token_t) * list->size);
    if(list->list)
        free(list->list);

    list->list = newList;
    list->list[list->size].string = currentToken; //Maybe it would be better to free this
    list->list[list->size].size = currentSize;

    switch(currentSize) {
        case 1:
            switch(currentToken[0]) {
                case '(': 
                    list->list[list->size].type = LBRACKET;
                    break;
                case ')': 
                    list->list[list->size].type = RBRACKET;
                    break;
                case '{': 
                    list->list[list->size].type = LCURLY;
                    break;
                case '}': 
                    list->list[list->size].type = RCURLY;
                    break;
                case '[': 
                    list->list[list->size].type = LCORNER;
                    break;
                case ']': 
                    list->list[list->size].type = RCORNER;
                    break;
                case ',': 
                    list->list[list->size].type = COMMA;
                    break;
                case '|': 
                    list->list[list->size].type = BAR;
                    break;
                case '#': 
                    list->list[list->size].type = HASHTAG;
                    break;
                default:
                    list->list[list->size].type = NAME;
                    break;
            }
            break;
        default:
            if(compareToCurrent("->"))
                list->list[list->size].type = ARROW;
            else if(compareToCurrent("=>"))
                list->list[list->size].type = CONDITION_ARROW;
            else if(compareToCurrent(":="))
                list->list[list->size].type = DEFINE;
            else if(compareToCurrent("::"))
                list->list[list->size].type = DECLARE;
            else if(compareToCurrent("from"))
                list->list[list->size].type = KEY_FROM;
            else if(compareToCurrent("module"))
                list->list[list->size].type = KEY_MODULE;
            else if(compareToCurrent("with"))
                list->list[list->size].type = KEY_WITH;
            else
                list->list[list->size].type = NAME;

            break;
    }

    ++list->size;
    currentSize = 0;
    currentToken = newCurrent;
}

static void lexer_fill(char* data, Token_List_t* list) {
    if(!strlen(data)) {
        end_token(list, data);
        return;
    }

    if(allowWhitespace) {
        if(!wasBackslash && currentSize && data[0] == '\"') {
            ++currentSize;
            allowWhitespace = 0;
            end_token(list, data + 1);
            lexer_fill(data + 1, list);
        }
        else {
            if(data[0] == '\\')
                wasBackslash = !wasBackslash; //This actually works (i think)
            else
                wasBackslash = 0;

            ++currentSize;
            lexer_fill(data + 1, list);
        }
    }
    else {
        const int isWhitespace = is_whitespace(data[0]);
        Token_Type eBreak = INVALID;
        const size_t whitespace = skip_whitespace(&data, &eBreak);

        if(strlen(data)) {
            if(whitespace)
                end_token(list, data + (isWhitespace ? 0 : 1));
            else {
                ++currentSize;

                if(currentSize == 1 && 
                       (currentToken[0] == '(' || 
                        currentToken[0] == ')' || 
                        currentToken[0] == '{' || 
                        currentToken[0] == '}' || 
                        currentToken[0] == '[' || 
                        currentToken[0] == ']' || 
                        currentToken[0] == ',' ||
                        currentToken[0] == '|' ||
                        currentToken[0] == '#'))
                    end_token(list, data + 1);
                else if(data[1] == '(' || 
                        data[1] == ')' || 
                        data[1] == '{' || 
                        data[1] == '}' || 
                        data[1] == '[' ||
                        data[1] == ']' ||
                        data[1] == ',' ||
                        data[1] == '|' ||
                        data[1] == '#')
                    end_token(list, data + 1);
            }

            if(eBreak) {
                Token_t* newList = malloc(sizeof(Token_t) * (list->size + 1));
                if(list->size)
                    memcpy(newList, list->list, sizeof(Token_t) * list->size);
                if(list->list)
                    free(list->list);

                list->list = newList;
                list->list[list->size].string = "";
                list->list[list->size].size = 0;
                list->list[list->size].type = BREAK;
                ++list->size;
            }

            if(data[0] == '\"')
                allowWhitespace = 1;

            lexer_fill(data + (isWhitespace ? 0 : 1), list);
        }
    }
}

Token_List_t lexer_lex(char* data) {
    Token_List_t returning = {.list = NULL, .size = 0};
    currentToken = data;
    char* passingData = data;
    lexer_fill(passingData, &returning);

    return returning;
}

void lexer_print(const Token_List_t list) {
    for(size_t i = 0; i < list.size; i++) {
        switch(list.list[i].type) {
            case INVALID:
                printf("Invalid!!");
            case BREAK:
                printf("Break   ");
            case LBRACKET:
                printf("L-Bracket");
                break;
            case RBRACKET:
                printf("R-Bracket");
                break;
            case LCURLY:
                printf("L-Curly  ");
                break;
            case RCURLY:
                printf("R-Curly  ");
                break;
            case LCORNER:
                printf("L-Corner ");
                break;
            case RCORNER:
                printf("R-Corner ");
                break;
            case COMMA:
                printf("Comma   ");
                break;
            case BAR:
                printf("Bar     ");
                break;
            case HASHTAG:
                printf("Hashtag ");
                break;
            case ARROW:
                printf("Arrow   ");
                break;
            case CONDITION_ARROW:
                printf("Condition   ");
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
            case KEY_WITH:
                printf("Key-\"with\"");
                break;
            case KEY_MODULE:
                printf("Key-\"module\"");
                break;
            case NAME:
                printf("Name    ");
                break;
        }

        if(list.list[i].size > 0) {
            printf("\t => ");

            for(size_t j = 0; j < list.list[i].size; j++)
                printf("%c", list.list[i].string[j]);
        }

        printf("\n");
    }
}
