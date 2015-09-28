#ifndef AXIOM_H
#define AXIOM_H
#include <string>

class Axiom
{
public:
    Axiom(std::string to);
    virtual ~Axiom();
    std::string get_to();
    void set_to(std::string to);
protected:
    std::string _to;
private:

};

#endif // AXIOM_H
