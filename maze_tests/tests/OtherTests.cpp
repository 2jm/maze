//
// Created by jonas on 13.04.16.
//

#include "gtest/gtest.h"


template <class T>
class TestClass
{
  public:
    bool isTPointer()
    {
      return std::is_pointer<T>::value;
    }
};


class OtherClass
{};

class TestClassInherit : public TestClass<OtherClass*>
{
  public:
    TestClassInherit() {};
};


TEST(OtherTest, test_std_is_pointer)
{
  TestClass<int*> testClass1;
  TestClass<int> testClass2;

  ASSERT_TRUE(testClass1.isTPointer());
  ASSERT_FALSE(testClass2.isTPointer());


  TestClass<OtherClass*> testClass3;
  TestClass<OtherClass> testClass4;

  ASSERT_TRUE(testClass3.isTPointer());
  ASSERT_FALSE(testClass4.isTPointer());


  TestClassInherit testClassInherit;

  ASSERT_TRUE(testClassInherit.isTPointer());
}