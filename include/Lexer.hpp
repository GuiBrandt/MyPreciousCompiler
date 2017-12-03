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

        /// Lê um caractere do arquivo
        char readChar();

        /// Obtém a última palavra lida do arquivo
        TokenType getToken() throw ();

        /// Verifica se o arquivo ainda contém alguma palavra
        char hasMoreTokens() throw ();

        /// Obtém o último nome lido
        char* getName() const throw ();

        /// Obtém o último inteiro lido
        int getValue() const throw ();

        /// Obtém a linha atual do arquivo sendo lida pelo analisador léxico
        int currentLine() const throw ();

        /// Obtém a coluna atual do arquivo sendo lida pelo analisador léxico
        int currentColumn() const throw ();

    private:

        /// Vetor de palavras reservadas (que o compilador reconhece)
        static char* reserved[];

        /// Arquivo sendo lido
        FILE* _file;

        /// Último nome lido
        char* _name;

        /// Último inteiro lido
        int _integer;

        /// Linha atual do lexer
        int _line;

        /// Coluna atual do lexer
        int _column;

        /// Última palavra lida
        TokenType _lastToken = (TokenType)-1;

        /// Determina o tipo de uma palavra lida
        TokenType getTokenType(const char*&) const throw ();
};

#endif
