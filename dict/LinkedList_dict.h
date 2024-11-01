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
     */


    bool is_in(key_type key);
    /*
     * checks is key int the LinkedList_dict
     */

    void pop(key_type key);
    /*
     * deletes ListEl with given key
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

    const value_type& operator[](key_type key) const{
        if (size == 0){
            throw std::logic_error("no elements here!!!");
//            return false;
        } else {

            ListEl<key_type, value_type>* curr_el = first_el;
            while (curr_el != nullptr){
                if (curr_el->key == key && !curr_el->is_empty) return curr_el ->value;
                curr_el = curr_el->next_pointer;
            }
            throw std::logic_error("no element here!!!");
        }
    }

    value_type& operator[](key_type key){
        if (size == 0){
            throw std::logic_error("no elements here!!!");
//            return false;
        } else {

            ListEl<key_type, value_type>* curr_el = first_el;
            while (curr_el != nullptr){
                if (curr_el->key == key && !curr_el->is_empty) return curr_el ->value;
                curr_el = curr_el->next_pointer;
            }
            throw std::logic_error("no element here!!!");
        }
    }

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

private:
    Couple<key_type,value_type> get_couple(int index);

    void find_element_with_key(key_type key, ListEl<key_type, value_type>*& previous_element, ListEl<key_type, value_type>*& element_to_delete) const {
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
    template <typename T>
    friend class HashSet;

    template<typename key_t, typename value_t>
    friend class HashDict;
};
// public
template<typename key_type, typename value_type>
void LinkedList_dict<key_type, value_type>::add(key_type key, value_type value){
    // do nothing
    if(is_in(key))  return;
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


#endif //LEARNING_LINKEDLIST_DICT_H
