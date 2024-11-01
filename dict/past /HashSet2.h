//
// Created by Volodymyr Avvakumov on 26.10.2024.
//
#include <cmath>
#include <iostream>

#ifndef LEARNING_HASHSET_H
#define LEARNING_HASHSET_H

template <typename var_type>
class HashSet {
protected:
    int real_size;
    int element_count;
    int curr_pow_for_primes;
    var_type* element_arr = nullptr;

public:
    HashSet() {
        real_size = 5;
        element_count = 0;
        curr_pow_for_primes = 3;
        element_arr = new var_type[real_size];
        for (int i = 0; i < real_size; i++) {
            element_arr[i] = NAN;
        }
    }

    ~HashSet(){
        int x = 0;
    };

    void add(var_type var);

    void pop(var_type ver);

    int getSize();

    void print(){
        for (int i = 0; i < real_size; i++){
            std::cout << element_arr[i] << " ";
        }
        std::cout << std::endl;
    }

protected:
    int getHash(int var) {
        return var;

    }

    void fixCollision();

    float get_occupancy();

    void create_new_elements_list();

    void copy_list(var_type* new_lst, int new_size);



    int next_prime();

    static bool is_prime(int num);
};



#endif //LEARNING_HASHSET_H
