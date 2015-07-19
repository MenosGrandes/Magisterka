#ifndef RULEAXIOM_H
#define RULEAXIOM_H
#include<SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <sstream>
#include <string>
#include <memory>
/**
Class that contains 2 sfg::Entry::Ptr :
rule  -> to contain the rule.
axiom -> to contain the axiom.
and 2 sfg::Label::Ptr for those entry.
*/
class RuleAxiom
{
public :
    sfg::Entry::Ptr entryAxiom,entryRule;
    sfg::Label::Ptr labelRule,labelAxiom;
    void Add(std::string labelA,std::string labelR,int number,sfg::Box::Ptr box);

};
typedef std::shared_ptr<RuleAxiom> SharedRuleAxiom;
typedef std::list<SharedRuleAxiom> SharedRuleAxiomList;


#endif // RULEAXIOM_H
