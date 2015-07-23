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
class Rule
{
public:
    Rule(std::string from,std::string to);
    virtual ~Rule();
    std::string getFrom();
    std::string getTo();
protected:
private:
    std::string m_from;
    std::string m_to;
};
typedef std::shared_ptr<Rule> SharedRule;
typedef std::list<SharedRule> SharedRuleList;


/*Struct that contains the values readed from JSON*/
class SystemData2D
{
public :
    SystemData2D(
   std::string name,
        std::string start,
        int iterations,
        float angle,
        SharedRuleList ruleList
    )
    {
    this->name=name;
    this->start=start;
    this->iterations=iterations;
    this->angle=angle;
    this->ruleList=ruleList;
    }
    SystemData2D(const SystemData2D& data) : name(data.name),start(data.start),iterations(data.iterations),angle(data.angle),ruleList(data.ruleList)
    { }
    SystemData2D()
    {}
    std::string name;
    std::string start;
    int iterations;
    float angle;
    SharedRuleList ruleList;

};
typedef std::shared_ptr<SystemData2D>SharedSystemData2D;
typedef std::list<SharedSystemData2D> SharedSystemData2DList;


#endif // RULE_H

