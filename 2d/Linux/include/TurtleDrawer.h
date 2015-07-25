#ifndef TURTLEDRAWER_H
#define TURTLEDRAWER_H
#include <SFML/Graphics.hpp>
#include<Turtle.h>
#include <mutex>
class TurtleDrawer :public sf::Drawable, public sf::Transformable
{
public:
    /** Default constructor */
    TurtleDrawer();
    /** Default destructor */
    virtual ~TurtleDrawer();

    unsigned int size();
#ifdef DEBUG
    void show()
    {
        std::cout<<m_vertices.getVertexCount()<<"\n";
        for(int i=0; i<m_vertices.getVertexCount(); i++)
        {
            std::cout<<m_vertices[i].position.x<<" "<<m_vertices[i].position.y<<"\n";
        }
    }
#endif // DEBUG
    void computeDraw(std::string initializer="",unsigned int length=10, float angle=0);

protected:
private:
    sf::VertexArray m_vertices;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        target.draw(m_vertices, states);
    }
    void rotate(sf::Vector2f &origin,float angleOfRotation);
    void translate(sf::Vector2f &origin,sf::Vector2f rotation,float lenght);
    float radToDegree(float degree);
    sf::Color randomColor();
    void computeInThread(std::string initializer="",unsigned int length=10, float angle=0);
    std::mutex drawningMutex;

};
typedef std::shared_ptr<TurtleDrawer> SharedTurtleDrawer;
typedef std::pair<sf::Vector2f,sf::Vector2f> PosRot;

#endif // TURTLEDRAWER_H
