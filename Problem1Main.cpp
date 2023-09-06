#include <chrono>
#include "refBLAS.hpp"

int main() {

   int n_start = 2;
   int n_end = 1024;

   double rand_int_end_val = 10;

   int num_flops;
   std::vector<int> average_times_in_flops;
   
   int ntrial = 10;

   for (int n=n_start; n<=n_end; n++) {

      num_flops = 2 * n;
      std::vector<int> times_in_flops;

      double a = create_random_double(rand_int_end_val);
      const std::vector<double> x = create_random_vector(n);

      for (int i=0; i<ntrial; i++) {

         std::vector<double> y = create_random_vector(n);

         auto start = std::chrono::high_resolution_clock::now();
         daxpy(a, x, y);
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