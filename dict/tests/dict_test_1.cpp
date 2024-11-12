#include "..//HashDict.h"
#include <gtest/gtest.h>

// Test fixture class for HashDict
class HashDictTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code, якщо потрібно
    }

    void TearDown() override {
        // Cleanup code, якщо потрібно
    }
};

// Тест для цілочисельних ключів
TEST_F(HashDictTest, AddIntKeys) {
HashDict<int, std::string> dict;
dict.add(1, "one");
dict.add(2, "two");
dict.add(3, "three");

ASSERT_EQ(dict.getSize(), 3);
EXPECT_EQ(dict[1], "one");
EXPECT_EQ(dict[2], "two");
EXPECT_EQ(dict[3], "three");
}

// Тест для ключів з плаваючою комою
TEST_F(HashDictTest, AddFloatKeys) {
HashDict<float, std::string> dict;
dict.add(1.5f, "one point five");
dict.add(2.75f, "two point seventy-five");
dict.add(3.0f, "three");

ASSERT_EQ(dict.getSize(), 3);
EXPECT_EQ(dict[1.5f], "one point five");
EXPECT_EQ(dict[2.75f], "two point seventy-five");
EXPECT_EQ(dict[3.0f], "three");
}

// Тест для рядкових ключів
TEST_F(HashDictTest, AddStringKeys) {
HashDict<std::string, int> dict;
dict.add("apple", 100);
dict.add("banana", 200);
dict.add("cherry", 300);

ASSERT_EQ(dict.getSize(), 3);
EXPECT_EQ(dict["apple"], 100);
EXPECT_EQ(dict["banana"], 200);
EXPECT_EQ(dict["cherry"], 300);
}

// Тест на видалення елементів з ключами різних типів
TEST_F(HashDictTest, RemoveVariousKeys) {
HashDict<int, std::string> intDict;
intDict.add(10, "ten");
intDict.pop(10);
EXPECT_THROW(intDict[10], std::logic_error);

HashDict<float, std::string> floatDict;
floatDict.add(2.5f, "two point five");
floatDict.pop(2.5f);
EXPECT_THROW(floatDict[2.5f], std::logic_error);

HashDict<std::string, int> stringDict;
stringDict.add("key", 123);
stringDict.pop("key");
EXPECT_THROW(stringDict["key"], std::logic_error);
}

// Тест на перевірку існування ключів з різними типами
TEST_F(HashDictTest, KeyExistenceCheckVariousTypes) {
HashDict<int, std::string> intDict;
intDict.add(10, "ten");
EXPECT_TRUE(intDict.is_in(10));
EXPECT_FALSE(intDict.is_in(20));

HashDict<float, std::string> floatDict;
floatDict.add(5.5f, "five point five");
EXPECT_TRUE(floatDict.is_in(5.5f));
EXPECT_FALSE(floatDict.is_in(1.1f));

HashDict<std::string, int> stringDict;
stringDict.add("test", 456);
EXPECT_TRUE(stringDict.is_in("test"));
EXPECT_FALSE(stringDict.is_in("absent"));
}

// Тест на зміну значень через оператор [] для різних типів ключів
TEST_F(HashDictTest, ModifyValuesUsingOperatorVariousTypes) {
HashDict<int, std::string> intDict;
intDict.add(1, "one");
intDict[1] = "updated one";
EXPECT_EQ(intDict[1], "updated one");

HashDict<float, std::string> floatDict;
floatDict.add(1.1f, "one point one");
floatDict[1.1f] = "updated one point one";
EXPECT_EQ(floatDict[1.1f], "updated one point one");

HashDict<std::string, int> stringDict;
stringDict.add("key", 789);
stringDict["key"] = 987;
EXPECT_EQ(stringDict["key"], 987);
}

// Тест на обробку колізій з ключами різних типів
TEST_F(HashDictTest, CollisionHandlingVariousTypes) {
HashDict<int, std::string> intDict;
intDict.add(1, "one");
intDict.add(6, "six"); // Можлива колізія
EXPECT_EQ(intDict[1], "one");
EXPECT_EQ(intDict[6], "six");

HashDict<std::string, int> stringDict;
stringDict.add("abc", 123);
stringDict.add("cba", 321); // Можлива колізія
EXPECT_EQ(stringDict["abc"], 123);
EXPECT_EQ(stringDict["cba"], 321);
}

// Тест на роботу з великими обсягами даних для різних типів ключів
TEST_F(HashDictTest, LargeDataSetVariousTypes) {
HashDict<int, int> intDict;
const int dataSize = 100000;
for (int i = 0; i < dataSize; ++i) {
intDict.add(i, i * 2);
}
ASSERT_EQ(intDict.getSize(), dataSize);

HashDict<float, float> floatDict;
for (float i = 0.0f; i < dataSize; i += 1.0f) {
floatDict.add(i, i * 3.5f);
}
ASSERT_EQ(floatDict.getSize(), dataSize);

HashDict<std::string, int> stringDict;
for (int i = 0; i < dataSize; ++i) {
stringDict.add("key" + std::to_string(i), i);
}
ASSERT_EQ(stringDict.getSize(), dataSize);
}

// Тест на коректну очистку пам'яті для різних типів ключів
TEST_F(HashDictTest, DestructorTestVariousTypes) {
HashDict<int, std::string>* intDict = new HashDict<int, std::string>();
intDict->add(1, "one");
delete intDict; // Очікуємо, що об'єкт знищується без помилок

HashDict<float, std::string>* floatDict = new HashDict<float, std::string>();
floatDict->add(2.5f, "two point five");
delete floatDict; // Очікуємо, що об'єкт знищується без помилок

HashDict<std::string, int>* stringDict = new HashDict<std::string, int>();
stringDict->add("key", 456);
delete stringDict; // Очікуємо, що об'єкт знищується без помилок
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
