#include "Lexer.hpp"
#include "Symbols.hpp"
#ifndef PARSER_HPP_INCLUDED
#define PARSER_HPP_INCLUDED

/**
 * Classe para o analisador sintático
 */
class Parser
{
    private:
        /// Analisador léxico
        Lexer _lexer;


        Variable* _var;

        Procedure* _procedure;

        Function* _function;

        Variable getVariable(const char*) const;

        Procedure getProcedure(const char*) const;

        Function getFunction(const char*) const;

        void addVariable(Variable);

        void addProcedure(Procedure);

        void addFunction(Function);

        int _varSize = 100;

        int _procedureSize = 100;

        int _functionSize = 100;

        int _varIndex = 0;

        int _procedureIndex = 0;

        int _functionIndex = 0;


    public:
        /// Construtor
        Parser(const char*);

        /// Compila o cabeçalho do programa
        void compileProgramBeginning();

        /// Compila uma lista de variáveis
        void compileVariable();

        /// Compila um procedimento
        void compileProcedure();

        /// Compila uma função
        void compileFunction();

        /// Compila um condicional
        void compileIf();

        /// Compila um repetidor `while'
        void compileWhile();

        /// Compila a declaração de parâmetros de um método
        void compileParameterDeclaration();

        /// Compila os parâmetros de uma chamada de função
        void compileParameters();

        /// Compila um comando composto (começa em `begin', termina em `end')
        void compileCompositeCommand();

        /// Compila um comando simples
        void compileCommand();

        /// Compila uma expressão e retorna seu tipo
        ValueType compileExpression();

        void deleteProcedure(const char*);

        void deleteFunction(const char*);

        void deleteVariable(const char*);
};

#endif // PARSER_HPP_INCLUDED
