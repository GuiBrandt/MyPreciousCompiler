#ifndef TOKENTYPE_HPP_INCLUDED
#define TOKENTYPE_HPP_INCLUDED

/**
 * Enumerador de tipos de palavra do analisador léxico
 */
typedef enum
{
    IF,
    THEN,
    ELSE,
    VAR,
    PROCEDURE,
    FUNCTION,
    BEGIN,
    WHILE,
    DO,
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
    AND_S,
    OR,
    OR_S,
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

    SETTER,

    WRITE,
    READ,

    TRUE,
    FALSE,

    COMMA,
    SEMICOLON,
    COLON,
    DOT,

    NUMBER,
    NAME,
    END_OF_FILE,
    UNKNOWN
} TokenType;

#endif
