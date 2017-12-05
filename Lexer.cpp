#include "include/Lexer.hpp"
#include <ctype.h>
#include <cstring>
#include <cstdlib>

// PARA TESTES
#include <cstdio>

/// Vetor de palavras reservadas
char* Lexer::reserved[] = {
    "if", "then", "else", "var", "procedure", "function", "begin", "while",
    "do", "end", "program", "integer", "boolean", "+", "-", "/", "*", "mod",
    "and", "or", "xor", "not", "==", "<>", ">", "<", ">=", "<=", "(", ")", "=",
    "write", "read", "true", "false", ",", ";", ":", NULL
};

/**
 * Construtor
 *
 * \param filename Nome do arquivo a ser lido
 */
Lexer::Lexer(const char* filename) throw (const char*)
{
    _file = fopen(filename, "r");
    if (_file == NULL)
        throw "Arquivo inexistente.";

    _integer = 0;
    _name = NULL;
    _line = _lineAux = 1;
    _column = _columnAux = 1;
}

/**
 * Obtém a linha do arquivo sendo lida pelo analisador léxico
 */
int Lexer::currentLine() const throw ()
{
    return _line;
}

/**
 * Obtém a coluna do arquivo sendo lida pelo analisador léxico
 */
int Lexer::currentColumn() const throw ()
{
    return _column;
}

/**
 * Determina o tipo de uma palavra
 *
 * \param token Palavra a ser analisada
 * \return O TokenType da palavra
 */
TokenType Lexer::getTokenType(const char*& token) const throw ()
{
    if (isdigit(token[0]))
        return NUMBER;

    int i;
    for (i = 0; reserved[i] != NULL; i++)
        if(strcmp(reserved[i], token) == 0)
            return (TokenType)i;

    if (isalpha(token[0]))
        return NAME;

    return UNKNOWN;
}

/**
 * Lê um caractere do arquivo e avança uma coluna
 */
char Lexer::readChar()
{
    char c = (char)fgetc(_file);

    _columnAux++;

    return (char)c;
}

/**
 * Avança uma palavra no arquivo
 *
 * \return O tipo da palavra lida
 */
TokenType Lexer::nextToken() throw (const char*)
{
    _line = _lineAux;
    _column = _columnAux;

    _integer = 0;
    _name = NULL;

	if (!hasMoreTokens())
		return END_OF_FILE;

    char* temp;
    int temp_length, temp_used;

    char chr = readChar();

    if (isalpha(chr))
    {
        temp = (char*)malloc(32);
        temp_length = 32;
        temp_used = 0;

        do
        {
            // Realoca o buffer caso necessário
            if (temp_length <= temp_used)
            {
                char* aux = (char*)malloc(temp_length * 2 + 1);
                memcpy(aux, temp, temp_length);
                temp_length *= 2;

                free(temp);
                temp = aux;
            }

            temp[temp_used++] = chr;
            chr = readChar();
        }
        while (isalnum(chr) && chr != EOF);

        ungetc(chr, _file);
        _columnAux--;

        temp[temp_used] = '\0';
        TokenType r = getTokenType((const char*&)temp);

        if (r == NAME)
            _name = temp;
        else
            free(temp);

        _lastToken = r;
        return r;

    }
    else if (isdigit(chr))
    {
        char* temp= (char*)malloc(sizeof(char)*2 + 1);
        temp_length = 2;
        temp_used = 0;

        do
        {
            // Realoca o buffer caso necessário
            if (temp_length <= temp_used)
            {
                char* a = (char*)malloc(temp_length * 2 + 1);
                memcpy(a, temp, temp_length);
                temp_length *= 2;

                free(temp);
                temp = a;
            }
            temp[temp_used++] = chr;
            chr = readChar();
        }
        while (isdigit(chr));

        ungetc(chr, _file);
        _columnAux--;

        temp[temp_used] = '\0';

        _integer = (int)strtol(temp, NULL, 10);

        free(temp);

        _lastToken = NUMBER;
        return NUMBER;
    }
    else
    {
        char* temp = (char*)malloc(sizeof(char) * 2 + 1);
        temp_length = 2;
        temp_used = 0;

        do
        {
            // Realoca o buffer caso necessário
            if (temp_length <= temp_used)
            {
                char* a = (char*)malloc(temp_length * 2 + 1);
                memcpy(a, temp, temp_length);
                temp_length *= 2;

                free(temp);
                temp = a;
            }

            temp[temp_used++] = chr;

            chr = fgetc(_file);

            if (chr == ')' || chr == ';' || chr == ',')
                break;
        }
        while (!isalnum(chr) && !isspace(chr) && chr != EOF);

        ungetc(chr, _file);
        _columnAux--;

        temp[temp_used] = '\0';
        TokenType t = getTokenType((const char*&)temp);

        free(temp);

        _lastToken = t;
        return t;
    }
}

/**
 * Obtém o tipo da última palavra lida sem consumí-la
 *
 * \return O tipo da última palavra lida do arquivo
 */
TokenType Lexer::getToken() throw ()
{
	if (_lastToken == -1)
		return nextToken();

	return _lastToken;
}

/**
 * Verifica se existem mais palavras no arquivo
 *
 * \return True se houverem mais palavras e False se não
 */
char Lexer::hasMoreTokens() throw ()
{
    char chr;
    do
    {
        chr = readChar();
        if (chr != EOF && !isspace(chr))
        {
        	ungetc(chr, _file);
        	_columnAux--;

            return true;
        }
        else
        {
            if (chr == '\n')
            {
                _lineAux++;
                _columnAux = 1;
            }
        }
    }
    while (chr != EOF);

    return false;
}

/**
 * Obtém o último nome lido
 *
 * \return O último nome lido do arquivo
 */
char* Lexer::getName() const throw ()
{
    return _name;
}

/**
 * Obtém o último inteiro lido
 *
 * \return O último inteiro lido do arquivo
 */
int Lexer::getValue() const throw ()
{
    return _integer;
}

/**
 * Destrutor
 */
Lexer::~Lexer()
{
    fclose(_file);
}
