//
// Created by jonas on 3/25/16.
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

        MatrixRow()
        {}

        ~MatrixRow()
        {}


      public:
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

    // This is the allocator for the std::vector rows, it is allowed to create
    // MatrixRows
    struct MatrixRowAllocator : public std::allocator<MatrixRow>
    {
        template< class U, class... Args >
        void construct( U* p, Args&&... args )
        {
          ::new((void *)p) U(std::forward<Args>(args)...);
        }

        template<class U>
        void destroy(U *p) {

        }

        template< class U > struct rebind { typedef MatrixRowAllocator other; };
    };


  private:
    Vector2d size_;
    std::vector<MatrixRow, MatrixRowAllocator> rows_;

    void resize();

  protected:
    template<typename U = T,
            typename std::enable_if< std::is_pointer<U>::value, int >::type = 0>
    char getCharacterOfElement(U &element) const
    {
      return static_cast<char>(*element);
    };

    template<typename U = T,
            typename std::enable_if< !std::is_pointer<U>::value, int >::type = 0>
    char getCharacterOfElement(U &element) const
    {
      return static_cast<char>(element);
    };

  public:
    Matrix();
    Matrix(unsigned int width, unsigned int height);
    Matrix(Vector2d size);

    void resize(unsigned int width, unsigned int height)
    {
      resize(Vector2d(width, height));
    }
    void resize(Vector2d new_size);

    Vector2d getSize()
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

    operator std::string() const;
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
  unsigned int row_index;

  rows_.resize(static_cast<unsigned int>(size_.x()));

  for(row_index = 0; row_index < rows_.size(); row_index++)
  {
    rows_[row_index].elements_.resize(static_cast<unsigned int>(size_.y()));
  }
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

template<class T>
Matrix<T>::operator std::string() const
{
  std::string matrix_string;

  unsigned int row_number, column_number;

  for(row_number = 0; row_number < size_.y(); row_number++)
  {
    for(column_number = 0; column_number < size_.x(); column_number++)
      matrix_string += getCharacterOfElement(rows_[column_number][row_number]);

    matrix_string += '\n';
  }

  return matrix_string;
}

#endif //MAZE_MATRIX_H
