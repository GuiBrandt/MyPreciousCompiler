#include "include/Symbols.hpp"

#include <cstring>
#include <cstdarg>
#include <cstdlib>

Symbol::Symbol(const char* name, unsigned char level)
{
    strcpy(this->_name, name);
    this->_level = level;
}

const char* Symbol::getName() const
{
    return this->_name;
}

unsigned char Symbol::getLevel() const
{
    return this->_level;
}


Variable::Variable(const char* name, unsigned char level, ValueType type)
: Symbol(name, level)
{
    this->_type = type;
}

Variable::Variable(const char* name, unsigned char level, ValueType type, Value value)
: Variable(name, level, type)
{
    this->_value = value;
}

ValueType Variable::getType() const
{
    return this->_type;
}

Variable::Value Variable::getValue() const
{
    return this->_value;
}


Parameter::Parameter(const char* name, unsigned char level, ValueType type)
: Symbol(name, level)
{
    this->_type = type;
}

ValueType Parameter::getType() const
{
    return this->_type;
}


Procedure::Procedure(const char* name, unsigned char level, int nParams, ...)
: Symbol(name, level)
{
    va_list parameters;
    va_start(parameters, nParams);

    this->_nParameters = nParams;
    this->_parameters = (Parameter*)malloc(sizeof(Parameter) * nParams);

    for (int i = 0; i < nParams; i++)
        this->_parameters[i] = va_arg(parameters, Parameter);

    va_end(parameters);
}

int Procedure::getParameterCount() const
{
    return this->_nParameters;
}

const Parameter* Procedure::getParameters() const
{
    return this->_parameters;
}

template<typename... Values> Function::Function(const char* name, unsigned char level, ValueType type, int nParams, Values... params)
: Procedure(name, level, nParams, params...)
{
    this->_returnType = type;
}

ValueType Function::getReturnType() const
{
    return this->_returnType;
}
