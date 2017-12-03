#include "include/Lexer.hpp"
#include "include/Parser.hpp"

#include <ctype.h>
#include <cstdlib>
#include <cstring>

#define ANSI_COLOR_RED     "\x1b[1;31m"
#define ANSI_COLOR_GREEN   "\x1b[1;32m"
#define ANSI_COLOR_YELLOW  "\x1b[1;33m"
#define ANSI_COLOR_BLUE    "\x1b[1;34m"
#define ANSI_COLOR_MAGENTA "\x1b[1;35m"
#define ANSI_COLOR_TEAL    "\x1b[0;36m"
#define ANSI_COLOR_CYAN    "\x1b[1;36m"
#define ANSI_COLOR_GRAY    "\x1b[1;30m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/**
 * Análise léxica
 */
void lexicalAnalysis(const char* filename)
{
    try {
        Lexer l(filename);

        printf(ANSI_COLOR_YELLOW "\r\nCode  Integer      Name" ANSI_COLOR_RESET "\r\n\r\n");

        while (l.hasMoreTokens())
        {
            TokenType tt = l.nextToken();
            printf(
                ANSI_COLOR_GREEN "0x%02x  %s0x%08x  " ANSI_COLOR_RESET "%s" ANSI_COLOR_RESET "\r\n",

                tt, l.getValue() == 0 ? ANSI_COLOR_TEAL : ANSI_COLOR_CYAN, l.getValue(), l.getName() != NULL ? l.getName() : ANSI_COLOR_GRAY "<NULL>");
        }
    } catch (const char* e) {
        fprintf(stderr, ANSI_COLOR_RED "Erro: %s" ANSI_COLOR_RESET, e);
    }

    printf("\r\n");
}

/**
 * Ponto de entrada
 */
int main(int argc, char** argv)
{
    char* filename;

    if (argc < 2 || argc > 3)
    {
        printf("Sintaxe: " ANSI_COLOR_YELLOW "lotr" ANSI_COLOR_TEAL " [-l|--lex] " ANSI_COLOR_GRAY " <nome do arquivo>");
        printf(ANSI_COLOR_RESET "\r\n\r\n");
        printf("Se especificada a flag -l ou --lex, o compilador mostra também");
        printf(" a análise léxica feita do código.");

        return 0;
    } else if (argc == 2) {

        if (strcmp(argv[1], "-l") == 0 || strcmp(argv[1], "--lex") == 0)
        {
            fprintf(stderr, ANSI_COLOR_RED "Arquivo não foi especificado." ANSI_COLOR_RESET);
            return -1;
        } else
            filename = argv[1];
    } else {
        if (strcmp(argv[1], "-l") != 0 && strcmp(argv[1], "--lex") != 0)
        {
            fprintf(stderr, ANSI_COLOR_RED "Opção desconhecida `%s'" ANSI_COLOR_RESET, argv[1]);
            return -1;
        }

        filename = argv[2];
        lexicalAnalysis(filename);
    }

    try {
        Parser p(filename);

        try {

            p.compileProgram();

            printf(ANSI_COLOR_YELLOW "Programa compilado com sucesso!" ANSI_COLOR_RESET "\r\n");

        } catch (const char* e) {
            fprintf(stderr, ANSI_COLOR_RED "Linha %d, Coluna %d: %s" ANSI_COLOR_RESET "\r\n\r\n", p.currentLine(), p.currentColumn(), e);

            FILE* file = fopen(filename, "r");

            int line = 1;
            while (line < p.currentLine())
                if (fgetc(file) == '\n') line++;

            char chr;
            while ((chr = fgetc(file)) != '\n')
                fprintf(stderr, "%c", chr == '\t' ? ' ' : chr);

            fprintf(stderr, "\r\n");

            int i;
            for (i = 0; i < p.currentColumn(); i++)
                fprintf(stderr, " ");

            fprintf(stderr, ANSI_COLOR_RED "^" ANSI_COLOR_RESET "\r\n");

            return -2;
        }

    } catch (const char* e) {
        fprintf(stderr, e);

        return -3;
    }

    return 0;
}
