#include "../include/TurtleDrawer.h"

TurtleDrawer::TurtleDrawer(std::string initializer,unsigned int length, float angle)
{
    std::stack<PosRot> posRotStack;


    sf::Vector2f currentPosition(100,100);
    sf::Vector2f direction(1,0);

    m_vertices.setPrimitiveType(sf::Lines);
    m_vertices.resize(initializer.size());


    m_vertices[0].position=currentPosition;
    this->translate(currentPosition,direction,length);

    for(int i=1; i<initializer.size()-1; i++)
    {

        char letter;
        letter=initializer[i];

        switch(letter)
        {
        case '+' :
            this->rotate(direction,angle);
            this->translate(currentPosition,direction,length);
            m_vertices[i].position=currentPosition;
            m_vertices[i].color=randomColor();
            break;
        case '-' :
            this->rotate(direction,-angle);
            this->translate(currentPosition,direction,length);
            m_vertices[i].position=currentPosition;
            m_vertices[i].color=randomColor();
            break;
        case '[':
            std::cout<<"PUSH\n";
            posRotStack.push( PosRot(currentPosition,direction));
            std::cout<<currentPosition.x<<" "<<currentPosition.y<<"\n";
            std::cout<<direction.x<<" "<<direction.y<<"\n";
            break;
        case ']':
            std::cout<<"pop\n";
            currentPosition=posRotStack.top().first;
            direction=posRotStack.top().second;
            posRotStack.pop();

            std::cout<<currentPosition.x<<" "<<currentPosition.y<<"\n";
            std::cout<<direction.x<<" "<<direction.y<<"\n";
            break;
        case 'A':
        case 'B':
        case 'F':

            m_vertices[i].position=currentPosition;
            m_vertices[i].color=randomColor();


            break;
        }

    }
}

TurtleDrawer::~TurtleDrawer()
{
    //dtor
}


/**
http://www.inversereality.org/tutorials/graphics%20programming/2dtransformations.html*/
void TurtleDrawer::rotate(sf::Vector2f &origin,float angleOfRotation)
{
    sf::Vector2f temp;
    temp=origin;
    temp.x=origin.x * std::cos(radToDegree(angleOfRotation)) - origin.y * std::sin(radToDegree(angleOfRotation));
    temp.y=origin.x * std::sin(radToDegree(angleOfRotation)) + origin.y * std::cos(radToDegree(angleOfRotation));
    origin=temp;
}
void TurtleDrawer::translate(sf::Vector2f &origin,sf::Vector2f direction,float lenght)
{
    origin.x += lenght*direction.x;
    origin.y += lenght*direction.y;

}
float TurtleDrawer::radToDegree(float degree)
{
    return degree * M_PI / 180.0;
}

sf::Color TurtleDrawer::randomColor()
{

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0, std::nextafter(255, std::numeric_limits<double>::max()));


    sf::Color color;
    color.r=dist(mt);
    color.g=dist(mt);
    color.b=dist(mt);
    return color;
}
unsigned int TurtleDrawer::size()
{
return m_vertices.getVertexCount();
}
