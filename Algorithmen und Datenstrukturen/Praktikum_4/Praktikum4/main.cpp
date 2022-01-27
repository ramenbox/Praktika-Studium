#define CATCH_CONFIG_RUNNER
#include "catch.h"

#include <iostream>
#include <omp.h>
#include <random>

#include "sorting.h"
#include "hashtable.h"

#define DEBUG 0

using namespace std;

//benchmark functions
void benchmark_quicksort();
void benchmark_mergesort();
void benchmark_shellsort();
void benchmark_heapsort();


int main(int argc, char** argv) {

  Catch::Session().run();
  std::cin.get();


  //benchmark_quicksort();
  //benchmark_shellsort();
  //benchmark_heapsort();
  //benchmark_mergesort();

  HashTable H(1000);

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> distrib(1000, 1500);

  for (size_t i = 0; i < 200; i++)
  {
      H.insert(distrib(gen));
  }

  cout << "Anzahl der Kollisionen: " << H.getCollisionCount() << endl;

  return 0;
}




//executes benchmark for quicksort
void benchmark_quicksort() {

  //file stream
  ofstream quicksort_measurement;
  quicksort_measurement.open("quicksort.txt", ios::out | ios::app);

  //benchmark parameters / variables
  double dtime;
  int n_start = 1000;
  int n_step = 1000;
  int n_end = 1000000;

  vector<int> V;

  //actual benchmark loop
  for (int n = n_start; n<=n_end; n += n_step) {
	
	//"progress bar"
    if (DEBUG) std::cout << "Running Quicksort with n: " << n << std::endl;

	//generate n random integers
	sorting::randomizeVector(V, n);

	//start measurement
    dtime = omp_get_wtime();
    
	//execute sorting algorithm
    sorting::QuickSort(V,0,V.size()-1);

	//stop time
    dtime = omp_get_wtime() - dtime;

	//write to file
    quicksort_measurement << n << "\t" << setprecision(10) << scientific << dtime << endl;
  }

  //close file handle
  quicksort_measurement.close();
}

//executes benchmark for mergesort
void benchmark_mergesort() {

    //file stream
    ofstream mergesort_measurement;
    mergesort_measurement.open("mergesort.txt", ios::out | ios::app);

    //benchmark parameters / variables
    double dtime;
    int n_start = 1000;
    int n_step = 1000;
    int n_end = 1000000;

    vector<int> V, tmp;

    //actual benchmark loop
    for (int n = n_start; n <= n_end; n += n_step) {

        //"progress bar"
        if (DEBUG) std::cout << "Running Mergesort with n: " << n << std::endl;

        //generate n random integers
        sorting::randomizeVector(V, n);
        tmp.resize(V.size());

        //start measurement
        dtime = omp_get_wtime();

        //execute sorting algorithm
        sorting::MergeSort(V, tmp, 0, V.size() - 1);

        //stop time
        dtime = omp_get_wtime() - dtime;

        //write to file
        mergesort_measurement << n << "\t" << setprecision(10) << scientific << dtime << endl;
    }

    //close file handle
    mergesort_measurement.close();
}

//executes benchmark for shellsort
void benchmark_shellsort() {

    //file stream
    ofstream shellsort_measurement;
    shellsort_measurement.open("shellsort.txt", ios::out | ios::app);

    //benchmark parameters / variables
    double dtime;
    int n_start = 1000;
    int n_step = 1000;
    int n_end = 1000000;

    vector<int> V;

    //actual benchmark loop
    for (int n = n_start; n <= n_end; n += n_step) {

        //"progress bar"
        if (DEBUG) std::cout << "Running Shellsort with n: " << n << std::endl;

        //generate n random integers
        sorting::randomizeVector(V, n);

        //start measurement
        dtime = omp_get_wtime();

        //execute sorting algorithm
        sorting::ShellSort(V, V.size() - 1);

        //stop time
        dtime = omp_get_wtime() - dtime;

        //write to file
        shellsort_measurement << n << "\t" << setprecision(10) << scientific << dtime << endl;
    }

    //close file handle
    shellsort_measurement.close();
}

//executes benchmark for heapsort
void benchmark_heapsort() {

    //file stream
    ofstream heapsort_measurement;
    heapsort_measurement.open("heapsort.txt", ios::out | ios::app);

    //benchmark parameters / variables
    double dtime;
    int n_start = 1000;
    int n_step = 1000;
    int n_end = 1000000;

    vector<int> V;

    //actual benchmark loop
    for (int n = n_start; n <= n_end; n += n_step) {

        //"progress bar"
        if (DEBUG) std::cout << "Running Heapsort with n: " << n << std::endl;

        //generate n random integers
        sorting::randomizeVector(V, n);

        //start measurement
        dtime = omp_get_wtime();

        //execute sorting algorithm
        sorting::HeapSort(V, V.size() - 1);

        //stop time
        dtime = omp_get_wtime() - dtime;

        //write to file
        heapsort_measurement << n << "\t" << setprecision(10) << scientific << dtime << endl;
    }

    //close file handle
    heapsort_measurement.close();
}

