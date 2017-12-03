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

        char hasSymbolAtLevel(const char*, unsigned char) const;

        void addVariable(const Variable&);

        void addProcedure(const Procedure&);

        void addFunction(const Function&);

        int _varSize = 100;

        int _procedureSize = 100;

        int _functionSize = 100;

        int _varCount = 0;

        int _procedureCount = 0;

        int _functionCount = 0;

        int _level = 0;

        void deleteProcedure(const char*);

        void deleteFunction(const char*);

        void deleteVariable(const char*);

        char hasProcedure(const char*);

        char hasFunction(const char*);

        char hasVariable(const char*);

        void compileParameters(const Procedure*);

        void increaseLevel();

        void decreaseLevel();

    public:
        /// Construtor
        Parser(const char*) throw (const char*);

        /// Obtém a linha atual sendo compilada
        int currentLine() const throw ();

        /// Obtém a coluna atual do arquivo sendo lida pelo analisador léxico
        int currentColumn() const throw ();

        /// Compila o cabeçalho do programa
        void compileProgram();

        /// Compila uma lista de variáveis
        void compileVariableDeclaration();

        /// Compila uma atribuição de variável
        void compileVariableAttribution();

        /// Compila um procedimento
        void compileProcedure();

        /// Compila uma função
        void compileFunction();

        /// Compila uma chamada de escrita
        void compileWrite();

        /// Compila uma chamada de leitura
        void compileRead();

        /// Compila um condicional
        void compileIf();

        /// Compila um repetidor `while'
        void compileWhile();

        /// Compila a declaração de parâmetros de um método
        int compileParameterDeclaration(Parameter**);

        /// Compila uma chamada de função/procedimento
        void compileMethodCall();
        ValueType compileFunctionCall();
        void compileProcedureCall();

        /// Compila um comando composto (começa em `begin', termina em `end')
        void compileCompositeCommand();

        /// Compila um comando simples
        void compileCommand();

        /// Compila uma expressão e retorna seu tipo
        ValueType compileExpression();
};

#endif // PARSER_HPP_INCLUDED
