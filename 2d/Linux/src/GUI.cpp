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
void GUI::AngleChange() {
	std::stringstream sstr;
	sstr << m_scaleAngle->GetValue();
	m_labelAngle->SetText( "Angle: " +sstr.str() );
}
void GUI::IterationChange() {
	std::stringstream sstr;
	sstr << m_scaleIterations->GetValue();
	m_labelIterations->SetText( "Iterations: " +sstr.str() );
}
void GUI::Run()
{



    auto fixed = sfg::Fixed::Create();
    auto m_button = sfg::Button::Create( "S" );
    m_button->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &GUI::OnButtonClick, this ) );
/**
Range for Angle
*/
auto scaleAngle = sfg::Scale::Create( sfg::Scale::Orientation::HORIZONTAL );

	auto scrollbar = sfg::Scrollbar::Create( sfg::Scrollbar::Orientation::VERTICAL );

	m_scaleAngle = scrollbar->GetAdjustment();
	scaleAngle->SetAdjustment( m_scaleAngle );

	m_scaleAngle->SetLower( 0.f );
	m_scaleAngle->SetUpper( 360.f );

	m_scaleAngle->SetMinorStep( 1.f );

	m_scaleAngle->SetMajorStep( 1.f );

	m_scaleAngle->SetPageSize( 0.f );

	m_scaleAngle->GetSignal( sfg::Adjustment::OnChange ).Connect( std::bind( &GUI::AngleChange, this ) );

	scaleAngle->SetRequisition( sf::Vector2f( 80.f, 20.f ) );
/**
Range for iterations
*/
auto scaleIterations = sfg::Scale::Create( sfg::Scale::Orientation::HORIZONTAL );

	auto scrollbar2 = sfg::Scrollbar::Create( sfg::Scrollbar::Orientation::VERTICAL );

	m_scaleIterations = scrollbar2->GetAdjustment();
	scaleIterations->SetAdjustment( m_scaleIterations );

	m_scaleIterations->SetLower( 0.f );
	m_scaleIterations->SetUpper( 10.f );

	m_scaleIterations->SetMinorStep( 1.f );

	m_scaleIterations->SetMajorStep( 1.f );

	m_scaleIterations->SetPageSize( 0.f );

	m_scaleIterations->GetSignal( sfg::Adjustment::OnChange ).Connect( std::bind( &GUI::IterationChange, this ) );

	scaleIterations->SetRequisition( sf::Vector2f( 80.f, 20.f ) );



    auto box = sfg::Box::Create( sfg::Box::Orientation::VERTICAL, 5.0f );

    box->Pack(m_button,false);
//Iterations
    m_entryIterations = sfg::Entry::Create();
    m_entryIterations->SetRequisition( sf::Vector2f( 80.f, 0.f ) );

    m_labelIterations = sfg::Label::Create();
    m_labelIterations->SetText( "Iterations :0" );


    m_entryAngle = sfg::Entry::Create();
    m_entryAngle->SetRequisition( sf::Vector2f( 80.f, 0.f ) );

    m_labelAngle = sfg::Label::Create();
    m_labelAngle->SetText( "Angle :0" );


        m_entryAxiom = sfg::Entry::Create();
    m_entryAxiom->SetRequisition( sf::Vector2f( 80.f, 0.f ) );

    m_labelAxiom = sfg::Label::Create();
    m_labelAxiom->SetText( "Axiom :" );
//    for(int i=0; i<radioButtons.size(); i++)
//    {
//        box->Pack( radioButtons[i], false );
//    }

    box->Pack(fixed);


    box->Pack( m_labelIterations );
	box->Pack( scaleIterations, false, false );
    box->Pack( m_labelAngle );
	box->Pack( scaleAngle, false, false );


    box->Pack( m_labelAxiom );
    box->Pack( m_entryAxiom );






// Create a window and add the box layouter to it. Also set the window's title.
    window= sfg::Window::Create();
    window->SetTitle( "GUI" );
    window->Add( box );
// Create a desktop and add the window to it.

    desktop.Add( window );




}


