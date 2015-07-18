#include "JSONReader.h"

JSONReader::JSONReader()
{
    //ctor
}

JSONReader::~JSONReader()
{
    //dtor
}
void JSONReader::openJSON(const std::string& fileName)
{
    FILE* fp = fopen(fileName.c_str(), "rb"); // non-Windows use "r"
    char readBuffer[65536];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));

doc.ParseStream<0>(is);    fclose(fp);


}
void JSONReader::readJSON()
{
//for (SizeType i = 0; i < doc["l-system"].Size(); i++){
////    printf("{x=%f, y=%s}", doc["l-system"][i]["angle"].GetDouble(), doc["l-system"][i]["name"].GetString());
//  std::cout << doc["l-system"][i]["rules"].GetString() << std::endl;
//}



    const Value& main = doc["list"];


    for (rapidjson::SizeType i = 0; i < main.Size(); i++)
    {
            const Value& l_system = main[i];

        printf("%s \n",l_system["name"].GetString());
                printf("%f \n",l_system["angle"].GetDouble());

        const Value& listOfAxioms=l_system["rules"];
//            for (rapidjson::SizeType i = 0; i < listOfAxioms.Size(); i++)
//            {
//                    const Value& fromTo = listOfAxioms[i];
//
//        printf("%s \n",fromTo["from"].GetString());
//        printf("%s \n",fromTo["to"].GetString());
//            }
    }


//    const Value& rules = main["rules"];
//        const Value& rulee = main["rulee"];


//    // rapidjson uses SizeType instead of size_t.
//    for (rapidjson::SizeType i = 0; i < rulee.Size(); i++)
//    {
//        const Value& fromTo = rulee[i];
//
//        printf("%s \n",fromTo["from"].GetString());
//        printf("%s \n",fromTo["to"].GetString());
//
//    }
//        printf("%s \n",main["name"].GetString());




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
