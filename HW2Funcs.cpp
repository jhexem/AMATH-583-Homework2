#include "refBLAS.hpp"

double create_random_double (double end_val) {

   std::random_device dev;
   std::mt19937 rng(dev());
   std::uniform_real_distribution<double> dist(0,1);

   double rNum = dist(rng) * end_val;
   return rNum;
}

std::vector<double> create_random_vector (int size) {

   std::vector<double> random_vector;

   std::random_device dev;
   std::mt19937 rng(dev());
   std::uniform_real_distribution<double> dist(0,1);

   for (int i=0; i<size; i++) {
      double rNum = dist(rng);
      random_vector.push_back(rNum);
   }
   return random_vector;
}

std::vector<std::vector<double>> create_random_matrix (int rows, int cols) {

   std::vector<std::vector<double>> random_matrix;

   std::random_device dev;
   std::mt19937 rng(dev());
   std::uniform_real_distribution<double> dist(0,1);

   for (int i=0; i<rows; i++) {
      std::vector<double> new_row;

      for (int j=0; j<cols; j++) {
         double rNum = dist(rng);
         new_row.push_back(rNum);
      }
      random_matrix.push_back(new_row);
   }
   return random_matrix;
}

void print_vector (std::vector<double> vec) {
   for (int i=0; i<vec.size(); i++) {
      std::cout << vec[i] << " ";
   }
   std::cout << std::endl;
}

void print_matrix (std::vector<std::vector<double>> matrix) {
   for (int i=0; i<matrix.size(); i++) {
      for (int j=0; j<matrix[i].size(); j++) {
         std::cout << matrix[i][j] << " ";
      }
      std::cout << std::endl;
   }
   std::cout << std::endl;
}

void scale_vector(double num, std::vector<double>& vec) {

   int size = vec.size();

   for (int i=0; i<size; i++) {
      vec[i] = num * vec[i];
   }
}

void scale_matrix(double num, std::vector<std::vector<double>>& matrix) {

   int row_size = matrix.size();
   int col_size = matrix[0].size();

   for (int i=0; i<row_size; i++) {
      for (int j=0; j<col_size; j++) {
         matrix[i][j] = num * matrix[i][j];
      }
   }
}

double average_vector (std::vector<int> vec) {
   int total = 0;
   for (int i=0; i<vec.size(); i++) {
      total += vec[i];
   }
   return total / vec.size();
}

void export_vector_to_csv (std::vector<int> vec) {
   std::ofstream file;
   file.open("results.csv");
   for (int i=0; i<vec.size(); i++) {
      file << vec[i] << "," << std::endl;
   }
   file.close();
}

void export_vector_to_csvT (std::vector<int> vec1, std::vector<int> vec2, std::vector<int> vec3) {
   std::ofstream file;
   file.open("results.csv");
   for (int i=0; i<vec1.size(); i++) {
      file << vec1[i] << "," << std::endl;
   }
   for (int i=0; i<vec2.size(); i++) {
      file << vec2[i] << "," << std::endl;
   }
   for (int i=0; i<vec3.size(); i++) {
      file << vec3[i] << "," << std::endl;
   }
   file.close();
}

double vector_dot_product (std::vector<double> vec1, std::vector<double> vec2) {

   int size = vec1.size();
   double dot_product = 0;

   for (int i=0; i<size; i++) {
      dot_product += vec1[i] * vec2[i];
   }
   return dot_product;
}

std::vector<std::vector<double>> matrix_transpose (std::vector<std::vector<double>> matrix) {

   int size = matrix.size();
   std::vector<std::vector<double>> transpose;

   for (int i=0; i<size; i++) {
      std::vector<double> column;
      for (int j=0; j<size; j++) {
         column.push_back(matrix[j][i]);
      }
      transpose.push_back(column);
   }
   return transpose; 

}

void daxpy (double a, const std::vector<double> &x, std::vector<double> &y) {
   
   int size = x.size();
   int ysize = y.size();
   
   if (size==ysize) {
      for (int i=0; i<size; i++) {
         y[i] = a * x[i] + y[i];
      }
   }
   else std::cout << "Wrong dimensions" << std::endl;
}

