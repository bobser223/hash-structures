//
// Created by Volodymyr Avvakumov on 27.10.2024.
//
#include "../LinkedList_dict.h"
#include <iostream>


int main() {
    LinkedList_dict<int, float> list;
//    int j = 10;
    for (int i = 0, j = 10; i < 10; i++, j--) {
        list.add(i, j);
    }
    std::cout << list << std::endl;
    list.pop(1);
    list.pop(8);
    std::cout << list << std::endl;
    for(int i = 0; i < list.get_size(); i++){

        Couple<int, float> c = list[i];
        std::cout << c.key << ':' << c.value << ' ';// << std::endl;
    }
}