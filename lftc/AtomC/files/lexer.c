#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "lexer.h"

Token *tokens; // single linked list of tokens
Token *lastTk; // the last token in list

int line = 1; // the current line in the input file

// adds a token to the end of the tokens list and returns it
// sets its code and line
Token *addTk(int code)
{
    Token *tk = safeAlloc(sizeof(Token));
    tk->code = code;
    tk->line = line;
    tk->next = NULL;
    if (lastTk)
    {
        lastTk->next = tk;
    } else
    {
        tokens = tk;
    }
    lastTk = tk;
    return tk;
}

char *extract(const char *begin, const char *end)
{
    size_t length = end - begin;
    char *result = safeAlloc(length + 1);

    memcpy(result, begin, length);
    result[length] = '\0';

    return result;
}

Token *tokenize(const char *pch)
{
    const char *start;
    Token *tk;
    for (;;)
    {
        switch (*pch)
        {
            case ' ':
            case '\t': pch++;
                break;
            case '\r': // handles different kinds of newlines (Windows: \r\n, Linux: \n, MacOS, OS X: \r or \n)
                if (pch[1] == '\n')pch++;
            // fallthrough to \n
            case '\n':
                line++;
                pch++;
                break;

            // Comment handling
            case '/':
                if (pch[1] == '/')
                {
                    // line comment
                    pch += 2;
                    while (*pch != '\r' && *pch != '\n' && *pch != '\0') pch++;
                } else
                {
                    addTk(DIV);
                    pch++;
                }
                break;

            case '\0': addTk(END);
                return tokens;

            // Delimiters
            case ',': addTk(COMMA);
                pch++;
                break;
            case ';': addTk(SEMICOLON);
                pch++;
                break;
            case '(': addTk(LPAR);
                pch++;
                break;
            case ')': addTk(RPAR);
                pch++;
                break;
            case '[': addTk(LBRACKET);
                pch++;
                break;
            case ']': addTk(RBRACKET);
                pch++;
                break;
            case '{': addTk(LACC);
                pch++;
                break;
            case '}': addTk(RACC);
                pch++;
                break;

            // Operators
            case '+': addTk(ADD);
                pch++;
                break;
            case '-': addTk(SUB);
                pch++;
                break;
            case '*': addTk(MUL);
                pch++;
                break;
            case '.': addTk(DOT);
                pch++;
                break;

            case '&':
                if (pch[1] == '&')
                {
                    addTk(AND);
                    pch += 2;
                } else
                {
                    err("invalid char: %c (%d), expecting &&", *pch, *pch);
                }
                break;

            case '|':
                if (pch[1] == '|')
                {
                    addTk(OR);
                    pch += 2;
                } else
                {
                    err("invalid char: %c (%d), expecting ||", *pch, *pch);
                }
                break;

            case '!':
                if (pch[1] == '=')
                {
                    addTk(NOTEQ);
                    pch += 2;
                } else
                {
                    addTk(NOT);
                    pch++;
                }
                break;

            case '=':
                if (pch[1] == '=')
                {
                    addTk(EQUAL);
                    pch += 2;
                } else
                {
                    addTk(ASSIGN);
                    pch++;
                }
                break;

            case '<':
                if (pch[1] == '=')
                {
                    addTk(LESSEQ);
                    pch += 2;
                } else
                {
                    addTk(LESS);
                    pch++;
                }
                break;

            case '>':
                if (pch[1] == '=')
                {
                    addTk(GREATEREQ);
                    pch += 2;
                } else
                {
                    addTk(GREATER);
                    pch++;
                }
                break;

            // Character constant
            case '\'':
                pch++;
                if (*pch == '\0' || *pch == '\n' || *pch == '\r')
                {
                    err("invalid char constant");
                }
                tk = addTk(CHAR);
                if (*pch == '\\')
                {
                    pch++;
                    switch (*pch)
                    {
                        case 'n': tk->c = '\n';
                            break;
                        case 't': tk->c = '\t';
                            break;
                        case '\\': tk->c = '\\';
                            break;
                        case '\'': tk->c = '\'';
                            break;
                        case 'r': tk->c = '\r';
                            break;
                        case '0': tk->c = '\0';
                            break;
                        default: err("unknown escape sequence: \\%c", *pch);
                    }
                    pch++;
                } else
                {
                    tk->c = *pch++;
                }

                if (*pch != '\'')
                {
                    err("missing closing quote for char constant");
                }
                pch++;
                break;

            // String constant
            case '"':
                start = ++pch;
                while (*pch != '"' && *pch != '\0' && *pch != '\n' && *pch != '\r') pch++;
                if (*pch != '"')
                {
                    err("missing closing quote for string constant");
                }
                tk = addTk(STRING);
                tk->text = extract(start, pch);
                pch++;
                break;

            default:
                // Identifiers and keywords
                if (isalpha(*pch) || *pch == '_')
                {
                    for (start = pch++; isalnum(*pch) || *pch == '_'; pch++)
                    {
                    }
                    char *text = extract(start, pch);
                    if (strcmp(text, "char") == 0) addTk(TYPE_CHAR);
                    else if (strcmp(text, "double") == 0) addTk(TYPE_DOUBLE);
                    else if (strcmp(text, "else") == 0) addTk(ELSE);
                    else if (strcmp(text, "if") == 0) addTk(IF);
                    else if (strcmp(text, "int") == 0) addTk(TYPE_INT);
                    else if (strcmp(text, "return") == 0) addTk(RETURN);
                    else if (strcmp(text, "struct") == 0) addTk(STRUCT);
                    else if (strcmp(text, "void") == 0) addTk(VOID);
                    else if (strcmp(text, "while") == 0) addTk(WHILE);
                    else
                    {
                        tk = addTk(ID);
                        tk->text = text;
                    }
                }
                // Integer and double constants
                else if (isdigit(*pch))
                {
                    start = pch;

                    while (isdigit(*pch)) pch++;

                    if (*pch == '.' || *pch == 'e' || *pch == 'E')
                    {
                        if (*pch == '.')
                        {
                            pch++;
                            if (!isdigit(*pch))
                            {
                                err("expecting digits after decimal point");
                            }
                            while (isdigit(*pch)) pch++;
                        }

                        if (*pch == 'e' || *pch == 'E')
                        {
                            pch++;
                            if (*pch == '+' || *pch == '-') pch++;
                            if (!isdigit(*pch))
                            {
                                err("expecting digits in exponent");
                            }
                            while (isdigit(*pch)) pch++;
                        }

                        tk = addTk(DOUBLE);
                        char *text = extract(start, pch);
                        tk->d = atof(text);
                        free(text);
                    } else
                    {
                        tk = addTk(INT);
                        char *text = extract(start, pch);
                        tk->i = atoi(text);
                        free(text);
                    }
                } else err("invalid char: %c (%d) %d", *pch, *pch, line);
        }
    }
}

