//
// Created by jonas on 3/25/16.
//

#ifndef MAZE_MATRIX_H
#define MAZE_MATRIX_H


#include <vector>
#include "Vector2d.h"

template<class T>
class Matrix
{
  public:
    class MatrixRow
    {
      private:
        std::vector<T> elements;

      public:
        MatrixRow();

        MatrixRow(int length);

        T operator[](int element_index)
        {
          return elements[element_index];
        }
    };


  private:
    Vector2d size_;
    std::vector<MatrixRow> rows;

  public:

    Matrix();
    Matrix(int w, int h);
    Matrix(Vector2d size);

    MatrixRow operator[](int row_index)
    {
      return rows[row_index];
    }
};


template<class T>
Matrix<T>::Matrix() : size_(10, 10)
{

}

template<class T>
Matrix<T>::Matrix(int w, int h) : size_(w, h)
{

}

template<class T>
Matrix<T>::Matrix(Vector2d size) : size_(size)
{

}


template<class T>
Matrix<T>::MatrixRow::MatrixRow()
{

}

template<class T>
Matrix<T>::MatrixRow::MatrixRow(int length)
{

}

#endif //MAZE_MATRIX_H
