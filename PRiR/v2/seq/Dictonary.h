#pragma once

#include <string>
#include <vector>
#include <iostream>

// openmp include
#include <omp.h>

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

    Data *find(const std::string &word) const {
        const auto hash_index = hash(word);
        auto &d = words[hash_index];
        if (d == nullptr) {
            return nullptr;
        }
        while (d != nullptr) {
            if (word == d->word)
                return d;
            d = d->next;
        }
        return nullptr;
    }

    std::vector<Data *> find_linear(const std::vector<std::string> &words_to_find) {
        unsigned long n = words_to_find.size();
        std::vector<Data *> result(n);
        for (int i = 0; i < n; ++i) {
            const std::string &word = words_to_find[i];
            auto ptr = find(word);
            result[i] = ptr;
        }
        return result;
    }

    std::vector<Data *> find_mp(const std::vector<std::string> &words_to_find) {
        unsigned long n = words_to_find.size();
        std::vector<Data *> result(words_to_find.size());
#pragma omp parallel for
        for (int i = 0; i < n; ++i) {
            const std::string &word = words_to_find[i];
            auto ptr = find(word);
            result[i] = ptr;
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