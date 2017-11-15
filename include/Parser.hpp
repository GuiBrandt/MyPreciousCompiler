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

        /// Compila parâmetros de um método
        void compileParameter();

        /// Compila um comando composto (começa em `begin', termina em `end')
        void compileCompositeCommand();

        /// Compila um comando simples
        void compileCommand();

        /// Compila uma expressão e retorna seu tipo
        ValueType compileExpression();
};

#endif // PARSER_HPP_INCLUDED
