#ifndef TURTLE_H
#define TURTLE_H

#include <Rule.h>
#include <random>
#include <map>
#include <chrono>


class Turtle
{

public:
    Turtle(unsigned char iterations);
    virtual ~Turtle();
    Turtle(const Turtle& other);
    Turtle& operator=(const Turtle& other);
    void compute();
    std::string GetResult();
    void SetResult(std::string val);
    void AddRule(SharedRule s);
    void AddIterations(unsigned int iterations);
    unsigned int GetIterations();
    void Reset();
    void SetIgnoredList(std::vector<std::string> list);
    void AddIgnoreListEntry(std::string ignore);

protected:
private:
    std::string m_result;
    unsigned char m_iterations;
    std::list<SharedRule> m_rules;
    std::vector<std::string>m_ignoreList;
    void ChangeContextSensitiveSystem(std::list<SharedRule>::iterator it,int i,std::string &temp,std::string &compareString,bool &found);
    void ChangeNonContextSensitiveSystem(std::list<SharedRule>::iterator it,int i,std::string &temp,std::string &compareString,bool &found);


};
typedef std::shared_ptr<Turtle> SharedTurtle;




#endif // TURTLE_H
