//
// Created by Volodymyr Avvakumov on 26.10.2024.
//
#include <iostream>
#include <cmath>

#include "HashSet2.h"



template <typename var_type>
void HashSet<var_type>::add(var_type var){

    int occ = HashSet<var_type>::get_occupancy();
    if (HashSet<var_type>::get_occupancy() > 75)  // checking occupancy if it < 75% just add element
        HashSet<var_type>::create_new_elements_list();

    int hash = HashSet<var_type>::getHash(var);
    int position = hash % HashSet<var_type>::real_size; //FIXME: rewrite for list element;

    if (HashSet<var_type>::element_list[position] != NAN) {
        HashSet<var_type>::element_list[position] = var; //FIXME: rewrite for list element;
    } else {
        //        HashSet<var_type>::fixCollision(var); //FIXME: rewrite for list element;
        std::cout << "colision" << std::endl;
    }

    HashSet<var_type>::element_count++;
}





//template <typename var_type>
//void HashSet<var_type>::add(var_type var){
//
//    int occ = HashSet<var_type>::get_occupancy();
//    if (HashSet<var_type>::get_occupancy() < 75) { // checking occupancy if it < 75% just add element
//        int hash = HashSet<var_type>::getHash(var);
//        int position = hash % HashSet<var_type>::real_size; //FIXME: rewrite for list element;
//        if (HashSet<var_type>::element_list[position] != NAN) {
//            HashSet<var_type>::element_list[position] = var; //FIXME: rewrite for list element;
//        } else {
//            //        HashSet<var_type>::fixCollision(var); //FIXME: rewrite for list element;
//            std::cout << "colision" << std::endl;
//        }
//    } else {
//        HashSet<var_type>::create_new_elements_list();
//
//
//    }
//    HashSet<var_type>::element_count++;
//}

template <typename var_type>
void HashSet<var_type>::pop(var_type var){
    int hash = HashSet<var_type>::getHash(var);
    int position = hash % HashSet<var_type>::real_size; //FIXME: rewrite for list element;
    if (HashSet<var_type>::element_list[position] != NAN){
        element_list[position] = NAN;
        HashSet<var_type>::element_count --;
    } else{
        std::cout << "no such element here" << std::endl;
    }
}


template <typename var_type> // FIXME: may be another realisation
int HashSet<var_type>::getSize() {
    int counter = 0;
    for (int i = 0; i < HashSet<var_type>::real_size; i++){
        if (HashSet<var_type>::element_list[i] != NAN) {
            counter ++;
        }
    }
    return counter;
}

// hash functions

//template <>
//int HashSet<int>::getHash(int var) {
//    return var;
//
//}

//template<> //FIXME
//int HashSet<double>::getHash(double var) {
//    return (int)var;
//}

// end hash functions

template <typename var_type> // FIXME
void HashSet<var_type>::fixCollision() {
    std::cout << "no realisation now" << std::endl;
}



template <typename var_type>
float HashSet<var_type>::get_occupancy() {
    if (HashSet<var_type>::real_size == 0) return 0;
    return ((float)HashSet<var_type>::element_count / HashSet<var_type>::real_size) * 100;
}


template <typename var_type>
void HashSet<var_type>::create_new_elements_list() {
    int new_size = HashSet<var_type>::next_prime();
    var_type* new_element_list = new var_type[new_size];

    HashSet<var_type>::copy_list(new_element_list, new_size);

    delete[] HashSet<var_type>::element_list;
    element_list = new_element_list;
    HashSet<var_type>::real_size = new_size;
}

template <typename var_type> // TODO refactor for LIST
void HashSet<var_type>::copy_list(var_type *new_lst,int new_size) {
    for (int i = 0; i < real_size; i ++){
        if (HashSet<var_type>::element_list[i] != NAN){
            int hash = HashSet<var_type>::getHash(HashSet<var_type>::element_list[i]);
            int position = hash % new_size;
            new_lst[position] = HashSet<var_type>::element_list[i];
        }
    }

}


template <typename var_type>
int HashSet<var_type>::next_prime() {
    int min_lim = pow(2, curr_pow_for_primes);
    int max_lim = pow(2, curr_pow_for_primes+1);
    for (int i = min_lim; i < max_lim; i++){
        if (HashSet<var_type>::is_prime(i)){
            curr_pow_for_primes ++;
            return i;
        }
    }
    // if no primes from 2^k-1 to 2^k;
    curr_pow_for_primes ++;
    return HashSet<var_type>::next_prime();
}

template <typename var_type>
bool HashSet<var_type>::is_prime(int num) {
    if (num < 2) return false;
    if (num == 2 || num == 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;

    int sqrt_num = static_cast<int>(std::sqrt(num));
    for (int i = 5; i <= sqrt_num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0)
            return false;
    }
    return true;
}

