//
// Created by Volodymyr Avvakumov on 26.10.2024.
//

#include <stdexcept>
#include <iostream>

#ifndef LEARNING_LINKEDLIST_H
#define LEARNING_LINKEDLIST_H


/**
 * @brief A templated structure representing a node in the linked list.
 *
 * @tparam var_type The type of the value stored in the node.
 */
template<typename var_type>
struct ListEl{
    bool is_empty;                     /**< Flag indicating if the node is empty (actually useless). */
    var_type var;                      /**< The value stored in the node. */
    ListEl<var_type>* next_pointer;    /**< Pointer to the next node in the list. */
};

/**
 * @brief A templated singly linked list class.
 *
 * Provides functionality to add, check, and remove elements. Supports iteration
 * through the list using a const iterator.
 *
 * @tparam var_type The type of elements stored in the linked list.
 */

template<typename var_type>
class LinkedList {

private:
    int size;                       /**< The number of elements in the list. */
    ListEl<var_type>* first_el;     /**< Pointer to the first element in the list. */


public:

    /**
     * @brief Default constructor.
     *
     * Initializes an empty linked list.
     */
    LinkedList() : first_el(nullptr), size(0) {}

    /**
     * @brief Destructor.
     *
     * Cleans up all nodes in the linked list.
     */
    ~LinkedList();

    /**
     * @brief Adds an element to the linked list.
     *
     * Adds a new element to the end of the list if it doesn't already exist.
     *
     * @param var The element to add.
     */
    void add(var_type var);

    /**
     * @brief Checks if an element exists in the linked list.
     *
     * @param var The element to check for.
     * @return true If the element is present.
     * @return false Otherwise.
     */
    bool is_in(var_type var);

    /**
     * @brief Removes an element from the linked list.
     *
     * Deletes the node containing the specified element.
     *
     * @param var The element to remove.
     * @throws std::logic_error If the element is not found.
     */
    void pop(var_type var);

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
     * @brief Prints the contents of the linked list.
     *
     * Iterates through all nodes and prints their values.
     *
     * @param out The output stream to print to. Defaults to std::cout.
     */
    void print(std::ostream& out = std::cout) const;



    /**
     * @brief A constant iterator for the LinkedList.
     *
     * Allows iteration over the linked list without modifying its elements.
     */
    class ConstIterator {
    private:
        const ListEl<var_type>* current; /**< Pointer to the current node in the iteration. */

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = const var_type;
        using difference_type = std::ptrdiff_t;
        using pointer = const var_type*;
        using reference = const var_type&;

        /**
         * @brief Constructs a ConstIterator.
         *
         * @param ptr Pointer to the starting node.
         */
        ConstIterator(const ListEl<var_type>* ptr) : current(ptr) {}

        /**
         * @brief Checks if two iterators are not equal.
         *
         * @param other The other iterator to compare with.
         * @return true If the iterators point to different nodes.
         * @return false Otherwise.
         */
        bool operator!=(const ConstIterator& other) const {
            return current != other.current;
        }

        /**
         * @brief Dereferences the iterator to access the current element.
         *
         * @return const var_type& Reference to the current element.
         */
        const var_type& operator*() const {
            return current->var;
        }

        /**
         * @brief Advances the iterator to the next element.
         *
         * @return ConstIterator& Reference to the updated iterator.
         */
        ConstIterator& operator++() {
            if(current != nullptr){
                current = current->next_pointer;
            }
            return *this;
        }
    };

    /**
     * @brief Returns an iterator to the beginning of the list.
     *
     * @return ConstIterator An iterator pointing to the first element.
     */
    ConstIterator begin() const {
        return ConstIterator(first_el);
    }

    /**
     * @brief Returns an iterator to the end of the list.
     *
     * @return ConstIterator An iterator pointing past the last element.
     */

    ConstIterator end() const {
        return ConstIterator(nullptr);
    }


protected:
    /**
     * @brief Finds the element with the given value and its preceding element.
     *
     * Searches the list for the specified value and sets pointers to the previous
     * and target elements.
     *
     * @param var The value to search for.
     * @param previous_element Reference to a pointer that will point to the preceding element.
     * @param element_to_delete Reference to a pointer that will point to the target element.
     * @throws std::logic_error If the element is not found.
     */
    void find_element_with_var(var_type var, ListEl<var_type>*& previous_element, ListEl<var_type>*& element_to_delete) const;

    /**
     * @brief Overloads the insertion operator to print the LinkedList.
     *
     * @param out The output stream.
     * @param lst The LinkedList to print.
     * @return std::ostream& The output stream.
     */
    friend std::ostream& operator <<(std::ostream& out,const LinkedList& lst){
        lst.print(out);
        return out;
    }


    template <typename T>
    friend class HashSet;
}; // End of the class

// methods implementation
template<typename var_type>
LinkedList<var_type>::~LinkedList(){
    ListEl<var_type>* curr_el = first_el;
    while (curr_el != nullptr){
        ListEl<var_type>* temp = curr_el;
        curr_el = curr_el->next_pointer;
        delete temp;
    }
}


template<typename var_type>
void LinkedList<var_type>::add(var_type var){
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

template<typename var_type>
bool LinkedList<var_type>::is_in(var_type var){
    if (size == 0){
        return false;
    } else {

        ListEl<var_type>* curr_el = first_el;
        // while current element exists
        while (curr_el != nullptr){
            if (curr_el->var == var && !curr_el->is_empty) return true;
            curr_el = curr_el->next_pointer;
        }
        return false;



    }
}


template<typename var_type>
void LinkedList<var_type>::pop(var_type var){
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

template<typename var_type>
void LinkedList<var_type>::print(std::ostream& out) const{
    ListEl<var_type>* curr_el = first_el;
    while (curr_el != nullptr){
        out << curr_el -> var << ' ';
        curr_el = curr_el ->next_pointer;
    }
}

//protected:
template<typename var_type>
void LinkedList<var_type>::find_element_with_var(var_type var, ListEl<var_type>*& previous_element, ListEl<var_type>*& element_to_delete) const {
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

#endif //LEARNING_LINKEDLIST_H

