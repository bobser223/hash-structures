//
// Created by Volodymyr Avvakumov on 27.10.2024.
//
#include <stdexcept>
#include <iostream>

#ifndef LEARNING_LINKEDLIST_DICT_H
#define LEARNING_LINKEDLIST_DICT_H


/**
 * @brief A structure representing a node in the linked list for HashDict.
 *
 * @tparam key_type The type of the key stored in the node.
 * @tparam value_type The type of the value stored in the node.
 */
template<typename key_type, typename value_type>
struct ListEl{
    bool is_empty;                                 /**< Flag indicating if the node is empty (actually useless). */
    key_type key;                                  /**< The key stored in the node. */
    value_type value;                              /**< The value associated with the key. */
    ListEl<key_type, value_type>* next_pointer;    /**< Pointer to the next node in the list. */
};


/**
 * @brief A structure representing a key-value pair.
 *
 * @tparam key_type The type of the key.
 * @tparam value_type The type of the value.
 */
template<typename key_type, typename value_type>
struct Couple{
    key_type key;          /**< The key of the pair. */
    value_type value;      /**< The value of the pair. */
};


/**
 * @brief A templated singly linked list class for HashDict.
 *
 * Provides functionality to add, check, and remove key-value pairs.
 * Supports access to values by key and iteration through the list.
 *
 * @tparam key_type The type of keys stored in the linked list.
 * @tparam value_type The type of values associated with the keys.
 */
template<typename key_type, typename value_type>
class LinkedList_dict {
private:

    int size;                                /**< The number of key-value pairs in the list. */
    ListEl<key_type, value_type>* first_el;  /**< Pointer to the first element in the list. */

public:
    /**
     * @brief Default constructor.
     *
     * Initializes an empty linked list.
     */
    LinkedList_dict() : size(0), first_el(nullptr) {}

    /**
     * @brief Destructor.
     *
     * Cleans up all nodes in the linked list.
     */
    ~LinkedList_dict();

     /**
     * @brief Adds a key-value pair to the linked list.
     *
     * Adds a new key-value pair to the end of the list if the key does not already exist.
     *
     * @param key The key to add.
     * @param value The value associated with the key.
     */
    void add(key_type key, value_type value);

    /**
     * @brief Checks if a key exists in the linked list.
     *
     * @param key The key to check for.
     * @return true If the key is present.
     * @return false Otherwise.
     */
    bool is_in(key_type key);

    /**
     * @brief Removes a key-value pair from the linked list.
     *
     * Deletes the node containing the specified key.
     *
     * @param key The key to remove.
     * @throws std::logic_error If the key is not found.
     */
    void pop(key_type key);

    /**
     * @brief Retrieves the number of key-value pairs in the linked list.
     *
     * @return int The count of elements.
     */
    int get_size(){
        return size;
    }

    // operators

    /**
     * @brief Overloads the equality operator.
     *
     * Compares the first element of the list with a given value.
     *
     * @tparam name The type of the value to compare.
     * @param var The value to compare with the first element.
     * @return true If the first element is equal to the value.
     * @return false Otherwise.
     */
    template<class name>
    bool operator==(name var){
        return first_el == var;
    }

    /**
     * @brief Overloads the inequality operator.
     *
     * Compares the first element of the list with a given value.
     *
     * @tparam name The type of the value to compare.
     * @param var The value to compare with the first element.
     * @return true If the first element is not equal to the value.
     * @return false Otherwise.
     */
    template<class name>
    bool operator!=(name var){
        return first_el != var;
    }

    /**
      * @brief Overloads the subscript operator to access values by key (const version).
      *
      * Finds the value associated with the given key. Throws an error if the key does not exist.
      * Allows copying the value associated with the key.
      *
      * Example:
      * @code
      * LinkedList_dict<int, std::string> list;
      * list.add(1, "one");
      * std::string value = list[1];
      * @endcode
      *
      * @param key The key whose associated value is to be accessed.
      * @return const value_type& Const reference to the value associated with the key.
      * @throws std::logic_error If the key is not found.
      */
    const value_type& operator[](key_type key) const;

    /**
     * @brief Overloads the subscript operator to access values by key.
     *
     * Finds the value associated with the given key. Throws an error if the key does not exist.
     * Allows modifying the value associated with the key.
     *
     * Example:
     * @code
     * LinkedList_dict<int, std::string> list;
     * list.add(1, "one");
     * list[1] = "uno";
     * @endcode
     *
     * @param key The key whose associated value is to be accessed.
     * @return value_type& Reference to the value associated with the key.
     * @throws std::logic_error If the key is not found.
     */
    value_type& operator[](key_type key);

    /**
     * @brief Prints the contents of the linked list.
     *
     * Iterates through all nodes and prints their key-value pairs.
     *
     * @param out The output stream to print to. Defaults to std::cout.
     */
    void print(std::ostream& out = std::cout) const;

    /**
     * @brief Overloads the insertion operator to print the LinkedList_dict.
     *
     * @param out The output stream.
     * @param lst The LinkedList_dict to print.
     * @return std::ostream& The output stream.
     */
    friend std::ostream& operator <<(std::ostream& out,const LinkedList_dict& lst){
        lst.print(out);
        return out;
    }


protected:
    /**
     * @brief Retrieves a key-value pair by index.
     *
     * Finds the key-value pair at the specified index and returns it as a Couple structure.
     *
     * @param index The index of the desired key-value pair.
     * @return Couple<key_type, value_type> The key-value pair at the specified index.
     * @throws std::logic_error If the index is out of bounds.
     */
    Couple<key_type,value_type> get_couple(int index);

