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

void RSA::decode()
{
    fileReader_.readInput();
    std::vector<int> encodedNumbers =
            fileReader_.toIntsVector (fileReader_.getInputMsg());
    int msgToDecodeSize = encodedNumbers.size();
    std::string decodedMsg (msgToDecodeSize, ' ');


    //MPI data
    int mynum, nprocs;
    MPI_Comm_rank(MPI_COMM_WORLD, &mynum);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    char decodedChar;
    int intTaken;
    int i;
    MPI_Status status;
    int type = 2;
    int source = 0;
    int bufferedInt;

    for (i = 0; i < msgToDecodeSize; i += nprocs)
    {
        printf("Processor %d: Iteration number %d \n", mynum, i);
        if (mynum == 0)
        {
            printf("Taking digit number %d\n", i);
            intTaken = encodedNumbers.at(i);
            for (int j = 1; j < nprocs; ++j)
            {
                printf("Processor %d: Iterating through processors; iteration %d\n", mynum, j);
                if (i+j >= msgToDecodeSize)
                    break;

                printf("Taking digit number %d\n", i+j);
                bufferedInt = encodedNumbers.at(i+j);
                printf("Processor %d: Sending int %d to processor %d\n", mynum, bufferedInt, j);
                MPI_Send (&bufferedInt, 1, MPI_INT, j, type, MPI_COMM_WORLD);
            }
            printf("Processor %d: Decoding digit %d \n", mynum, intTaken);
            decodedChar = decodeChar(intTaken);
            printf("Putting char number %d\n", i);
            decodedMsg.at(i) = decodedChar;
        }
        else
        {
            if (mynum + i >= msgToDecodeSize)
            {
                printf("Breaking loop in processor %d", mynum);
                break;
            }

            MPI_Recv(&bufferedInt, 1, MPI_INT, source, type, MPI_COMM_WORLD, &status);

            printf("Processor %d: Received digit %d to processor %d\n", mynum, bufferedInt, mynum);
            decodedChar = decodeChar (bufferedInt);
            MPI_Send(&decodedChar, 1, MPI_CHAR, 0, type, MPI_COMM_WORLD);
        }

        if (mynum == 0)
        {
            for (int j = 1; j < nprocs; ++j)
            {
                char bufferedDecodedChar;
                if (i+j >= msgToDecodeSize)
                    break;
                MPI_Recv(&bufferedDecodedChar, 1, MPI_CHAR, j, type, MPI_COMM_WORLD, &status);
                printf("Processor %d: Received decoded char %c\n", mynum, bufferedDecodedChar);
                printf("Processor %d: i = %d, j = %d\n", mynum, i, j);
                printf("Putting decoded char number %d\n", i+j);
                decodedMsg.at(i+j) = bufferedDecodedChar;
            }
        }
    }

    if (mynum == 0)
    {
        bool writeSuccessful = fileReader_.writeToOutput (decodedMsg);
        if (writeSuccessful)
        {
            std::cout << std::string (50, '*') << std::endl;
            std::cout << "Decoded digits has been "
                    "successfully written to output file " <<
                      fileReader_.getOutputFilename() << std::endl;
        }
    }
}

void RSA::encode()
{
    fileReader_.readInput();
    std::string msgToEncode = fileReader_.getInputMsg();

    //MPI data
    int mynum, nprocs;
    MPI_Comm_rank(MPI_COMM_WORLD, &mynum);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    printf("Number of processors %d\n", nprocs);
    printf ("My rank %d\n", mynum);

    //data for calculations
    int msgToEncodeSize = msgToEncode.size();
    int encodedChar;
    int charTaken;
    int i;
    MPI_Status status;
    int type = 2;
    int source = 0;

    std::vector<int> encodedChars (msgToEncodeSize);

    char bufferedChar;
    for (i = 0; i < msgToEncodeSize; i += nprocs) {

        printf("Processor %d: Iteration number %d \n", mynum, i);
        if (mynum == 0)
        {
            printf("Taking char number %d\n", i);
            charTaken = msgToEncode.at(i);
            for (int j = 1; j < nprocs; ++j)
            {
                printf("Processor %d: Iterating through processors; iteration %d\n", mynum, j);
                if (i+j >= msgToEncodeSize)
                    break;

                printf("Taking char number %d\n", i+j);
                bufferedChar = msgToEncode.at(i+j);
                printf("Processor %d: Sending char %c to processor %d\n", mynum, bufferedChar, j);
                MPI_Send (&bufferedChar, 1, MPI_CHAR, j, type, MPI_COMM_WORLD);
            }
            printf("Processor %d: Encoding char %c \n", mynum, charTaken);
            encodedChar = encodeChar(charTaken);
            printf("Putting char number %d\n", i);
            encodedChars.at(i) = encodedChar;
        }
        else
        {
            if (mynum + i >= msgToEncodeSize)
            {
                printf("Breaking loop in processor %d", mynum);
                break;
            }

            MPI_Recv(&bufferedChar, 1, MPI_CHAR, source, type, MPI_COMM_WORLD, &status);

            printf("Processor %d: Received char %c to processor %d\n", mynum, bufferedChar, mynum);
            encodedChar = encodeChar(bufferedChar);
            MPI_Send(&encodedChar, 1, MPI_INT, 0, type, MPI_COMM_WORLD);
        }

        if (mynum == 0)
        {
            for (int j = 1; j < nprocs; ++j)
            {
                int bufferedEncodedChar;
                if (i+j >= msgToEncodeSize)
                    break;
                MPI_Recv(&bufferedEncodedChar, 1, MPI_INT, j, type, MPI_COMM_WORLD, &status);
                printf("Processor %d: Received encoded digit %d\n", mynum, bufferedEncodedChar);
                printf("Processor %d: i = %d, j = %d\n", mynum, i, j);
                printf("Putting encoded char number %d\n", i+j);
                encodedChars.at(i+j) = bufferedEncodedChar;
            }
        }
    }

    if (mynum == 0)
    {
        bool writeSuccessful = fileReader_.writeToOutput (encodedChars);
        if (writeSuccessful)
        {
            std::cout << std::string (50, '*') << std::endl;
            std::cout << "Encoded digits has been "
                    "successfully written to output file " <<
                      fileReader_.getOutputFilename() << std::endl;
        }
    }

}

int RSA::encodeChar(char c)
{
    int charDigit = toNumber (c);
    if (charDigit == -1)
        return charDigit;

    fileReader_.writeToHelperOutput (charDigit);

    // int le = calculatePowerMod(charDigit, publicKeyParams.first,
    // publicKeyParams.second);

    double power = static_cast<double>(publicKeyParams.first);
    double base = static_cast<double>(charDigit);
    long long le = static_cast<long long>(std::pow (base, power));
    int result = le % publicKeyParams.second;
	//int result = le % publicKeyParams.second;
    return result;
}

char RSA::decodeChar (int number)
{
    long long cd = calculatePowerMod (number, privateKeyParams.first,
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

    double base = static_cast<double>(c);
    double exp = 2.0;

    int rest = d % 2;
    if (rest == 0)
    {
        int newBase = static_cast<int>(std::pow (base, exp)) % n;
        int newD = d/2;
        return calculatePowerMod (newBase, newD, n);
    }
    else
    {
        int newBase = static_cast<int>(std::pow (base, exp)) % n;
        int newD = (d-1)/2;

        return c * calculatePowerMod (newBase, newD, n);
    }
}
