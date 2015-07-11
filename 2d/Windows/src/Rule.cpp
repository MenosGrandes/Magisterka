#include "Rule.h"

Rule::Rule(std::string from,std::string to)
{
    this->m_from=from;
    this->m_to=to;
}

Rule::~Rule()
{
    //dtor
}
std::string Rule::getFrom()
{
    return this->m_from;
}
std::string Rule::getTo()
{
    return this->m_to;
}

