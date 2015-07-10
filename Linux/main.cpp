
#include<iostream>
#include<cstdlib>
#include <TurtleDrawer.h>
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
Turtle *t=new Turtle(3);
SharedRule a(new Rule("F","F+F-F-F+F"));
SharedRule b(new Rule("0","1[0]0"));

//SharedRule b(new Rule("0","1[0]0"));
t->SetResult("F");

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
