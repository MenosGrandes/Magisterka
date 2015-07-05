
#include<iostream>
#include<cstdlib>
#include <SFML/Graphics.hpp>
#include<Turtle.h>
int main()
{
//    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//    sf::CircleShape shape(100.f);
//    shape.setFillColor(sf::Color::Green);
//
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        window.clear();
//        window.draw(shape);
//        window.display();
//    }
Turtle *t=new Turtle(31);
SharedRule a(new Rule("a","ba"));
SharedRule b(new Rule("b","a"));

t->m_result="a";
t->m_rules.push_back(a);
t->m_rules.push_back(b);

t->change();



    return 0;
}
