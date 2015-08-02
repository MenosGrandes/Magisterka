#include "GUI.h"
GUI::GUI(SharedTurtle t, SharedTurtleDrawer td)
{
    this->m_t=t;
    this->m_td=td;
    /*
    Add all gui widgets
    */
    this->RunAddFractals();
}


/*Function to get value from slider, and set it at the thext box.*/
void GUI::IterationChange()
{
    std::stringstream sstr;
    sstr << this->m_scaleIterations->GetValue();
    this->m_labelIterations->SetText( "Iterations: " +sstr.str() );
}
/*Start button default click handler.*/
void GUI::OnButtonClick()
{
#ifdef DEBUG
    std::cout<<"CLICKED!\n";
#endif // DEBUG
    std::cout<<" DRAWING\n";
    /*If "START" button was clicked call ReRun function.*/
    ReRun();


}
/*Method to add fractals from the SharedSystem2D std::shared_ptr. SharedSystem2D contains all information about one fractal. GO TO Rule.h */
void GUI::DrawFractalFromList(SharedSystemData2D data)
{
    /*Reset the list of axioms and rules*/
    m_t->Reset();
    /*Set the iterations*/
    m_t->AddIterations(data->iterations);
    /*Loop for all rules in corespondent rule list*/
    SharedRuleList::iterator it;
    for (it= data->ruleList.begin(); it != data->ruleList.end(); it++)
    {

        SharedRule rule(new Rule((*it)->getFrom(),(*it)->getAxiomSet()));

        /*Add SharedRule to the SharedTurtle rule list.*/
        m_t->AddRule(rule);
    }
    /*Set the start string for calculate the l-system.*/
    m_t->SetResult(data->start);
    /*Compute the l-system*/
    m_t->compute();
    /*Draw the output.
    10 -> length of the line (whatever value)*/
    m_td->computeDraw(m_t->GetResult(),10,data->angle);

}
/*Create GUI correspondedt to data in JSON file. JSON file name "db.json" must be in the same directory as the executable.*/
void GUI::RunAddListFractals()
{
    /*Create vertical GUI container*/
    m_boxAddListFractals = sfg::Box::Create( sfg::Box::Orientation::VERTICAL, 5.0f );
    /*Create shared_ptr for JSON manipulations*/
    SharedJSONReader json(new JSONReader());
    /*Open JSON file*/
    json->openJSON("db.json");
    /*Create a list of SharedData2D*/
    SharedSystemData2DList list2dData;
    /*Data is read and return as a list */
    list2dData=json->readJSON();
    /*Iterate through the list*/
    SharedSystemData2DList::iterator it;
    for (it= list2dData.begin(); it != list2dData.end(); it++)
    {
        /*Create the button correspondent to the iterated data.
          The name of button is the name of the l-system.
          The button click event is DrawFractalFromList with "data" value, data is needed for informations about l-system.
          GO TO DrawFractalFromList.
          */
        auto btn = sfg::Button::Create( (*it)->name);
        btn->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &GUI::DrawFractalFromList, this,(*it) ) );
        m_boxAddListFractalsViewport->Pack(btn);
    }


}
/*Create GUI correspondent to manual creator of l-system.*/
void GUI::RunAddFractals()
{
	/* Create the ScrolledWindow.*/
	auto scrolledwindow = sfg::ScrolledWindow::Create();

/* Set the ScrolledWindow to always show the horizontal scrollbar and only show the vertical scrollbar when needed.*/
	scrolledwindow->SetScrollbarPolicy(  sfg::ScrolledWindow::VERTICAL_AUTOMATIC );
/*Box for viewport*/
    m_boxAddListFractalsViewport = sfg::Box::Create( sfg::Box::Orientation::VERTICAL, 5.0f );

/*Add the ScrolledWindow box to the ScrolledWindow and create a new viewport automatically.*/
	scrolledwindow->AddWithViewport( m_boxAddListFractalsViewport );
/* Always remember to set the minimum size of a ScrolledWindow.*/
	scrolledwindow->SetRequisition( sf::Vector2f( 200.f, 600.f ) );

	/* Create the ScrolledWindow.*/
	auto scrolledwindow2 = sfg::ScrolledWindow::Create();

/* Set the ScrolledWindow to always show the horizontal scrollbar and only show the vertical scrollbar when needed.*/
	scrolledwindow2->SetScrollbarPolicy(  sfg::ScrolledWindow::VERTICAL_AUTOMATIC );
/*Box for viewport*/
    m_boxAddFractalsViewport = sfg::Box::Create( sfg::Box::Orientation::VERTICAL, 5.0f );

/*Add the ScrolledWindow box to the ScrolledWindow and create a new viewport automatically.*/
	scrolledwindow2->AddWithViewport( m_boxAddFractalsViewport );
/* Always remember to set the minimum size of a ScrolledWindow.*/
	scrolledwindow2->SetRequisition( sf::Vector2f( 200.f, 600.f ) );
	/*Add RUle Button*/
    auto m_button_addRule = sfg::Button::Create( "Add rule" );
    /*Click event for button is ReRun methos*/
    m_button_addRule->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &GUI::AddRule, this ) );


    auto fixed = sfg::Fixed::Create();
    /*Create button to START the calculations*/
    auto m_button = sfg::Button::Create( "START" );
    /*Click event for button is ReRun methos*/
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

    /*Add START button.*/
    m_boxAddFractalsViewport->Pack(m_button,false);
    m_boxAddFractalsViewport->Pack(m_button_addRule,false);
    /* Add List*/
    RunAddListFractals();

