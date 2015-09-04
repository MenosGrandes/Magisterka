#ifndef CONTEXTAXIOM_H
#define CONTEXTTAXIOM_H
#include <memory>
#include <string>

enum BIGGERLOWER
{
    BIGGER,LOWER
};

class ContextAxiom2L
{
public :
    ContextAxiom2L(std::string preceded,std::string fallowed,std::string to)
    {
        this->m_preceded=preceded;
        this->m_fallowed=fallowed;
        this->m_to=to;
    };
    void set_m_preceded(std::string preceded)
    {
        this->m_preceded=preceded;
    };
    void set_m_fallowed(std::string fallowed)
    {
        this->m_fallowed=fallowed;
    };
    void set_m_to(std::string to)
    {
        this->m_to=to;
    };
    std::string get_m_preceded()
    {
        return m_preceded;
    };
    std::string get_m_fallowed()
    {
        return m_fallowed;
    };
    std::string get_m_to()
    {
        return m_to;
    };


private :
    std::string m_preceded;
    std::string m_fallowed;
    std::string m_to;
};
class ContextAxiom1L
{
public :
    ContextAxiom1L(std::string pre_fall_ed,BIGGERLOWER sign)
    {
        this->m_pre_fall_ed=pre_fall_ed;
        this->m_sign=sign;
    };
    void set_m_pre_fall_ed(std::string pre_fall_ed)
    {
        this->m_pre_fall_ed=pre_fall_ed;
    }
    void set_sign(BIGGERLOWER sign)
    {
        this->m_sign=sign;
    }
private :
    std::string m_pre_fall_ed;
    BIGGERLOWER m_sign;
};
typedef std::shared_ptr<ContextAxiom2L> SharedContextAxiom2L;
typedef std::vector<SharedContextAxiom2L>SharedContextAxiomVector2L;

#endif // CONTEXT_H
