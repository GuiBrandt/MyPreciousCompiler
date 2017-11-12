#include "include/Lexer.hpp"
#include <ctype.h>
#include <cstring>
#include <cstdlib>

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
            while (isalnum(chr));

            temp[temp_used]='\0';
            TokenType r= getTokenType(temp);
            if(r==NAME)
                _name=temp;
            else
                free(temp);

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

            temp[temp_used]='\0';
            _integer=(int)strtol(temp,NULL,10);
            free(temp);
            return NUMBER;
        }
        else
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
                chr = fgetc(_file);
            }
            while (!isalnum(chr) && chr!= '\n' && chr!= ' ' && chr != '\t');

            temp[temp_used]='\0';
            TokenType t = getTokenType(temp);
            free(temp);
            return t;
        }
    }

    char Lexer::hasMoreTokens() const
    {
        char chr;
        do{
            chr = fgetc(_file);
            if(chr!='\n' && chr!='\n' && chr!= ' ')
                return true;
        }while(chr!=EOF);
        return false;
    }

    char* Lexer::getName() const
    {
        return _name;
    }

    int Lexer::getValue() const
    {
        return _integer;
    }

    Lexer::~Lexer()
    {
        fclose(_file);
    }

};
