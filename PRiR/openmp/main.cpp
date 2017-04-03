//local includes
#include "FileReader.h"
#include "RSA.h"

//openmp includes
#include <omp.h>

//std includes
#include <iostream>

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
    if (argc != 5)
    {
        printUsage();
        return -1;
    }
    std::string inputFile = std::string (argv[1]);
    std::string outputFile = std::string (argv [2]);
    std::string encodeParam = argv [3];
    int numberOfThreads = std::atoi(argv [4]);
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


    //options
    omp_set_num_threads (numberOfThreads);

    double startTime = omp_get_wtime();
    if (enc)
    {
        rsa.encode();
    }
    else
    {
        rsa.decode();
    }
    double endTime = omp_get_wtime();

    std::cout << "Time elapsed: " << (endTime - startTime) << " sec" << std::endl;
    return 0;
}