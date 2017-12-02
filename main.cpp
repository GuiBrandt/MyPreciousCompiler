#include "include/Lexer.hpp"

int main(int argc, char** argv)
{
    Lexer l("teste.txt");

    printf("Code  Integer      Name\r\n\r\n");

    while (l.hasMoreTokens())
    {
        TokenType tt = l.nextToken();
        printf("0x%02x  0x%09x  %s\r\n", tt, l.getValue(), l.getName() != NULL ? l.getName() : "NULL");
    }

    return 0;
}
