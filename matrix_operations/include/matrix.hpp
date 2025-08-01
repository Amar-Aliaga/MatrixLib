#pragma once
#include <vector>
#include <utility>
#include <memory>
#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <iomanip>
#include <algorithm>
#include <thread>  

namespace mxlib {

    //template <typename T1>
    class Matrix {

        friend Matrix operator+(const Matrix &lhs, const Matrix &rhs);
        friend Matrix operator-(const Matrix &lhs, const Matrix &rhs);
        friend Matrix operator*(const Matrix& lhs, const Matrix& rhs);

        public:
            Matrix(size_t rows, size_t cols, int initial_value = 0) : rows(rows), cols(cols) {
                if(rows == 0 || cols == 0) {
                    throw std::invalid_argument("Rows or Columns are zero");
                }

                matrix.resize(rows * cols, initial_value);
            }


            Matrix(std::initializer_list<std::initializer_list<int>> list) {
                if (list.size() == 0) {
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


            friend std::ostream &operator<<(std::ostream &os, const Matrix &mat) {
                for(size_t i = 0; i<mat.size(); ++i) {
                    if(i % mat.cols == 0 && i != 0) {
                        os << std::endl;
                    }
                    os << std::setw(4) << mat[i] << " "; // update later
                }
                os << std::endl;
                return os;
            }


            const int &operator[](size_t index) const {
                if(index >= matrix.size()) {
                    throw std::out_of_range("Index out of bounds");
                }
                return matrix[index];
            }


            int &operator[](size_t index) {
                if(index >= matrix.size()) {
                    throw std::out_of_range("Index out of bounds");
                }
                return matrix[index];
            }


            int &operator()(size_t row, size_t col) {
                if (row >= rows || col >= cols) {
                    throw std::out_of_range("Matrix subscript out of bounds");
                }
                return matrix[row * cols + col];
            }


            const int &operator()(size_t row, size_t col) const {
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

                std::vector<int> result(rows * other.cols, 0);
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
                    std::vector<int> result(rows * cols, 0);
                    for(size_t i = 0; i<rows; ++i) {
                        for(size_t j = 0; j<cols; ++j) {
                            result[j * rows + i] = matrix[i * cols + j];
                        }
                    }
                    matrix = std::move(result);
                    std::swap(rows, cols);
                }
            }


            size_t get_rows() const { return rows; }
            size_t get_cols() const { return cols; }
            size_t size() const { return cols * rows; }
            bool empty() const { return rows == 0 || cols == 0; }

        private:
        std::vector<int> matrix;
        size_t cols, rows;
    };


    Matrix operator+(const Matrix &lhs, const Matrix &rhs) {
        Matrix result = lhs;  
        result += rhs;        
        return result;        
    }

    Matrix operator-(const Matrix &lhs, const Matrix &rhs) {
        Matrix result = lhs; 
        result -= rhs;        
        return result;       
    }   

    Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
        Matrix result = lhs;  
        result *= rhs;       
        return result;        
    }
}
