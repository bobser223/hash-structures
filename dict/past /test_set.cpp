//
// Created by Volodymyr Avvakumov on 26.10.2024.
//
#include "HashSetTemplates2.cpp"

using namespace std;

int main(){
    HashSet<int> set;

    for (int i = 0; i < 10; i ++){
        set.add(i);
        set.print();
    }
    set.add(3);

    return 0;
}