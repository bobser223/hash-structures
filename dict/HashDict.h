//
// Created by Volodymyr Avvakumov on 27.10.2024.
//

#include "LinkedList_dict.h"

#ifndef LEARNING_HASHDICT_H
#define LEARNING_HASHDICT_H

template<typename key_t,typename value_t>
class HashDict {
protected:
    int real_size;
    int element_count;
    int curr_pow_for_primes;

    LinkedList_dict<key_t, value_t>* element_arr;
public:
    HashDict(){
        real_size = 5;
        element_count = 0;
        curr_pow_for_primes = 3;
        element_arr = new LinkedList_dict<key_t, value_t>[real_size];
        for (int i = 0; i < 5; i++) element_arr[i].first_el = nullptr;
    }

    ~HashDict(){
        delete[] element_arr;
    }
    // standard dict methods
    void add(key_t key, value_t value);
    /*
     * if there less than 25% of free buckets in elements arr creating new longer arr
     * if not just continue
     *  than finds key's hash
     * adds key and value to element_arr by hash
     *  |look to the LinkedList_dict for understanding structure|
     */

    void pop(key_t key);
    /*
     *  finds key's hash
     *  finds place in the element_arr by hash
     *  using LinkedList_dict method pop
     *  |look to the LinkedList_dict for understanding structure|
     */

    bool is_in(key_t key);
    /*
     *  finds key's hash
     *  finds place in the element_arr by hash
     *  using LinkedList_dict method is_in
     *  |look to the LinkedList_dict for understanding structure|
     */

    int getSize() const {
        return element_count;
    }
    /*
     * @return count of elements
     */

    int getTrueSize() const {
        return real_size;
    }
    /*
     * @return buffer size
     */

    // operators
    value_t& operator[](key_t key);
    /*
     * finds value by key
     * for changing value
     * dict[key] = value2;
     */

    const value_t& operator[](key_t key) const;
    /*
     * finds value by key
     * for copying value
     * value_t value_var = dict[key]
     */

    void print(std::ostream& out = std::cout) const {
        for (int i = 0; i < real_size; i++){
            // if bucket is empty
            if (element_arr[i] == nullptr) continue;
            out << element_arr[i] << " ";
        }
    }

protected:
    void add_to_array(LinkedList_dict<key_t, value_t>* arr,int arr_size, key_t key, value_t value);
    /*
     * realisation add method for new element_arr
     * @param arr | new element_arr
     * @param arr_size | size of new element_arr
     * @param key | key to add
     * @param value | value to add
     * @return void but in fact changing arr
     */

    template <typename T>
    typename std::enable_if<std::is_integral<T>::value, long long int>::type
    getHash(T value, int size) const {
        long long int result = 0;
        while (value) {
            result = (result << 5) | (result >> (sizeof(long long int) * 8 - 5));
            result ^= (value & 0xFF);
            value >>= 8;
        }

        return result % size;
    }

    template <typename T>
    typename std::enable_if<std::is_floating_point<T>::value, long long int>::type
    getHash(T value, int size) const {
        long long int result = 0;
        unsigned char* bytePtr = reinterpret_cast<unsigned char*>(&value);
        for (size_t i = 0; i < sizeof(T); ++i) {
            result = (result << 5) | (result >> (sizeof(long long int) * 8 - 5));
            result ^= bytePtr[i];
        }

        return result % size;
    }

    template <typename T>
    typename std::enable_if<std::is_pointer<T>::value, long long int>::type
    getHash(T value, int size) const {
        long long int result = 0;
        uintptr_t ptr = reinterpret_cast<uintptr_t>(value);
        unsigned char* bytePtr = reinterpret_cast<unsigned char*>(&ptr);
        for (size_t i = 0; i < sizeof(ptr); ++i) {
            result = (result << 5) | (result >> (sizeof(long long int) * 8 - 5));
            result ^= bytePtr[i];
        }
        return result % size;
    }

    [[nodiscard]] long long int getHash(const std::string& value, int size) const{
        long long int result = 0;
        for (char c : value) {
            result = (result << 5) | (result >> (sizeof(long long int) * 8 - 5));
            result ^= static_cast<unsigned char>(c);
        }
        return result % size;
    }
    // for random type;
    template <typename T>
    typename std::enable_if<!std::is_integral<T>::value &&
                            !std::is_floating_point<T>::value &&
                            !std::is_pointer<T>::value, long long int>::type
    getHash(const T& value, int size) const {
        long long int result = 0;
        const unsigned char* bytePtr = reinterpret_cast<const unsigned char*>(&value);
        for (size_t i = 0; i < sizeof(T); ++i) {
            result = (result << 5) | (result >> (sizeof(long long int) * 8 - 5));
            result ^= bytePtr[i];
        }
        return (result % size);
    }

    float get_occupancy();
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

    void copy_list(LinkedList_dict<key_t, value_t>* new_arr, int new_size);
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

    friend std::ostream& operator <<(std::ostream& out,const HashDict& dict){
        dict.print(out);
        return out;
    }
}; // End of class



// methods implementation
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

    if (HashDict<key_t, value_t>::element_arr[position] != nullptr){
        element_arr[position].pop(key);
        element_count --;
    } else{
        throw std::logic_error("no elements here!!!");
    }
} //FIXME: no if else

template<typename key_t,typename value_t>
bool HashDict<key_t, value_t>::is_in(key_t key){
    int position = HashDict<key_t, value_t>::getHash(key, real_size);
    // calling LinkedList func is_in
    return HashDict<key_t, value_t>::element_arr[position].is_in(key);
}

template<typename key_t,typename value_t>
value_t& HashDict<key_t, value_t>::operator[](key_t key) {
    int position = HashDict<key_t, value_t>::getHash(key, real_size);
    return element_arr[position][key];
}

template<typename key_t,typename value_t>
const value_t& HashDict<key_t, value_t>::operator[](key_t key) const{
    int position = getHash(key, real_size);
    return element_arr[position][key];
}







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

