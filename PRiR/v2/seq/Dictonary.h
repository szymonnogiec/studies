#pragma once

#include <cstring>
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>

// MPI include
#include <mpi.h>

class Dictionary {
    struct Data {
        std::string word = "";
        Data *next = nullptr;

        ~Data() = default;
    };

public:
    const unsigned int MAX_BUCKETS;

    explicit Dictionary(unsigned int maxBuckets = 20000000)
            : MAX_BUCKETS(maxBuckets), words(new Data *[MAX_BUCKETS]) {
        memset(words, 0, sizeof(Data *) * MAX_BUCKETS);
    }

    ~Dictionary() {
        for (int i = 0; i < MAX_BUCKETS; ++i)
            delete words[i];
        delete[] words;
    }

    void insert(const std::string &word) {
        const auto hash_index = hash(word);
        auto &d = words[hash_index];
        if (d == nullptr) {
            d = new Data;
            d->word = word;
        } else {
            while (d->next != nullptr) {
                d = d->next;
            }
            d->next = new Data;
            d->word = word;
        }
    }

    bool find(const std::string &word) const {
        const auto hash_index = hash(word);
        auto &d = words[hash_index];
        if (d == nullptr) {
            return false;
        }
        while (d != nullptr) {
            if (word == d->word)
                return true;
            d = d->next;
        }
        return false;
    }

    std::vector<bool> find_linear(const std::vector<std::string> &words_to_find) {
        unsigned long n = words_to_find.size();
        std::vector<bool> result(n);
        for (int i = 0; i < n; ++i) {
            const std::string &word = words_to_find[i];
            bool ptr = find(word);
            result[i] = ptr;
        }
        return result;
    }

    std::vector<bool> find_mpi(const std::vector<std::string> &words_to_find) {
        int mynum, nprocs;
        MPI_Comm_rank(MPI_COMM_WORLD, &mynum);
        MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
        std::vector<bool> result = std::vector<bool>(words_to_find.size());

        unsigned long n = words_to_find.size();
        //data for calculations
        size_t words_to_find_size = words_to_find.size();
        bool is_found;
        std::string word_to_find;
        std::string buffered_word_to_find;
        int i;
        MPI_Status status;
        int type = 2;
        int source = 0;

        for (i = 0; i < words_to_find_size; i += nprocs) {
            //printf("Processor %d: Iteration number %d \n", mynum, i);
            if (mynum == 0) {
                word_to_find = words_to_find[i];
//                printf("Taking word to find: %s\n", word_to_find.c_str());
                for (int j = 1; j < nprocs; ++j) {
//                    printf("Processor %d: Iterating through processors; iteration %d\n", mynum, j);
                    if (i + j >= words_to_find_size)
                        break;

                    buffered_word_to_find = words_to_find[i + j];
//                    printf("Taking word to find %s\n", buffered_word_to_find.c_str());
//                    printf("Processor %d: Sending string %s to processor %d\n", mynum, buffered_word_to_find.c_str(), j);
                    MPI_Send(buffered_word_to_find.c_str(), buffered_word_to_find.size(), MPI_CHAR, j, type,
                             MPI_COMM_WORLD);
                }
//                printf("Processor %d: Searching string %s \n", mynum, word_to_find.c_str());
                is_found = find(word_to_find);
//                printf("Processor %d: Putting is found number %d value: %d\n", mynum, i, is_found);
                result.at(i) = is_found;
//                printf("Processor %d: Put successful\n", mynum);
            } else {
                if (mynum + i >= words_to_find_size) {
//                    printf("Breaking loop in processor %d", mynum);
                    break;
                }
//                printf("Processor %d: Probing for word size \n", mynum);
                MPI_Probe(source, type, MPI_COMM_WORLD, &status);
                int l;
//                printf("Processor %d: Getting count of chars\n", mynum);
                MPI_Get_count(&status, MPI_CHAR, &l);
//                printf("Processor %d: Creating word with size: %d\n", mynum, l);
                char *buf = new char[l];
                MPI_Recv(buf, l, MPI_CHAR, source, type, MPI_COMM_WORLD, &status);

//                printf("Processor %d: Received word %s to processor %d\n", mynum, buf, mynum);
                is_found = find(std::string(buf));
                MPI_Send(&is_found, 1, MPI_CXX_BOOL, 0, type, MPI_COMM_WORLD);
                delete[] buf;
            }

            if (mynum == 0) {
                for (int j = 1; j < nprocs; ++j) {
//                    printf("Processor %d: Loop recv index: %d\n", mynum, j);
                    bool received_is_found;
                    if (i + j >= words_to_find_size) {
//                        printf("Processor %d: Breaking from for loop\n", mynum);
                        break;
                    }
//                    printf("Processor %d: Breaking from for loop\n", mynum);
                    MPI_Recv(&received_is_found, 1, MPI_CXX_BOOL, j, type, MPI_COMM_WORLD, &status);
//                    printf("Processor %d: Received is_found %d\n", mynum, received_is_found);
//                    printf("Processor %d: i = %d, j = %d\n", mynum, i, j);
//                    printf("Putting result in %d\n", i + j);
                    result[i + j] = received_is_found;
                }
            }
//            printf("Processor %d: Breaking from main loop\n", mynum);
        }
        return result;
    }

private:
/* D. J. Bernstein hash function */
    unsigned int hash(const std::string &word_str) const {
        unsigned int hash = 5381;
        const char *word = word_str.c_str();
        while (*word)
            hash = 33 * hash ^ (unsigned char) *word++;
        return hash % MAX_BUCKETS;
    }

    Data **words;
};