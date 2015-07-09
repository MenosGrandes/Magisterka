
#include<iostream>
#include<cstdlib>
#include <TurtleDrawer.h>
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
Turtle *t=new Turtle(10);
SharedRule a(new Rule("A","B-A-B"));
SharedRule b(new Rule("B","A+B+A"));

//SharedRule b(new Rule("0","1[0]0"));
t->SetResult("A");

t->AddRule(a);
t->AddRule(b);

//t->m_rules.push_back(b);

t->compute();
std::cout<<t->GetResult()<<"\n";
SharedTurtleDrawer td(new TurtleDrawer(t->GetResult()));
/*
DRAWING!
*/
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(*td);
        window.display();
    }


    return 0;
}
