//
// Created by simon on 06.03.17.
//

#include <iostream>
#include "RSA.h"

RSA::RSA(FileReader& fileReader) : publicKeyParams (std::make_pair(11, 6721)),
             privateKeyParams (std::make_pair(611, 6721)),
                                   fileReader_ (fileReader),
                                   charsMovement_ (96)
{

}

RSA::~RSA()
{

}

int RSA::toNumber(char c)
{
    if (std::isspace(c))
        return 0;

    int lower = std::tolower(c);
    //not a-z letter
    if (lower < 97 || lower > 122)
        return -1;

    // movement of chars
    return (lower - charsMovement_);
}

bool RSA::decode()
{
    fileReader_.readInput();
    std::vector<int> encodedNumbers =
            fileReader_.toIntsVector (fileReader_.getInputMsg());
    std::string decodedMsg;
    for (int encodedDigit : encodedNumbers)
    {
        decodedMsg.push_back (decodeChar (encodedDigit));
    }

    bool writeSuccessful = fileReader_.writeToOutput (decodedMsg);
    if (writeSuccessful)
    {
        std::cout << std::string (50, '*') << std::endl;
        std::cout << "Decoded digits has been "
                "successfully written to output file " <<
                  fileReader_.getOutputFilename() << std::endl;
    }
    return writeSuccessful;
}

bool RSA::encode()
{
    fileReader_.readInput();
    const std::string msgToEncode = fileReader_.getInputMsg();
    std::vector<int> encodedChars;
    for (auto cChar : msgToEncode)
    {
        encodedChars.push_back (encodeChar(cChar));
    }
    bool writeSuccessful = fileReader_.writeToOutput (encodedChars);
    if (writeSuccessful)
    {
        std::cout << std::string (50, '*') << std::endl;
        std::cout << "Encoded digits has been "
        "successfully written to output file " <<
                  fileReader_.getOutputFilename() << std::endl;
    }
    return writeSuccessful;
}

int RSA::encodeChar(char c)
{
    int charDigit = toNumber (c);
    if (charDigit == -1)
        return charDigit;

    fileReader_.writeToHelperOutput (charDigit);

    int c = calculatePowerMod(charDigit, publicKeyParams.first,
    publicKeyParams.second);
    /*double power = static_cast<double>(publicKeyParams.first);
    double base = static_cast<double>(charDigit);
    long long le = static_cast<long long>(std::pow (base, power));
    int result = le % publicKeyParams.second;*/
	int result = c % publicKeyParams.second;
    return result;
}

char RSA::decodeChar (int number)
{
    int cd = calculatePowerMod (number, privateKeyParams.first,
    privateKeyParams.second);
    int decodedNumber = cd % privateKeyParams.second;
    //move

    if (decodedNumber == 0)
        return char (' ');

    decodedNumber += charsMovement_;
    return static_cast<char>(decodedNumber);
}

long long RSA::calculatePowerMod(int c, int d, int n)
{
    if (d == 1)
        return c;

    int rest = d % 2;
    if (rest == 0)
    {
        int newBase = static_cast<int>(std::sqrt (c)) % n;
        int newD = d/2;
        return calculatePowerMod (newBase, newD, n);
    }
    else
    {
        int newBase = static_cast<int>(std::sqrt(c)) % n;
        int newD = (d-1)/2;

        return c * calculatePowerMod (newBase, newD, n);
    }
}
