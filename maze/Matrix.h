//------------------------------------------------------------------------------
// Matrix.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_MATRIX_H
#define MAZE_MATRIX_H


#include <vector>
#include <memory>
#include "Vector2d.h"

//------------------------------------------------------------------------------
// Matrix class
//
// This class implements a two dimensional matrix. It can store any type and
// have any size.
//
// -Matrix Size
// The matrix can be constructed with a specific size. Afterwards the size can
// be changed with the resize method.
// When using the put method to fill the matrix with elements it is
// automatically resized to the needed dimensions.
//
// -Element Access
// Elements are accessed with [column][row], [Vector2d(column, row)],
// .at(column).at(row) or at(Vector2d(column, row).
// The at method does bounds checking.
//
template <class T>
class Matrix
{
  public:
    //--------------------------------------------------------------------------
    // Column class
    //
    // This class represents one column of the matrix, the matrix consists of
    // multiple matrix columns.
    //
    class Column
    {
      private:
        std::vector<T> elements_;

      public:
        //----------------------------------------------------------------------
        // Constructor
        //
        Column();

        //----------------------------------------------------------------------
        // Constructor
        //
        Column(unsigned int size);

        //----------------------------------------------------------------------
        // Copy Constructor
        //
        // @param original The original Column to copy
        //
        Column(const Column &original);

        //----------------------------------------------------------------------
        // Destructor
        //
        ~Column();

        //----------------------------------------------------------------------
        // Resize
        // Resize the elements_ vector
        //
        // @param size The new size of the vector
        //
        void resize(unsigned int size);

        //----------------------------------------------------------------------
        // operator[]
        // Uses the std::vector::operator[] internally.
        //
        // @param element_index index of the element
        //
        // @return Returns the element with index element_index from the
        //         std::vector<T> elements_.
        //
        T& operator[](unsigned int element_index);
        const T& operator[](unsigned int element_index) const;

        //----------------------------------------------------------------------
        // at
        // Same as operator[] but does bounds checking and throws a
        // std::out_of_range if element_index is out of range.
        // Uses the std::vector::at(size_type n) internally.
        //
        // @param element_index index of the element
        //
        // @return Returns the element with index element_index from the
        //         std::vector<T> elements_.
        //
        T& at(unsigned int element_index);
        const T& at(unsigned int element_index) const;

        //----------------------------------------------------------------------
        // begin and end iterators
        //
        // @return Returns the begin and end iterators of the
        //         std::vector<T> elements_.
        //
        typename std::vector<T>::const_iterator begin() const;
        typename std::vector<T>::iterator begin();
        typename std::vector<T>::const_iterator end() const;
        typename std::vector<T>::iterator end();
    };

  protected:
    Vector2d size_;
    std::vector<Column> columns_;
    void resize();

  public:
    //--------------------------------------------------------------------------
    // Constructor
    //
    // Constructs the matrix with a size of 0/0.
    //
    Matrix();

    //--------------------------------------------------------------------------
    // Constructor
    //
    // @param width  The width the matrix should be constructed with
    // @param height The height the matrix should be constructed with
    //
    Matrix(unsigned int width, unsigned int height);

    //--------------------------------------------------------------------------
    // Constructor
    //
    // @param size A 2D vector containing the size the matrix should be
    //             constructed with
    //
    Matrix(Vector2d size);

    //--------------------------------------------------------------------------
    // Copy Constructor
    //
    Matrix(const Matrix &original);

    //--------------------------------------------------------------------------
    // Resize
    //
    // @param width  The width the matrix should be resized to
    // @param height The height the matrix should be resized to
    //
    void resize(unsigned int width, unsigned int height);

    //--------------------------------------------------------------------------
    // Resize
    //
    // @param new_size A 2D vector containing the size the matrix should be
    //                 resized to
    //
    void resize(Vector2d new_size);

    //--------------------------------------------------------------------------
    // Get Size
    //
    // @return Returns the size of the matrix.
    //
    Vector2d getSize() const;

    //--------------------------------------------------------------------------
    // operator[unsigned int]
    //
    // @param column_index The index of the column
    //
    // @return Returns the column with index column_index.
    //
    Column& operator[](unsigned int column_index);
    const Column& operator[](unsigned int column_index) const;

    //--------------------------------------------------------------------------
    // operator[Vector2d]
    //
    // @param position The column and row of the accessing element.
    //
    // @return Returns the element on the position position.
    //
    T& operator[](Vector2d position);
    const T& operator[](Vector2d position) const;

    //--------------------------------------------------------------------------
    // at(unsigned int)
    //
    // Same as operator[unsigned int] but does bounds checking and throws a
    // std::out_of_range if element_index is out of range.
    // Uses the std::vector::at(size_type n) internally.
    //
    // @param column_index The index of the column
    //
    // @return Returns the column with index column_index.
    //
    Column& at(unsigned int column_index);
    const Column& at(unsigned int column_index) const;

    //--------------------------------------------------------------------------
    // at(Vector2d)
    //
    // Same as operator[Vector2d] but does bounds checking and throws a
    // std::out_of_range if Vector2d is out of range.
    // Uses the std::vector::at(size_type n) internally.
    //
    // @param position The column and row of the accessing element.
    //
    // @return Returns the element on the position position.
    //
    T& at(unsigned int row_index, unsigned int element_index);
    const T& at(unsigned int row_index, unsigned int element_index) const;