void daxpy_unroll (double a, const std::vector<double> &x, std::vector<double> &y, int block_size) {
   
   int size = x.size();
   int ysize = y.size();
   int i = 0;

   if (size==ysize) {
      switch (block_size) {
         case 1:
            for (int i=0; i<size; i++) {
               y[i] = a * x[i] + y[i];
            }
            break;
         case 2:
            for (i=0; i<(size-block_size); i+=block_size) {
               y[i] = a * x[i] + y[i];
               y[i+1] = a * x[i+1] + y[i+1];
            }
            for (int j=i; j<size; j++) {
               y[j] = a * x[j] + y[j];
            }
            break;
         case 3:
            for (i=0; i<(size-block_size); i+=block_size) {
               y[i] = a * x[i] + y[i];
               y[i+1] = a * x[i+1] + y[i+1];
               y[i+2] = a * x[i+2] + y[i+2];
            }
            for (int j=i; j<size; j++) {
               y[j] = a * x[j] + y[j];
            }
            break;
         default:
            for (i=0; i<(size-block_size); i+=block_size) {
               int j;
               for (j=i; j<(i+block_size - 4); j+=4) {
                  y[j] = a * x[j] + y[j];
                  y[j+1] = a * x[j+1] + y[j+1];
                  y[j+2] = a * x[j+2] + y[j+2];
                  y[j+3] = a * x[j+3] + y[j+3];
               }
               for (int k=j; k<(i+block_size); k++) {
                  y[k] = a * x[k] + y[k];
               }
            }
            for (int l=i; l<size; l++) {
               y[l] = a * x[l] + y[l];
            }
      }
   }
   else std::cout << "Wrong dimensions" << std::endl;
}

void dgemv(double a, const std::vector<std::vector<double>> &A, const std::vector<double> &x, double b, std::vector<double> &y) {

   int size = x.size();
   int sizey = y.size();
   int sizeArows = A.size();
   int sizeAcols = A[0].size();

   if (size==sizeAcols && sizey==sizeArows) {
      for (int i=0; i<size; i++) {
         y[i] = a * vector_dot_product(x, A[i]) + b * y[i];
      }
   }
   else std::cout << "Wrong dimensions" << std::endl;
}

void dgemm(double a, const std::vector<std::vector<double>> &A, const std::vector<std::vector<double>> &B, double b, std::vector<std::vector<double>> &C) {

   int sizeArows = A.size();
   int sizeAcols = A[0].size();
   int sizeBrows = B.size();
   int sizeBcols = B[0].size();
   int sizeCrows = C.size();
   int sizeCcols = C[0].size();

   if (sizeAcols==sizeBrows && sizeCrows==sizeArows && sizeCcols==sizeBcols) {
      std::vector<std::vector<double>> Btranspose = matrix_transpose(B);

      for (int i=0; i<sizeArows; i++) {
         for (int j=0; j<sizeBcols; j++) {
            C[i][j] = a * vector_dot_product(A[i], Btranspose[j]) + b * C[i][j];
         }
      }
   }
   else std::cout << "Wrong dimensions" << std::endl;
}

std::vector<std::vector<double>> matrix_identity(int size) {

   std::vector<std::vector<double>> matrix;

   for (int i=0; i<size; i++) {
      std::vector<double> row;
      for (int j=0; j<size; j++) {
         if (i==j) row.push_back(1.0);
         else row.push_back(0.0);
      }
      matrix.push_back(row);
   }
   return matrix;
}

std::vector<double> vector_identity(int size, int spot) {

   std::vector<double> vec;
   for (int i=0; i<size; i++) {
      if (i==spot) vec.push_back(1.0);
      else vec.push_back(0.0);
   }
   return vec;

}

// Templates-----------------------------------------------------------------------------------------

template <typename T>
T create_random (T end_val) {

   std::random_device dev;
   std::mt19937 rng(dev());
   std::uniform_real_distribution<T> dist(0,1);

   T rNum = dist(rng) * end_val;
   return rNum;
}

template <typename T>
std::vector<T> create_random_vectorT (int size) {

   std::vector<T> random_vector;

   std::random_device dev;
   std::mt19937 rng(dev());
   std::uniform_real_distribution<T> dist(0,1);

   for (int i=0; i<size; i++) {
      T rNum = dist(rng);
      random_vector.push_back(rNum);
   }
   return random_vector;
}

