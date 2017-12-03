#include "include/Lexer.hpp"
#include "include/PARSER.HPP"
#include <cstdlib>

/**
 * Teste do lexer
 */
void lexerTest(const char* filename)
{
    try {
        Lexer l(filename);

        printf("Code  Integer      Name\r\n\r\n");

        while (l.hasMoreTokens())
        {
            TokenType tt = l.nextToken();
            printf("0x%02x  0x%09x  %s\r\n", tt, l.getValue(), l.getName() != NULL ? l.getName() : "NULL");
        }
    } catch (const char* e) {
        fprintf(stderr, "Erro: %s", e);
    }
}

/**
 * Ponto de entrada
 */
int main(int argc, char** argv)
{
    //lexerTest("teste.txt");
    Parser p("teste.txt");

    try {
        p.compileProgram();

        printf("Programa compilado com sucesso!");
    } catch (const char* e) {
        fprintf(stderr, "Linha %d, Coluna %d: %s", p.currentLine(), p.currentColumn(), e);
    }

    return 0;
}
