#include "../include/Rule.h"



Rule::~Rule()
{
    //dtor
}
std::string Rule::getFrom()
{
    return this->m_from;
}

SharedProbabilityAxiomSet Rule::getAxiomSet()
{
return axiomSet;
}
Rule::Rule(std::string from, SharedProbabilityAxiomSet axiomSet)
{
        this->m_from=from;
this->axiomSet=axiomSet;
}

void Rule::setAxiomSet(SharedProbabilityAxiomSet axiom)
{
    this->axiomSet=axiom;
}

