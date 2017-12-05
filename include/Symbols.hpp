#ifndef SYMBOLS_HPP_INCLUDED
#define SYMBOLS_HPP_INCLUDED

/**
 * Enumerador de tipos de valor de variável, parâmetro e função
 */
typedef enum
{
    tINTEGER,
    tBOOLEAN,
    tVOID
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

        /// Define o nome do símbolo
        void setName(const char*);

        /// Obtém o nível do símbolo
        unsigned char getLevel() const;

        /// Define o nível do símbolo
        void setLevel(unsigned char);

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
        /// Construtor
        Variable(const char*, unsigned char, ValueType);

        /// Obtém o tipo da variável
        ValueType getType() const;

    private:

        /// Tipo da variável
        ValueType _type;
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

        /// Define o tipo do símbolo
        void setType(ValueType);

    private:

        /// Tipo do parâmetro
        ValueType _type;
};

/**
 * Classe para as funções
 */
class Function : public Symbol
{
    public:

        /// Construtor
        Function(const char*, unsigned char, ValueType, int, Parameter*);

        /// Obtém o tipo de retorno da função
        ValueType getReturnType() const;

        /// Obtém o número de parâmetros da função
        int getParameterCount() const;

        /// Obtém os parâmetros da função
        const Parameter* getParameters() const;

    private:

        /// Tipo de retorno da função
        ValueType _returnType;

        /// Número de parâmetros da função
        int _nParameters;

        /// Vetor de parâmetros da função
        Parameter* _parameters;
};

#endif // SYMBOLS_HPP_INCLUDED
