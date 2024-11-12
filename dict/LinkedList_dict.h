//
// Created by Volodymyr Avvakumov on 27.10.2024.
//
#include <stdexcept>
#include <iostream>

#ifndef LEARNING_LINKEDLIST_DICT_H
#define LEARNING_LINKEDLIST_DICT_H



template<typename key_type, typename value_type>
struct ListEl{
    bool is_empty;
    key_type key;
    value_type value;
    ListEl<key_type, value_type>* next_pointer;
};


template<typename key_type, typename value_type>
struct Couple{
    key_type key;
    value_type value;
};




template<typename key_type, typename value_type>
class LinkedList_dict {
private:
    int size;
    ListEl<key_type, value_type>* first_el;
public:
    LinkedList_dict() : size(0), first_el(nullptr) {}

    ~LinkedList_dict(){
        ListEl<key_type, value_type>* curr_el= first_el;
        while (curr_el != nullptr){

            ListEl<key_type, value_type>* next = curr_el->next_pointer;
            delete curr_el;
            curr_el = next;
        }
    }

    void add(key_type key, value_type value);
    /*
     * pushes back ListEl with key and value
     *
     * checks is there element with same key as input key
     * if there is does nothing
     * if not makes new ListEl with input key and value then
     * goes to the last element and changes last element
     * next pointer to new ListEl, now new ListEl is the last element
     * P.S if there is 0 elements first_el = new ListEl
     * @param key to add
     * @param value to add
     */


    bool is_in(key_type key);
    /*
     * checks is key int the LinkedList_dict
     * @param value to check
     */

    void pop(key_type key);
    /*
     * deletes ListEl with given key
     * @param value to delete
     */

    int get_size(){
        return size;
    }

    // operators

    template<class name>
    bool operator==(name var){
        return first_el == var;
    }

    template<class name>
    bool operator!=(name var){
        return first_el != var;
    }

    /*
     * operator != and == are needed for checking is LinkedList_dict empty
     * I used it to check first_el is it nullptr or not;
     */

    const value_type& operator[](key_type key) const;
    /*
     * finds value by key
     * for copying value
     * value_type value_var = list[key]
     */

    value_type& operator[](key_type key);
    /*
    * finds value by key
    * for changing value
    * list[key] = value2;
    */

    void print(std::ostream& out = std::cout) const{
        ListEl<key_type, value_type>* curr_el = first_el;
        while (curr_el != nullptr){
            out << curr_el -> key << ':' << curr_el -> value << ' ';
            curr_el = curr_el ->next_pointer;
        }
    }

    friend std::ostream& operator <<(std::ostream& out,const LinkedList_dict& lst){
        lst.print(out);
        return out;
    }
    /*
     * overloading cout operator <<
     */

private:
    Couple<key_type,value_type> get_couple(int index);
    /*
     * finds element by index and returns struct with key and value
     * this function needed for copying this list to another
     * @param index
     * @return struct couple(key, value)
     */

    void find_element_with_key(key_type key, ListEl<key_type, value_type>*& previous_element, ListEl<key_type, value_type>*& element_to_delete) const;
    /*
     * finds element with present key and previous element to it.
     * I've used it for finding elements to delete.
     * @param key
     * @param previous_element
     * @param element_to_delete
     * no returning but changing previous_element and element_to_delete
     */
    template <typename T>
    friend class HashSet;

    template<typename key_t, typename value_t>
    friend class HashDict;
};
// public
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


// private
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
