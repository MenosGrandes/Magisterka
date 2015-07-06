#include "TurtleDrawer.h"

TurtleDrawer::TurtleDrawer(std::string initializer)
{
float currentRotation=0;
float rotate=90;

sf::Vector2f currentPosition(0,0);

        m_vertices.setPrimitiveType(sf::LinesStrip);
        m_vertices.resize(initializer.length());
       // sf::Vertex* quad2 = &m_vertices[0];
        //m_vertices[0].position = currentPosition;

for(int i=0;i<initializer.length();i++)
{


    char sign=initializer[i];
    switch(sign)
    {
        case '+' :
            //std::cout<<" + ";
/* Rotate left*/
currentRotation+=rotate;

            break;
        case '-' :
            /* Rotate right*/
           // std::cout<<" - ";
currentRotation-=rotate;
            break;
        case 'F' :
           // std::cout<<" F ";
currentPosition.x+=1;
currentPosition.y+=1;
m_vertices[i].position = sf::Vector2f((currentPosition.x), (currentPosition.y));
//std::cout<<quad[i].position.x<<" "<<quad[i].position.y<<"\n";
            break;

    }





}


}

TurtleDrawer::~TurtleDrawer()
{
    //dtor
}
