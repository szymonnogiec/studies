//
// Created by simon on 06.03.17.
//

#include "FileReader.h"

FileReader::FileReader() : inputMsgFilename_ ("msg"), outputMsgFilename_ ("ciphered")
{
}

FileReader::~FileReader ()
{
}

void FileReader::setInputFilename(const std::string &inputFilename)
{
    inputMsgFilename_ = inputFilename;
}

void FileReader::setOutputFilename(const std::string &outputFilename)
{
    outputMsgFilename_ = outputFilename;
}

bool FileReader::writeToOutput(const std::string &msg)
{
    return false;
}

bool FileReader::readInput()
{
    return false;
}