    //--------------------------------------------------------------------------
    // Put method
    //
    // This method puts the element on the position. If the matrix is to small
    // it is automatically grown.
    //
    // @param element  The element to push
    // @param position The column and row the element should be put to.
    //
    void put(T element, Vector2d position);

    //--------------------------------------------------------------------------
    // Put method
    //
    // This method puts the element on the position. If the matrix is to small
    // it is automatically grown.
    //
    // @param element The element to push
    // @param column  The column the element should be put to.
    // @param row     The row the element should be put to.
    //
    void put(T element, unsigned int column, unsigned int row);
};




//------------------------------------------------------------------------------
//
// The Matrix method implementations
//

template<class T>
Matrix<T>::Matrix() :
        size_(0, 0),
        columns_(static_cast<unsigned int>(size_.getX()),
                 Column(static_cast<unsigned int>(size_.getY())))
{

}


template<class T>
Matrix<T>::Matrix(unsigned int width, unsigned int height) :
        size_(width, height),
        columns_(static_cast<unsigned int>(size_.getX()),
                 Column(static_cast<unsigned int>(size_.getY())))
{

}


template<class T>
Matrix<T>::Matrix(Vector2d size) :
        size_(size),
        columns_(static_cast<unsigned int>(size_.getX()),
                 Column(static_cast<unsigned int>(size_.getY())))
{

}


template<class T>
Matrix<T>::Matrix(const Matrix &original) :
        size_(original.size_),
        columns_(original.columns_)
{

}


template<class T>
void Matrix<T>::resize()
{
  columns_.resize(static_cast<unsigned int>(size_.getX()));

  for(auto &row : columns_)
    row.resize(static_cast<unsigned int>(size_.getY()));
}


template<class T>
void Matrix<T>::resize(unsigned int width, unsigned int height)
{
  resize(Vector2d(width, height));
}


template<class T>
void Matrix<T>::resize(Vector2d new_size)
{
  size_ = new_size;
  resize();
}


template<class T>
Vector2d Matrix<T>::getSize() const
{
  return size_;
}


template<class T>
typename Matrix<T>::Column& Matrix<T>::operator[](unsigned int column_index)
{
  return columns_[column_index];
}


template<class T>
const typename
Matrix<T>::Column& Matrix<T>::operator[](unsigned int column_index) const
{
  return columns_[column_index];
}


template<class T>
T& Matrix<T>::operator[](Vector2d position)
{
  return columns_[position.getX()][position.getY()];
}


template<class T>
const T& Matrix<T>::operator[](Vector2d position) const
{
  return columns_[position.getX()][position.getY()];
}


template<class T>
typename Matrix<T>::Column& Matrix<T>::at(unsigned int column_index)
{
  return columns_.at(column_index);
}


template<class T>
const
typename Matrix<T>::Column& Matrix<T>::at(unsigned int column_index) const
{
  return columns_.at(column_index);
}


template<class T>
T& Matrix<T>::at(unsigned int row_index, unsigned int element_index)
{
  return columns_.at(row_index).at(element_index);
}


template<class T>
const T& Matrix<T>::at(unsigned int row_index, unsigned int element_index) const
{
  return columns_.at(row_index).at(element_index);
}


template<class T>
void Matrix<T>::put(T element, Vector2d position)
{
  Vector2d new_size = size_;

  if(position.getX() >= size_.getX())
    new_size.setX(position.getX() + 1);

  if(position.getY() >= size_.getY())
    new_size.setY(position.getY() + 1);

  resize(new_size);

  (*this)[position] = element;
}


template<class T>
void Matrix<T>::put(T element, unsigned int column, unsigned int row)
{
  put(element, Vector2d(column, row));
}



//------------------------------------------------------------------------------
//
// The Matrix::Column method implementations
//

template<class T>
Matrix<T>::Column::Column()
{

}


template<class T>
Matrix<T>::Column::Column(unsigned int size) : elements_(size)
{

}


template<class T>
Matrix<T>::Column::Column(const Column &original) :
        elements_(original.elements_)
{

};


template<class T>
Matrix<T>::Column::~Column()
{

}

template<class T>
void Matrix<T>::Column::resize(unsigned int size)
{
  elements_.resize(size);
}


template<class T>
T& Matrix<T>::Column::operator[](unsigned int element_index)
{
  return elements_[element_index];
}


template<class T>
const T& Matrix<T>::Column::operator[](unsigned int element_index) const
{
  return elements_[element_index];
}


template<class T>
T& Matrix<T>::Column::at(unsigned int element_index)
{
  return elements_.at(element_index);
}


template<class T>
const T& Matrix<T>::Column::at(unsigned int element_index) const
{
  return elements_.at(element_index);
}


template<class T>
typename std::vector<T>::const_iterator Matrix<T>::Column::begin() const
{
  return elements_.begin();
};


template<class T>
typename std::vector<T>::iterator Matrix<T>::Column::begin()
{
  return elements_.begin();
};


template<class T>
typename std::vector<T>::const_iterator Matrix<T>::Column::end() const
{
  return elements_.end();
};


template<class T>
typename std::vector<T>::iterator Matrix<T>::Column::end()
{
  return elements_.end();
}



#endif //MAZE_MATRIX_H
