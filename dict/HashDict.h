//
// Created by Volodymyr Avvakumov on 27.10.2024.
//

#include "LinkedList_dict.h"

#ifndef LEARNING_HASHDICT_H
#define LEARNING_HASHDICT_H

/**
 * @brief A templated HashDict class implementing a hash table using separate chaining.
 *
 * This class provides functionality to add, check, and remove key-value pairs.
 * It automatically resizes when the occupancy exceeds 75% to maintain efficiency.
 *
 * @tparam key_t The type of keys stored in the HashDict.
 * @tparam value_t The type of values associated with the keys.
 */

template<typename key_t,typename value_t>
class HashDict {
protected:
    int real_size;                                /**< The current size of the hash table. */
    int element_count;                            /**< The number of key-value pairs currently in the hash dictionary. */
    int curr_pow_for_primes;                      /**< The current power used to determine the next prime size. */

    LinkedList_dict<key_t, value_t>* element_arr; /**< Array of linked lists for separate chaining. */
public:
    /**
     * @brief Default constructor.
     *
     * Initializes the hash dictionary with a default size and sets up the linked lists.
     */
    HashDict();

    /**
     * @brief Destructor.
     *
     * Cleans up the allocated memory for the hash table.
     */
    ~HashDict(){
        delete[] element_arr;
    }

    /**
     * @brief Adds a key-value pair to the HashDict.
     *
     * If the occupancy exceeds 75%, the hash table is resized to maintain performance.
     *
     * @param key The key to be added.
     * @param value The value associated with the key.
     */
    void add(key_t key, value_t value);

    /**
     * @brief Removes a key-value pair from the HashDict.
     *
     * Finds the key's hash, locates the appropriate bucket, and removes the key-value pair.
     *
     * @param key The key to be removed.
     * @throws std::logic_error If the key is not found.
     */
    void pop(key_t key);

    /**
     * @brief Checks if a key exists in the HashDict.
     *
     * Finds the key's hash, locates the appropriate bucket, and checks for the key's existence.
     *
     * @param key The key to check for.
     * @return true If the key is present.
     * @return false Otherwise.
     */
    bool is_in(key_t key);

    /**
     * @brief Retrieves the number of key-value pairs in the HashDict.
     *
     * @return int The count of elements.
     */
    [[nodiscard]] int getSize() const {
        return element_count;
    }

    /**
     * @brief Retrieves the current size of the hash table.
     *
     * @return int The size of the hash table.
     */
    [[nodiscard]] int getTrueSize() const {
        return real_size;
    }


    // operators


    /**
     * @brief Overloads the subscript operator to access values by key.
     *
     * Finds the value associated with the given key. Throws an error if the key does not exist.
     * Allows modifying the value associated with the key.
     *
     * Example:
     * @code
     * HashDict<int, std::string> dict;
     * dict.add(1, "one");
     * dict[1] = "uno";
     * @endcode
     *
     * @param key The key whose associated value is to be accessed.
     * @return value_t& Reference to the value associated with the key.
     * @throws std::logic_error If the key is not found.
     */
    value_t& operator[](key_t key);


    /**
     * @brief Overloads the subscript operator to access values by key (const version).
     *
     * Finds the value associated with the given key. Throws an error if the key does not exist.
     * Allows copying the value associated with the key.
     *
     * Example:
     * @code
     * HashDict<int, std::string> dict;
     * dict.add(1, "one");
     * std::string value = dict[1];
     * @endcode
     *
     * @param key The key whose associated value is to be accessed.
     * @return const value_t& Const reference to the value associated with the key.
     * @throws std::logic_error If the key is not found.
     */
    const value_t& operator[](key_t key) const;

    /**
     * @brief Prints the contents of the HashDict.
     *
     * Iterates through each linked list and prints its key-value pairs.
     *
     * @param out The output stream to print to. Defaults to std::cout.
     */
    void print(std::ostream& out = std::cout) const;


protected:

    /**
     * @brief Adds a key-value pair to a specified array.
     *
     * Used internally when resizing the hash table to add elements to the new array.
     *
     * @param arr Pointer to the new array of linked lists.
     * @param arr_size The size of the new array.
     * @param key The key to add.
     * @param value The value associated with the key.
     */
    void add_to_array(LinkedList_dict<key_t, value_t>* arr,int arr_size, key_t key, value_t value);

    /**
     * @brief Computes the hash for integral types.
     *
     * Uses bitwise operations to generate a hash value for integers.
     *
     * @tparam T Integral type.
     * @param value The value to hash.
     * @param size The size of the hash table.
     * @return long long int The computed hash modulo the table size.
     */
    template <typename T>
    typename std::enable_if<std::is_integral<T>::value, long long int>::type
    getHash(T value, int size) const;

