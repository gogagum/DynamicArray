//
// Created by gogagum on 26.10.18.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include "DynamicArray.hpp"

TEST(DynamicArrayConstructor, Constructor) {
  DynamicArray<int> test_array;
  EXPECT_EQ(test_array.Size(), 0);
}

TEST(DynamicArrayConstructor, ConstructorWithSize) {
  DynamicArray<int> test_array(3);
  EXPECT_EQ(test_array.Size(), 3);
}

TEST(DynamicArrayConstructor, ArrayConstructorFromArray) {
  int *array = new int[5];
  for (int i = 0; i < 5; i++) {
    array[i] = i + 1;
  }
  DynamicArray<int> test_array(5, array);
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(test_array[i], i + 1);
  }
}

TEST(DynamicArrayConstructor, ConstructorFromIterators) {
  std::vector<int> v = {0, 1, 2, 3, 4};
  DynamicArray<int> test_array(v.begin(), v.end());
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(test_array[i], i);
  }
  EXPECT_EQ(test_array.Size(), 5);
}

TEST(DynamicArrayConstructor, CopyConstructor) {
  DynamicArray<int> test_array1(5);
  for (int i = 0; i < 5; i++) {
    test_array1[i] = i + 1;
  }
  DynamicArray<int> test_array2(test_array1);
  EXPECT_EQ(test_array2.Size(), 5);
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(test_array2[i], i + 1);
  }
}

TEST(SimpleTests, PushBack) {
  DynamicArray<int> test_array;
  for (int i = 0; i < 5; i++) {
    test_array.PushBack(i + 1);
  }

  EXPECT_EQ(test_array.Size(), 5);
  for (int i = 0; i < test_array.Size(); i++){
    EXPECT_EQ(test_array[i], i + 1);
  }
}

TEST(SimpleTests, Eq){
  DynamicArray<int> test_array2;
  DynamicArray<int> test_array1;
  for (int i = 0; i < 5; i++){
    test_array1.PushBack(i + 1);
    test_array2.PushBack(i + 1);
  }
  EXPECT_EQ(test_array1 == test_array2, true);
}

TEST(SimpleTests, Clear) {
  DynamicArray<int> test_array;
  test_array.PushBack(10);
  test_array.PushBack(110);
  test_array.Clear();
  EXPECT_EQ(test_array.Size(), 0);
}

TEST (SimpleTests, Erase) {
  DynamicArray<int> test_array(10);
  for (int i = 0; i < 10; i++) {
    test_array[i] = i;
  }
  test_array.PopBack();
  EXPECT_EQ(test_array.Size(), 9);
}