void showTokens(const Token *tokens)
{
    for (const Token *tk = tokens; tk; tk = tk->next)
    {
        printf("%d\t", tk->line);

        switch (tk->code)
        {
            case ID:
                printf("ID:%s", tk->text);
                break;

            // Constants
            case INT:
                printf("INT:%d", tk->i);
                break;
            case DOUBLE:
                printf("DOUBLE:%g", tk->d);
                break;
            case CHAR:
                printf("CHAR:");
                switch (tk->c)
                {
                    case '\n': printf("\\n");
                        break;
                    case '\t': printf("\\t");
                        break;
                    case '\r': printf("\\r");
                        break;
                    case '\\': printf("\\\\");
                        break;
                    case '\'': printf("\\'");
                        break;
                    case '\"': printf("\\\"");
                        break;
                    case '\0': printf("\\0");
                        break;
                    default: printf("%c", tk->c);
                }
                break;
            case STRING:
                printf("STRING:%s", tk->text);
                break;

            // Keywords
            case TYPE_CHAR: printf("TYPE_CHAR");
                break;
            case TYPE_DOUBLE: printf("TYPE_DOUBLE");
                break;
            case ELSE: printf("ELSE");
                break;
            case IF: printf("IF");
                break;
            case TYPE_INT: printf("TYPE_INT");
                break;
            case RETURN: printf("RETURN");
                break;
            case STRUCT: printf("STRUCT");
                break;
            case VOID: printf("VOID");
                break;
            case WHILE: printf("WHILE");
                break;

            // Delimiters
            case COMMA: printf("COMMA");
                break;
            case SEMICOLON: printf("SEMICOLON");
                break;
            case LPAR: printf("LPAR");
                break;
            case RPAR: printf("RPAR");
                break;
            case LBRACKET: printf("LBRACKET");
                break;
            case RBRACKET: printf("RBRACKET");
                break;
            case LACC: printf("LACC");
                break;
            case RACC: printf("RACC");
                break;
            case END: printf("END");
                break;

            // Operators
            case ADD: printf("ADD");
                break;
            case SUB: printf("SUB");
                break;
            case MUL: printf("MUL");
                break;
            case DIV: printf("DIV");
                break;
            case DOT: printf("DOT");
                break;
            case AND: printf("AND");
                break;
            case OR: printf("OR");
                break;
            case NOT: printf("NOT");
                break;
            case ASSIGN: printf("ASSIGN");
                break;
            case EQUAL: printf("EQUAL");
                break;
            case NOTEQ: printf("NOTEQ");
                break;
            case LESS: printf("LESS");
                break;
            case LESSEQ: printf("LESSEQ");
                break;
            case GREATER: printf("GREATER");
                break;
            case GREATEREQ: printf("GREATEREQ");
                break;
            default: printf("UNKNOWN");
                break;
        }
        printf("\n");
    }
}
