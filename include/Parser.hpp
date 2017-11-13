#include "Lexer.hpp"
#include "Symbols.hpp"
#ifndef PARSER_HPP_INCLUDED
#define PARSER_HPP_INCLUDED

class Parser
{
    private:
        Lexer _lexer;
    public:
        Parser(Lexer);
        void compileProgramBeginning();
        void compileVariable();
        void compileProcedure();
        void compileFunction();
        void compileIf();
        void compileWhile();
        void compileCompositeCommand();
        void compileCommand();
        ValueType compileExpression();
};

#endif // PARSER_HPP_INCLUDED
