//
// Created by Volodymyr Avvakumov on 26.10.2024.
//
#include <iostream>
#include <type_traits>

#include "LinkedList.h"

#ifndef LEARNING_HASHSET_H
#define LEARNING_HASHSET_H


/**
 * @brief A templated HashSet class implementing a hash set using separate chaining.
 *
 * This class provides functionality to add, check, and remove elements from the set.
 * It automatically resizes when the occupancy exceeds 75% to maintain efficiency.
 *
 * @tparam var_type The type of elements stored in the HashSet.
 */
template<typename var_type>
class HashSet {
protected:
    int real_size;                 /**< The current size of the hash table. */
    int element_count;             /**< The number of elements currently in the hash set. */
    int curr_pow_for_primes;       /**< The current power used to determine the next prime size. */

    LinkedList<var_type>* element_arr; /**< Array of linked lists for separate chaining. */

public:

    /**
     * @brief Default constructor.
     *
     * Initializes the hash set with a default size and sets up the linked lists.
     */
    HashSet();

    /**
     * @brief Destructor.
     *
     * Cleans up the allocated memory for the hash table.
     */
    ~HashSet(){
        delete[] element_arr;
    }


    /**
     * @brief Adds an element to the HashSet.
     *
     * If the occupancy exceeds 75%, the hash table is resized to maintain performance.
     *
     * @param var The element to be added.
     */
    void add(var_type var);

    /**
     * @brief Checks if an element exists in the HashSet.
     *
     * @param var The element to check for.
     * @return true If the element is present.
     * @return false Otherwise.
     */
    bool is_in(var_type var);

    /**
     * @brief Removes an element from the HashSet.
     *
     * Deletes the element by finding its hash and removing it from the corresponding linked list.
     *
     * @param var The element to be removed.
     * @throws std::logic_error If the element is not found.
     */
    void pop(var_type var);

    /**
     * @brief Retrieves the number of elements in the HashSet.
     *
     * @return int The count of elements.
     */
    int getSize(){
        return element_count;
    }

    /**
     * @brief Prints the contents of the HashSet.
     *
     * Iterates through all linked lists and prints their elements.
     *
     * @param out The output stream to print to. Defaults to std::cout.
     */
    void print(std::ostream& out = std::cout) const;


protected:

    /**
     * @brief Computes the hash for integral types.
     *
     * Uses bitwise operations to generate a hash value for integers.
     *
     * @tparam T Integral type.
     * @param value The value to hash.
     * @return long long int The computed hash.
     */
    template <typename T>
    typename std::enable_if<std::is_integral<T>::value, long long int>::type
    getHash(T value);

    /**
     * @brief Computes the hash for floating-point types.
     *
     * Processes the binary representation of floating-point numbers to generate a hash.
     *
     * @tparam T Floating-point type.
     * @param value The value to hash.
     * @return long long int The computed hash.
     */
    template <typename T>
    typename std::enable_if<std::is_floating_point<T>::value, long long int>::type
    getHash(T value);


    /**
     * @brief Computes the hash for pointer types.
     *
     * Hashes the memory address of the pointer.
     *
     * @tparam T Pointer type.
     * @param value The pointer to hash.
     * @return long long int The computed hash.
     */
    template <typename T>
    typename std::enable_if<std::is_pointer<T>::value, long long int>::type
    getHash(T value);

    /**
     * @brief Computes the hash for std::string.
     *
     * Processes each character in the string to generate a hash.
     *
     * @param value The string to hash.
     * @return long long int The computed hash.
     */
    long long int getHash(const std::string& value) const;

    /**
     * @brief Calculates the current occupancy of the hash table.
     *
     * Determines the percentage of filled elements relative to the total size.
     *
     * @return float The occupancy percentage.
     */
    float get_occupancy(){
        if (HashSet<var_type>::real_size == 0) return 0;
        return ((float)HashSet<var_type>::element_count / HashSet<var_type>::real_size) * 100;
    }

    /**
     * @brief Resizes the hash table by creating a new array with a larger prime size.
     *
     * Allocates a new array, rehashes existing elements, and replaces the old array.
     */
    void create_new_elements_arr();

    /**
     * @brief Copies all elements from the old hash table to the new one.
     *
     * Rehashes each element and inserts it into the appropriate linked list in the new array.
     *
     * @param new_lst Pointer to the new array of linked lists.
     * @param new_size The size of the new array.
     */
    void copy_list(LinkedList<var_type>* new_lst, int new_size);


    /**
     * @brief Finds the next prime number for resizing the hash table.
     *
     * Searches for prime numbers within the range [2^k, 2^(k+1)-1]. If no prime is found,
     * it increments k and searches the next range.
     *
     * @return long long The next prime number to be used as the new size.
     */
    long long next_prime();

    /**
     * @brief Checks if a number is prime.
     *
     * Uses trial division to determine if a number is prime.
     *
     * @param num The number to check.
     * @return true If the number is prime.
     * @return false Otherwise.
     */
    static bool is_prime(long long num);

    /**
     * @brief Overloads the insertion operator to print the HashSet.
     *
     * @param out The output stream.
     * @param set The HashSet to print.
     * @return std::ostream& The output stream.
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
