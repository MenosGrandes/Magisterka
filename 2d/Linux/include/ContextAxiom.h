#ifndef CONTEXTAXIOM_H
#define CONTEXTTAXIOM_H
#include <memory>
#include <string>
class ContextAxiom
{public :
ContextAxiom(std::string preceded,std::string fallowed)
{
this->m_preceded=preceded;
this->m_fallowed=fallowed;
};
void set_m_preceded(std::string preceded){this->m_preceded=preceded;}
void set_m_fallowed(std::string fallowed){this->m_fallowed=fallowed;}
private :
std::string m_preceded;
std::string m_fallowed;
};
typedef std::shared_ptr<ContextAxiom> SharedContextAxiom;
typedef std::set<SharedContextAxiom>SharedContextAxiomSet;

#endif // CONTEXT_H
