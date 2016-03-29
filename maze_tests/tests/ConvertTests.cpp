//
// Created by jonas on 3/29/16.
//

#include <Convert.h>
#include "gtest/gtest.h"

TEST(ConvertTest, unsigned_int_valid)
{
  std::string number_string = "2134";
  unsigned int number;

  ASSERT_NO_THROW(number = Convert::toUInt(number_string));

  EXPECT_EQ(number, 2134);
}


TEST(ConvertTest, unsigned_int_negativ_number)
{
  std::string number_string = "-2134";

  ASSERT_THROW(Convert::toUInt(number_string), std::invalid_argument);
}


TEST(ConvertTest, unsigned_int_out_of_range)
{
  std::string number_string = "5000000000";

  ASSERT_THROW(Convert::toUInt(number_string), std::out_of_range);
}


TEST(ConvertTest, unsigned_int_no_number_1)
{
  std::string number_string = "abc";

  ASSERT_THROW(Convert::toUInt(number_string), std::invalid_argument);
}


TEST(ConvertTest, unsigned_int_no_number_2)
{
  std::string number_string = "1234 abc";

  ASSERT_THROW(Convert::toUInt(number_string), std::invalid_argument);
}


TEST(ConvertTest, unsigned_int_no_number_3)
{
  std::string number_string = "1234abc";

  ASSERT_THROW(Convert::toUInt(number_string), std::invalid_argument);
}


TEST(ConvertTest, unsigned_int_no_number_4)
{
  std::string number_string = "abc1324";

  ASSERT_THROW(Convert::toUInt(number_string), std::invalid_argument);
}


TEST(ConvertTest, unsigned_int_no_number_5)
{
  std::string number_string = "abc 1324";

  ASSERT_THROW(Convert::toUInt(number_string), std::invalid_argument);
}