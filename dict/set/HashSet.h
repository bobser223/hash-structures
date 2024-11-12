//
// Created by Volodymyr Avvakumov on 26.10.2024.
//
#include <iostream>
#include <type_traits>

#include "LinkedList.h"

#ifndef LEARNING_HASHSET_H
#define LEARNING_HASHSET_H

template<typename var_type>
class HashSet {
protected:
    int real_size;
    int element_count;
    int curr_pow_for_primes;

    LinkedList<var_type>* element_arr;

public:
    HashSet();

    ~HashSet(){
        delete[] element_arr;
    }


    void add(var_type var);
    /*
     * Adds a key to the dictionary.
     * Resizes the array if occupancy exceeds 75%.
    */
    bool is_in(var_type var);

    void pop(var_type var);
    /*
     *  deletes hash
     *
     *  finds var's hash
     *  finds place in the element_arr by hash
     *  using LinkedList_dict method pop
     *  |look to the LinkedList_dict for understanding structure|
     */
    int getSize(){
        return element_count;
    }
    /*
     * @return count of elements
     */

    void print(std::ostream& out = std::cout) const;

protected:

    template <typename T>
    typename std::enable_if<std::is_integral<T>::value, long long int>::type
    getHash(T value);
    // hash for integers

    template <typename T>
    typename std::enable_if<std::is_floating_point<T>::value, long long int>::type
    getHash(T value);
    // hash for floats


    template <typename T>
    typename std::enable_if<std::is_pointer<T>::value, long long int>::type
    getHash(T value);
    //hash for dynamic structures (pointers)

    long long int getHash(const std::string& value) const;
    //hash for strings

    float get_occupancy(){
        if (HashSet<var_type>::real_size == 0) return 0;
        return ((float)HashSet<var_type>::element_count / HashSet<var_type>::real_size) * 100;
    }
    /*
     * finds the percentage ratio of filled elements to the full size of the buffer
     * @return buffer occupancy
     */

    void create_new_elements_arr();
    /*
     * crates new element_arr with larger size
     * copies pairs(key, value) from old array (direct) to new
     * changes ald array (direct) to new one
     * deletes old
     */

    void copy_list(LinkedList<var_type>* new_lst, int new_size);
    /*
     * copies all element from old element_arr (direct) to the new element_arr
     * @param new_arr | new element_arr
     * @param new_size | size of new element_arr
     */


    long long next_prime();
    /*
     * the best sizes of Hash structure are primes between 2^k and 2^(k+1)-1
     * this function finds them,
     * so it starts from the middle of [2^k, 2^(k+1)-1]
     * and goes simultaneously to the right and left of segment
     *  checking each number;
     *  if there's no prime number in this segment k = k+1 and does the same
     *  if there is prime k = k+1 and returning it;
     *  @return prime number for element_arr size
     */

    static bool is_prime(long long num);
    /*
     * standard prime check
     */

    friend std::ostream& operator <<(std::ostream& out,const HashSet& set){
        set.print(out);
        return out;
    }
}; // End of the class

// methods implementation

template<typename var_type>
HashSet<var_type>::HashSet() {
    real_size = 5;
    element_count = 0;
    curr_pow_for_primes = 3;
    element_arr = new LinkedList<var_type>[real_size];
    for (int i = 0; i < 5; i++) element_arr[i].first_el = nullptr;
}


template<typename var_type>
void HashSet<var_type>::add(var_type var){

    if (get_occupancy() > 75)
        create_new_elements_arr();

//    std::cout << var << " hash started" << std::endl;
    long long int  hash = HashSet<var_type>::getHash(var);

    if (hash < 0) hash = -hash;

    int position = hash % real_size;

    element_arr[position].add(var);

    element_count++;
}

template<typename var_type>
bool HashSet<var_type>::is_in(var_type var){
    long long hash = getHash(var);

    if(hash < 0)
        hash = -hash;

    long long position = hash % real_size;

    return element_arr[position].is_in(var);
}

