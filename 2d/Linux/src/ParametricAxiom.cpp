#include "ParametricAxiom.h"

ParametricAxiom::ParametricAxiom(std::string to,char name):Axiom(to),m_name(name)
{

}

ParametricAxiom::~ParametricAxiom()
{
    //dtor
}
void ParametricAxiom::addParameter(Parameter p)
{

    m_parameters.insert({p.c,p.v});
}
void ParametricAxiom::addParameter(char c,int v)
{
    m_parameters.insert({c,v});
}
Parameter ParametricAxiom::findParameter(char c)
{
    ParameterMap::const_iterator got = m_parameters.find (c);
    if ( got == m_parameters.end() )
    {
        return Parameter('0',0);
    }
    else
    {
        return Parameter(got->first,got->second);
    }
}
void ParametricAxiom::show()
{
  std::cout<<this->m_name<<"(";
      for(std::pair<char,int> d: this->m_parameters)
    {
        std::cout<<d.first<<"-"<<d.second<<" ";
    }
    std::cout<<")\n\n";
}