for(int i=0;i<0;i++){
     SharedRuleAxiomGUI ra(new RuleAxiomGUI());
    ra->Add("Axiom","Rule",i,m_boxAddFractalsViewport);
}




    /* Create a window and add the box layouter to it. Also set the window's title.*/
    window= sfg::Window::Create();
    window->SetTitle( "GUI" );
    /**/
    m_boxAddListFractals->Pack(scrolledwindow,false,true);
    m_boxAddFractals->Pack(scrolledwindow2,false,true);
    /*Add notebook pages*/
    AddNotebook();
    /* Create a desktop and add the window to it.*/
    desktop.Add( window );
}
void GUI::AddRule()
{
static int counter=0;
counter++;
 SharedRuleAxiomGUI ra(new RuleAxiomGUI());
    ra->Add("Axiom","Rule",counter,m_boxAddFractalsViewport);
//    ruleList.push_back(ra);
}
/*
Rerun the calculations of Turtle and TurtleDrawer
*/
void GUI::ReRun()
{
//#ifdef DEBUG
//    std::cout<<ruleList.size()<<" rule list size\n";
//#endif // DEBUG
//    m_t->Reset();
//    m_t->AddIterations(m_scaleIterations->GetValue());
//    SharedRuleAxiomListGUI::iterator it;
//    for (it= ruleList.begin(); it != ruleList.end(); it++)
//    {
//        SharedRule a(new Rule((*it)->entryAxiom->GetText(),(*it)->entryRule->GetText(),100));
//#ifdef DEBUG
//        std::cout<<a->getFrom()<<" to "<<a->getTo()<<" "<<a->getProbability();
//#endif // DEBUG
//        m_t->AddRule(a);
//    }
//    m_t->SetResult(m_entryStart->GetText());
//    m_t->compute();
//
//
//    std::string num = m_entryAngle->GetText();
//#ifdef DEBUG
//    std::cout<<(std::string)m_t->GetResult()<<" string \n";
//#endif // DEBUG
//    float angle = ::atof(num.c_str());
//
//    m_td->computeDraw(m_t->GetResult(),10,angle);
//

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

    m_boxAddFractalsViewport->Pack( m_labelIterations );
    m_boxAddFractalsViewport->Pack( scaleIterations, false, false );


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

    m_boxAddFractalsViewport->Pack( labelEntryStart );
    m_boxAddFractalsViewport->Pack(m_entryStart);

    m_boxAddFractalsViewport->Pack( labelAngle );


    m_boxAddFractalsViewport->Pack(m_entryAngle);
}
void GUI::AddNotebook()
{



    m_notebook=sfg::Notebook::Create();
    m_notebook->AppendPage( m_boxAddFractals, sfg::Label::Create( "Add new Fractal" ) );
    m_notebook->AppendPage( m_boxAddListFractals, sfg::Label::Create( "L-system List" ) );
    window->Add( m_notebook );
}
