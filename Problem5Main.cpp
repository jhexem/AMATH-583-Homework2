#include <chrono>
#include "refBLAS.hpp"

int main() {

   int n_start = 2;
   int n_end = 1024;

   float rand_int_end_val = 10;

   int num_flops1; int num_flops2; int num_flops3;
   std::vector<int> average_times_in_flops1;
   std::vector<int> average_times_in_flops2;
   std::vector<int> average_times_in_flops3;
   
   int ntrial = 3;

   for (int n=n_start; n<=n_end; n++) {

      num_flops1 = 2 * n;
      num_flops2 = 2 * n * n + 2 * n;
      num_flops3 = 2 * n * n * n + 2 * n * n;
      std::vector<int> times_in_flops1;
      std::vector<int> times_in_flops2;
      std::vector<int> times_in_flops3;

      float a = create_random<float>(rand_int_end_val);
      float b = create_random<float>(rand_int_end_val);
      const std::vector<float> x = create_random_vectorT<float>(n);
      const std::vector<std::vector<float>> A = create_random_matrixT<float>(n, n);
      const std::vector<std::vector<float>> B = create_random_matrixT<float>(n, n);

      for (int i=0; i<ntrial; i++) {
         std::vector<float> y1 = create_random_vectorT<float>(n);

         auto start1 = std::chrono::high_resolution_clock::now();
         axpy<float>(a, x, y1);
         auto stop1 = std::chrono::high_resolution_clock::now();
         auto duration1 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop1 - start1);
         times_in_flops1.push_back(((double)num_flops1 * 1000.0) / (double)duration1.count());

         std::vector<float> y2 = create_random_vectorT<float>(n);

         auto start2 = std::chrono::high_resolution_clock::now();
         gemv<float>(a, A, x, b, y2);
         auto stop2 = std::chrono::high_resolution_clock::now();
         auto duration2 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop2 - start2);
         times_in_flops2.push_back(((double)num_flops2 * 1000.0) / (double)duration2.count());

         std::vector<std::vector<float>> C = create_random_matrixT<float>(n, n);

         auto start3 = std::chrono::high_resolution_clock::now();
         gemm<float>(a, A, B, b, C);
         auto stop3 = std::chrono::high_resolution_clock::now();
         auto duration3 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop3 - start3);
         times_in_flops3.push_back(((double)num_flops3 * 1000.0) / (double)duration3.count());
      }
      average_times_in_flops1.push_back(average_vector(times_in_flops1));
      average_times_in_flops2.push_back(average_vector(times_in_flops2));
      average_times_in_flops3.push_back(average_vector(times_in_flops3));
      times_in_flops1.clear();
      times_in_flops2.clear();
      times_in_flops3.clear();
   }
   export_vector_to_csvT(average_times_in_flops1, average_times_in_flops2, average_times_in_flops3);

   return 0;
}