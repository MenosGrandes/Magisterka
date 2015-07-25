#include "../include/Rule.h"



Rule::~Rule()
{
    //dtor
}
std::string Rule::getFrom()
{
    return this->m_from;
}

SharedContextProbabilityAxiomSet Rule::getAxiomSet()
{
    return m_axioms;
}
Rule::Rule(std::string from, SharedContextProbabilityAxiomSet axiomSet)
{
    this->m_from=from;
    this->m_axioms=axiomSet;
}

void Rule::setAxiomSet(SharedContextProbabilityAxiomSet axiom)
{
    this->m_axioms=axiom;
}

