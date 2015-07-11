#include "GUI.h"

void GUI::OnRadioButtonClick()
{
    for(int i=0; i<radioButtons.size(); i++)
    {
        if( radioButtons[i]->IsActive() )
        {
            //window->SetStyle( window->GetStyle() ^ sfg::Window::TITLEBAR );

        }
    }
}
void GUI::OnButtonClick()
{
std::cout<<"Clicked!";
}
void GUI::ButtonToggle()
{
std::cout<<"toogled!";

}
void GUI::Run()
{



    auto fixed = sfg::Fixed::Create();
    auto m_button = sfg::Button::Create( "Start" );
    m_button->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &GUI::OnButtonClick, this ) );

// Create the label.

    label = sfg::Label::Create( "Path Find Algorithms" );
    pathLenth=sfg::Label::Create("Path Lenth ");
    timeLast=sfg::Label::Create("Time[us] ");
    openNodesCount=sfg::Label::Create("All nodes searched : ");
    m_toggle_button=sfg::ToggleButton::Create("Tie Breaker");

    fixed->Put(m_toggle_button, sf::Vector2f(10,10));

// Create a simple button and connect the click signal.



    m_toggle_button->GetSignal( sfg::ToggleButton::OnToggle ).Connect( std::bind( &GUI::ButtonToggle, this ) );
    sfg::RadioButton::Ptr button = sfg::RadioButton::Create( "Manhattan" );
    button->GetSignal( sfg::ToggleButton::OnToggle ).Connect( std::bind( &GUI::OnRadioButtonClick, this ) );
    radioButtons.push_back(button);


    sfg::RadioButton::Ptr button2 = sfg::RadioButton::Create( "Chebyszev",radioButtons[0]->GetGroup() );
    button2->GetSignal( sfg::ToggleButton::OnToggle ).Connect( std::bind( &GUI::OnRadioButtonClick, this ) );
    radioButtons.push_back(button2);

    sfg::RadioButton::Ptr button3 = sfg::RadioButton::Create( "Diagonal",radioButtons[0]->GetGroup() );
    button3->GetSignal( sfg::ToggleButton::OnToggle ).Connect( std::bind( &GUI::OnRadioButtonClick, this ) );
    radioButtons.push_back(button3);

    sfg::RadioButton::Ptr button4 = sfg::RadioButton::Create( "BFS",radioButtons[0]->GetGroup() );
    button4->GetSignal( sfg::ToggleButton::OnToggle ).Connect( std::bind( &GUI::OnRadioButtonClick, this ) );
    radioButtons.push_back(button4);
    sfg::RadioButton::Ptr button5 = sfg::RadioButton::Create( "DFS",radioButtons[0]->GetGroup() );
    button5->GetSignal( sfg::ToggleButton::OnToggle ).Connect( std::bind( &GUI::OnRadioButtonClick, this ) );
    radioButtons.push_back(button5);
    sfg::RadioButton::Ptr button6 = sfg::RadioButton::Create( "DIJKSTRA",radioButtons[0]->GetGroup() );
    button6->GetSignal( sfg::ToggleButton::OnToggle ).Connect( std::bind( &GUI::OnRadioButtonClick, this ) );
    radioButtons.push_back(button6);
    radioButtons[0]->SetActive( true );
// Create a vertical box layouter with 5 pixels spacing and add the label
// and button to it.
    auto box = sfg::Box::Create( sfg::Box::Orientation::VERTICAL, 5.0f );

    box->Pack(m_button,false);
    for(int i=0; i<radioButtons.size(); i++)
    {
        box->Pack( radioButtons[i], false );
    }
    box->Pack(fixed);

    box->Pack( label );
    box->Pack(pathLenth);
    box->Pack(timeLast);
    box->Pack(openNodesCount);



// Create a window and add the box layouter to it. Also set the window's title.
    window= sfg::Window::Create();
    window->SetTitle( "GUI" );
    window->Add( box );
// Create a desktop and add the window to it.

    desktop.Add( window );




}
