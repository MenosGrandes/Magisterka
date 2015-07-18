#include "GUI.h"
GUI::GUI(SharedTurtle t, SharedTurtleDrawer td)
{
    m_t=t;
    m_td=td;
}



void GUI::IterationChange()
{
    std::stringstream sstr;
    sstr << m_scaleIterations->GetValue();
    m_labelIterations->SetText( "Iterations: " +sstr.str() );
}
void GUI::OnButtonClick()
{
#ifdef DEBUG
    std::cout<<"CLICKED!\n";
#endif // DEBUG
    ReRun();


}
void GUI::RunAddListFractals()
{

m_boxAddListFractals = sfg::Box::Create( sfg::Box::Orientation::VERTICAL, 5.0f );
SharedJSONReader json(new JSONReader());
json->openJSON("db.json");
json->readJSON();
}
void GUI::RunAddFractals()
{



    auto fixed = sfg::Fixed::Create();
    auto m_button = sfg::Button::Create( "START" );
    m_button->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &GUI::ReRun, this ) );


     m_boxAddFractals = sfg::Box::Create( sfg::Box::Orientation::VERTICAL, 5.0f );


    /*Entry*/
    CreateEntry();

    /*Sliders and Labels to Sliders*/
    SliderPreferences spIterations,spAngle;
    spIterations.label="Iterations :0";
    spIterations.lower=0.f;
    spIterations.upper=20.0f;
    spIterations.minor_step=1.0f;
    spIterations.minor_step=1.0f;
    spIterations.pageSize=0.0f;
    spIterations.requistion=sf::Vector2f( 80.f, 20.f );

    CreateSliders(spIterations);
/*RuleAxiom*/
    SharedRuleAxiom ra(new RuleAxiom());
    ra->Add("Axiom","Rule",1,m_boxAddFractals);
    ruleList.push_back(ra);
    SharedRuleAxiom ra2(new RuleAxiom());
    ra2->Add("Axiom2","Rule2",2,m_boxAddFractals);
    ruleList.push_back(ra2);
    SharedRuleAxiom ra3(new RuleAxiom());
    ra2->Add("Axiom2","Rule2",3,m_boxAddFractals);
    ruleList.push_back(ra3);

    m_boxAddFractals->Pack(m_button,false);
/* Add List*/
RunAddListFractals();
std::cout<<"!!!";
// Create a window and add the box layouter to it. Also set the window's title.
    window= sfg::Window::Create();
    window->SetTitle( "GUI" );
//    window->Add( box );
AddNotebook();
// Create a desktop and add the window to it.

    desktop.Add( window );




}
/**
Rerun the calculations of Turtle and TurtleDrawer
*/
void GUI::ReRun()
{
    m_t->Reset();
    m_t->AddIterations(m_scaleIterations->GetValue());
    SharedRuleAxiomList::iterator it;
    for (it= ruleList.begin(); it != ruleList.end(); it++)
    {
        SharedRule a(new Rule((*it)->entryAxiom->GetText(),(*it)->entryRule->GetText()));
        m_t->AddRule(a);
    }
    m_t->SetResult(m_entryStart->GetText());
    m_t->compute();


    std::string num = m_entryAngle->GetText();
    float angle = ::atof(num.c_str());

    m_td->computeDraw(m_t->GetResult(),10,angle);


}
void GUI::CreateSliders(SliderPreferences sp)
{
    /*Iterations*/
    auto scaleIterations = sfg::Scale::Create( sfg::Scale::Orientation::HORIZONTAL );

    auto scrollbar2 = sfg::Scrollbar::Create( sfg::Scrollbar::Orientation::VERTICAL );

    m_scaleIterations = scrollbar2->GetAdjustment();
    scaleIterations->SetAdjustment( m_scaleIterations );

    m_scaleIterations->SetLower( sp.lower );
    m_scaleIterations->SetUpper( sp.upper);

    m_scaleIterations->SetMinorStep( sp.minor_step );

    m_scaleIterations->SetMajorStep( sp.major_step );

    m_scaleIterations->SetPageSize( sp.pageSize);

    m_scaleIterations->GetSignal( sfg::Adjustment::OnChange ).Connect( std::bind( &GUI::IterationChange, this ) );

    scaleIterations->SetRequisition( sp.requistion );


    m_labelIterations = sfg::Label::Create();
    m_labelIterations->SetText( sp.label );

    m_boxAddFractals->Pack( m_labelIterations );
    m_boxAddFractals->Pack( scaleIterations, false, false );


}

void GUI::CreateEntry()
{
    m_entryStart = sfg::Entry::Create();
    m_entryAngle =sfg::Entry::Create();
    m_entryStart->SetRequisition( sf::Vector2f( 80.f, 0.f ) );
    m_entryAngle->SetRequisition( sf::Vector2f( 80.f, 0.f ) );


    sfg::Label::Ptr labelEntryStart = sfg::Label::Create();
    labelEntryStart->SetText("Start Axiom");

    sfg::Label::Ptr labelAngle = sfg::Label::Create();
    labelAngle->SetText("Angle");

    m_boxAddFractals->Pack( labelEntryStart );
    m_boxAddFractals->Pack(m_entryStart);

    m_boxAddFractals->Pack( labelAngle );


    m_boxAddFractals->Pack(m_entryAngle);
}
void GUI::AddNotebook()
{
m_notebook=sfg::Notebook::Create();
m_notebook->AppendPage( m_boxAddFractals, sfg::Label::Create( "Add new Fractal" ) );
	m_notebook->AppendPage( m_boxAddListFractals, sfg::Label::Create( "L-system List" ) );
window->Add( m_notebook );
}
