#include "../include/TurtleDrawer.h"

TurtleDrawer::TurtleDrawer()
{


}

TurtleDrawer::~TurtleDrawer()
{
    //dtor
}
void TurtleDrawer::computeInThread(std::string initializer,unsigned int length, float angle)
{
#ifdef DEBUG
    std::cout<<"\nSTART COMPUTING\n";
sf::Clock clock; // starts the clock

sf::Time elapsed1 = clock.getElapsedTime();
std::cout << elapsed1.asMilliseconds() << std::endl;
clock.restart();
#endif // DEBUG
 /*
       Stack to get the PosRot values
       */
    std::stack<PosRot> posRotStack;
    /*
    PosRot ofcurrent position and current rotation. Both set to default values
    pos = sf::Vector2f(100,100);
    rot = sf::Vector2f(0,1);
    */
    PosRot current;
    current.first=sf::Vector2f(100,100);
    current.second=sf::Vector2f(1,1);


    /*
    Create a sf::VecrtexArray, container of sf::Vertex, to store the points in L-system.
    */
    m_vertices=sf::VertexArray(sf::PrimitiveType::Lines,1);
    m_vertices.clear();
    /*
    Add first point. The start point.
    */
    sf::Vertex v(sf::Vector2f(current.first),randomColor());
    m_vertices.append(v);


    /*
    For every  char from initializer string check
    */
    for(int i=0; i!=initializer.size(); i++)
    {
        /*
        Get char from initializer.
        */
        char letter;
        letter=initializer[i];

        switch(letter)
        {
        /*
        If '+' rotate by angle.
        */
        case '+' :
            this->rotate(current.second,angle);

            break;
        /* If '+' rotate by angle * -1 .*/
        case '-' :
            this->rotate(current.second,-angle);

            break;
        case '[' :
            /*
            Add current PosRot to stack.
            */
            posRotStack.push(PosRot(current.first,current.second));

            break;
        case ']' :
            /*
            Get latest PosRot from stack and update the current PosRot
            */
            current.first=posRotStack.top().first;
            current.second=posRotStack.top().second;
            m_vertices.append(sf::Vertex(current.first,randomColor()));
            posRotStack.pop();
            break;
        case 'G' :
        case 'F':
            /*
            Translate current point by length
            */
            this->translate(current.first,current.second,length);
            sf::Vertex v(sf::Vector2f(current.first),randomColor());
            m_vertices.append(v);
            /*
            In case if the next one in initializer isn't '[', so it appends another point to createthe strait line, without gaps.

            */
            if(initializer[i+1]!=']')
            {
                sf::Vertex v(sf::Vector2f(current.first),randomColor());
                m_vertices.append(v);
            }


            break;
        }
//        std::cout<<".";

    }
    #ifdef DEBUG
    sf::Time elapsed2 = clock.getElapsedTime();
std::cout << elapsed2.asMilliseconds() << std::endl;
    std::cout<<"\nEND COMPUTING\n";
    #endif // DEBUG

}
void TurtleDrawer::computeDraw(std::string initializer,unsigned int length, float angle)
{

std::thread drawInThread(&TurtleDrawer::computeInThread,this,initializer,length,angle);
drawInThread.detach();

}

/*
http://www.inversereality.org/tutorials/graphics%20programming/2dtransformations.html
Rotate sf::Vector2f origin .
*/
void TurtleDrawer::rotate(sf::Vector2f &origin,float angleOfRotation)
{
    sf::Vector2f temp;
    temp=origin;
    temp.x=origin.x * std::cos(radToDegree(angleOfRotation)) - origin.y * std::sin(radToDegree(angleOfRotation));
    temp.y=origin.x * std::sin(radToDegree(angleOfRotation)) + origin.y * std::cos(radToDegree(angleOfRotation));
    origin=temp;
}
/*
Translate sf::Vector2f origin by lenght
*/
void TurtleDrawer::translate(sf::Vector2f &origin,sf::Vector2f direction,float lenght)
{
    origin.x += lenght*direction.x;
    origin.y += lenght*direction.y;

}
/*
Convert radians to degrees.
*/
float TurtleDrawer::radToDegree(float degree)
{
    return degree * M_PI / 180.0;
}
/*
Get random color. C++11 needed.
*/
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
/*
Return the size of m_vertices
*/
unsigned int TurtleDrawer::size()
{
    return m_vertices.getVertexCount();
}
