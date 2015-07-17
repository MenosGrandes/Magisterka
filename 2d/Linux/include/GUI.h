#ifndef GUI_H
#define GUI_H
#include <memory>
#include <SFGUI/SFGUI.hpp>
#include <SFML/Graphics.hpp>
#include <SFGUI/Widgets.hpp>
#include <TurtleDrawer.h>

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
    void Run();
    void ReRun();

private:
    sfg::Window::Ptr window;
    sfg::Entry::Ptr m_entryIterations,m_entryAngle,m_entryAxiom;
    sfg::Label::Ptr m_labelIterations,m_labelAngle,m_labelAxiom;
    sfg::Adjustment::Ptr m_scaleAngle,m_scaleIterations;
    SharedTurtle m_t;
    SharedTurtleDrawer m_td;
    void OnButtonClick();

    void AngleChange();
    void IterationChange();
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
        void Add(std::string labelA,std::string labelR,sfg::Box::Ptr box)
        {
            entryAxiom = sfg::Entry::Create();
            entryAxiom->SetRequisition( sf::Vector2f( 80.f, 0.f ) );
            labelAxiom=sfg::Label::Create();
            labelAxiom->SetText( labelA );
            box->Pack( labelAxiom );
            box->Pack( entryAxiom );


            entryRule = sfg::Entry::Create();
            entryRule->SetRequisition( sf::Vector2f( 80.f, 0.f ) );

            labelRule=sfg::Label::Create();
            labelRule->SetText( labelR );

            box->Pack( labelRule );
            box->Pack( entryRule );



        }


    };
    typedef std::shared_ptr<RuleAxiom> SharedRuleAxiom;
    typedef std::list<SharedRuleAxiom> SharedRuleAxiomList;
    SharedRuleAxiomList ruleList;

};

typedef std::shared_ptr<GUI> SharedGUI;

#endif // GUI_H
