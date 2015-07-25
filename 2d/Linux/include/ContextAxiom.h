#ifndef CONTEXTAXIOM_H
#define CONTEXTTAXIOM_H
#include <memory>
#include <string>
class ContextAxiom
{
void set_m_preceded(std::string preceded){this->m_preceded=preceded};
void set_m_fallowed(std::string fallowed){this->m_fallowed=fallowed};
void set_m_current(std::string current){this->m_current=current};
private :
std::string m_preceded;
std::string m_fallowed;
std::string m_current;
};
typedef std::shared_ptr<ContextAxiom> SharedContextAxiom;
typedef std::list<SharedContextAxiom>SharedContextAxiomList;

#endif // CONTEXT_H
