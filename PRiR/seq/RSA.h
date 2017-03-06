//
// Created by simon on 06.03.17.
//

#ifndef PRIR_RSA_H
#define PRIR_RSA_H

//std includes
#include <utility>
#include <unordered_map>

//local includes
#include "FileReader.h"


class RSA
{
public:
    RSA (FileReader& fileReader);
    ~RSA();

private:
    int toNumber(char c);

    //private keys parameters
    const std::pair<int, int> publicKeyParams;
    const std::pair<int, int> privateKeyParams;

    FileReader& fileReader_;
};


#endif //PRIR_RSA_H
