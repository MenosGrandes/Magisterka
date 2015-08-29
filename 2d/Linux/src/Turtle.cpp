#include "../include/Turtle.h"

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
void Turtle::compute()
{
    /*Calculate the rules numbers, so how many rules->from are the same, but they have different rule->to*/

    /*asd*/

    std::string temp;
    temp="";
#ifdef DEBUG
    sf::Clock clock; // starts the clock
    sf::Time elapsed1 = clock.getElapsedTime();
    std::cout << elapsed1.asMilliseconds() << std::endl;
    clock.restart();
#endif // DEBUG
    for(int i1=0; i1<m_iterations; i1++)
    {
#ifdef DEBUG
        std::cout<<"ITERATION :"<<i1<<std::endl;
        std::cout<<"AXIOM :"<<m_result<<std::endl;
#endif // DEBUG
        int resultSize=m_result.length();
        for(int i=0; i<resultSize; i++)
        {
            bool found=false;
            std::stringstream ss;
            std::string compareString,compareStringNext,compareStringPrevious;

            char a = m_result[i];
            char b = m_result[i+1];
            char c = m_result[i-1];
            ss << a;
            ss >> compareString;
            ss.clear();
            ss << b;
            ss >> compareStringNext;
            ss.clear();
            ss << c;
            ss >> compareStringPrevious;
            ss.clear();
            std::list<SharedRule>::iterator it;
            for (it= m_rules.begin(); it != m_rules.end(); it++)
            {

                /*Consequently, if a context-free and a context-sensitive production both apply
                to a given letter, the context-sensitive one should be selected. If no pro-
                duction applies, this letter is replaced by itself as previously assumed
                for OL-systems.*/
                /*If there is only one axiom*/





                if(it->get()->getAxiomSet()->probabilitySet.size()==1)
                {

                    if(it->get()->getFrom().compare(compareString) == 0)
                    {

                        /*Check if there is correspondend context-sensitive
                        Check the L1System, because there is only one possibility the
                        "a > a_r --> x"
                        */



                        SharedProbabilityAxiomSet axiomSet=it->get()->getAxiomSet()->probabilitySet;
                        temp+=(*axiomSet.begin())->get_m_to();
#ifdef DEBUG
                        std::cout<<"CHANGED FROM "<<compareString<<" TO "<<(*axiomSet.begin())->get_m_to()<<std::endl;
#endif // DEBUG
                        found=true;

                    }


                }
                /*If there is more than 1, then you have to calculate the probability of change*/
                else
                {
                    if(it->get()->getFrom().compare(compareString) == 0)
                    {
                        /*

                        */

                        SharedContextAxiomSet2L contextSet=it->get()->getAxiomSet()->contextSet;

                        if(contextSet.size()>0)
                        {
#ifdef DEBUG
                            std::cout<<"\n\n\nCONTEXT AXIOMS\n\n\n";
#endif // DEBUG
                            if(compareStringPrevious.compare((*contextSet.begin())->get_m_preceded()) && compareStringNext.compare((*contextSet.begin())->get_m_fallowed()))
                            {
#ifdef DEBUG
std::cout<<"CHECKING :\t"<<compareStringPrevious<<"\n";
                                std::cout<<(*contextSet.begin())->get_m_preceded()<<" < "<<compareString<<" < "<<(*contextSet.begin())->get_m_fallowed()<<" TO: "<<(*contextSet.begin())->get_m_to()<<"\n";
#endif // DEBUG
                                temp+=(*contextSet.begin())->get_m_to();
                                found = true;
                            }
                        }
                        else
                        {
                            /*Type for range values*/
                            typedef std::list<std::pair<int,int>> Range;
#ifdef DEBUG
                            std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"<<it->get()->getFrom()<<" FROM\n";
#endif // DEBUG
                            /*Random number generation*/
                            auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
                            auto rando = std::bind(std::uniform_int_distribution<int>(0,100),
                                                   std::mt19937(seed));
                            /*Get AxiomSET*/
                            SharedProbabilityAxiomSet axiomSet=it->get()->getAxiomSet()->probabilitySet;
                            /*Create iterator for axiomSet*/
                            SharedProbabilityAxiomSet::iterator iterat;
                            /*Get random number*/
                            int rand=rando();
                            Range range;
                            /*Current probability*/
                            int currentProbability=0;
                            for(iterat=axiomSet.begin(); iterat!=axiomSet.end(); iterat++)
                            {
                                /*Get probability of current axiom*/
                                float probab=(*iterat)->get_m_probability();
                                /*If the axiom in list is the first axiom than it's probability  must be from 0 to this->probability*/
                                if(iterat==axiomSet.begin())
                                {
                                    range.push_back(std::make_pair(currentProbability,probab));
                                }
                                /*If the axiom in the list is the last axiom the probability must be from currentProbability to 100*/
                                else if(iterat==axiomSet.end())
                                {
                                    range.push_back(std::make_pair(currentProbability,100));

                                }/*If it's somewhere in middle than probability must be from currentProbability to currentProbability+this->probability*/
                                else
                                {
                                    range.push_back(std::make_pair(currentProbability,currentProbability+probab));
                                }
                                /*Add this->probability to currentProbability*/
                                currentProbability+=probab;
                                /*If there is more than 100% of probability so there must be something wrong*/
                                if(currentProbability>100)
                                {
                                    std::cout<<"TOO MUCH!!!!!!! MUST BE LOWER THEN 100%\n";
                                }


                            }/*Now the values must be chacked, so form what range the probability have hit*/
                            Range::iterator rangeIterator;

                            int iteratorForSet=0;
                            for(rangeIterator=range.begin(); rangeIterator!=range.end(); rangeIterator++)
                            {
                                if((*rangeIterator).first<=rand &&rand<=(*rangeIterator).second)
                                {
#ifdef DEBUG
                                    std::cout<<(*rangeIterator).first<<" < ="<<rand<<"<="<<(*rangeIterator).second<<"\n";
#endif // DEBUG
                                    /*If it have found the range quit the loop*/
                                    break;
                                }
                                iteratorForSet++;
                            }
#ifdef DEBUG
                            std::cout<<rand<<" random generated\n";
#endif // DEBUG
                            /*Go to the object correspondent to range*/
                            SharedProbabilityAxiomSet::iterator itProb = axiomSet.begin();
                            std::advance(itProb, iteratorForSet); // now it is advanced by five
                            /*Change*/
                            temp+=(*itProb)->get_m_to();
                            found = true;
#ifdef DEBUG
                            std::cout<<"CHANGED FROM "<<compareString<<" TO "<<(*itProb)->get_m_to()<<std::endl;

#endif // DEBUG
                        }
                    }
                }
            }
            if(found==false)
            {
#ifdef DEBUG
                std::cout<<compareString<<" WAS NOT FOUND\n"<<std::endl;
#endif // DEBUG
                temp+=compareString;
            }



        }

        m_result=temp;
        temp="";
#ifdef DEBUG

        std::cout<<"ENDED :"<<m_result<<std::endl;
        std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~\n";
#endif // DEBUG

    }
#ifdef DEBUG
    sf::Time elapsed2 = clock.getElapsedTime();
    std::cout << elapsed2.asMilliseconds() << std::endl;
#endif // DEBUG

}


std::string Turtle::GetResult()
{
    return this->m_result;
}

void Turtle::SetResult(std::string val)
{
    this->m_result=val;
}
void Turtle::AddRule(SharedRule s)
{

    this->m_rules.push_back(s);
}
void Turtle::AddIterations(unsigned int iterations)
{
    this->m_iterations=iterations;
}

unsigned int Turtle::GetIterations()
{
    return this->m_iterations;
}
void Turtle::Reset()
{
    this->m_rules.clear();
}
