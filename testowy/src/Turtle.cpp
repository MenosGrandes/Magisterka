#include "Turtle.h"

Turtle::Turtle(unsigned char iterations)
{
    this->m_iterations=iterations;
}

Turtle::~Turtle()
{

}

Turtle::Turtle(const Turtle& other)
{
    //copy ctor
}

Turtle& Turtle::operator=(const Turtle& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
void Turtle::change()
{
    std::string temp;
    temp="";
    for(int i1=0; i1<m_iterations; i1++)
    {
        std::cout<<"ITERATION :"<<i1<<std::endl;
        int resultSize=m_result.length();
        for(int i=0; i<resultSize; i++)
        {
            bool found=false;
            std::stringstream ss;
            std::string compareString;

            char c = m_result[i];

            ss << c;
            ss >> compareString;
            std::list<SharedRule>::iterator it;
            for (it= m_rules.begin(); it != m_rules.end(); it++)
            {

                if(it->get()->getFrom().compare(compareString) == 0)
                {
                    temp+=it->get()->getTo();
                    std::cout<<"CHANGED FROM "<<it->get()->getFrom()<<" TO "<<it->get()->getTo()<<std::endl;
                    found=true;

                }


            }
            if(found==false)
            {
                std::cout<<"NOT FOUND"<<std::endl;
                temp+=compareString;
            }



        }

        m_result=temp;
        temp="";
        std::cout<<"ENDED :"<<m_result<<std::endl;
        std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~\n";

    }
}
