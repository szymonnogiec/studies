//local includes
#include "FileReader.h"
#include "RSA.h"

void printUsage ()
{

}

bool encode (std::string msg)
{
    char enc = std::tolower(msg.at(0));
    if (enc == 'e')
        return true;
    else
        return false;
}
int main(int argc, char* argv [])
{
    if (argc != 4)
    {
        printUsage();
        return -1;
    }
    std::string inputFile = std::string (argv[1]);
    std::string outputFile = std::string (argv [2]);
    std::string encodeParam = argv [3];

    if (encodeParam.size() != 1)
    {
        printUsage();
        return -2;
    }
    bool enc = encode (encodeParam);

    FileReader fileReader;
    fileReader.setInputFilename (inputFile);
    fileReader.setOutputFilename (outputFile);
    RSA rsa (fileReader);

    if (enc)
    {
        rsa.encode();
    }
    else
    {
        rsa.decode();
    }

    return 0;
}