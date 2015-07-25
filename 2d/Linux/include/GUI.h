#ifndef GUI_H
#define GUI_H
#include <SFML/Graphics.hpp>
#include <TurtleDrawer.h>
#include <JSONReader.h>
#include <RuleAxiomGUI.h>
#include <mutex>

class GUI
{
public:
// Our button click handler.
/*M_SFGUI is needed to create main actions witch gui*/
    sfg::SFGUI m_sfgui;

/*SFGUI Desktop used to create a desktop*/
    sfg::Desktop desktop;
/*Constructor using SharedTurtle and SharedTurtleDrawer to compute turtle graphics*/
    GUI(SharedTurtle t,SharedTurtleDrawer td);


private:
    /*Struct that contains the preferences for sliders*/

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
    void RunAddFractals();
    void RunAddListFractals();

    void ReRun();
    SharedRuleAxiomListGUI ruleList;


};

typedef std::shared_ptr<GUI> SharedGUI;

#endif // GUI_H
