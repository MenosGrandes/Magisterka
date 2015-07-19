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

    doc.ParseStream<0>(is);
    fclose(fp);


}
SystemData2DList JSONReader::readJSON()
{
/*Container of Data2D*/
    SystemData2DList dataList;

    /*Get main name from JSON*/
    const Value& main = doc["list"];

    /* Its an Array so iterate through it*/
    for (rapidjson::SizeType i = 0; i < main.Size(); i++)
    {




        /*Get every object from array*/
        const Value& l_system = main[i];

            SystemData2D data;
    data.name=l_system["name"].GetString();
    data.iterations=static_cast<int>(l_system["iterations"].GetDouble());
    data.angle=l_system["angle"].GetDouble();
//        /*Get it's name*/
//        printf("name :%s \n",l_system["name"].GetString());
//        /*Get it's angle*/
//        printf("angle :%f \n",l_system["angle"].GetDouble());
//        /*Get it's iterations*/
//        printf("iter :%f \n",l_system["iterations"].GetDouble());
        /*Get another array inside the main array.*/
        const Value& listOfAxioms=l_system["rules"];

        SharedRuleList ruleList;

        /*Iterate through the second array(array in array)*/
        for (rapidjson::SizeType i = 0; i < listOfAxioms.Size(); i++)
        {

            /*Get object from the array*/
            const Value& fromTo = listOfAxioms[i];
            /*Get "from" and "to" axioms*/
//            printf("%s \n",fromTo["from"].GetString());
//            printf("%s \n",fromTo["to"].GetString());
            SharedRule rule(new Rule(fromTo["from"].GetString(),fromTo["to"].GetString()));
            ruleList.push_back(rule);
        }
        data.ruleList=ruleList;
        dataList.push_back(data);
    }
return dataList;

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
