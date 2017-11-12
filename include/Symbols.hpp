#ifndef SYMBOLS_HPP_INCLUDED
#define SYMBOLS_HPP_INCLUDED

typedef enum
{
    INTEGER,
    BOOLEAN
}
ValueType;

class Symbol
{
    public:
        Symbol(const char*, unsigned char);

        const char* getName() const;
        unsigned char getLevel() const;

    private:
        char _name[256];
        unsigned char _level;
};

class Variable : public Symbol
{
    public:
        typedef union
        {
            int i;
            char b;
        } Value;

        Variable(const char*, unsigned char, ValueType);
        Variable(const char*, unsigned char, ValueType, Value);

        ValueType getType() const;
        Value getValue() const;

    private:
        ValueType _type;
        Value _value;
};

class Parameter : public Symbol
{
    public:
        typedef union
        {
            int i;
            char b;
        } Value;

        Parameter(const char*, unsigned char, ValueType);

        ValueType getType() const;

    private:
        ValueType _type;
};

class Procedure : public Symbol
{
    public:
        Procedure(const char*, unsigned char, int, ...);

        int getParameterCount() const;
        const Parameter* getParameters() const;

    private:
        int _nParameters;
        Parameter* _parameters;
};

class Function : public Procedure
{
    public:
        template<typename... Values> Function(const char*, unsigned char, ValueType, int, Values...);

        ValueType getReturnType() const;

    private:
        ValueType _returnType;
};

#endif // SYMBOLS_HPP_INCLUDED
