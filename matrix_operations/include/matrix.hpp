#pragma once
#include <vector>
#include <utility>
#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <iomanip>
#include <algorithm>
#include <sstream>


namespace mxlib {

    template <typename T>
    class Matrix {


        template <typename U>
        friend Matrix<U> operator+(Matrix<U> lhs, const Matrix<U> &rhs);

        template <typename U>
        friend Matrix<U> operator-(Matrix<U> lhs, const Matrix<U> &rhs);

        template <typename U>
        friend Matrix<U> operator*(Matrix<U> lhs, const Matrix<U> &rhs);


        public:
            Matrix(size_t rows, size_t cols, const T &fill_value = T{}) 
                : rows(rows), cols(cols) {
                if (rows == 0 || cols == 0) {
                    throw std::invalid_argument("Matrix dimensions must be positive");
                }
                matrix.assign(rows * cols, fill_value);
            }


            Matrix() noexcept : rows(0), cols(0), matrix{} {}


            template <typename OtherT>
            Matrix(const Matrix<OtherT> &other) : Matrix(other.get_rows(), other.get_cols()) {
                for (size_t i = 0; i < other.size(); ++i) {
                    matrix[i] = static_cast<T>(other[i]); 
                }
            }


            Matrix(std::initializer_list<std::initializer_list<T>> list) {
                if (list.empty()) {
                    throw std::invalid_argument("Empty initializer list");
                }
        
                rows = list.size();
                cols = list.begin()->size();
        
                if (cols == 0) {
                    throw std::invalid_argument("Empty rows in initializer list");
                }
        
                matrix.reserve(rows * cols); 
        
                for (const auto& row : list) {
                    if (row.size() != cols) {
                        throw std::invalid_argument("Inconsistent row sizes");
                    }
                    for (const auto& element : row) {
                        matrix.emplace_back(element); 
                    }
                }
            }


            friend std::ostream &operator<<(std::ostream &os, const Matrix<T> &mat) {
                size_t max_width = 0;
                for(size_t i = 0; i<mat.size(); ++i) {
                    std::ostringstream oss;
                    oss << mat.matrix[i];
                    max_width = std::max(max_width, oss.str().length());
                }
                max_width = std::max<size_t>(max_width, 3);

                for (size_t i = 0; i < mat.get_rows(); ++i) {
                    for (size_t j = 0; j < mat.get_cols(); ++j) {
                        os << std::setw(max_width) << mat(i, j) << " ";
                    }
                    os << '\n';
                }
                return os;
            }


            const T &operator[](size_t index) const {
                if(index >= matrix.size()) {
                    throw std::out_of_range("Index out of bounds");
                }
                return matrix[index];
            }


            T &operator[](size_t index) {
                if(index >= matrix.size()) {
                    throw std::out_of_range("Index out of bounds");
                }
                return matrix[index];
            }


            T &operator()(size_t row, size_t col) {
                if (row >= rows || col >= cols) {
                    throw std::out_of_range("Matrix subscript out of bounds");
                }
                return matrix[row * cols + col];
            }


            const T &operator()(size_t row, size_t col) const {
                if (row >= rows || col >= cols) {
                    throw std::out_of_range("Matrix subscript out of bounds");
                }
                return matrix[row * cols + col];
            }


            Matrix &operator+=(const Matrix &other) {
                if(rows != other.rows || cols != other.cols) {
                    throw std::invalid_argument("Matrix dimensions don't match"); // might update it
                }

                for(size_t i = 0; i<matrix.size(); ++i) {
                    matrix[i] += other.matrix[i];
                }
                return *this;
            }


            Matrix &operator-=(const Matrix &other) {
                if(rows != other.rows || cols != other.cols) {
                    throw std::invalid_argument("Matrix dimensions don't match"); 
                }

                for(size_t i = 0; i<matrix.size(); ++i) {
                    matrix[i] -= other.matrix[i];
                }
                return *this;
            }


            Matrix &operator*=(const Matrix& other) {
                if(cols != other.rows) {
                    throw std::invalid_argument("Matrix dimensions are incompatible for multiplication.");
                }

                std::vector<T> result(rows * other.cols, T{});
                for(size_t i = 0; i<rows; ++i) {
                    for(size_t j = 0; j<other.cols; ++j) {
                        for(size_t k = 0; k<cols; ++k) {
                            result[i * other.cols + j] += matrix[i * cols + k] * other.matrix[k * other.cols + j];
                        }
                    }
                }
                matrix = std::move(result);
                cols = other.cols;
                return *this;
            }


            void transpose() {
                if(rows == cols) {
                    for(size_t i = 0; i<rows; ++i) {
                        for(size_t j = i+1; j<cols; ++j) {
                            std::swap(matrix[i * cols + j], matrix[j * cols + i]);
                        }
                    }
                }else {
                    std::vector<T> result(rows * cols, T{});
                    for(size_t i = 0; i<rows; ++i) {
                        for(size_t j = 0; j<cols; ++j) {
                            result[j * rows + i] = matrix[i * cols + j];
                        }
                    }
                    matrix = std::move(result);
                    std::swap(rows, cols);
                }
            }


            size_t get_rows() const noexcept { return rows; }
            size_t get_cols() const noexcept { return cols; }
            size_t     size() const noexcept { return cols * rows; }
            bool      empty() const noexcept { return rows == 0 || cols == 0; }

            std::vector<T>::iterator          begin() noexcept { return matrix.begin();  }
            std::vector<T>::iterator            end() noexcept { return matrix.end();    }
            std::vector<T>::reverse_iterator rbegin() noexcept { return matrix.rbegin(); }
            std::vector<T>::reverse_iterator   rend() noexcept { return matrix.rend();   }

            std::vector<T>::const_iterator          begin() const noexcept { return matrix.begin();  } 
            std::vector<T>::const_iterator            end() const noexcept { return matrix.end();    }
            std::vector<T>::const_reverse_iterator rbegin() const noexcept { return matrix.rbegin(); }
            std::vector<T>::const_reverse_iterator   rend() const noexcept { return matrix.rend();   }


        private:
            std::vector<T> matrix;
            size_t rows, cols;
    };


    template <typename U>
    Matrix<U> operator+(Matrix<U> lhs, const Matrix<U> &rhs) {  
        lhs += rhs;        
        return lhs;        
    }


    template <typename U>
    Matrix<U> operator-(Matrix<U> lhs, const Matrix<U> &rhs) {
        lhs -= rhs;
        return lhs;      
    }   


    template <typename U>
    Matrix<U> operator*(Matrix<U> lhs, const Matrix<U> &rhs) {
        lhs *= rhs;
        return lhs;       
    }


    template <typename T>
    Matrix(size_t, size_t, T) -> Matrix<T>;


    template<typename T>
    Matrix(std::initializer_list<std::initializer_list<T>>) -> Matrix<T>;


    Matrix(size_t, size_t) -> Matrix<double>;


    Matrix() -> Matrix<double>;

} 
