//
// Created by Volodymyr Avvakumov on 26.10.2024.
//

#include <stdexcept>
#include <iostream>

#ifndef LEARNING_LINKEDLIST_H
#define LEARNING_LINKEDLIST_H

template<typename var_type>
struct ListEl{
    bool is_empty;
    var_type var;
    ListEl<var_type>* next_pointer;
};

template<typename var_type>
class LinkedList {

private:
    int size;
    ListEl<var_type>* first_el;

public:

    LinkedList() : first_el(nullptr), size(0) {}
    ~LinkedList(){
        ListEl<var_type>* curr_el = first_el;
        while (curr_el != nullptr){
            ListEl<var_type>* temp = curr_el;
            curr_el = curr_el->next_pointer;
            delete temp;
        }
    }

    void add(var_type var){
        if(is_in(var))  return;
        ListEl<var_type>* new_el = new ListEl<var_type>;
        new_el -> var = var;
        new_el -> next_pointer = nullptr;
        new_el ->is_empty = false;
        if (size == 0){
            first_el = new_el;
        } else {
            ListEl<var_type>* curr_el = first_el;
            while (curr_el -> next_pointer != nullptr){
                curr_el = curr_el -> next_pointer;
            }
            curr_el -> next_pointer = new_el;
        }

        size ++;

    }

    bool is_in(var_type var){
        if (size == 0){
//            throw std::logic_error("no elements here!!!");
            return false;
        } else {

            ListEl<var_type>* curr_el = first_el;
            while (curr_el != nullptr){
                if (curr_el->var == var && !curr_el->is_empty) return true;
                curr_el = curr_el->next_pointer;
            }
            return false;



        }
    }

    void pop(var_type var){
        if (!is_in(var)){
            throw std::logic_error("this variable isn't here!!!");
        }

        if (size == 1){
            delete first_el;
            first_el = nullptr;
        } else if (first_el->var == var){
            ListEl<var_type>* temp = first_el;
            first_el = first_el->next_pointer;
            delete temp;
        } else {
            ListEl<var_type>* previous_element = nullptr;
            ListEl<var_type>* element_to_delete = nullptr;
            find_element_with_var(var, previous_element, element_to_delete);

            if (element_to_delete != nullptr && previous_element != nullptr){
                previous_element->next_pointer = element_to_delete->next_pointer;
                delete element_to_delete;
            }
        }

        size--;
    }

    //just for checking is there first element;
    template<class name>
    bool operator==(name var){
        return first_el == var;
    }

    template<class name>
    bool operator!=(name var){
        return first_el != var;
    }

    void print(std::ostream& out = std::cout) const{
        ListEl<var_type>* curr_el = first_el;
        while (curr_el != nullptr){
            out << curr_el -> var << ' ';
            curr_el = curr_el ->next_pointer;
        }
    }

    friend std::ostream& operator <<(std::ostream& out,const LinkedList& lst){
        lst.print(out);
        return out;
    }

    class ConstIterator {
    private:
        const ListEl<var_type>* current;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = const var_type;
        using difference_type = std::ptrdiff_t;
        using pointer = const var_type*;
        using reference = const var_type&;

        ConstIterator(const ListEl<var_type>* ptr) : current(ptr) {}

        bool operator!=(const ConstIterator& other) const {
            return current != other.current;
        }

        const var_type& operator*() const {
            return current->var;
        }

        ConstIterator& operator++() {
            if(current != nullptr){
                current = current->next_pointer;
            }
            return *this;
        }
    };

    ConstIterator begin() const {
        return ConstIterator(first_el);
    }

    ConstIterator end() const {
        return ConstIterator(nullptr);
    }


private:
    void find_element_with_var(var_type var, ListEl<var_type>*& previous_element, ListEl<var_type>*& element_to_delete) const {
        if (size == 0){
            throw std::logic_error("no elements here!!!");
        }

        previous_element = nullptr;
        element_to_delete = nullptr;
        ListEl<var_type>* curr_el = first_el;

        while (curr_el != nullptr){
            if (curr_el->var == var && !curr_el->is_empty){
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
};


#endif //LEARNING_LINKEDLIST_H
