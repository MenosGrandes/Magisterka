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

protected:
private:
    std::string m_result;
    unsigned char m_iterations;
    std::list<SharedRule> m_rules;



};
typedef std::shared_ptr<Turtle> SharedTurtle;

#endif // TURTLE_H
