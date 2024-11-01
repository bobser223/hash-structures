//
// Created by Volodymyr Avvakumov on 27.10.2024.
//

#include "HashDict.h"

int main(){
    HashDict<int, int> d;
    d.add(1, 2);
    for (int i = 0; i < 100; i ++) d.add(i, i+1);
    std::cout << d << std::endl;
    std::cout << d.is_in(1000) << std::endl;
    std::cout << d.is_in(10) << std::endl;
    for (int i = 0; i < 100; i ++) d.pop(i);
    d.add(0, 0);
    std::cout << d << std::endl;
    int a = d[0];
    a = 100;
    std::cout << d << std::endl;
    d[0] = 100;
    std::cout << d << std::endl;
    std::cout << d.getTrueSize() << std::endl;

}