#ifndef LEXER_HPP_INCLUDED
#define LEXER_HPP_INCLUDED

#include <cstdio>
#include "TokenType.hpp"

/**
 * Classe para o analisador léxico do compilador
 */
class Lexer
{
    public:

        /// Construtor
        Lexer(const char*) throw (const char*);

        /// Destrutor
        ~Lexer();

        /// Avança uma palavra no arquivo
        TokenType nextToken() throw (const char*);

        /// Obtém a última palavra lida do arquivo
        TokenType getToken() throw ();

        /// Verifica se o arquivo ainda contém alguma palavra
        char hasMoreTokens() throw ();

        /// Obtém o último nome lido
        char* getName() const throw ();

        /// Obtém o último inteiro lido
        int getValue() const throw ();

    private:

        /// Vetor de palavras reservadas (que o compilador reconhece)
        static char* reserved[];

        /// Arquivo sendo lido
        FILE* _file;

        /// Último nome lido
        char* _name;

        /// Último inteiro lido
        int _integer;

        /// Última palavra lida
        TokenType _lastToken = (TokenType)-1;

        /// Determina o tipo de uma palavra lida
        TokenType getTokenType(const char*&) const throw ();
};

#endif
