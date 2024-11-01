//
// Created by Volodymyr Avvakumov on 26.10.2024.
//
#include <iostream>
#include <type_traits>

#include "LinkedList.h"

#ifndef LEARNING_HASHSET_H
#define LEARNING_HASHSET_H

// TODO: remake ~;
template<typename var_type>
class HashSet {
protected:
    int real_size;
    int element_count;
    int curr_pow_for_primes;

    LinkedList<var_type>* element_arr;

public:
    HashSet(){
        real_size = 5;
        element_count = 0;
        curr_pow_for_primes = 3;
        element_arr = new LinkedList<var_type>[real_size];
        for (int i = 0; i < 5; i++) element_arr[i].first_el = nullptr;
    }

    ~HashSet(){
        delete[] element_arr;
    }


    void add(var_type var){

        if (get_occupancy() > 75)
            create_new_elements_list();

        int hash = getHash(var);
        int position = hash % real_size;

        element_arr[position].add(var);

        element_count++;
    }

    void pop(var_type var){

        int hash = HashSet<var_type>::getHash(var);
        int position = hash % HashSet<var_type>::real_size;

        if (HashSet<var_type>::element_arr[position] != nullptr){
            element_arr[position].pop(var);
            element_count --;
        } else{
            throw std::logic_error("no elements here!!!");
        }
    }

    bool is_in(var_type var){
        long long hash = getHash(var);
        long long position = hash % real_size;
        return element_arr[position].is_in(var);
    }

    int getSize(){
        return element_count;
    }

    void print(std::ostream& out = std::cout) const {
        for (int i = 0; i < real_size; i++){
            if (element_arr[i] == nullptr) continue;
            out << element_arr[i] << " ";
        }
    }

    void debug_print(std::ostream& out = std::cout) const {
        for (int i = 0; i < real_size; i++){
            if (element_arr[i] == nullptr){
                out << "NONE" << " ";
                continue;
            }
            out << element_arr[i] << " ";
        }
    }

protected:

    template <typename T>
    typename std::enable_if<std::is_integral<T>::value, long long int>::type
    getHash(T value) {
        long long int result = 0;
        while (value) {
            result = (result << 5) | (result >> (sizeof(long long int) * 8 - 5));
            result ^= (value & 0xFF);
            value >>= 8;
        }

        return result;
    }

    template <typename T>
    typename std::enable_if<std::is_floating_point<T>::value, long long int>::type
    getHash(T value) {
        long long int result = 0;
        unsigned char* bytePtr = reinterpret_cast<unsigned char*>(&value);
        for (size_t i = 0; i < sizeof(T); ++i) {
            result = (result << 5) | (result >> (sizeof(long long int) * 8 - 5));
            result ^= bytePtr[i];
        }

        return result;
    }

    template <typename T>
    typename std::enable_if<std::is_pointer<T>::value, long long int>::type
    getHash(T value) {
        long long int result = 0;
        uintptr_t ptr = reinterpret_cast<uintptr_t>(value);
        unsigned char* bytePtr = reinterpret_cast<unsigned char*>(&ptr);
        for (size_t i = 0; i < sizeof(ptr); ++i) {
            result = (result << 5) | (result >> (sizeof(long long int) * 8 - 5));
            result ^= bytePtr[i];
        }
        return result;
    }
    // for random type;
    template <typename T>
    typename std::enable_if<!std::is_integral<T>::value &&
                            !std::is_floating_point<T>::value &&
                            !std::is_pointer<T>::value, long long int>::type
    getHash(const T& value) {
        long long int result = 0;
        const unsigned char* bytePtr = reinterpret_cast<const unsigned char*>(&value);
        for (size_t i = 0; i < sizeof(T); ++i) {
            result = (result << 5) | (result >> (sizeof(long long int) * 8 - 5));
            result ^= bytePtr[i];
        }
        return result;
    }



    float get_occupancy(){
        if (HashSet<var_type>::real_size == 0) return 0;
        return ((float)HashSet<var_type>::element_count / HashSet<var_type>::real_size) * 100;
    }

    void create_new_elements_list() {
        long long new_size = HashSet<var_type>::next_prime();

        LinkedList<var_type>* new_element_arr = new LinkedList<var_type>[new_size];

        HashSet<var_type>::copy_list(new_element_arr, new_size);

        delete[] HashSet<var_type>::element_arr;
        element_arr = new_element_arr;
        HashSet<var_type>::real_size = new_size;
    }

    void copy_list(LinkedList<var_type>* new_lst, int new_size){
        for (int i = 0; i < real_size; i ++){
            if (HashSet<var_type>::element_arr[i] != nullptr){
                for (auto element: element_arr[i]){

                    int hash = HashSet<var_type>::getHash(element);
                    int position = hash % new_size;

                    if (new_lst[position] != nullptr){  //FIXME: rewrite code; == add() func;
                        LinkedList<var_type> lst;
                        lst.add( element);
                        new_lst[position] = lst;
                    } else {
                        new_lst[position].add(element);
                    }

                }


            }
        }

    }



    long long next_prime(){
        long long min_lim = pow(2, curr_pow_for_primes);
        long long max_lim = pow(2, curr_pow_for_primes+1);

        long long middle = (min_lim + max_lim) / 2;
        for (long long i = middle; i < max_lim - 1; i++){
            if (HashSet<var_type>::is_prime(middle - i)){
                curr_pow_for_primes ++;
                return middle - i;
            }
            if (HashSet<var_type>::is_prime(middle + i)){
                curr_pow_for_primes ++;
                return middle + i;
            }
        }
        // if no primes from 2^k-1 to 2^k;
        curr_pow_for_primes ++;
        return HashSet<var_type>::next_prime();
    }

    static bool is_prime(long long num) {
        if (num < 2) return false;
        if (num == 2 || num == 3) return true;
        if (num % 2 == 0 || num % 3 == 0) return false;

        int sqrt_num = static_cast<long long>(std::sqrt(num)); //FIXME !!!!!!!!!!!!!!! ststic_cast<int>
        for (long long i = 5; i <= sqrt_num; i += 6) {
            if (num % i == 0 || num % (i + 2) == 0)
                return false;
        }
        return true;
    }
    // TODO: change to default print;
    friend std::ostream& operator <<(std::ostream& out,const HashSet& set){
        set.print(out);
        return out;
    }
};

//#include "HashSet.cpp"

#endif //LEARNING_HASHSET_H
