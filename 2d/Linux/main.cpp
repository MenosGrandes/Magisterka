#include<iostream>
#include<cstdlib>
#include <TurtleDrawer.h>
#include <GUI.h>
#include <ParametricAxiom.h>
int main()
{
ParametricAxiom::StringToClass *s=new ParametricAxiom::StringToClass();


SharedParametricAxiomVector v=s->toClass("A(2)B(3,3)");
for(SharedParametricAxiom a: v)
{
a->show();
}




    sf::Vector2f prev;

    sf::View view2(sf::Vector2f(350, 300), sf::Vector2f(300, 200));
    sf::RenderWindow window(sf::VideoMode(1366, 768), "MastersSystem!",sf::Style::Default);
    /*
    SharedTurtle, aka std::shared_ptr<Turtle>, is used to calculate the string of the L-System.
    Turtle calculates the string from SharedRule, aka std::shared_ptr<Rule>. SharedRule contains 2 strings, from and to.

    Rules are added in GUI.
    */
    SharedTurtle t(new Turtle(1));


    /*
    SharedTurtleDrawer, aka std::shared_ptr<TurtleDrawer>, is used to draw lines from string calculated in Turtle.
    */
    SharedTurtleDrawer td(new TurtleDrawer());
    /*
    Ther is an bug in sfgui, when program won't draw any content the letters in gui are really weird.
    So compute the draw.
    */
    td->computeDraw();
    /*
    Create gui and pass an SharedTurtleDrawer and SharedTurtle, to recalculate the whole Rules and Axioms, if they were added at GUI side.
    */
    SharedGUI gui(new GUI(t,td));
    /*Compute the l-system*/
    t->compute();
    /*Draw the output.
    10 -> length of the line (whatever value)*/
    td->computeDraw(t->GetResult(),10,22.5);
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
            /**Temporary workround*/
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();

                }
                break;
            }


        }
        gui->desktop.Update( clock.restart().asSeconds() );

        window.clear();
        window.setView(view2);
        /*
        Draw the calculated L-system
        */
        window.draw(*td);
        /*
        Draw GUI
        */
        gui->m_sfgui.Display( window);
        window.display();
    }


    return 0;
}
