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
    sfg::Label::Ptr pathLenth,timeLast,openNodesCount;

private:
    std::vector<sfg::RadioButton::Ptr> radioButtons;
    sfg::Window::Ptr window;
    sfg::ToggleButton::Ptr m_toggle_button;

    void OnButtonClick();
    void ButtonToggle();
    void OnRadioButtonClick();

};
typedef std::shared_ptr<GUI> SharedGUI;

#endif // GUI_H
