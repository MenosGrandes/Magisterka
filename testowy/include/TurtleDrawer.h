#ifndef TURTLEDRAWER_H
#define TURTLEDRAWER_H
#include <SFML/Graphics.hpp>
#include<Turtle.h>
class TurtleDrawer :public sf::Transformable, public sf::Drawable
{
    public:
        /** Default constructor */
        TurtleDrawer(std::string initializer);
        /** Default destructor */
        virtual ~TurtleDrawer();
    protected:
    private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture


        // draw the vertex array
        target.draw(m_vertices, states);
    }
        sf::VertexArray m_vertices;
};
typedef std::shared_ptr<TurtleDrawer> SharedTurtleDrawer;
enum ROTATION_STATE
{
    ROTATE_LEFT,ROTATE_RIGHT,NONE
};
#endif // TURTLEDRAWER_H
