#include "include/Lexer.hpp"
#include <ctype.h>

namespace AnalisadorLexicoMaligno
{

    char* Lexer::reserved[33] = {
        "if", "var", "procedure", "function", "begin", "while",
        "end", "program", "+", "-", "/", "*", "mod", "and", "or",
        "xor", "not", "=", "<>", ">", "<", ">=", "<=", "(", ")",
        "[", "]", ":=", "write", "read", "true", "false", NULL
    };

    Lexer::Lexer(char* filename)
    {
        _file = fopen(filename, "r");
    }

    TokenType Lexer::getTokenType(char* token)
    {
        int i = 0;
    }

    TokenType Lexer::nextToken()
    {
        char* temp;
        int temp_length, temp_used;

        char chr;

        do
        {
            chr = (char)fgetc(_file);

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
                        char* aux = (char*)malloc(temp_length * 2);
                        memcpy(aux, temp, temp_length);
                        temp_length *= 2;

                        free(temp);
                        temp = aux;
                    }

                    temp[temp_used++] = chr;
                    chr = (char)fgetc(_file);
                }
                while (isalnum(chr));


            }
            else if (isdigit(chr))
            {

            }
            else
            {

            }

        } while (chr != EOF)
    }

    char Lexer::hasMoreTokens()
    {

    }

    char* getName()
    {

    }

    int getValue()
    {

    }

    Lexer::~Lexer()
    {
        fclose(_file);
    }

};
