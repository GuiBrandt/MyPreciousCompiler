#include "include/Lexer.hpp"
#include <ctype.h>
#include <cstring>
#include <cstdlib>

// PARA TESTES
#include <cstdio>

/// Vetor de palavras reservadas
char* Lexer::reserved[] = {
    "if",  "else",    "var",     "procedure", "function", "begin", "while",
    "end", "program", "integer", "boolean",   "+",        "-",     "/",
    "*",   "%",       "&&",      "||",        "^",        "!",     "==",
    "<>",  ">",       "<",       ">=",        "<=",       "(",     ")",
    "=",   "write",   "read",    "true",      "false",    ",",     ";",
    ":",   NULL
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
 * Avança uma palavra no arquivo
 *
 * \return O tipo da palavra lida
 */
TokenType Lexer::nextToken() throw (const char*)
{
    _integer = 0;
    _name = NULL;

	if (!hasMoreTokens())
		throw "EOF";

    char* temp;
    int temp_length, temp_used;

    char chr = (char)fgetc(_file);

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
            chr = (char)fgetc(_file);
        }
        while (isalnum(chr) && chr != EOF);

        ungetc(chr, _file);

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
            chr = (char)fgetc(_file);
        }
        while (isdigit(chr));
        ungetc(chr, _file);

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
        }
        while (!isalnum(chr) && !isspace(chr) && chr != EOF);

        ungetc(chr, _file);

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
        chr = fgetc(_file);
        if (chr != EOF && !isspace(chr))
        {
        	ungetc(chr, _file);
            return true;
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
