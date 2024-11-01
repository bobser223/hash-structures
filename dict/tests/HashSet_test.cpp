//
// Created by Volodymyr Avvakumov on 27.10.2024.
//
#include <iostream>
#include "../set/LinkedList.h"
#include "../set/HashSet.h"

int main(){
    HashSet<int> set;
    for (int i = 10; i < 100; i ++){
        set.add(i);
        std::cout << set << std::endl;
    }
    std::cout << set << std::endl;
    set.pop(10);
    std::cout << set << std::endl;
    set.add(10);
    set.add(10);
    std::cout << set << std::endl;
    std::cout << set.is_in(5) << std::endl;
    std::cout << set.is_in(89) << std::endl;

    HashSet<char> set_char;
    std::string str("AABCCDEFFGHIJJKL?MMN?OPQQRSTTUVWXYZ//");
    for (char ch: str) { set_char.add(ch); }

    std::cout << set_char << std::endl;

    for (char ch: str) { std::cout << set_char.is_in(ch)<< " "; }

    HashSet<float> set_f;
    for (float i = 10; i > 2; i -= 0.76){
        set_f.add(i);
        std::cout << set_f << std::endl;
    }

    HashSet<int> set_i;
    for (int i = 100; i > 10; i --){
        set_i.add(i);
        std::cout << set_i << std::endl;
    }
    std::cout << set_i.getSize() << std::endl;

    return 0;

}