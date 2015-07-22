#include<iostream>
#include<cstdlib>
#include <TurtleDrawer.h>
#include <GUI.h>

int main()
{

    sf::Vector2f prev;

    sf::View view2(sf::Vector2f(350, 300), sf::Vector2f(300, 200));

    sf::RenderWindow window(sf::VideoMode(1366, 768), "SFML works!",sf::Style::Default);
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
//#include <SFML/Graphics.hpp>
//#include "AnimatedSprite.h"
//#include <iostream>
//
//int main()
//{
//    // setup window
//    sf::Vector2i screenDimensions(800,600);
//    sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Animations!");
//    window.setFramerateLimit(60);
//
//    // load texture (spritesheet)
//    sf::Texture texture;
//    if (!texture.loadFromFile("img/loading.png"))
//    {
//        std::cout << "Failed to load player spritesheet!" << std::endl;
//        return 1;
//    }
//
//    // set up the animations for all four directions (set spritesheet and push frames)
//    Animation walkingAnimationDown;
//for(int i=0;i<6;i++)
//{
//
//for(int j=0;j<5;j++)
//{
//int x,y;
//x=i*300;
//y=j*400;
//   walkingAnimationDown.addFrame(sf::IntRect(y, x, 400, 300));
//    std::cout<<y<<" "<<x<<"\n";
//
//
//}
//}
//    walkingAnimationDown.setSpriteSheet(texture);
//
//    Animation* currentAnimation = &walkingAnimationDown;
//
//    // set up AnimatedSprite
//    AnimatedSprite animatedSprite(sf::seconds(0.2), true, false);
//    animatedSprite.setPosition(sf::Vector2f(screenDimensions / 2));
//
//    sf::Clock frameClock;
//
//    float speed = 80.f;
//    bool noKeyWasPressed = true;
//
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
//                window.close();
//        }
//
//        sf::Time frameTime = frameClock.restart();
//
//        // if a key was pressed set the correct animation and move correctly
//        sf::Vector2f movement(0.f, 0.f);
//
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
//        {
//            currentAnimation = &walkingAnimationDown;
//            noKeyWasPressed = false;
//        }
//
//        animatedSprite.play(*currentAnimation);
//        animatedSprite.move(movement * frameTime.asSeconds());
//
//        // if no key was pressed stop the animation
////        if (noKeyWasPressed)
////        {
////            animatedSprite.stop();
////        }
////        noKeyWasPressed = true;
//
//        // update AnimatedSprite
//        animatedSprite.update(frameTime);
//
//        // draw
//        window.clear();
//        window.draw(animatedSprite);
//        window.display();
//    }
//
//    return 0;
//}