template<typename var_type>
void HashSet<var_type>::pop(var_type var){

    int hash = HashSet<var_type>::getHash(var);
    int position = hash % HashSet<var_type>::real_size;
    // if element_arr[i] is not empty, overloaded operator, look to LinkedList.h
    if (HashSet<var_type>::element_arr[position] != nullptr){
        element_arr[position].pop(var);
        element_count --;
    } else{
        throw std::logic_error("no elements here!!!");
    }
}

template<typename var_type>
void HashSet<var_type>::print(std::ostream& out) const {
    for (int i = 0; i < real_size; i++) {
        if (element_arr[i] == nullptr) continue;
        out << element_arr[i] << " ";
    }
}


//protected

//hash functions

template<typename var_type>
template <typename T>
typename std::enable_if<std::is_integral<T>::value, long long int>::type
HashSet<var_type>::getHash(T value) {
    // hash function works only for positive nums
    if (value < 0) {
        value = -value;
    }
    long long int result = 0;
    while (value) {
        result = (result << 5) | (result >> (sizeof(long long int) * 8 - 5));
        result ^= (value & 0xFF);
        value >>= 8;
    }


    return result;
}


template<typename var_type>
template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, long long int>::type
HashSet<var_type>::getHash(T value) {
    long long int result = 0;
    unsigned char* bytePtr = reinterpret_cast<unsigned char*>(&value);
    for (size_t i = 0; i < sizeof(T); ++i) {
        result = (result << 5) | (result >> (sizeof(long long int) * 8 - 5));
        result ^= bytePtr[i];
    }


    return result;
}

template<typename var_type>
template <typename T>
typename std::enable_if<std::is_pointer<T>::value, long long int>::type
HashSet<var_type>::getHash(T value) {
    long long int result = 0;
    uintptr_t ptr = reinterpret_cast<uintptr_t>(value);
    unsigned char* bytePtr = reinterpret_cast<unsigned char*>(&ptr);
    for (size_t i = 0; i < sizeof(ptr); ++i) {
        result = (result << 5) | (result >> (sizeof(long long int) * 8 - 5));
        result ^= bytePtr[i];
    }


    return result;
}

template<typename var_type>
long long int HashSet<var_type>::getHash(const std::string& value) const {
    long long int result = 0;
    for (char c : value) {

        result = (result << 5) | (result >> (sizeof(long long int) * 8 - 5));
        result ^= static_cast<unsigned char>(c);
    }


    return result;
}

// puffer scaling functions
template<typename var_type>
void HashSet<var_type>::create_new_elements_arr() {
    long long new_size = HashSet<var_type>::next_prime();

    LinkedList<var_type>* new_element_arr = new LinkedList<var_type>[new_size];
    HashSet<var_type>::copy_list(new_element_arr, new_size);

    delete[] HashSet<var_type>::element_arr;

    element_arr = new_element_arr;
    HashSet<var_type>::real_size = new_size;
}

template<typename var_type>
void HashSet<var_type>::copy_list(LinkedList<var_type>* new_lst, int new_size){
    // running through all buckets
    for (int i = 0; i < real_size; i ++){
        // if there is at least one element |look at the LinkedList|
        if (HashSet<var_type>::element_arr[i] != nullptr){
            // for all element in linked list
            for (auto element: element_arr[i]){

                long long int  hash = HashSet<var_type>::getHash(element);

                if (hash < 0) hash = -hash;

                int position = hash % new_size;

                new_lst[position].add(element);

            }
        }
    }
}

template<typename var_type>
long long HashSet<var_type>::next_prime(){
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

template<typename var_type>
bool HashSet<var_type>::is_prime(long long num) {
    if (num < 2) return false;
    if (num == 2 || num == 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;

    int sqrt_num = static_cast<long long>(std::sqrt(num));
    for (long long i = 5; i <= sqrt_num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0)
            return false;
    }
    return true;
}
#endif //LEARNING_HASHSET_H
