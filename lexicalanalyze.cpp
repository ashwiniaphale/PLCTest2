#include <stdio.h>
#include <ctype.h>
#include <string.h>

class LexicalAnalyzer
{
public:
    int charClass;
    char lexeme[100];
    char nextChar;
    int lexLen;
    int token;
    int nextToken;
    FILE *in_fp;

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token codes */
#define BEGIN 1
#define END 2
#define BYTE 3
#define INT 4
#define SHORT 5
#define LONG 6
#define AND_OP 7
#define OR_OP 8
#define IDENT 11
#define IF 12
#define ELSE 13
#define WHILE 14
#define UNDERSCORE 15
#define VARIABLE 16
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define MODUL 30
#define LESS_THAN 31
#define GREATER_THAN 32
#define LESS_EQUAL 33
#define GREATER_EQUAL 34
#define EQUAL_TO 35
#define NOT_EQUAL 36
#define NEWLINE 37

    /* lookup - a function to look up operators and
     parentheses and return the token */

    int lookup(char ch)
    {
        switch (ch)
        {
        case '(':
            addChar();
            nextToken = LEFT_PAREN;
            break;
        case ')':
            addChar();
            nextToken = RIGHT_PAREN;
            break;
        case '+':
            addChar();
            nextToken = ADD_OP;
            break;
        case '-':
            addChar();
            nextToken = SUB_OP;
            break;
        case '*':
            addChar();
            nextToken = MULT_OP;
            break;
        case '/':
            addChar();
            nextToken = DIV_OP;
            break;
        case '%':
            addChar();
            nextToken = MODUL;
            break;
        case '<':
            addChar();
            nextToken = LESS_THAN;
            break;
        case '>':
            addChar();
            nextToken = GREATER_THAN;
            break;
        case '!':
            addChar();
            nextToken = NOT_EQUAL;
            break;
        case '#':
            addChar();
            nextToken = LESS_EQUAL;
            break;
        case '$':
            addChar();
            nextToken = GREATER_EQUAL;
            break;
        case '~':
            addChar();
            nextToken = EQUAL_TO;
            break;
        case '=':
            addChar();
            nextToken = ASSIGN_OP;
            break;
        case '\n':
            addChar();
            nextToken = NEWLINE;
            break;
        default:
            addChar();
            nextToken = EOF;
            break;
        }
        return nextToken;
    }
    /* addChar - a function to add nextChar to lexeme */
    void addChar(void)
    {
        if (lexLen <= 98)
        {
            lexeme[lexLen++] = nextChar;
            lexeme[lexLen] = '\0';
        }
        else
            printf("Error - lexeme is too long \n");
    }
    /* getChar - a function to get the next character of
     input and determine its character class */

    void getChar(void)
    {
        if ((nextChar = getc(in_fp)) != EOF)
        {
            if (isalpha(nextChar))
                charClass = LETTER;
            else if (nextChar == '_')
                charClass = UNDERSCORE;
            else if (isdigit(nextChar))
                charClass = DIGIT;
            else
                charClass = UNKNOWN;
        }
        else
            charClass = EOF;
    }
    /* getNonBlank - a function to call getChar until it
     returns a non-whitespace character */
    void getNonBlank(void)
    {
        while (isspace(nextChar))
            getChar();
    }
    /* lex - a simple lexical analyzer for arithmetic
     expressions */
    int lex(void)
    {
        lexLen = 0;
        getNonBlank();
        switch (charClass)
        {
            /* Identifiers */
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER || charClass == UNDERSCORE && (lexLen >= 6 || lexLen <= 8))
            {
                addChar();
                getChar();
            }
            if (!strcmp(lexeme, "pie"))
            {
                nextToken = WHILE;
            }
            else if (!strcmp(lexeme, "cake"))
            {
                nextToken = IF;
            }
            else if (!strcmp(lexeme, "cookies"))
            {
                nextToken = ELSE;
            }
            else if (!strcmp(lexeme, "begin"))
            {
                nextToken = BEGIN;
            }
            else if (!strcmp(lexeme, "end"))
            {
                nextToken = END;
            }
            else if (!strcmp(lexeme, "data"))
            {
                nextToken = VARIABLE;
            }
            else if (lexLen >= 6 && lexLen <= 8)
            {
                nextToken = IDENT;
            }
            else
            {
                nextToken = UNKNOWN;
            }
            break;
            /* Integer literals */
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT || charClass == LETTER || charClass == UNDERSCORE)
            {
                addChar();
                getChar();
            }
            if (lexeme[strlen(lexeme) - 1] == 'b')
                nextToken = BYTE;
            else if (lexeme[strlen(lexeme) - 1] == 's')
                nextToken = SHORT;
            else if (lexeme[strlen(lexeme) - 1] == 'i')
                nextToken = INT;
            else if (lexeme[strlen(lexeme) - 1] == 'l')
                nextToken = LONG;
            else if (charClass == UNKNOWN)
                nextToken = UNKNOWN;
            break;
            /* Parentheses and operators */
        case UNKNOWN:
            lookup(nextChar);
            getChar();
            break;
            /* EOF */
        case EOF:
            nextToken = EOF;
            lexeme[0] = 'E';
            lexeme[1] = 'O';
            lexeme[2] = 'F';
            lexeme[3] = '\0';
            break;
        } /* End of switch */
        if (nextToken == 99 || (nextToken == -1 && charClass != EOF))
        {
            printf("Error: Character entered is not in language \n");
        }
        else
        {
            printf("Next token is: %d, Next lexeme is %s\n",
                   nextToken, lexeme);
        }
        return nextToken;
    } /* End of function lex */
};
/* main driver */
int main(void)
{
    LexicalAnalyzer lexObj;
    /* Open the input data file and process its contents */
    if ((lexObj.in_fp = fopen("front.in", "r")) == NULL)
        printf("ERROR - cannot open front.in \n");
    else
    {
        lexObj.getChar();
        do
        {
            lexObj.lex();
        } while (lexObj.nextToken != EOF && lexObj.nextToken != 99);
    }
    return 0;
}
