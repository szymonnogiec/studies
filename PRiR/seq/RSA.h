//
// Created by simon on 06.03.17.
//

#ifndef PRIR_RSA_H
#define PRIR_RSA_H

//std includes
#include <utility>
#include <unordered_map>
#include <cmath>
#include <vector>

//local includes
#include "FileReader.h"


class RSA
{
public:
    RSA (FileReader& fileReader);
    ~RSA();

    bool encode ();
    bool decode ();
private:
    int toNumber (char c);
    int encodeChar (char c);
    char decodeChar (int number);
    int calculatePowerMod (int c, int d, int n);
    long long calculatePowerRecursively (long long base, int power);
    //private keys parameters
    const std::pair<int, int> publicKeyParams;
    const std::pair<int, int> privateKeyParams;

    FileReader& fileReader_;
    const int charsMovement_;
};


#endif //PRIR_RSA_H
