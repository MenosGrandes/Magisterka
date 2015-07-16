#ifndef GUI_H
#define GUI_H
#include <memory>
#include <SFGUI/SFGUI.hpp>
#include <SFML/Graphics.hpp>
#include <SFGUI/Widgets.hpp>
class GUI
{
public:
// Our button click handler.
    sfg::SFGUI m_sfgui;
    sfg::Label::Ptr label;
    sfg::Desktop desktop;

    void Run();

private:
    std::vector<sfg::RadioButton::Ptr> radioButtons;
    sfg::Window::Ptr window;
	sfg::Entry::Ptr m_entryIterations,m_entryAngle,m_entryAxiom;
	    sfg::Label::Ptr m_labelIterations,m_labelAngle,m_labelAxiom;
	sfg::Adjustment::Ptr m_scaleAngle,m_scaleIterations;
    void OnButtonClick();
    void ButtonToggle();
    void OnRadioButtonClick();
    void AngleChange();
    void IterationChange();

};
typedef std::shared_ptr<GUI> SharedGUI;

#endif // GUI_H