    /**
     * @brief Computes the hash for floating-point types.
     *
     * Processes the binary representation of floating-point numbers to generate a hash.
     *
     * @tparam T Floating-point type.
     * @param value The value to hash.
     * @param size The size of the hash table.
     * @return long long int The computed hash modulo the table size.
     */
    template <typename T>
    typename std::enable_if<std::is_floating_point<T>::value, long long int>::type
    getHash(T value, int size) const;

    /**
     * @brief Computes the hash for pointer types.
     *
     * Hashes the memory address of the pointer.
     *
     * @tparam T Pointer type.
     * @param value The pointer to hash.
     * @param size The size of the hash table.
     * @return long long int The computed hash modulo the table size.
     */
    template <typename T>
    typename std::enable_if<std::is_pointer<T>::value, long long int>::type
    getHash(T value, int size) const;

    /**
     * @brief Computes the hash for std::string.
     *
     * Processes each character in the string to generate a hash.
     *
     * @param value The string to hash.
     * @param size The size of the hash table.
     * @return long long int The computed hash modulo the table size.
     */
    [[nodiscard]] long long int getHash(const std::string& value, int size) const;

    /**
     * @brief Calculates the current occupancy of the hash table.
     *
     * Determines the percentage of filled elements relative to the total size.
     *
     * @return float The occupancy percentage.
     */
    float get_occupancy();

    /**
     * @brief Resizes the hash table by creating a new array with a larger prime size.
     *
     * Allocates a new array, rehashes existing elements, and replaces the old array.
     */
    void create_new_elements_arr();

    /**
     * @brief Copies all elements from the old hash table to the new one.
     *
     * Rehashes each key-value pair and inserts it into the appropriate linked list in the new array.
     *
     * @param new_arr Pointer to the new array of linked lists.
     * @param new_size The size of the new array.
     */
    void copy_list(LinkedList_dict<key_t, value_t>* new_arr, int new_size);


    /**
     * @brief Finds the next prime number for resizing the hash table.
     *
     * Searches for prime numbers within the range [2^k, 2^(k+1)-1]. If no prime is found,
     * it increments k and searches the next range recursively.
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
     * @brief Overloads the insertion operator to print the HashDict.
     *
     * @param out The output stream.
     * @param dict The HashDict to print.
     * @return std::ostream& The output stream.
     */
    friend std::ostream& operator <<(std::ostream& out,const HashDict& dict){
        dict.print(out);
        return out;
    }
}; // End of the class



// methods implementation

//public:

template<typename key_t,typename value_t>
HashDict<key_t, value_t>::HashDict() {
    real_size = 5;
    element_count = 0;
    curr_pow_for_primes = 3;
    element_arr = new LinkedList_dict<key_t, value_t>[real_size];
}

template<typename key_t,typename value_t>
void HashDict<key_t, value_t>::add(key_t key, value_t value){

    // preventing an increase in the chance of collision by enlarging an element array
    if (HashDict<key_t, value_t>::get_occupancy() > 75)
        HashDict<key_t, value_t>::create_new_elements_arr();

    unsigned position = HashDict<key_t, value_t>::getHash(key, real_size);

    HashDict<key_t, value_t>::element_arr[position].add(key, value);

    HashDict<key_t, value_t>::element_count++;
}

template<typename key_t,typename value_t>
void HashDict<key_t, value_t>::pop(key_t key){

    int position = HashDict<key_t, value_t>::getHash(key, real_size);
    // if element_arr[i] is not empty, overloaded operator, look to LinkedList.h
    if (HashDict<key_t, value_t>::element_arr[position] != nullptr){
        element_arr[position].pop(key);
        element_count --;
    } else{
        throw std::logic_error("no elements here!!!");
    }
}

template<typename key_t,typename value_t>
bool HashDict<key_t, value_t>::is_in(key_t key){
    int position = HashDict<key_t, value_t>::getHash(key, real_size);
    // calling LinkedList func is_in
    return HashDict<key_t, value_t>::element_arr[position].is_in(key);
}

template<typename key_t,typename value_t>
value_t& HashDict<key_t, value_t>::operator[](key_t key) {
    if(!is_in(key)) throw std::logic_error("no such key in the dict!!!");
    int position = HashDict<key_t, value_t>::getHash(key, real_size);
    return element_arr[position][key];
}

template<typename key_t,typename value_t>
const value_t& HashDict<key_t, value_t>::operator[](key_t key) const{
    if(!is_in(key)) throw std::logic_error("no such key in the dict!!!");
    int position = getHash(key, real_size);
    return element_arr[position][key];
}

