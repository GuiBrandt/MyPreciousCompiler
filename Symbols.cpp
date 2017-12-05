#include "include/Symbols.hpp"

#include <cstring>
#include <cstdarg>
#include <cstdlib>

Symbol::Symbol(const char* name, unsigned char level)
{
    memset(this->_name, 0, 256);
    strcpy(this->_name, name);
    this->_level = level;
}

const char* Symbol::getName() const
{
    return this->_name;
}

void Symbol::setName(const char* name)
{
    strcpy(this->_name, name);
}

unsigned char Symbol::getLevel() const
{
    return this->_level;
}

void Symbol::setLevel(unsigned char level)
{
    this->_level = level;
}

Variable::Variable(const char* name, unsigned char level, ValueType type)
: Symbol(name, level)
{
    this->_type = type;
}

ValueType Variable::getType() const
{
    return this->_type;
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

void Parameter::setType(ValueType type)
{
    this->_type = type;
}

int Function::getParameterCount() const
{
    return this->_nParameters;
}

const Parameter* Function::getParameters() const
{
    return this->_parameters;
}

Function::Function(const char* name, unsigned char level, ValueType type, int nParams, Parameter* params)
: Symbol(name, level)
{
    this->_nParameters = nParams;
    this->_parameters = (Parameter*)malloc(sizeof(Parameter) * nParams);

    for (int i = 0; i < nParams; i++)
        this->_parameters[i] = params[i];
    this->_returnType = type;
}

ValueType Function::getReturnType() const
{
    return this->_returnType;
}
