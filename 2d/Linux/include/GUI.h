#ifndef GUI_H
#define GUI_H
#include <SFML/Graphics.hpp>
#include <TurtleDrawer.h>
#include <JSONReader.h>
#include <RuleAxiom.h>

class GUI
{
public:
// Our button click handler.
    sfg::SFGUI m_sfgui;
    sfg::Label::Ptr label;
    sfg::Desktop desktop;
    GUI(SharedTurtle t,SharedTurtleDrawer td);
    void RunAddFractals();
    void RunAddListFractals();

    void ReRun();

private:
    /*Struct that contains the preferences for sliders*/
    struct SliderPreferences
    {
        float lower=0.0f;
        float upper=10.0f;
        float minor_step=0.1f;
        float major_step=1.0f;
        float pageSize=0.0f;
        sf::Vector2f requistion =sf::Vector2f( 80.f, 20.f );
        std::string label="";
    };




    sfg::Window::Ptr window;
    sfg::Label::Ptr m_labelIterations,m_labelAngle,m_labelStartAxiom ;
    sfg::Adjustment::Ptr m_scaleIterations;
    sfg::Entry::Ptr m_entryStart,m_entryAngle;
    sfg::Notebook::Ptr m_notebook;
    sfg::Box::Ptr m_boxAddFractals,m_boxAddListFractals;
    SharedTurtle m_t;
    SharedTurtleDrawer m_td;
    void OnButtonClick();

    void AngleChange();
    void IterationChange();
    void CreateSliders(SliderPreferences sp);
    void CreateEntry();
    void AddNotebook();
    void DrawFractalFromList(SharedSystemData2D data);

    SharedRuleAxiomList ruleList;


};

typedef std::shared_ptr<GUI> SharedGUI;

#endif // GUI_H
