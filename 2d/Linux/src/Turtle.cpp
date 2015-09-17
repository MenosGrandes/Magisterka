#include "../include/Turtle.h"
#define ELPP_STL_LOGGING
#include "easylogging++.h"
INITIALIZE_EASYLOGGINGPP




Turtle::Turtle(unsigned char iterations)
{
    this->m_iterations=iterations;
    // Load configuration from file
    el::Configurations conf("file.conf");
    // Reconfigure single logger
    el::Loggers::reconfigureLogger("default", conf);
    // Actually reconfigure all loggers instead
    el::Loggers::reconfigureAllLoggers(conf);
    // Now all the loggers will use configuration from file
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


    std::string temp;
    temp="";

    sf::Clock clock; // starts the clock
    sf::Time elapsed1 = clock.getElapsedTime();
    clock.restart();





    for(int i1=0; i1<m_iterations; i1++)
    {
        LOG(INFO)<<"ITERATION :"<<i1;
        LOG(INFO)<<"AXIOM :"<<m_result;
        int resultSize=m_result.length();
        for(int i=0; i<resultSize; i++)
        {
            bool found=false;
            m_level=0;
            std::stringstream ss;
            std::string compareString;
            char a = m_result[i];
            ss << a;
            ss >> compareString;
            ss.clear();

            if(compareString == "[")
            {
                ++m_level;
            }
            if(compareString == "]")
            {
                --m_level;
            }

            std::list<SharedRule>::iterator it;
            for (it= m_rules.begin(); it != m_rules.end(); it++)
            {

/*Check if the compareString sign is in the bracket, and in which one. So if

F1F0F0F0[+F1F1]F1[-F1F1][+F1F1]F1 -> and compareString is '1' at 15 place you must ommit all brackets.

compareString is '1' at 19 place the
*/
                ChangeNonContextSensitiveSystem(it,i,temp,compareString,found);

                ChangeContextSensitiveSystem(it,i,temp,compareString,found);

            }
            if(found==false)
            {

                LOG(DEBUG)<<compareString<<" WAS NOT FOUND";

                temp+=compareString;
            }



        }

        m_result=temp;
        temp="";


        LOG(INFO)<<"ENDED :"<<m_result;


    }

    sf::Time elapsed2 = clock.getElapsedTime();
    LOG(DEBUG)<<"TIME: "<<elapsed2.asMilliseconds();


}

/*If there is situation when the '[' or ']' occurs those symbols must be ignored so if there is A[ABABABABCA]ABB and A<A>B it can change because the [..] is ignored  */
void Turtle::ChangeContextSensitiveSystem(std::list<SharedRule>::iterator it, int i, std::string& temp, std::string& compareString, bool& found)
{
    SharedContextAxiomVector2L contextSet=it->get()->getAxiomSet()->contextSet;
    if(contextSet.size()>0)
    {
        std::string compareStringNext,compareStringPrevious;
        std::stringstream ss;
        bool compareNB=false,comparePB=false;

        if(it->get()->getFrom().compare(compareString) == 0)
        {
            /*Check next sign*/
            for(int g=i+1; g<m_result.size(); g++)
            {
                char b = m_result[g];
                ss << b;
                ss >> compareStringNext;
                ss.clear();

                if(compareStringNext=="[" )
                {
                    LOG(TRACE)<<compareStringNext;
                    LOG(TRACE)<<g;
//                    do
//                    {
                        do
                        {
                            b = m_result[++g];
                            ss << b;
                            ss >> compareStringNext;
                            ss.clear();
                            LOG(TRACE)<<"changed to :"<<compareStringNext;

                        }
                        while(compareStringNext!="]");

                        b = m_result[++g];
                        ss << b;
                        ss >> compareStringNext;
                        ss.clear();
//                    }
//                    while(compareStringNext!="[");
                    LOG(TRACE)<<"changed2 to :"<<compareStringNext;



                }


                if (std::find(m_ignoreList.begin(), m_ignoreList.end(), compareStringNext) != m_ignoreList.end())
                {
                    /*if it's then you can go to another sign because it's should not be evaluated*/

                    LOG(DEBUG)<<compareStringNext<<" is in IGNORE IN NEXT";

                    compareNB=true;
                }
                else
                {
                    compareNB=false;

                    LOG(DEBUG)<<g<<" : "<<compareStringNext<<" becoming compareStringNext";


                    break;
                }

            }
            if(compareNB || compareStringNext.empty())
            {

                LOG(DEBUG)<<"compareStringNext not found or empty. Going to next iteration";

                return;
            }




            for(int g=i-1; g>=0; g--)
            {
                char c = m_result[g];
                ss << c;
                ss >> compareStringPrevious;
                ss.clear();

                if(compareStringPrevious=="]" )
                {
                    LOG(TRACE)<<compareStringPrevious;
                    LOG(TRACE)<<g;
//                    do
//                    {
                        do
                        {
                            c = m_result[--g];
                            ss << c;
                            ss >> compareStringPrevious;
                            ss.clear();
                            LOG(TRACE)<<"changed to :"<<compareStringPrevious;

                        }
                        while(compareStringPrevious!="[");

                        c = m_result[--g];
                        ss << c;
                        ss >> compareStringPrevious;
                        ss.clear();
    //                    }
    //                    while(compareStringPrevious!="]");
                    LOG(TRACE)<<"changed2 to :"<<compareStringPrevious;



                }

                if (std::find(m_ignoreList.begin(), m_ignoreList.end(), compareStringPrevious) != m_ignoreList.end())
                {
                    /*if it's then you can go to another sign because it's should not be evaluated*/

                    LOG(DEBUG)<<compareStringPrevious<<" is in IGNORE IN PREVIUS";

                    comparePB=true;
                }
                else
                {
                    comparePB=false;


                    LOG(DEBUG)<<g<<" : "<<compareStringPrevious<<" becoming compareStringPrevious ";

                    break;
                }


            }
            if(comparePB  || compareStringPrevious.empty())
            {

                LOG(DEBUG)<<"compareStringPrevious not found. Going to next iteration";

                return;
            }








            /*Now the algorithm must find the specifix axiom. So it must find out which one of axioms are the same as the founded "proceed" and "succed"*/
            SharedContextAxiomVector2L::iterator itContext;
            itContext = std::find_if(contextSet.begin(), contextSet.end(),
                                     [&compareStringPrevious,&compareStringNext](SharedContextAxiom2L const &obj)

            {
                return (obj->get_m_preceded() == compareStringPrevious && obj->get_m_fallowed() == compareStringNext);

            }

                                    );
            if(itContext != contextSet.end())
            {

                LOG(INFO)<<"CHANGING :"<<compareString<<" -----> "<<(*itContext)->get_m_preceded()<<" < "<<compareString<<" < "<<(*itContext)->get_m_fallowed()<<" TO: "<<(*itContext)->get_m_to();

                temp+=(*itContext)->get_m_to();
                found = true;
            }
            else
            {

                LOG(DEBUG)<<compareStringPrevious<<" < "<<compareString<<" < "<<compareStringNext<<" \nRule in contextSet not Found";

            }

        }

    }
}

