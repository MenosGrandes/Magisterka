#ifndef TURTLE_H
#define TURTLE_H

#include <stack>
#include <string>
#include <list>
#include <iostream>
#include <Rule.h>
#include <cmath>
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
    void addIterations(unsigned int iterations);
    unsigned int getIterations();

protected:
private:
    std::string m_result;
    unsigned char m_iterations;
    std::list<SharedRule> m_rules;

};
typedef std::shared_ptr<Turtle> SharedTurtle;

#endif // TURTLE_H
