#ifndef TOKENTYPE_HPP_INCLUDED
#define TOKENTYPE_HPP_INCLUDED

/**
 * Enumerador de tipos de palavra do analisador léxico
 */
typedef enum
{
    IF,
    ELSE,
    VAR,
    PROCEDURE,
    FUNCTION,
    BEGIN,
    WHILE,
    END,
    PROGRAM,

    INTEGER,
    BOOLEAN,

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

    COMMA,
    SEMICOLON,
    COLON,

    NUMBER,
    NAME,
    UNKNOWN
} TokenType;

#endif
