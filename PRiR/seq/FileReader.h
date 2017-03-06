//
// Created by simon on 06.03.17.
//

#ifndef PRIR_FILEREADER_H
#define PRIR_FILEREADER_H

//std includes
#include <fstream>
#include <string>

class FileReader
{
public:
    FileReader();
    ~FileReader();

    void setInputFilename (const std::string& inputFilename);
    void setOutputFilename (const std::string& outputFilename);
    bool readInput ();
    bool writeToOutput (const std::string& msg);

private:
    std::string inputMsgFilename_;
    std::string outputMsgFilename_;

};


#endif //PRIR_FILEREADER_H
