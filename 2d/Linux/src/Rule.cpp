#include "../include/Rule.h"



Rule::~Rule()
{
    //dtor
}
std::string Rule::getFrom()
{
    return this->m_from;
}

SharedContextProbabilityParametricAxiomSet Rule::getAxiomSet()
{
    return m_axioms;
}
Rule::Rule(std::string from, SharedContextProbabilityParametricAxiomSet axiomSet)
{
    this->m_from=from;
    this->m_axioms=axiomSet;
}

void Rule::setAxiomSet(SharedContextProbabilityParametricAxiomSet axiom)
{
    this->m_axioms=axiom;
}


