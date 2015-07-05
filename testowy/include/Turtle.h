#ifndef TURTLE_H
#define TURTLE_H

#include <stack>
#include <string>
#include <list>
#include <iostream>
#include <Rule.h>

class Turtle
{

    public:
        Turtle(unsigned char iterations);
        virtual ~Turtle();
        Turtle(const Turtle& other);
        Turtle& operator=(const Turtle& other);
        void change();



        std::stack< std::string > m_resultStack;

        std::string m_start;
        std::string m_result;
        unsigned char m_iterations;
        std::list<SharedRule> m_rules;

    protected:
    private:

};

#endif // TURTLE_H
