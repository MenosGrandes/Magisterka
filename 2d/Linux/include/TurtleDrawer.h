#ifndef TURTLEDRAWER_H
#define TURTLEDRAWER_H
#include <SFML/Graphics.hpp>
#include<Turtle.h>
#include <stack>
#include <random>
class TurtleDrawer :public sf::Drawable, public sf::Transformable
{
public:
    /** Default constructor */
TurtleDrawer(std::string initializer,unsigned int length, float angle);
    /** Default destructor */
    virtual ~TurtleDrawer();

    unsigned int size();
void show()
{

for(int i=0;i<m_vertices.getVertexCount();i++)
{
std::cout<<m_vertices[i].position.x<<" "<<m_vertices[i].position.y<<"\n";
}}
protected:
private:
    sf::VertexArray m_vertices;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture


        // draw the vertex array
        target.draw(m_vertices, states);
    }
    // sf::Vector2f rotate(sf::Vector2f origin,float angleOfRotation);
    void rotate(sf::Vector2f &origin,float angleOfRotation);
    void translate(sf::Vector2f &origin,sf::Vector2f direction,float lenght);
    float radToDegree(float degree);
    sf::Color randomColor();

};
typedef std::shared_ptr<TurtleDrawer> SharedTurtleDrawer;
typedef std::pair<sf::Vector2f,sf::Vector2f> PosRot;

#endif // TURTLEDRAWER_H
