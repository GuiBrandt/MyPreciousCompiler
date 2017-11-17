#include "include/Parser.hpp"
#include "include/Lexer.hpp"

#include <cstdlib>
#include <cstring>
#include <cstdio>

/**
 * Construtor
 *
 * \param filename Nome do arquivo para se analisar
 */
Parser::Parser(const char* filename) : _lexer(filename)
{
    _var = (Variable*)malloc(sizeof(Variable)*_varSize);
    _procedure = (Procedure*)malloc(sizeof(Procedure)*_procedureSize);
    _function = (Function*)malloc(sizeof(Function)* _functionSize);
}

Variable Parser::getVariable(const char* name) const
{
    int i;
    for (i = 0; i < _varIndex; i++)
    {
        if (strcmp(_var[i].getName(), name) == 0)
            return _var[i];
    }

    throw "Variável não encontrada";
}

Procedure Parser::getProcedure(const char* name) const
{
    int i;
    for (i = 0; i < _procedureIndex; i++)
    {
        if (strcmp(_procedure[i].getName(), name) == 0)
            return _procedure[i];
    }

    throw "Procedimento não encontrado";
}

Function Parser::getFunction(const char* name) const
{
    int i;
    for (i = 0; i < _functionIndex; i++)
    {
        if (strcmp(_function[i].getName(), name) == 0)
            return _function[i];
    }

    throw "Função não encontrada";
}

void Parser::addVariable(Variable v)
{
    if (_varIndex >= _varSize)
    {
        Variable* aux = (Variable*)malloc(sizeof(Variable) * _varSize * 2);
        memcpy(aux, _var, sizeof(Variable) * _varSize);
        free(_var);
        _var = aux;
        _varSize *= 2;
    }

    _var[_varIndex++] = v;
}

void Parser::addProcedure(Procedure p)
{
    if (_procedureIndex >= _procedureSize)
    {
        Procedure* aux = (Procedure*)malloc(sizeof(Procedure) * _procedureSize * 2);
        memcpy(aux, _procedure, sizeof(Procedure) * _procedureSize);
        free(_procedure);
        _procedure = aux;
        _procedureSize *= 2;
    }

    _procedure[_procedureIndex++] = p;
}

void Parser::addFunction(Function f)
{
    if (_functionIndex >= _functionSize)
    {
        Function* aux = (Function*)malloc(sizeof(Function) * _functionSize * 2);
        memcpy(aux, _function, sizeof(Function) * _functionSize);
        free(_function);
        _function = aux;
        _functionSize *= 2;
    }

    _function[_functionIndex++] = f;
}

void Parser::deleteFunction(const char* name)
{
    int i;
    for (i = 0; i < _functionIndex; i++)
    {
        if (strcmp(_function[i].getName(), name) == 0)
        {
            int j;
            for(j=i; j<_functionIndex; j++)
                _function[j] = _function[j+1];
            _functionIndex--;
            break;
        }
    }
    throw "Função não encontrada";
}

void Parser::deleteProcedure(const char* name)
{
    int i;
    for (i = 0; i < _procedureIndex; i++)
    {
        if (strcmp(_procedure[i].getName(), name) == 0)
        {
            int j;
            for(j=i; j<_procedureIndex; j++)
                _procedure[j] = _procedure[j+1];
            _procedureIndex--;
            break;
        }
    }
    throw "Procedimento não encontrado";
}

void Parser::deleteVariable(const char* name)
{
    int i;
    for (i = 0; i < _varIndex; i++)
    {
        if (strcmp(_var[i].getName(), name) == 0)
        {
            int j;
            for(j=i; j<_varIndex; j++)
                _var[j] = _var[j+1];
            _varIndex--;
            break;
        }
    }
    throw "Procedimento não encontrado";
}

/**
 * Compila um condicional
 */
void Parser::compileIf()
{
    TokenType prox = _lexer.getToken();
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
    TokenType prox = _lexer.getToken();
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

    while ((prox = _lexer.nextToken()) != END)
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
                    compileParameters();
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
int Parser::compileParameterDeclaration(Parameter** params)
{
    TokenType prox = _lexer.nextToken();
    if (prox != OPEN_PARENTESIS)
        throw "Abre parênteses esperado";

    int n = 0;

    int sz = 8;
    *params = (Parameter*)malloc(sz * sizeof(Parameter));

    while(prox != CLOSE_PARENTESIS)
    {
        prox = _lexer.nextToken();
        if (prox != INTEGER && prox != BOOLEAN)
            throw "Tipo do parâmetro esperado";

        if (n >= sz)
        {
            Parameter* aux = (Parameter*)malloc(sizeof(Parameter) * sz * 2);
            memcpy(aux, *params, sz);
            sz *= 2;

            free(*params);
            *params = aux;
        }

        (*params)[n].setType(prox == INTEGER ? tINTEGER : tBOOLEAN);

        prox = _lexer.nextToken();

        if (prox != NAME)
            throw "Nome do parâmetro esperado";

        (*params)[n].setName(_lexer.getName());

        prox = _lexer.nextToken();

        if(prox != COMMA && prox != CLOSE_PARENTESIS)
            throw "Vírgula esperada";

        n++;
    }

    return n;
}

void Parser::compileProcedure()
{
    TokenType prox = _lexer.getToken();

    if (prox != PROCEDURE)
        throw "Declaração de procedimento esperada";

    prox = _lexer.nextToken();
    if (prox != NAME)
        throw "Nome da função esperado";

    const char* name = _lexer.getName();

    Parameter* parameters;
    int n = compileParameterDeclaration(&parameters);

    compileCompositeCommand();

    Procedure p(name, 0, n, parameters);
}
