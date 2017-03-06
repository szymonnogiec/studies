//
// Created by simon on 06.03.17.
//

#include "RSA.h"

RSA::RSA(FileReader& fileReader) : publicKeyParams (std::make_pair(11, 899)),
             privateKeyParams (std::make_pair(611, 899)), fileReader_ (fileReader)
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

    return lower;
}
