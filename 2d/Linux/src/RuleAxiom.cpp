#include <RuleAxiom.h>
void RuleAxiom::Add(std::string labelA,std::string labelR,int number,sfg::Box::Ptr box)
{
    std::stringstream ss;
    std::string numberString;
    ss << number;
    ss >> numberString;

    auto separator = sfg::Separator::Create( sfg::Separator::Orientation::HORIZONTAL );
    box->Pack( separator, false, true );
    auto alignment_box = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL );

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
    auto frame = sfg::Frame::Create( "Rule "+numberString );
    frame->SetAlignment( sf::Vector2f( .3f, .3f ) );
    frame->Add( alignment_box );
    box->Pack( frame, true, true );


}
