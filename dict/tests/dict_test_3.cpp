//
// Created by Volodymyr Avvakumov on 05.11.2024.
//
#include "../HashDict.h"
#include <gtest/gtest.h>
#include <cmath>
#include <string>

// Тест для методу pop з великими обсягами даних
TEST(HashDictLargeDataTest, PopMethodLargeData) {
    HashDict<int, std::string> dict;
    const int dataSize = 100000;

    // Додавання великої кількості елементів
    for (int i = 0; i < dataSize; ++i) {
        dict.add(i, "value_" + std::to_string(i));
    }

    ASSERT_EQ(dict.getSize(), dataSize);

    // Видалення половини елементів
    for (int i = 0; i < dataSize / 2; ++i) {
        dict.pop(i);
    }

    ASSERT_EQ(dict.getSize(), dataSize / 2);

    // Перевірка, що видалені елементи більше не існують
    for (int i = 0; i < dataSize / 2; ++i) {
        EXPECT_FALSE(dict.is_in(i));
    }

    // Перевірка, що інші елементи все ще існують
    for (int i = dataSize / 2; i < dataSize; ++i) {
        EXPECT_TRUE(dict.is_in(i));
        EXPECT_EQ(dict[i], "value_" + std::to_string(i));
    }
}

// Тест для оператора [] з великими обсягами даних і різними типами ключів
TEST(HashDictLargeDataTest, BracketOperatorLargeData) {
    // Тест для цілочисельних ключів
    HashDict<int, double> intDict;
    const int intDataSize = 100000;

    for (int i = 0; i < intDataSize; ++i) {
        intDict.add(i, static_cast<double>(i) * 1.5);
    }

    ASSERT_EQ(intDict.getSize(), intDataSize);

    for (int i = 0; i < intDataSize; ++i) {
        EXPECT_EQ(intDict[i], static_cast<double>(i) * 1.5);
    }
    // Тест для ключів типу float
    HashDict<float, std::string> floatDict;
    const int floatDataSize = 50;

    for (int i = 0; i < floatDataSize; ++i) {
        float key = static_cast<float>(i) / 100.0f;
        floatDict.add(key, "value_" + std::to_string(i));
    }

    ASSERT_EQ(floatDict.getSize(), floatDataSize);

    for (int i = 0; i < floatDataSize; ++i) {
        float key = static_cast<float>(i) / 100.0f;
        EXPECT_EQ(floatDict[key], "value_" + std::to_string(i));
    }

    // Тест для ключів типу string
    HashDict<std::string, int> stringDict;
    const int stringDataSize = 20000;

    for (int i = 0; i < stringDataSize; ++i) {
        stringDict.add("key_" + std::to_string(i), i);
    }

    ASSERT_EQ(stringDict.getSize(), stringDataSize);

    for (int i = 0; i < stringDataSize; ++i) {
        EXPECT_EQ(stringDict["key_" + std::to_string(i)], i);
    }

    // Тест на доступ до неіснуючих ключів, які викликають виключення
    EXPECT_THROW(intDict[-1], std::logic_error);
    EXPECT_THROW(floatDict[99999.99f], std::logic_error);
    EXPECT_THROW(stringDict["non_existent_key"], std::logic_error);
}

// Тест для змішаних типів даних і масштабного видалення
TEST(HashDictLargeDataTest, MixedTypePopAndAccess) {
    HashDict<std::string, double> dict;
    const int dataSize = 30000;

    // Додавання великої кількості різних значень
    for (int i = 0; i < dataSize; ++i) {
        dict.add("key_" + std::to_string(i), sin(static_cast<double>(i)));
    }

    ASSERT_EQ(dict.getSize(), dataSize);

    // Видалення кожного третього елемента
    for (int i = 0; i < dataSize; i += 3) {
        dict.pop("key_" + std::to_string(i));
    }

    ASSERT_EQ(dict.getSize(), dataSize - dataSize / 3);

    // Перевірка, що видалені ключі не існують
    for (int i = 0; i < dataSize; i += 3) {
        EXPECT_FALSE(dict.is_in("key_" + std::to_string(i)));
    }

    // Перевірка, що інші ключі все ще існують і значення правильні
    for (int i = 1; i < dataSize; i += 3) {
        EXPECT_TRUE(dict.is_in("key_" + std::to_string(i)));
        EXPECT_DOUBLE_EQ(dict["key_" + std::to_string(i)], sin(static_cast<double>(i)));
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
