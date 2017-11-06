#ifndef LEXER_HPP_INCLUDED
#define LEXER_HPP_INCLUDED

#include <cstdio>
#include "TokenType.hpp"

namespace AnalisadorLexicoMaligno
{
    class Lexer
    {
        private:

            static char* reserved[];

            FILE* _file;

            char* _name;
            int _integer;

            TokenType getTokenType(char*);

        public:

            Lexer(char*);
            ~Lexer();

            TokenType nextToken();
            char hasMoreTokens() const;

            char* getName() const;
            int getValue() const;
    };
};

#endif