    /**
     * @brief Finds the node with the specified key and its preceding node.
     *
     * Searches the list for the specified key and sets pointers to the previous
     * and target nodes.
     *
     * @param key The key to search for.
     * @param previous_element Reference to a pointer that will point to the preceding node.
     * @param element_to_delete Reference to a pointer that will point to the target node.
     * @throws std::logic_error If the key is not found.
     */
    void find_element_with_key(key_type key, ListEl<key_type, value_type>*& previous_element, ListEl<key_type, value_type>*& element_to_delete) const;


    template <typename T>
    friend class HashSet;

    template<typename key_t, typename value_t>
    friend class HashDict;
}; // End of the class


// public

template<typename key_type, typename value_type>
LinkedList_dict<key_type, value_type>::~LinkedList_dict(){
    ListEl<key_type, value_type>* curr_el= first_el;
    while (curr_el != nullptr){

        ListEl<key_type, value_type>* next = curr_el->next_pointer;
        delete curr_el;
        curr_el = next;
    }
}

template<typename key_type, typename value_type>
void LinkedList_dict<key_type, value_type>::add(key_type key, value_type value){

    if(is_in(key))  return; // do nothing

    ListEl<key_type, value_type>* new_el = new ListEl<key_type, value_type>;
    new_el -> key = key;
    new_el -> value = value;
    new_el -> next_pointer = nullptr;
    new_el ->is_empty = false;
    if (size == 0){
        first_el = new_el;
    } else {
        ListEl<key_type, value_type>* curr_el = first_el;
        // while element is not last
        while (curr_el -> next_pointer != nullptr){
            curr_el = curr_el -> next_pointer;
        }
        curr_el -> next_pointer = new_el;
    }

    size ++;

}

template<typename key_type, typename value_type>
bool LinkedList_dict<key_type, value_type>::is_in(key_type key){
    if (size == 0){
        return false;
    } else {

        ListEl<key_type, value_type>* curr_el = first_el;
        while (curr_el != nullptr){
            if (curr_el->key == key && !curr_el->is_empty) return true;
            curr_el = curr_el->next_pointer;
        }
        return false;
    }
}

template<typename key_type, typename value_type>
void LinkedList_dict<key_type, value_type>::pop(key_type key){
    if (!is_in(key)){
        throw std::logic_error("this variable isn't here!!!");
    }

    if (size == 1){
        delete first_el;
        first_el = nullptr;
    } else if (first_el->key == key){
        ListEl<key_type, value_type>* temp = first_el;
        first_el = first_el->next_pointer;
        delete temp;
    } else {
        ListEl<key_type, value_type>* previous_element = nullptr;
        ListEl<key_type, value_type>* element_to_delete = nullptr;
        find_element_with_key(key, previous_element, element_to_delete);

        if (element_to_delete != nullptr && previous_element != nullptr){
            previous_element->next_pointer = element_to_delete->next_pointer;
            delete element_to_delete;
        }
    }

    size--;
}

template<typename key_type, typename value_type>
const value_type& LinkedList_dict<key_type, value_type>::operator[](key_type key) const{
    if (size == 0){
        throw std::logic_error("no elements here!!!");
    } else {

        ListEl<key_type, value_type>* curr_el = first_el;
        while (curr_el != nullptr){
            if (curr_el->key == key && !curr_el->is_empty) return curr_el ->value;
            curr_el = curr_el->next_pointer;
        }
        throw std::logic_error("no element here!!!");
    }
}

template<typename key_type, typename value_type>
value_type& LinkedList_dict<key_type, value_type>::operator[](key_type key){
    if (size == 0){
        throw std::logic_error("no elements here!!!");
    } else {

        ListEl<key_type, value_type>* curr_el = first_el;
        while (curr_el != nullptr){
            if (curr_el->key == key && !curr_el->is_empty) return curr_el ->value;
            curr_el = curr_el->next_pointer;
        }
        throw std::logic_error("no element here!!!");
    }
}

template<typename key_type, typename value_type>
void LinkedList_dict<key_type, value_type>::print(std::ostream& out) const{
    ListEl<key_type, value_type>* curr_el = first_el;
    while (curr_el != nullptr){
        out << curr_el -> key << ':' << curr_el -> value << ' ';
        curr_el = curr_el ->next_pointer;
    }
}


// protected


template<typename key_type, typename value_type>
Couple<key_type,value_type> LinkedList_dict<key_type, value_type>::get_couple(int index){
    if (index > size - 1) throw std::logic_error("too big index!!!");

    ListEl<key_type, value_type>* curr_el = first_el;

    int i = 0;
    while(i <= index){
        if (i == index){
            Couple<key_type, value_type> c;
            c.key = curr_el ->key;
            c.value = curr_el ->value;
            return c;
        }
        curr_el = curr_el -> next_pointer;
        i++;
    }


}

template<typename key_type, typename value_type>
void LinkedList_dict<key_type, value_type>::find_element_with_key(key_type key, ListEl<key_type, value_type>*& previous_element, ListEl<key_type, value_type>*& element_to_delete) const {
    if (size == 0){
        throw std::logic_error("no elements here!!!");
    }

    previous_element = nullptr;
    element_to_delete = nullptr;
    ListEl<key_type, value_type>* curr_el = first_el;

    while (curr_el != nullptr){
        if (curr_el->key == key && !curr_el->is_empty){
            element_to_delete = curr_el;
            break;
        }
        previous_element = curr_el;
        curr_el = curr_el->next_pointer;
    }

    if (element_to_delete == nullptr){
        throw std::logic_error("Element not found!");
    }
}

#endif //LEARNING_LINKEDLIST_DICT_H
