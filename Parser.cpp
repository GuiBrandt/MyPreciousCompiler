#include "include/Parser.hpp"
#include <cstdio>

Parser::Parser(Lexer l)
{
    this->_lexer = l;
}

void Parser::compileIf()
{
    TokenType prox = _lexer.nextToken();
    if(prox!=IF)
    {
        fprintf(sdterr,"If esperado");
        return;
    }

    ValueType type = compileExpression();
    if(type != BOOLEAN)
    {
        fprintf(sdterr,"Expressão booleana esperada");
        return;
    }

    prox = _lexer.getToken();

    if(prox == BEGIN)
        compileCompositeCommand();
    else
        compileCommand();

    prox = _lexer.getToken();

    if(prox == ELSE)
    {
        prox = _lexer.nextToken();

        if(prox == BEGIN)
            compileCompositeCommand();
        else
            compileCommand();
    }
}


void Parser::compileWhile()
{
    TokenType prox = _lexer.nextToken();
    if(prox!=WHILE)
    {
        fprintf(sdterr,"While esperado");
        return;
    }

    ValueType type = compileExpression();
    if(type != BOOLEAN)
    {
        fprintf(sdterr,"Expressão booleana esperada");
        return;
    }

    prox = _lexer.getToken();

    if(prox == BEGIN)
        compileCompositeCommand();
    else
        compileCommand();

}

void Parser::compileCompositeCommand()
{
    TokenType prox = _lexer.nextToken();

    if(prox != BEGIN)
    {
        fprintf(sdterr,"Begin esperado");
        return;
    }


    while ((prox = _lexer.getToken()) != END)
        compileCommand();

}

void Parser::compileCommand()
{
    TokenType prox = _lexer.getToken();

    if(prox == IF)
        compileIf();
    else if(prox == WHILE)
        compileWhile();
    else if(prox == FUNCTION)
        compileFunction();
    else if(prox == PROCEDURE)
        compileProcedure();
    //else if(prox == NAME)
}
