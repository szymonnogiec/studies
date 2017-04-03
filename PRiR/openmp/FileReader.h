//
// Created by simon on 06.03.17.
//

#ifndef PRIR_FILEREADER_H
#define PRIR_FILEREADER_H

//std includes
#include <fstream>
#include <string>
#include <iterator>
#include <vector>
#include <sstream>
#include <array>

class FileReader
{
public:
    FileReader();
    ~FileReader();

    void setInputFilename (const std::string& inputFilename);
    void setOutputFilename (const std::string& outputFilename);
    const std::string& getOutputFilename () const { return outputMsgFilename_; };
    const std::string& getInputFilename () const { return inputMsgFilename_; };
    bool readInput ();
    const std::string& getInputMsg () const { return inputMsg_; };
    bool writeToOutput (const std::string& msg);

    bool writeToOutput (const std::vector<int>& encodedDigits);
    bool writeToHelperOutput (int number);
    std::vector<int> toIntsVector (const std::string& input);
private:
    int toInt (const std::string& input);
    std::string inputMsgFilename_;
    std::string outputMsgFilename_;

    std::string helperOutputFilename_;
    std::fstream helperOutput_;
    std::string inputMsg_;
};


#endif //PRIR_FILEREADER_H
