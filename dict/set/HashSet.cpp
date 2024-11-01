//
// Created by Volodymyr Avvakumov on 26.10.2024.
//
#include <stdexcept>
#include "HashSet.h"
#include "LinkedList.h"

template <typename var_type>
void HashSet<var_type>::add(var_type var){

    if (HashSet<var_type>::get_occupancy() > 75)  // checking occupancy if it < 75% just add element
        HashSet<var_type>::create_new_elements_list();

    int hash = HashSet<var_type>::getHash(var);
    int position = hash % HashSet<var_type>::real_size;

    if (HashSet<var_type>::element_arr[position] != nullptr) {
        LinkedList<var_type> lst;
        HashSet<var_type>::element_arr[position] = lst;
        lst.add(var);

    } else {
        // Fixing collision;
        element_arr[position]-> add(var);
    }

    HashSet<var_type>::element_count++;
}

template <typename var_type>
void HashSet<var_type>::pop(var_type var){

    int hash = HashSet<var_type>::getHash(var);
    int position = hash % HashSet<var_type>::real_size;

    if (HashSet<var_type>::element_arr[position] != nullptr){
        element_arr[position] -> pop(var);
        element_count --;
    } else{
        throw std::logic_error("no elements here!!!");
    }
}


template <typename var_type>
void HashSet<var_type>::print(std::ostream& out){
    for (int i = 0; i < real_size; i++){
        if (element_arr[i] == nullptr) continue;
        out << element_arr[i] << " ";
    }
}

template <typename var_type> // TODO: do not forget to delete this;
void HashSet<var_type>::debug_print(std::ostream& out){
    for (int i = 0; i < real_size; i++){
        if (element_arr[i] == nullptr){
            out << "NONE" << " ";
            continue;
        }
        out << element_arr[i] << " ";
    }
}


template <typename var_type>
void HashSet<var_type>::create_new_elements_list() {
    long long new_size = HashSet<var_type>::next_prime();

    LinkedList<var_type>* new_element_arr = new LinkedList<var_type>[new_size];

    HashSet<var_type>::copy_list(new_element_arr, new_size);

    delete[] HashSet<var_type>::element_arr;
    element_arr = new_element_arr;
    HashSet<var_type>::real_size = new_size;
}

template <typename var_type> // TODO refactor for LIST
void HashSet<var_type>::copy_list(LinkedList<var_type>* new_lst,int new_size) {
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

template <typename var_type>
float HashSet<var_type>::get_occupancy() {
    if (HashSet<var_type>::real_size == 0) return 0;
    return ((float)HashSet<var_type>::element_count / HashSet<var_type>::real_size) * 100;
}

//template <typename var_type>
//int HashSet<var_type>::next_prime() {
//    int min_lim = pow(2, curr_pow_for_primes);
//    int max_lim = pow(2, curr_pow_for_primes+1);
//    for (int i = min_lim; i < max_lim; i++){
//        if (HashSet<var_type>::is_prime(i)){
//            curr_pow_for_primes ++;
//            return i;
//        }
//    }
//    // if no primes from 2^k-1 to 2^k;
//    curr_pow_for_primes ++;
//    return HashSet<var_type>::next_prime();
//}

template <typename var_type>
long long HashSet<var_type>::next_prime() {
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

template <typename var_type>
bool HashSet<var_type>::is_prime(long long num) {
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

