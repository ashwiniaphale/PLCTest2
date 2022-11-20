#include "lexicalanalyze.cpp"

class Syntax
{

    void program(void)
    {
        if (nextToken == BEGIN)
        {
            lex();
        }
        stmt_list();
        if (nextToken == END)
        {
            lex();
        }
    }

    void stmt(void)
    {
        if (nextToken == VARIABLE)
        {
            lex();
        }
        else if (nextToken == WHILE)
        {
            lex();
            while_loop();
        }
        else if (nextToken == IF)
        {
            lex();
            if_stmt();
        }
        else if (nextToken == ASSIGN_OP)
        {
            lex();
        }
        else
        {
            error();
        }
    }

    void declare(void)
    {
        if (nextToken == DATA)
        {
            lex();
            if (nextToken == IDENT)
            {
                lex();
            }
        }
    }

    void assign(void)
    {
        if (nextToken == IDENT)
        {
            lex();
            if (nextToken == ASSIGN_OP)
            {
                lex();
                expr();
            }
        }
    }

    void while_loop()
    {
        if (nextToken == WHILE)
        {
            lex();
            if (nextToken == LEFT_PAREN)
            {
                lex();
                bool_expr();
                if (nextToken == RIGHT_PAREN)
                {
                    lex();
                    stmt();
                }
            }
        }
    }

    void if_stmt()
    {
        if (nextToken == IF)
        {
            lex();
            if (nextToken == LEFT_PAREN)
            {
                lex();
                bool_expr();
                if (nextToken == RIGHT_PAREN)
                {
                    lex();
                    stmt();
                }
                else
                {
                    error();
                }
            }
            else
            {
                error();
            }
        }
    }

    void expr(void)
    {
        term();
        while (nextToken == ADD_OP || nextToken == MULT_OP)
        {
            lex();
            term();
        }
    }

    void term(void)
    {
        factor();
        while (nextToken == SUB_OP || nextToken == DIV_OP || nextToken == MODUL)
        {
            lex();
            factor();
        }
    }

    void factor(void)
    {
        if (nextToken == IDENT)
        {
            lex();
        }
        else if (nextToken == INT_LIT)
        {
            lex();
        }
        else if (nextToken == LEFT_PAREN)
        {
            lex();
            expr();
            if (nextToken == RIGHT_PAREN)
            {
                lex();
            }
        }
    }

    void bool_expr(void)
    {
        brel();
        if (nextToken == NOT_EQUAL || nextToken == EQUAL_TO)
        {
            lex();
            brel();
        }
    }

    void brel(void)
    {
        bexpr();
        if (nextToken == LESS_THAN || nextToken == GREATER_THAN ||
            nextToken == LESS_EQUAL || nextToken == GREATER_EQUAL)
        {
            lex();
            bexpr();
        }
    }

    void bexpr(void)
    {
        bterm();
        if (nextToken == ADD_OP || nextToken == MULT_OP)
        {
            lex();
            bterm();
        }
    }

    void bterm(void)
    {
        bfactor();
        while (nextToken == SUB_OP || nextToken == DIV_OP || nextToken == MODUL)
        {
            lex();
            bfactor();
        }
    }

    void bfactor(void)
    {
        if (nextToken == IDENT)
        {
            lex();
        }
        else if (nextToken == INT_LIT)
        {
            lex();
        }
        else if (nextToken == BOOL)
        {
            lex();
        }
    }
    else if (nextToken == LEFT_PAREN)
    {
        lex();
        expr();
        if (nextToken == RIGHT_PAREN)
        {
            lex();
        }
    }
};

int main()
{
    Syntax synObj;
}