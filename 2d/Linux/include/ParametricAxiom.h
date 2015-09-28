#ifndef PARAMETRICAXIOM_H
#define PARAMETRICAXIOM_H
#include "Axiom.h"
#include <unordered_map>
#include <vector>
#include <memory>
#include <iostream>
struct Parameter
{
    char c;
    int v;
    Parameter(char c,int v):c(c),v(v)
    {}
    void toClass(std::string)
    {

    }
};

typedef std::unordered_map<char,int> ParameterMap;


class ParametricAxiom : public Axiom
{

public:
    ParametricAxiom(std::string to,char name);
    virtual ~ParametricAxiom();
    void addParameter(Parameter p);
    void addParameter(char c,int v);
    Parameter findParameter(char c);
    ParameterMap m_parameters;//values in predecesor
 char m_name;
 void show();
protected:
private:

public :
    class StringToClass
    {
    public :
        typedef std::shared_ptr<ParametricAxiom> SharedParametricAxiom;
        typedef std::vector<SharedParametricAxiom>SharedParametricAxiomVector;

        /*
        Class created for changing the std::string in to ParametricAxiom example:
        std::string a=B(2)A(4,4) ;
        StringToClass->toClass(a) will return vector with:
        SharedParametricAxiom a;
        a.name='B'
        a._parameters[0]=Parameter('a',2)

        SharedParametrixAxiom b;
        b.name='A';
        b._parameters[0]=Parameter('a',4);
        b._parameters[1]=Parameter('b',4);
        */
        SharedParametricAxiomVector toClass(std::string toClass)
        {
            SharedParametricAxiomVector tmp_v;
            for ( int i=0; i<toClass.size(); i++)
            {
                char tmp_c=toClass[i];
                if(checkCharConfirmLetter(tmp_c))
                {
                    char letter = 'a';
                    SharedParametricAxiom a(new ParametricAxiom("asd",tmp_c));
                    i++;

                    if(toClass[i]=='(')
                    {
                    i++;
                        do
                        {
                            if(std::isdigit(toClass[i]))
                            {
                                a->addParameter(letter,toClass[i]-'0');
                                letter=static_cast<char>(letter+1);
                                i++;
                            }
                            else if(toClass[i]==',')
                            {
                                i++;
                            }
                            else
                            {
                                std::cout<<"ERROR";
                            }

                        }
                        while(toClass[i]!=')');
                        tmp_v.push_back(a);
                    }

                }
            }

            return tmp_v;
        }

        bool checkCharConfirmLetter(char tmp_c)
        {
            return (tmp_c>='A' && tmp_c<='E') ?  true :  false;

        }
    };

};
typedef std::shared_ptr<ParametricAxiom> SharedParametricAxiom;
typedef std::vector<SharedParametricAxiom>SharedParametricAxiomVector;


#endif // PARAMETRICAXIOM_H
