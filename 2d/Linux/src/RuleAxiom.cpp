#include <RuleAxiom.h>
void RuleAxiomGUI::Add(std::string labelA,std::string labelR,int number,sfg::Box::Ptr box)
{
    std::stringstream ss;
    std::string numberString;
    ss << number;
    ss >> numberString;
    /*Create Separator */
    auto separator = sfg::Separator::Create( sfg::Separator::Orientation::HORIZONTAL );
    /*Add separator to Box*/
    box->Pack( separator, false, true );

    auto alignment_box = sfg::Box::Create( sfg::Box::Orientation::VERTICAL );

    entryAxiom = sfg::Entry::Create();
    entryAxiom->SetRequisition( sf::Vector2f( 80.f, 0.f ) );
    labelAxiom=sfg::Label::Create();
    labelAxiom->SetText( labelA );


    entryRule = sfg::Entry::Create();
    entryRule->SetRequisition( sf::Vector2f( 80.f, 0.f ) );

    labelRule=sfg::Label::Create();
    labelRule->SetText( labelR );


    alignment_box->Pack(labelAxiom);
    alignment_box->Pack(entryAxiom);
    alignment_box->Pack(labelRule);
    alignment_box->Pack(entryRule);


    /*Sliders Probability*/
    auto scaleProbability = sfg::Scale::Create( sfg::Scale::Orientation::HORIZONTAL );

    auto scrollbar2 = sfg::Scrollbar::Create( sfg::Scrollbar::Orientation::VERTICAL );

    probabilityOfAxiom = scrollbar2->GetAdjustment();
    scaleProbability->SetAdjustment( probabilityOfAxiom );

    probabilityOfAxiom->SetLower( 0);
    probabilityOfAxiom->SetUpper( 100);

    probabilityOfAxiom->SetMinorStep( 1 );

    probabilityOfAxiom->SetMajorStep( 1 );

    probabilityOfAxiom->SetPageSize(0.0f);

    probabilityOfAxiom->GetSignal( sfg::Adjustment::OnChange ).Connect( std::bind( &RuleAxiomGUI::ProbabilityChange, this ) );

    scaleProbability->SetRequisition( sf::Vector2f( 80.f, 20.f ));


    labelProbabilityOfAxiom = sfg::Label::Create();
    labelProbabilityOfAxiom->SetText( "Probability: 0%" );

    alignment_box->Pack( labelProbabilityOfAxiom );
    alignment_box->Pack( scaleProbability, false, false );


    auto frame = sfg::Frame::Create( "Rule "+numberString );
    frame->SetAlignment( sf::Vector2f( .3f, .3f ) );
    frame->Add( alignment_box );
    box->Pack( frame, true, true );
}
void RuleAxiomGUI::ProbabilityChange()
{
    std::stringstream sstr;
    sstr << this->probabilityOfAxiom->GetValue();
    this->labelProbabilityOfAxiom->SetText( "Probability: " +sstr.str()+"%" );
}
