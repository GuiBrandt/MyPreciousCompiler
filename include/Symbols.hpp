#ifndef SYMBOLS_HPP_INCLUDED
#define SYMBOLS_HPP_INCLUDED

/**
 * Enumerador de tipos de valor de variável, parâmetro e função
 */
typedef enum
{
    tINTEGER,
    tBOOLEAN
}
ValueType;

/**
 * Classe base para os símbolos (variáveis, funções, procedimentos e parâmetros)
 */
class Symbol
{
    public:

        /// Construtor
        Symbol(const char*, unsigned char);

        /// Obtém o nome do símbolo
        const char* getName() const;

        /// Obtém o nível do símbolo
        unsigned char getLevel() const;

    private:

        /// Nome do símbolo
        char _name[256];

        /// Nível do símbolo
        unsigned char _level;
};

/**
 * Classe para as Variáveis
 */
class Variable : public Symbol
{
    public:

        /// Union de valor
        typedef union
        {
            int i;
            char b;
        } Value;

        /// Construtor
        Variable(const char*, unsigned char, ValueType);

        /// Construtor
        Variable(const char*, unsigned char, ValueType, Value);

        /// Obtém o tipo da variável
        ValueType getType() const;

        /// Obtém o valor da variável
        Value getValue() const;

    private:

        /// Tipo da variável
        ValueType _type;

        /// Valor da variável
        Value _value;
};

/**
 * Classe para os parâmetros de procedimentos e funções
 */
class Parameter : public Symbol
{
    public:

        /// Construtor
        Parameter(const char*, unsigned char, ValueType);

        /// Obtém o tipo do parâmetro
        ValueType getType() const;

    private:

        /// Tipo do parâmetro
        ValueType _type;
};

/**
 * Classe para os procedimentos
 */
class Procedure : public Symbol
{
    public:

        /// Construtor
        Procedure(const char*, unsigned char, int, ...);

        /// Obtém o número de parâmetros do procedimento
        int getParameterCount() const;

        /// Obtém a lista de parâmetros do procedimento
        const Parameter* getParameters() const;

    private:

        /// Número de parâmetros do procedimento
        int _nParameters;

        /// Lista de parâmetros do procedimento
        Parameter* _parameters;
};

/**
 * Classe para as funções
 */
class Function : public Procedure
{
    public:

        /// Construtor
        template<typename... Values> Function(const char*, unsigned char, ValueType, int, Values...);

        /// Obtém o tipo de retorno da função
        ValueType getReturnType() const;

    private:

        /// Tipo de retorno da função
        ValueType _returnType;
};

#endif // SYMBOLS_HPP_INCLUDED
