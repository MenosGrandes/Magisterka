#ifndef RULE_H
#define RULE_H
#include <memory>
#include <string>
#include <sstream>
#include <algorithm>
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
#endif // RULE_H
