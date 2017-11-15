#include "include/Parser.hpp"
#include "include/Lexer.hpp"

#include <cstdio>

/**
 * Construtor
 *
 * \param filename Nome do arquivo para se analisar
 */
Parser::Parser(const char* filename) : _lexer(filename) {}

/**
 * Compila um condicional
 */
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
    if (prox == ELSE)
    {
        prox = _lexer.nextToken();

        if (prox == BEGIN)
            compileCompositeCommand();
        else
            compileCommand();
    }
}

/**
 * Compila um repetidor `while'
 */
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

/**
 * Compila um comando composto (começa em `begin', termina em `end')
 */
void Parser::compileCompositeCommand()
{
    TokenType prox = _lexer.nextToken();
    if(prox != BEGIN)
        throw "Begin esperado";

    while ((prox = _lexer.getToken()) != END)
        compileCommand();
}

/**
 * Compila um comando simples
 */
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
        prox = _lexer.nextToken();

        if(prox == EQUAL)
            compileVariable();
        else if(prox == OPEN_PARENTESIS)
            {
                prox = _lexer.getToken();
                if(prox != CLOSE_PARENTESIS)
                    compileParameter();
        }
        else
            throw "Esse comando não existe";
    }
}

/**
 * Compila o cabeçalho do programa
 */
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

/**
 * Compila uma expressão
 *
 * \return O tipo da expressão compilada
 */
ValueType Parser::compileExpression()
{
}

/**
 * Compila uma lista de parâmetros
 */
void Parser::compileParameter()
{
    TokenType prox = _lexer.getToken();

    while(prox != CLOSE_PARENTESIS)
    {
        prox = _lexer.nextToken();
        if (prox != INTEGER && prox != BOOLEAN)
        throw "Tipo do parâmetro esperado";

        prox = _lexer.nextToken();

        if(prox != NAME)
            throw "Nome do parâmetro esperado";

        prox = _lexer.nextToken();

        if(prox != COMMA && prox != CLOSE_PARENTESIS)
            throw "Vírgula esperada";
    }

}