template <typename T>
std::vector<std::vector<T>> create_random_matrixT (int rows, int cols) {

   std::vector<std::vector<T>> random_matrix;

   std::random_device dev;
   std::mt19937 rng(dev());
   std::uniform_real_distribution<T> dist(0,1);

   for (int i=0; i<rows; i++) {
      std::vector<T> new_row;

      for (int j=0; j<cols; j++) {
         T rNum = dist(rng);
         new_row.push_back(rNum);
      }
      random_matrix.push_back(new_row);
   }
   return random_matrix;
}

template <typename T>
T vector_dot_productT (std::vector<T> vec1, std::vector<T> vec2) {

   int size = vec1.size();
   T dot_product = 0;

   for (int i=0; i<size; i++) {
      dot_product += vec1[i] * vec2[i];
   }
   return dot_product;
}

template <typename T>
std::vector<std::vector<T>> matrix_transposeT (std::vector<std::vector<T>> matrix) {

   int size = matrix.size();
   std::vector<std::vector<T>> transpose;

   for (int i=0; i<size; i++) {
      std::vector<T> column;
      for (int j=0; j<size; j++) {
         column.push_back(matrix[j][i]);
      }
      transpose.push_back(column);
   }
   return transpose; 

}

template <typename T>
void axpy (T a, const std::vector<T> &x, std::vector<T> &y) {
   
   int size = x.size();
   int ysize = y.size();
   
   if (size==ysize) {
      for (int i=0; i<size; i++) {
         y[i] = a * x[i] + y[i];
      }
   }
   else std::cout << "Wrong dimensions" << std::endl;
}

template <typename T>
void gemv(T a, const std::vector<std::vector<T>> &A, const std::vector<T> &x, T b, std::vector<T> &y) {

   int size = x.size();
   int sizey = y.size();
   int sizeArows = A.size();
   int sizeAcols = A[0].size();

   if (size==sizeAcols && sizey==sizeArows) {
      for (int i=0; i<size; i++) {
         y[i] = a * vector_dot_productT<T>(x, A[i]) + b * y[i];
      }
   }
   else std::cout << "Wrong dimensions" << std::endl;
}

template <typename T>
void gemm(T a, const std::vector<std::vector<T>> &A, const std::vector<std::vector<T>> &B, T b, std::vector<std::vector<T>> &C) {

   int sizeArows = A.size();
   int sizeAcols = A[0].size();
   int sizeBrows = B.size();
   int sizeBcols = B[0].size();
   int sizeCrows = C.size();
   int sizeCcols = C[0].size();

   if (sizeAcols==sizeBrows && sizeCrows==sizeArows && sizeCcols==sizeBcols) {
      std::vector<std::vector<T>> Btranspose = matrix_transposeT<T>(B);

      for (int i=0; i<sizeArows; i++) {
         for (int j=0; j<sizeBcols; j++) {
            C[i][j] = a * vector_dot_productT<T>(A[i], Btranspose[j]) + b * C[i][j];
         }
      }
   }
   else std::cout << "Wrong dimensions" << std::endl;
}

template float create_random<float> (float end_val);
template std::vector<float> create_random_vectorT<float> (int size);
template std::vector<std::vector<float>> create_random_matrixT<float> (int rows, int cols);
template float vector_dot_productT<float> (std::vector<float> vec1, std::vector<float> vec2);
template std::vector<std::vector<float>> matrix_transposeT<float> (std::vector<std::vector<float>> matrix);
template void axpy<float> (float a, const std::vector<float> &x, std::vector<float> &y);
template void gemv<float> (float a, const std::vector<std::vector<float>> &A, const std::vector<float> &x, float b, std::vector<float> &y);
template void gemm<float> (float a, const std::vector<std::vector<float>> &A, const std::vector<std::vector<float>> &B, float b, std::vector<std::vector<float>> &C);

template double create_random<double> (double end_val);
template std::vector<double> create_random_vectorT<double> (int size);
template std::vector<std::vector<double>> create_random_matrixT<double> (int rows, int cols);
template double vector_dot_productT<double> (std::vector<double> vec1, std::vector<double> vec2);
template std::vector<std::vector<double>> matrix_transposeT<double> (std::vector<std::vector<double>> matrix);
template void axpy<double> (double a, const std::vector<double> &x, std::vector<double> &y);
template void gemv<double> (double a, const std::vector<std::vector<double>> &A, const std::vector<double> &x, double b, std::vector<double> &y);
template void gemm(double a, const std::vector<std::vector<double>> &A, const std::vector<std::vector<double>> &B, double b, std::vector<std::vector<double>> &C);