#include<iostream>
#include<cstdlib>
#include <TurtleDrawer.h>
#include <GUI.h>

int main()
{

    sf::Vector2f prev;

    sf::View view2(sf::Vector2f(350, 300), sf::Vector2f(300, 200));

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    Turtle *t=new Turtle(2);
    SharedRule a(new Rule("1","11"));
    SharedRule b(new Rule("0","1[0]0"));

//SharedRule b(new Rule("0","1[0]0"));
    t->SetResult("0");

    t->AddRule(a);
    t->AddRule(b);

//t->m_rules.push_back(b);

    t->compute();
    t->SetResult("0000");

    SharedTurtleDrawer td(new TurtleDrawer(t->GetResult(),100,45));
td->show();
        std::cout<<td->size()<<"\n";
SharedGUI gui(new GUI());
gui->Run();
    /*
    DRAWING!
    */
    	sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
        	gui->desktop.HandleEvent( event );
            //Position of mouse on screen
            sf::Vector2f ms, delta;
            //get mouse position on screen
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            //calculate mouse position on window
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

            switch(event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                view2.setSize(event.size.width, event.size.height);
                view2.setCenter(view2.getSize() * 0.5f );
                break;
                //refresh the position of mouse on screen
            case sf::Event::MouseMoved:
            {
                ms = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
                delta = ms - prev;
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    view2.setCenter(view2.getCenter() - delta);
                prev = ms;

                break;
            }
        //zoom and unzoom the view
            case sf::Event::MouseWheelMoved:
            {



                if(event.mouseWheel.delta>0)
                {
                    view2.zoom(1.1f);

                }
                else
                {
                    view2.zoom(0.9f);

                }
            }
            break;
            }


        }
        	gui->desktop.Update( clock.restart().asSeconds() );

        window.clear();
        window.setView(view2);

        window.draw(*td);
        	gui->m_sfgui.Display( window);
        window.display();
    }


    return 0;
}
