#include <chrono>
#include "refBLAS.hpp"

int main() {

   std::vector<int> average_times_in_flops;
   
   int n = 2048;
   int ntrial = 100;
   int num_flops = 2 * n;

   for (int block_size=1; block_size<128; block_size *= 2) {
      std::vector<int> times_in_flops;

      double a = create_random_double(10);
      const std::vector<double> x = create_random_vector(n);

      for (int i=0; i<ntrial; i++) {

         std::vector<double> y = create_random_vector(n);

         auto start = std::chrono::high_resolution_clock::now();
         daxpy_unroll(a, x, y, block_size);
         auto stop = std::chrono::high_resolution_clock::now();
         auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
         
         times_in_flops.push_back(((double)num_flops * 1000.0) / (double)duration.count());
      }
      average_times_in_flops.push_back(average_vector(times_in_flops));
      times_in_flops.clear();
   }
   export_vector_to_csv(average_times_in_flops);

   return 0;
}