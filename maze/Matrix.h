//------------------------------------------------------------------------------
// <Filename>.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
// Matthias Klotz (1530653)
// Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_MATRIX_H
#define MAZE_MATRIX_H


#include <vector>
#include <memory>
#include "Vector2d.h"
#include <iostream>

// Matrix class
//
// Set size on construction or with resize()
// Access members with [x][y] or at(x, y)
template<class T>
class Matrix
{
  public:
    // MatrixRow represents one row of the matrix, the matrix consists of
    // multiple matrix rows.
    // The elements of the MatrixRow can be accessed with the [] operator
    // or the at() method, the later one does boundaries checking.
    // The constructor of the MatrixRow is private so only itself or the Matrix
    // class, which is a friend, can create a row.
    // Because of that the Matrix class needs an own allocator that is allowed
    // to construct a MatrixRow.
    class MatrixRow
    {
      friend class Matrix;

      private:
        std::vector<T> elements_;

      public:
        MatrixRow()
        {}

        ~MatrixRow()
        {}

        T& operator[](unsigned int element_index)
        {
          return elements_[element_index];
        }

        const T& operator[](unsigned int element_index) const
        {
          return elements_[element_index];
        }

        T& at(unsigned int element_index)
        {
          return elements_.at(element_index);
        }

        typename std::vector<T>::const_iterator begin() const
        {
          return elements_.begin();
        };

        typename std::vector<T>::iterator begin()
        {
          return elements_.begin();
        };

        typename std::vector<T>::const_iterator end() const
        {
          return elements_.end();
        };

        typename std::vector<T>::iterator end()
        {
          return elements_.end();
        };
    };

  protected:
    Vector2d size_;
    std::vector<MatrixRow> rows_;

    void resize();

  public:
    Matrix();
    Matrix(unsigned int width, unsigned int height);
    Matrix(Vector2d size);

    void resize(unsigned int width, unsigned int height)
    {
      resize(Vector2d(width, height));
    }
    void resize(Vector2d new_size);

    Vector2d getSize() const
    {
      return size_;
    }

    MatrixRow& operator[](unsigned int row_index)
    {
      return rows_[row_index];
    }

    MatrixRow& at(unsigned int row_index)
    {
      return rows_.at(row_index);
    }

    T& at(unsigned int row_index, unsigned int element_index)
    {
      return rows_.at(row_index).at(element_index);
    }

    T& operator[](Vector2d position)
    {
      return rows_[position.x()][position.y()];
    }

    void put(T element, Vector2d position);
    void put(T element, int position_x, int position_y)
    {
      put(element, Vector2d(position_x, position_y));
    }
};


template<class T>
Matrix<T>::Matrix() : size_(0, 0)
{
  resize();
}


template<class T>
Matrix<T>::Matrix(unsigned int width, unsigned int height) : size_(width, height)
{
  resize();
}


template<class T>
Matrix<T>::Matrix(Vector2d size) : size_(size)
{
  resize();
}


template<class T>
void Matrix<T>::resize()
{
  rows_.resize(static_cast<unsigned int>(size_.x()));

  for(auto &row : rows_)
    row.elements_.resize(static_cast<unsigned int>(size_.y()));
}


template<class T>
void Matrix<T>::resize(Vector2d new_size)
{
  size_ = new_size;
  resize();
}


template<class T>
void Matrix<T>::put(T element, Vector2d position)
{
  Vector2d new_size = size_;

  if(position.x() >= size_.x())
    new_size.setX(position.x() + 1);

  if(position.y() >= size_.y())
    new_size.setY(position.y() + 1);

  resize(new_size);

  (*this)[position] = element;
}

#endif //MAZE_MATRIX_H
