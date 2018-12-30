#pragma once

#include <cstring>
#include <cstdio>



class Dictionary
{
    struct Data
    {
        char* word = nullptr;
        Data* next = nullptr;

        ~Data()
        {
            delete [] word;
        }
    };

public:
    const unsigned int MAX_BUCKETS;
    Dictionary(unsigned int maxBuckets = 2000000)
            : MAX_BUCKETS(maxBuckets)
            , words(new Data*[MAX_BUCKETS])
    {
        memset(words, 0, sizeof(Data*) * MAX_BUCKETS);
    }

    ~Dictionary()
    {
        for (int i = 0; i < MAX_BUCKETS; ++i)
            delete words[i];
        delete [] words;
    }

    void insert(const char* word)
    {
        const auto hash_index = hash(word);
        auto& d = words[hash_index];
        if (d == nullptr)
        {
            d = new Data;
            copy_string(d, word);
        }
        else
        {
            while (d->next != nullptr)
            {
                d = d->next;
            }
            d->next = new Data;
            copy_string(d->next, word);
        }
    }

    void copy_string(Data* d, const char* word)
    {
        const auto word_length = strlen(word)+1;
        d->word = new char[word_length];
        strcpy(d->word, word);
        printf("%s\n", d->word);
    }

    const char* find(const char* word) const
    {
        const auto hash_index = hash(word);
        auto& d = words[hash_index];
        if (d == nullptr)
        {
            return nullptr;
        }
        while (d != nullptr)
        {
            printf("Comparing string %s with %s\n", word, d->word);
            if (strcmp(d->word, word) == 0)
                return d->word;
            d = d->next;
        }
        return nullptr;
    }
private:

    /* D. J. Bernstein hash function */
    unsigned int hash(const char* word) const
    {
        unsigned int hash = 5381;
        while (*word)
            hash = 33 * hash ^ (unsigned char) *word++;
        return hash % MAX_BUCKETS;
    }

    Data** words;
};