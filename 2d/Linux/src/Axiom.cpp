#include "Axiom.h"

Axiom::Axiom(std::string to)
{
    this->_to=to;
}

Axiom::~Axiom()
{
    //dtor
}
std::string Axiom::get_to()
{
    return this->_to;
};
void Axiom::set_to(std::string to)
{
    this->_to=to;
}
