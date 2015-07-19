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
    struct SystemData2D
    {
        std::string name;
        int iterations;
        float angle;
        SharedRuleList ruleList;

    };
    typedef std::list<SystemData2D> SystemData2DList;

#endif // RULE_H

