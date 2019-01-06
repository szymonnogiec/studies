#include <string>
#include <stdlib.h>
#include <map>
#include <iostream>

#include "Dictonary.h"

int main() {
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
    for (int i = 0; i < 3000000; ++i) {
        dict.insert((str1 + std::to_string(i)));
        dict.insert((str2 + std::to_string(i)));
        dict.insert((str3 + std::to_string(i)));
        dict.insert((str4 + std::to_string(i)));
        dict.insert((str5 + std::to_string(i)));
    }

    std::vector<std::string> words_to_find;
    for (int i = 0; i < 20000000; ++i) {
        int rand_val_item = rand_r(&seed) % 4;
        std::string word = items_map.at(rand_val_item);
        rand_val_item = rand_r(&seed) % 204800;
        word += std::to_string(rand_val_item);
        words_to_find.push_back(word);
    }

    std::vector<std::pair<std::string, double>> results;
    std::cout << "----LINEAR SEARCH----" << std::endl;
    double startTime = omp_get_wtime();
    dict.find_linear(words_to_find);
    double endTime = omp_get_wtime();
    results.emplace_back(std::make_pair("Linear", (endTime - startTime)));

    short threads_num[5] = {1, 2, 4, 8, 16};
    for (short threads_number : threads_num) {
        std::cout << "----OPENMP PARALLEL SEARCH----" << std::endl;
        startTime = omp_get_wtime();
        omp_set_num_threads(threads_number);
        dict.find_mp(words_to_find);
        endTime = omp_get_wtime();
        results.emplace_back(std::make_pair("omp " + std::to_string(threads_number),
                                            (endTime - startTime)));
    }

    for (auto &i : results) {
        std::cout << i.first << " --- " << i.second << std::endl;
    }
    return 0;
}