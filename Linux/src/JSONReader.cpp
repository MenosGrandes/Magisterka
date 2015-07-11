#include "JSONReader.h"

JSONReader::JSONReader()
{
    //ctor
}

JSONReader::~JSONReader()
{
    //dtor
}
void JSONReader::openJSON(std::string fileName)
{
    FILE* fp = fopen(fileName.c_str(), "rb"); // non-Windows use "r"
    char readBuffer[65536];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    m_d.ParseStream(is);
    fclose(fp);
}
void JSONReader::readJSON()
{
    assert(m_d.HasMember("hello"));
    assert(m_d["hello"].IsString());
}

void JSONReader::saveJSON(std::string fileName)
{
//    m_d.Parse(json);
//// ...
//    FILE* fp = fopen(fileName.c_str(), "wb"); // non-Windows use "w"
//    char writeBuffer[65536];
//    FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
//    Writer<FileWriteStream> writer(os);
//    m_d.Accept(writer);
//    fclose(fp);
}
