#ifndef GUI_H
#define GUI_H
#include <memory>
#include <SFGUI/SFGUI.hpp>
#include <SFML/Graphics.hpp>
#include <SFGUI/Widgets.hpp>
#include <TurtleDrawer.h>
#include <JSONReader.h>

typedef std::vector<sfg::Entry::Ptr> EntryVector;
typedef std::vector<sfg::Label::Ptr> LabelVector;

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
    /**
    Class that contains 2 sfg::Entry::Ptr :
    rule  -> to contain the rule.
    axiom -> to contain the axiom.
    and 2 sfg::Label::Ptr for those entry.
    */
    class RuleAxiom
    {
    public :
        sfg::Entry::Ptr entryAxiom,entryRule;
        sfg::Label::Ptr labelRule,labelAxiom;
        void Add(std::string labelA,std::string labelR,int number,sfg::Box::Ptr box)
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


    };
    typedef std::shared_ptr<RuleAxiom> SharedRuleAxiom;
    typedef std::list<SharedRuleAxiom> SharedRuleAxiomList;
    SharedRuleAxiomList ruleList;


};

typedef std::shared_ptr<GUI> SharedGUI;

#endif // GUI_H
