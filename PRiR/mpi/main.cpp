//local includes
#include "FileReader.h"
#include "RSA.h"

//std includes
#include <iostream>

//mpi includes
#include <mpi.h>

void printUsage ()
{
    std::cout << std::endl;
    std::cout << "Usage: ./program inputFilename outputFilename [e|d] [numberOfThreads]" << std::endl;
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
    MPI_Init(nullptr, nullptr);

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

    MPI_Finalize();
    return 0;
}