/*Function to change only NonContext L-system. */
void Turtle::ChangeNonContextSensitiveSystem( std::list<SharedRule>::iterator it, int i, std::string& temp, std::string& compareString, bool& found)
{

    /*Check the size of probabilityAxioms in this perticular Rule*/

    /*If it's 1 the Rule is DOL ( Deterministic )*/
    if(it->get()->getAxiomSet()->probabilitySet.size()==1)
    {

        if(it->get()->getFrom().compare(compareString) == 0)
        {
            SharedProbabilityAxiomVector axiomSet=it->get()->getAxiomSet()->probabilitySet;
            temp+=(*axiomSet.begin())->get_m_to();

            LOG(INFO)<<"CHANGED FROM "<<compareString<<" TO "<<(*axiomSet.begin())->get_m_to();

            found=true;

        }


    }
    /*If there is more than one posibility of change for this sign, this must be the SOL ( Stochiastic )*/
    else if(it->get()->getAxiomSet()->probabilitySet.size()>1)
    {

        if(it->get()->getFrom().compare(compareString) == 0)
        {

            /*Type for range values*/
            typedef std::list<std::pair<int,int>> Range;

            LOG(DEBUG)<<it->get()->getFrom()<<" FROM";

            /*Random number generation*/
            auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
            auto rando = std::bind(std::uniform_int_distribution<int>(0,100),
                                   std::mt19937(seed));
            /*Get AxiomSET*/
            SharedProbabilityAxiomVector axiomSet=it->get()->getAxiomSet()->probabilitySet;
            /*Create iterator for axiomSet*/
            SharedProbabilityAxiomVector::iterator iterat;
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
                    LOG(DEBUG)<<"TOO MUCH!!!!!!! MUST BE LOWER THEN 100%";
                }


            }/*Now the values must be chacked, so form what range the probability have hit*/
            Range::iterator rangeIterator;

            int iteratorForSet=0;
            for(rangeIterator=range.begin(); rangeIterator!=range.end(); rangeIterator++)
            {
                if((*rangeIterator).first<=rand &&rand<=(*rangeIterator).second)
                {

                    LOG(DEBUG)<<(*rangeIterator).first<<" < ="<<rand<<"<="<<(*rangeIterator).second;

                    /*If it have found the range quit the loop*/
                    break;
                }
                iteratorForSet++;
            }
            LOG(DEBUG)<<rand<<" random generated";
            /*Go to the object correspondent to range*/
            SharedProbabilityAxiomVector::iterator itProb = axiomSet.begin();
            std::advance(itProb, iteratorForSet);
            /*Change*/
            temp+=(*itProb)->get_m_to();
            found = true;

            LOG(INFO)<<"CHANGED FROM "<<compareString<<" TO "<<(*itProb)->get_m_to();


        }

    }
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
void Turtle::SetIgnoredList(std::vector<std::string> list)
{
    this->m_ignoreList=list;
}

void Turtle::AddIgnoreListEntry(std::string ignore)
{
    this->m_ignoreList.push_back(ignore);
}
