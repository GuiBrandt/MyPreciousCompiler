#ifndef TOKENTYPE_HPP_INCLUDED
#define TOKENTYPE_HPP_INCLUDED

typedef enum
{
    IF,
    VAR,
    PROCEDURE,
    FUNCTION,
    BEGIN,
    WHILE,
    END,
    PROGRAM,

    SUM,
    SUBTRACT,
    DIVIDE,
    MULTIPLY,
    MOD,

    AND,
    OR,
    XOR,
    NOT,

    EQUAL,
    DIFFERENT,
    GREATER_THAN,
    SMALLER_THAN,
    GREATER_OR_EQUAL,
    SMALLER_OR_EQUAL,

    OPEN_PARENTESIS,
    CLOSE_PARENTESIS,

    OPEN_BRACKET,
    CLOSE_BRACKET,

    SETTER,

    WRITE,
    READ,

    TRUE,
    FALSE,

    NUMBER,
    NAME,
    UNKNOWN
} TokenType;

#endif
