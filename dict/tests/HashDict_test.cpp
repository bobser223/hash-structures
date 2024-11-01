//
// Created by Volodymyr Avvakumov on 27.10.2024.
//
#include "../HashDict.h"
#include <iostream>
#include <gtest/gtest.h>
#include <string>
#include <sstream>

// Масштабний тест для числових цілочисельних ключів
TEST(HashDictTest, LargeScaleIntKeys) {
HashDict<int, std::string> dict;
for (int i = 0; i < 10000; ++i) {
dict.add(i, "value" + std::to_string(i));
}

//// Перевірка наявності всіх доданих елементів
for (int i = 0; i < 10000; ++i) {
EXPECT_TRUE(dict.is_in(i));
}

// Перевірка відсутності ключа за межами доданих
EXPECT_FALSE(dict.is_in(10001));
}

// Масштабний тест для рядкових ключів
TEST(HashDictTest, LargeScaleStringKeys) {
HashDict<std::string, int> dict;
for (int i = 0; i < 10000; ++i) {
dict.add("key" + std::to_string(i), i);
}

// Перевірка наявності всіх доданих елементів
for (int i = 0; i < 10000; ++i) {
EXPECT_TRUE(dict.is_in("key" + std::to_string(i)));
}

// Перевірка відсутності ключа за межами доданих
EXPECT_FALSE(dict.is_in("key10001"));
}

// Тест для типу з плаваючою комою як ключ
TEST(HashDictTest, LargeScaleDoubleKeys) {
HashDict<double, std::string> dict;
for (int i = 0; i < 10000; ++i) {
dict.add(i * 0.1, "value" + std::to_string(i));
}

// Перевірка наявності всіх доданих елементів
for (int i = 0; i < 10000; ++i) {
EXPECT_TRUE(dict.is_in(i * 0.1));
}

// Перевірка відсутності ключа за межами доданих
EXPECT_FALSE(dict.is_in(10000.1));
}

// Тест для користувацького типу як ключа
struct CustomKey {
    int id;
    std::string name;

    bool operator==(const CustomKey& other) const {
        return id == other.id && name == other.name;
    }
};

namespace std {
    template<>
    struct hash<CustomKey> {
        size_t operator()(const CustomKey& key) const {
            return hash<int>()(key.id) ^ hash<std::string>()(key.name);
        }
    };
}

TEST(HashDictTest, LargeScaleCustomKeys) {
HashDict<CustomKey, std::string> dict;

for (int i = 0; i < 1000; ++i) {
CustomKey key = {i, "name" + std::to_string(i)};
dict.add(key, "value" + std::to_string(i));
}

// Перевірка наявності всіх доданих елементів
for (int i = 0; i < 1000; ++i) {
CustomKey key = {i, "name" + std::to_string(i)};
EXPECT_TRUE(dict.is_in(key));
}

// Перевірка відсутності неіснуючого ключа
CustomKey missing_key = {1001, "name1001"};
EXPECT_FALSE(dict.is_in(missing_key));
}

// Тест на додавання та видалення великої кількості елементів
TEST(HashDictTest, LargeScaleAddAndRemove) {
HashDict<int, std::string> dict;

// Додавання 5000 елементів
for (int i = 0; i < 5000; ++i) {
dict.add(i, "value" + std::to_string(i));
}

// Видалення половини елементів
for (int i = 0; i < 2500; ++i) {
dict.pop(i);
}

// Перевірка відсутності видалених елементів
for (int i = 0; i < 2500; ++i) {
EXPECT_FALSE(dict.is_in(i));
}

// Перевірка наявності залишених елементів
for (int i = 2500; i < 5000; ++i) {
EXPECT_TRUE(dict.is_in(i));
}
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


//
//int main(){
//    HashDict<int, int> dict;
//    dict.add(1, 2);
//    std::cout << dict << std::endl;
//    std::cout << dict.is_in(1) << std::endl;
//    std::cout << dict.is_in(2) << std::endl;
//    dict.pop(1);
//    std::cout << dict << std::endl;
//    return 0;
//}