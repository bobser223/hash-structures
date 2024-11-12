#include "..//HashDict.h"
#include <gtest/gtest.h>
#include <cmath>
#include <string>

// Тест для великих даних з ключами float
TEST(HashDictLargeDataTest, LargeFloatKeys) {
    HashDict<float, std::string> dict;
    const int dataSize = 1000000;

    for (int i = 0; i < dataSize; ++i) {
        dict.add(static_cast<float>(i) / 10.0f, "value_" + std::to_string(i));
    }

    ASSERT_EQ(dict.getSize(), dataSize);

    for (int i = 0; i < dataSize; ++i) {
        EXPECT_EQ(dict[static_cast<float>(i) / 10.0f], "value_" + std::to_string(i));
    }
}

// Тест для великих даних з ключами string
TEST(HashDictLargeDataTest, LargeStringKeys) {
    HashDict<std::string, int> dict;
    const int dataSize = 500000;

    for (int i = 0; i < dataSize; ++i) {
        dict.add("key_" + std::to_string(i), i);
    }

    ASSERT_EQ(dict.getSize(), dataSize);

    for (int i = 0; i < dataSize; ++i) {
        EXPECT_EQ(dict["key_" + std::to_string(i)], i);
    }
}


// Тест для великих даних з ключами типу int*
TEST(HashDictLargeDataTest, IntPointerKeys) {
    HashDict<int*, std::string> dict;
    const int dataSize = 10000;
    int* pointers[dataSize];

    for (int i = 0; i < dataSize; ++i) {
        pointers[i] = new int(i);
        dict.add(pointers[i], "value_" + std::to_string(i));
    }

    ASSERT_EQ(dict.getSize(), dataSize);

    for (int i = 0; i < dataSize; ++i) {
        EXPECT_EQ(dict[pointers[i]], "value_" + std::to_string(i));
        delete pointers[i]; // Очистка пам'яті
    }
}

// Тест для великих даних з ключами типу float*
TEST(HashDictLargeDataTest, FloatPointerKeys) {
    HashDict<float*, int> dict;
    const int dataSize = 10000;
    float* pointers[dataSize];

    for (int i = 0; i < dataSize; ++i) {
        pointers[i] = new float(static_cast<float>(i) * 0.5f);
        dict.add(pointers[i], i);
    }

    ASSERT_EQ(dict.getSize(), dataSize);

    for (int i = 0; i < dataSize; ++i) {
        EXPECT_EQ(dict[pointers[i]], i);
        delete pointers[i]; // Очистка пам'яті
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
