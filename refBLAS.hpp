#ifndef REFBLAS_HPP
#define REFBLAS_HPP

#include <iostream>
#include <vector>
#include <random>
#include <fstream>

double create_random_double (double end_val);
std::vector<double> create_random_vector (int size);
std::vector<std::vector<double>> create_random_matrix (int rows, int cols);
void print_vector (std::vector<double> vec);
void print_matrix (std::vector<std::vector<double>> matrix);
void scale_vector(double num, std::vector<double>& vec);
void scale_matrix(double num, std::vector<std::vector<double>>& matrix);
double average_vector (std::vector<int> vec);
void export_vector_to_csv (std::vector<int> vec);
void export_vector_to_csvT (std::vector<int> vec1, std::vector<int> vec2, std::vector<int> vec3);
double vector_dot_product (std::vector<double> vec1, std::vector<double> vec2);
std::vector<std::vector<double>> matrix_transpose (std::vector<std::vector<double>> matrix);
void daxpy (double a, const std::vector<double> &x, std::vector<double> &y);
void daxpy_unroll (double a, const std::vector<double> &x, std::vector<double> &y, int block_size);
void dgemv(double a, const std::vector<std::vector<double>> &A, const std::vector<double> &x, double b, std::vector<double> &y);
void dgemm(double a, const std::vector<std::vector<double>> &A, const std::vector<std::vector<double>> &B, double b, std::vector<std::vector<double>> &C);
std::vector<std::vector<double>> matrix_identity(int size);
std::vector<double> vector_identity(int size, int spot);
template <typename T> 
T create_random (T end_val);
template <typename T> 
std::vector<T> create_random_vectorT (int size);
template <typename T> 
std::vector<std::vector<T>> create_random_matrixT (int rows, int cols);
template <typename T> 
T vector_dot_productT (std::vector<T> vec1, std::vector<T> vec2);
template <typename T> 
std::vector<std::vector<T>> matrix_transposeT (std::vector<std::vector<T>> matrix);
template <typename T> 
void axpy (T a, const std::vector<T> &x, std::vector<T> &y);
template <typename T> 
void gemv(T a, const std::vector<std::vector<T>> &A, const std::vector<T> &x, T b, std::vector<T> &y);
template <typename T> 
void gemm(T a, const std::vector<std::vector<T>> &A, const std::vector<std::vector<T>> &B, T b, std::vector<std::vector<T>> &C);

#endif