#include "include/Lexer.hpp"
#include <ctype.h>
#include <cstring>
namespace AnalisadorLexicoMaligno
{

    char* Lexer::reserved[] = {
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
        while(reserved[i]!= NULL){
            if(strcmp(reserved[i],token)==0)
                return (TokenType)i;
            i++;
        }

        if(isdigit(token[0]))
            return NUMBER;

        return NAME;

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

                TokenType r= getTokenType(temp);
                if(r==NAME)
                    _name=temp;
                else
                    free(temp);

                return r;

            }
            else if (isdigit(chr))
            {
                temp = (char*)malloc(8);
                temp_used = 0;

                do
                {
                    temp[temp_used++] = chr;
                    chr = (char)fgetc(_file);
                }
                while (isnum(chr));

                _integer=(int)strtol(temp,NULL,10);
                free(temp);
                return NUMBER;
            }
            else
            {
                char* temp= (char*)malloc(sizeof(char)*2);
                temp_length = 2;
                temp_used = 0;

                do
                {
                    // Realoca o buffer caso necessário
                    if (temp_length <= temp_used)
                    {
                        char* a = (char*)malloc(temp_length * 2);
                        memcpy(a, temp, temp_length);
                        temp_length *= 2;

                        free(temp);
                        temp = a;
                    }
                    temp[temp_used++] = chr;
                    chr = fgetc(_file);
                }
                while (!isalnum(chr) && chr!= '\n' && chr!= ' ' && chr != '\t');

                TokenType t = getTokenType(temp);
                return t;
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
