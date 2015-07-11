#ifndef JSONREADER_H
#define JSONREADER_H
#include <string>
#include "rapidjson/filereadstream.h"
#include <rapidjson/document.h>
using namespace rapidjson;

class JSONReader
{
    public:
        JSONReader();
        virtual ~JSONReader();
        void openJSON(std::string fileName);
        void readJSON();
        void saveJSON(std::string fileName);
    protected:
    private:
    Document m_d;
};

#endif // JSONREADER_H
