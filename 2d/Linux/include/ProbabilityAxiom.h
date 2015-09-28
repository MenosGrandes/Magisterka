#ifndef PROBABILITYAXIOM_H
#define PROBABILITYAXIOM_H
#include <memory>
#include <set>
#include <string>
#include "Axiom.h"
class ProbabilityAxiom : public Axiom
{
public:
    ProbabilityAxiom(std::string to,float prob) : Axiom(to)
    {
        this->m_to=to;
        this->m_probability=prob;
    }


    float get_m_probability()
    {
        return this->m_probability;
    }
    void set_m_probability(float prob)
    {
        this->m_probability=prob;
    };

private:
    std::string m_to;
    float m_probability;
};
typedef std::shared_ptr<ProbabilityAxiom>SharedProbabilityAxiom;
typedef std::vector<SharedProbabilityAxiom>SharedProbabilityAxiomVector;


#endif // PROBABILITYAXIOM_H
