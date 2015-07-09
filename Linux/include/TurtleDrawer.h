#ifndef TURTLEDRAWER_H
#define TURTLEDRAWER_H
#include <SFML/Graphics.hpp>
#include<Turtle.h>

class TurtleDrawer :public sf::Drawable, public sf::Transformable
{
public:
    /** Default constructor */
    TurtleDrawer(std::string initializer);
    /** Default destructor */
    virtual ~TurtleDrawer();
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

};
typedef std::shared_ptr<TurtleDrawer> SharedTurtleDrawer;

#endif // TURTLEDRAWER_H
