#include<iostream>
#include<random>
#include<omp.h>



/*! \brief Recursively perform a Merge Sort
 *
 * \param [in]  sortvec
 *                   Pointer to the first element of the data that should be sorted.
 * \param [in]  auxiliary
 *                   Pointer to the first element of an auxiliary vector that can hold temporary sorting operations.
 * \param [in]  nelements
 *                   Number of elements to sort during this call to mergesort.
 */
void mergesort(double* sortvec, double* auxiliary, int nelements) {
  if ( nelements > 2 ) {
    // Recursively split the vector into two different sorting operations
    mergesort(&sortvec[0], &auxiliary[0], nelements / 2);
    mergesort(&sortvec[nelements / 2], &auxiliary[nelements / 2], nelements - (nelements / 2));
  }

  // Do a complete sort into the auxiliary space
  int i = 0;
  int j = nelements / 2;
  for (int icompare = 0; icompare < nelements; icompare++) {
    if ( i >= nelements / 2 ) {
      auxiliary[icompare] = sortvec[j];
      j++;
    }
    else if ( j >= nelements ) {
      auxiliary[icompare] = sortvec[i];
      i++;
    }
    else if ( sortvec[i] < sortvec[j] ) {
      auxiliary[icompare] = sortvec[i];
      i++;
    }
    else {
      auxiliary[icompare] = sortvec[j];
      j++;
    }
  }

  // Copy the sorted auxiliary data back into the sortvec
  for (int i = 0; i < nelements; i++) {
    sortvec[i] = auxiliary[i];
  }
}



int main(int argc, char *argv[]) {

  // We will initialize the random number seed with the process rank
  std::mt19937 mt = std::mt19937(1);
  std::uniform_real_distribution<double> dist(0.0, 1.0);

  // Create a set of random values on each rank
  int nvalues = 20000000;
  std::vector<double> sortvec(nvalues);
  for (int ivalue = 0; ivalue < nvalues; ivalue++) {
    sortvec[ivalue] = dist(mt);
  }

  double start_time = omp_get_wtime();

  // Do a Merge Sort
  std::vector<double> auxiliary(nvalues); // temporary storage space for sorting
  mergesort(sortvec.data(), auxiliary.data(), nvalues);

  double walltime = omp_get_wtime() - start_time;

  // Print the final values
  // Because Merge Sort is fast, we generally run with a large enough array that printing every value will take a long time.
  // This loop only prints every thousandth value, but you can adjust this behavior for testing purposes.
  for ( int ivalue = 0; ivalue < nvalues; ivalue += 1000) {
    std::cout << "   Index: " << ivalue << "   Value: " << sortvec[ivalue] << std::endl;
  }

  // Verify that there are no errors in the ordering
  for (int i = 1; i < nvalues; i++) {
    if ( sortvec[i] < sortvec[i-1] ) {
      std::cerr << "ERROR: VALUES " << i-1 << " AND " << i << " ARE MISORDERED." << std::endl;
    }
  }

  std::cout << "Total walltime: " << walltime << std::endl;

}