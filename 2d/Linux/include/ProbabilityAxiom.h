#ifndef PROBABILITYAXIOM_H
#define PROBABILITYAXIOM_H
#include <memory>
#include <set>
#include <string>

class ProbabilityAxiom
{
public:
    ProbabilityAxiom(std::string to,float prob)
    {
        this->m_to=to;
        this->m_probability=prob;
    }
    std::string get_m_to()
    {
        return this->m_to;
    };
    void set_m_to(std::string to)
    {
        this->m_to=to;
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
typedef std::set<SharedProbabilityAxiom>SharedProbabilityAxiomSet;


#endif // PROBABILITYAXIOM_H
