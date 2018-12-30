#include <string>
#include <stdlib.h>
#include <map>
#include <iostream>

#include "Dictonary.h"

int main()
{
    unsigned int seed = time(nullptr);

    std::map<int, std::string> items_map;
    std::string str1("Apple");
    std::string str2("Rocket");
    std::string str3("Calculator");
    std::string str4("Monitor");
    std::string str5("PRiR_seq");
    items_map.insert(std::make_pair(0, str1));
    items_map.insert(std::make_pair(1, str2));
    items_map.insert(std::make_pair(2, str3));
    items_map.insert(std::make_pair(3, str4));
    items_map.insert(std::make_pair(4, str5));

    Dictionary dict;
    for (int i = 0; i < 1024; ++i)
    {
        dict.insert((str1 + std::to_string(i)).c_str());
        dict.insert((str2 + std::to_string(i)).c_str());
        dict.insert((str3 + std::to_string(i)).c_str());
        dict.insert((str4 + std::to_string(i)).c_str());
        dict.insert((str5 + std::to_string(i)).c_str());
    }

    for (int i = 0; i < 20; ++i)
    {
        int rand_val_item = rand_r(&seed) % 4;
        std::string word = items_map.at(rand_val_item);
        rand_val_item = rand_r(&seed) % 2048;
        word += std::to_string(rand_val_item);
        printf("Searching for string %s\n", word.c_str());
        const char* result = dict.find(word.c_str());
        if (result != nullptr)
        {
            printf("String %s found\n", word.c_str());
        }
        else
        {
            printf("String %s not found\n", word.c_str());
        }
    }
    return 0;
}