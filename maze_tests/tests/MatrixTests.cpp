//
// Created by jonas on 3/28/16.
//

#include <Matrix.h>
#include "gtest/gtest.h"

TEST(MatrixTest, assignment)
{
  Matrix<int> matrix(3, 3);

  matrix[0][0] = 7;

  EXPECT_EQ(matrix[0][0], 7);   //that works \o/
}

TEST(MatrixTest, boundaries_check)
{
  Matrix<int> matrix(3, 3);

  EXPECT_THROW(matrix.at(234, 23) = 7, std::out_of_range);
}

TEST(MatrixTest, resize)
{
  Matrix<int> matrix(3, 3);

  EXPECT_THROW(matrix.at(5, 5) = 7, std::out_of_range);

  matrix.resize(7, 7);

  EXPECT_NO_THROW(matrix.at(5, 5) = 7);

  matrix.resize(3, 3);

  EXPECT_THROW(matrix.at(5, 5) = 7, std::out_of_range);
}