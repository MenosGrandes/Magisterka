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
SharedSystemData2DList JSONReader::readJSON()
{
    /*Container of Data2D*/
    SharedSystemData2DList dataList;

    /*Get main name from JSON*/
    const Value& main = doc["list"];

    /* Its an Array so iterate through it*/
    for (rapidjson::SizeType i = 0; i < main.Size(); i++)
    {

        /*Get every object from array*/
        const Value& l_system = main[i];
        /*struct to contain data from json*/
        SystemData2D data;
        /*Get it's name*/
        data.name=l_system["name"].GetString();

        /*Get it's start string*/
        data.start=l_system["start"].GetString();

        /*Get it's iterations*/
        data.iterations=static_cast<int>(l_system["iterations"].GetDouble());

        /*Get it's angle*/
        data.angle=l_system["angle"].GetDouble();

        /*Get another array inside the main array.*/
        const Value& listOfAxioms=l_system["rules"];
        /*Get ignore signs for ContextAxioms*/


                const Value& ignore_list = l_system["ignore"];
                for (rapidjson::SizeType i = 0; i < ignore_list.Size(); i++)
                {
                data.ignore_list.push_back(ignore_list[i].GetString());
                }

        /*List of rules*/
        SharedRuleList ruleList;

        /*Iterate through the second array(array in array)*/
        for (rapidjson::SizeType i = 0; i < listOfAxioms.Size(); i++)
        {

            SharedProbabilityAxiomVector probabilityAxiomSet;
            SharedContextAxiomVector2L contextAxiomSet;
            /*Get object from the array*/
            const Value& from = listOfAxioms[i];

            const Value& axiomsProbability = from["listProbability"];
            for (rapidjson::SizeType i = 0; i < axiomsProbability.Size(); i++)
            {
                const Value& axiom = axiomsProbability[i];
                SharedProbabilityAxiom probabilityAxiom(new ProbabilityAxiom(axiom["to"].GetString(),axiom["probability"].GetDouble()));
                probabilityAxiomSet.push_back(probabilityAxiom);
            }
            const Value& axiomsContext = from["listContext"];
            for (rapidjson::SizeType i = 0; i < axiomsContext.Size(); i++)
            {
                const Value& axiom = axiomsContext[i];

                SharedContextAxiom2L contextAxiom(new ContextAxiom2L (axiom["preceded"].GetString(),axiom["fallowed"].GetString(),axiom["to"].GetString()));

                contextAxiomSet.push_back(contextAxiom);
            }
            SharedContextProbabilityAxiomSet axioms(new ContextProbabilityAxiomSet(contextAxiomSet,probabilityAxiomSet));

            SharedRule rule(new Rule(from["from"].GetString(),axioms));
            ruleList.push_back(rule);

        }
        data.ruleList=ruleList;
        SharedSystemData2D dataShared=std::make_shared<SystemData2D>(data);
        dataList.push_back(dataShared);

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
