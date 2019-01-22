#include <string>
#include <stdlib.h>
#include <map>
#include <iostream>
#include <chrono>

#include "Dictonary.h"

int main() {
    MPI_Init(nullptr, nullptr);
    int mynum, nprocs;
    MPI_Comm_rank(MPI_COMM_WORLD, &mynum);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
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

    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point end_time;
    std::chrono::duration<double> diff;
//    std::cout << "----LINEAR SEARCH----" << std::endl;
//    start_time =
//            std::chrono::high_resolution_clock::now();
//    dict.find_linear(words_to_find);
//    end_time =
//            std::chrono::high_resolution_clock::now();
//    diff = end_time - start_time;
//    results.emplace_back(std::make_pair("Linear", diff.count()));

    if (mynum == 0) {
        std::cout << "----OPENMP PARALLEL SEARCH----" << std::endl;
        start_time = std::chrono::high_resolution_clock::now();
    }
    dict.find_mpi(words_to_find);
    std::cout << "find mpi done" << std::endl;
    if (mynum == 0) {
        end_time = std::chrono::high_resolution_clock::now();
        diff = end_time - start_time;
        std::cout << "MPI time took " << diff.count() << " with " << nprocs << " processors." << std::endl;
    }
    MPI_Finalize();
    return 0;
}