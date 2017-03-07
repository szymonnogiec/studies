//
// Created by simon on 06.03.17.
//

#include "FileReader.h"

FileReader::FileReader() : inputMsgFilename_ ("msg"), outputMsgFilename_ ("ciphered"),
                           helperOutputFilename_ ("beforeEncoding")
{
    helperOutput_.open (helperOutputFilename_, std::fstream::out | std::fstream::trunc);
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
    std::fstream outputFile;
    outputFile.open (outputMsgFilename_,
                     std::fstream::out | std::fstream::trunc);

    if (outputFile.is_open())
    {
        outputFile << msg;
        outputFile.close();
        return true;
    }
    return false;
}

bool FileReader::readInput()
{
    std::fstream inputFile;
    inputFile.open (inputMsgFilename_, std::fstream::in);

    if (inputFile.is_open())
    {
        inputMsg_ = std::string
                (std::istreambuf_iterator<char>{inputFile}, {});
        return true;
    }
    return false;
}

bool FileReader::writeToOutput(const std::vector<int>& encodedDigits)
{
    //digits separated with spaces
    std::string outputString;
    for (auto it = encodedDigits.begin();
            it != encodedDigits.end(); ++it)
    {
        outputString.append (std::to_string(*it));
        //append space up to the last digit
        if ((it+1) != encodedDigits.end())
        {
            outputString.append(" ");
        }
    }
    return writeToOutput (outputString);
}

bool FileReader::writeToHelperOutput (int number)
{
    if (helperOutput_.is_open())
    {
        helperOutput_ << std::to_string(number) << " ";
        return true;
    }
    return false;
}

std::vector<int> FileReader::toIntsVector(const std::string& input)
{
    std::vector<int> returnContainer;
    //split string to vector of strings
    std::istringstream ss (input);
    std::vector<std::string> splitedStrings;
    std::copy(std::istream_iterator <std::string>(ss),
    std::istream_iterator<std::string>(),
    std::back_inserter (splitedStrings));

    for (const std::string& str : splitedStrings)
    {
        returnContainer.push_back (toInt (str));
    }
    return returnContainer;
}

int FileReader::toInt(const std::string& input)
{
    return std::atoi (input.c_str());
}
