//
// Created by simon on 06.03.17.
//

#include <iostream>
#include "RSA.h"

RSA::RSA(FileReader& fileReader) : publicKeyParams (std::make_pair(11, 899)),
             privateKeyParams (std::make_pair(611, 899)),
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
        std::cout << std::string ("*", 50) << std::endl;
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
        std::cout << std::string ("*", 50) << std::endl;
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

    //casting to double for std::pow function
    double charDigitDb = static_cast<double>(charDigit);
    double eDb = static_cast<double>(publicKeyParams.first);
    long long power = static_cast<long long>(std::pow (charDigitDb, eDb));
    int result = static_cast<int> (power % publicKeyParams.second);

    return result;
}

char RSA::decodeChar (int number)
{
    int decodedNumber = calculatePowerMod (number, privateKeyParams.first,
    privateKeyParams.second);
    //move

    if (decodedNumber == 0)
        return char (' ');
    decodedNumber += charsMovement_;
    return static_cast<char>(decodedNumber);
}

int RSA::calculatePowerMod(int c, int d, int n)
{
    if (d == 1)
        return c;
    int rest = d % 2;
    if (rest == 0)
    {
        long newBase = static_cast<long>(std::sqrt (c)) % n;
        return newBase * calculatePowerMod (c, d/2, n);
    }
    else
    {
        long newBase = static_cast<long>(std::sqrt(c)) % n;
        newBase *= c;
        return newBase * calculatePowerMod (c, (d/2) - 1, n);
    }
}