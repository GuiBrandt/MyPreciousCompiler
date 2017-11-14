#include "include/Parser.hpp"
#include <cstdio>

Parser::Parser(Lexer l)
{
    this->_lexer = l;
}

void Parser::compileIf()
{
    TokenType prox = _lexer.nextToken();
    if (prox != IF)
        throw "If esperado";

    ValueType type = compileExpression();
    if(type != BOOLEAN)
        throw "Expressão booleana esperada";

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
    if(prox != WHILE)
        throw "While esperado";

    ValueType type = compileExpression();
    if(type != BOOLEAN)
        throw "Expressão booleana esperada";

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
        throw "Begin esperado";

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
    else if(prox == NAME)
    {
        prox = _lexer.nextToken();
        prox = _lexer.netxToken();

        if(prox == EQUAL)
            compileVariable();
        else if(prox == OPEN_PARENTESIS)
            {
                prox = getToken();
                if(prox != CLOSE_PARENTESIS)
                    compileParameter();
        }
        else
            throw "Esse comando não existe";
    }
}

void Parser::compileProgramBeginning()
{
    TokenType prox = _lexer.nextToken();
    if(prox != PROGRAM)

        throw "Program esperado";

    prox = _lexer.nextToken();
    if(prox != NAME)
        throw "Nome do programa esperado";

    prox = _lexer.nextToken();
    if(prox == VAR)
        compileVariable();

    compileCompositeCommand();
}

ValueType Parser::compileExpression()
{
}

void Parser::compileParameter()
{
    TokenType prox = _lexer.getToken();


    while(prox != CLOSE_PARENTESIS)
    {
        prox = _lexer.nextToken();
        if(prox != INTEGER && prox != BOOLEAN)
        throw "Tipo do parâmetro esperado";

        prox = _lexer.nextToken();

        if(prox != NAME)
            throw "Nome do parâmetro esperado";

        prox = _lexer.nextToken();

        if(prox != COMMA && prox != CLOSE_PARENTESIS)
            throw "Vírgula esperada";
    }

}

}
