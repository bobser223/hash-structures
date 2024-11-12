// Created by Volodymyr Avvakumov on 05.11.2024.
#include "../set/HashSet.h"
#include "../set/LinkedList.h"
#include <gtest/gtest.h>
#include <string>
#include <cmath>

// Тест для додавання елементів та перевірки наявності у множині
TEST(HashSetLargeDataTest, AddAndIsInTest) {
    HashSet<int> set;
    const int dataSize = 100000;

    // Додавання великої кількості елементів
    for (int i = 0; i < dataSize; ++i) {
        set.add(i);
    }
    ASSERT_EQ(set.getSize(), dataSize);

    // Перевірка, що всі елементи існують
    for (int i = 0; i < dataSize; ++i) {
        EXPECT_TRUE(set.is_in(i));
    }
}

// Тест для видалення елементів та перевірки наявності
TEST(HashSetLargeDataTest, PopMethodLargeData) {
    HashSet<int> set;
    const int dataSize = 50000;

    // Додавання елементів
    for (int i = 0; i < dataSize; ++i) {
        set.add(i);
    }
    ASSERT_EQ(set.getSize(), dataSize);

    // Видалення кожного другого елемента
    for (int i = 0; i < dataSize; i += 2) {
        set.pop(i);
    }
    ASSERT_EQ(set.getSize(), dataSize / 2);

    // Перевірка, що видалені елементи не існують
    for (int i = 0; i < dataSize; i += 2) {
        EXPECT_FALSE(set.is_in(i));
    }

    // Перевірка, що інші елементи все ще існують
    for (int i = 1; i < dataSize; i += 2) {
        EXPECT_TRUE(set.is_in(i));
    }
}

// Тест для великих даних з float типами
TEST(HashSetLargeDataTest, FloatKeys) {
    HashSet<float> set;
    const int dataSize = 10000;

    // Додавання чисел з плаваючою точкою
    for (int i = 0; i < dataSize; ++i) {
        set.add(static_cast<float>(i) / 10.0f);
    }
    ASSERT_EQ(set.getSize(), dataSize);

    // Перевірка наявності доданих значень
    for (int i = 0; i < dataSize; ++i) {
        EXPECT_TRUE(set.is_in(static_cast<float>(i) / 10.0f));
    }
}

// Тест для великих даних з рядковими ключами
TEST(HashSetLargeDataTest, StringKeys) {
    HashSet<std::string> set;
    const int dataSize = 2000;
    // Додавання рядкових значень
    for (int i = 0; i < dataSize; ++i) {
        set.add("key_" + std::to_string(i));
//        std::cout << set << std::endl;
    }
    ASSERT_EQ(set.getSize(), dataSize);
//    std::cout << set << std::endl;
    // Перевірка наявності кожного рядка
    for (int i = 0; i < dataSize; ++i) {
        EXPECT_TRUE(set.is_in("key_" + std::to_string(i)));
    }
}

// Тест для переповнення та збільшення розміру масиву
TEST(HashSetLargeDataTest, ResizeOnHighOccupancy) {
    HashSet<int> set;

    // Додаємо достатню кількість елементів, щоб переповнити початковий розмір
    for (int i = 0; i < 100; ++i) {
        set.add(i);
    }

    // Перевірка, що всі елементи існують навіть після збільшення розміру
    for (int i = 0; i < 100; ++i) {
        EXPECT_TRUE(set.is_in(i));
    }
}

// Тест для перевірки виключення при видаленні елементу, що не існує
TEST(HashSetLargeDataTest, PopNonExistentElement) {
    HashSet<int> set;
    set.add(10);

    // Видаляємо існуючий елемент
    set.pop(10);
    EXPECT_FALSE(set.is_in(10));

    // Спроба видалити неіснуючий елемент, що повинна викликати виключення
    EXPECT_THROW(set.pop(10), std::logic_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