template<typename key_t,typename value_t>
void HashDict<key_t, value_t>::print(std::ostream& out) const {
    for (int i = 0; i < real_size; i++){
        // if element_arr[i] is empty, overloaded operator, look at LinkedList_dict.h
        if (element_arr[i] == nullptr) continue;
        out << element_arr[i] << " ";
    }
}


//protected:


// hash functions
template<typename key_t,typename value_t>
template <typename T>
typename std::enable_if<std::is_integral<T>::value, long long int>::type
HashDict<key_t, value_t>::getHash(T value, int size) const {
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

    return result % size;
}

template<typename key_t,typename value_t>
template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, long long int>::type
HashDict<key_t, value_t>::getHash(T value, int size) const {
    long long int result = 0;
    unsigned char* bytePtr = reinterpret_cast<unsigned char*>(&value);
    for (size_t i = 0; i < sizeof(T); ++i) {
        result = (result << 5) | (result >> (sizeof(long long int) * 8 - 5));
        result ^= bytePtr[i];
    }

    return result % size;
}

template<typename key_t,typename value_t>
template <typename T>
typename std::enable_if<std::is_pointer<T>::value, long long int>::type
HashDict<key_t, value_t>::getHash(T value, int size) const {
    long long int result = 0;
    uintptr_t ptr = reinterpret_cast<uintptr_t>(value);
    unsigned char* bytePtr = reinterpret_cast<unsigned char*>(&ptr);
    for (size_t i = 0; i < sizeof(ptr); ++i) {
        result = (result << 5) | (result >> (sizeof(long long int) * 8 - 5));
        result ^= bytePtr[i];
    }
    return result % size;
}

template<typename key_t,typename value_t>
long long int HashDict<key_t, value_t>::getHash(const std::string& value, int size) const{
    long long int result = 0;
    for (char c : value) {
        result = (result << 5) | (result >> (sizeof(long long int) * 8 - 5));
        result ^= static_cast<unsigned char>(c);
    }
    return result % size;
}


// buffer scaling functions
template<typename key_t,typename value_t>
void HashDict<key_t, value_t>::add_to_array(LinkedList_dict<key_t, value_t>* arr,int arr_size, key_t key, value_t value){
    int position = HashDict<key_t, value_t>::getHash(key, arr_size);
    // in fact LinkedList.add(key, value)
    arr[position].add(key, value);
}

template<typename key_t,typename value_t>
float HashDict<key_t, value_t>::get_occupancy(){
    if (real_size == 0) return 0;
    return ((float)element_count / real_size) * 100;
}

template<typename key_t,typename value_t>
void HashDict<key_t, value_t>::create_new_elements_arr(){
        long long new_size = HashDict<key_t, value_t>::next_prime();

        LinkedList_dict<key_t, value_t>* new_element_arr = new LinkedList_dict<key_t, value_t>[new_size];

        HashDict<key_t, value_t>::copy_list(new_element_arr, new_size);

        delete[] HashDict<key_t, value_t>::element_arr;
        element_arr = new_element_arr;
        HashDict<key_t, value_t>::real_size = new_size;
}

template<typename key_t,typename value_t>
void HashDict<key_t, value_t>::copy_list(LinkedList_dict<key_t, value_t>* new_arr, int new_size){
    // running through all buckets
    for (int i = 0; i < real_size; i ++){
        // if there is at least one element |look at the LinkedList_dict|
        if (element_arr[i] != nullptr){
            // for all element in linked list
            for (int j = 0; j < element_arr[i].get_size(); j++){
                Couple<key_t, value_t> c = element_arr[i].get_couple(j);
                add_to_array(new_arr, new_size, c.key, c.value);
            }
        }
    }

}

template<typename key_t,typename value_t>
long long HashDict<key_t, value_t>::next_prime(){
    long long min_lim = pow(2, curr_pow_for_primes);
    long long max_lim = pow(2, curr_pow_for_primes+1);

    long long middle = (min_lim + max_lim) / 2;
    for (long long i = middle; i < max_lim - 1; i++){
        if (HashDict<key_t, value_t>::is_prime(middle - i)){
            curr_pow_for_primes ++;
            return middle - i;
        }
        if (HashDict<key_t, value_t>::is_prime(middle + i)){
            curr_pow_for_primes ++;
            return middle + i;
        }
    }
    // if no primes from 2^k-1 to 2^k;
    curr_pow_for_primes ++;
    return HashDict<key_t, value_t>::next_prime();
}

template<typename key_t,typename value_t>
bool HashDict<key_t, value_t>::is_prime(long long num){
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

#endif //LEARNING_HASHDICT_H