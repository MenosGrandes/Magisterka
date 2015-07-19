#ifndef JSONREADER_H
#define JSONREADER_H
#include <string>
#include <memory>
#include <iostream>
#include <rapidjson/filereadstream.h>
#include <rapidjson/document.h>
#include <sstream>
#include <fstream>
#include <GUI.h>
using namespace rapidjson;

class JSONReader
{
    public:
        JSONReader();
        virtual ~JSONReader();
        void openJSON(const std::string& filename);
        SystemData2DList readJSON();
        void saveJSON(std::string fileName);
        Document doc;



    protected:
    private:

};
typedef std::shared_ptr<JSONReader> SharedJSONReader;

#endif // JSONREADER_H
