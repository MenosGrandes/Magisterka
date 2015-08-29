#ifndef RULE_H
#define RULE_H
#include <memory>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <list>
#include <stack>
#include <cmath>
#include <random>
#include <iostream>
#include <thread>
#include <SFML/System.hpp>
#include <ProbabilityAxiom.h>
#include <ContextAxiom.h>

/*ContextProbabilityAxiomSet*/
class ContextProbabilityAxiomSet
{
public :
    ContextProbabilityAxiomSet(SharedContextAxiomSet2L context,SharedProbabilityAxiomSet probabilitySet)
    {
        this->contextSet=context;
        this->probabilitySet=probabilitySet;
    }
    SharedContextAxiomSet2L contextSet;
    SharedProbabilityAxiomSet probabilitySet;
};
typedef std::shared_ptr<ContextProbabilityAxiomSet>SharedContextProbabilityAxiomSet;
/* RULE */
class Rule
{
public:
    Rule(std::string from,SharedContextProbabilityAxiomSet axiomSet);
    virtual ~Rule();
    std::string getFrom();
    SharedContextProbabilityAxiomSet getAxiomSet();
    void setAxiomSet(SharedContextProbabilityAxiomSet axioms);
private:
    std::string m_from;
    SharedContextProbabilityAxiomSet m_axioms;
};
typedef std::shared_ptr<Rule> SharedRule;
typedef std::list<SharedRule> SharedRuleList;
/*END RULE*/

/*Struct that contains the values readed from JSON*/
class SystemData2D
{
public :
    SystemData2D(
        std::string name,
        std::string start,
        int iterations,
        float angle,
        SharedRuleList ruleList,
        std::vector<std::string> ignore_list
    )
    {
        this->name=name;
        this->start=start;
        this->iterations=iterations;
        this->angle=angle;
        this->ruleList=ruleList;
        this->ignore_list=ignore_list;
    }
    SystemData2D(const SystemData2D& data) : name(data.name),start(data.start),iterations(data.iterations),angle(data.angle),ruleList(data.ruleList),ignore_list(data.ignore_list)
    { }
    SystemData2D()
    {}
    std::string name;
    std::string start;
    int iterations;
    float angle;
    SharedRuleList ruleList;
    std::vector<std::string> ignore_list;
};
typedef std::shared_ptr<SystemData2D>SharedSystemData2D;
typedef std::list<SharedSystemData2D> SharedSystemData2DList;
/*Struct witch contain the preferences to sliders (SFGUI)*/
struct SliderPreferences
{
    float lower=0.0f;
    float upper=10.0f;
    float minor_step=0.1f;
    float major_step=1.0f;
    float pageSize=0.0f;
    sf::Vector2f requistion =sf::Vector2f( 80.f, 20.f );
    std::string label="";
};



#endif // RULE_H


