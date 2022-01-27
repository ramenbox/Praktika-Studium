#include "sorting.h"

namespace sorting {

	//************
	// QuickSort *
	//************      
	void QuickSort(vector<int> &arr, int left, int right) {
		
		//***************************
		// implement quicksort here *
		//************ **************
		if (left < right)
		{
			// Pivotelement
			int q = Partition(arr, left, right);
			// Linke Hälfte
			QuickSort(arr, left, q - 1);
			// Rechte Hälfte
			QuickSort(arr, q + 1, right);
		}
	}

	int Partition(vector<int>& arr, int left, int right)
	{
		int x = arr[right]; // Letztes Element in der Teilmenge
		int i = left - 1; // Erstes Element in der Teilmenge

		// Teilmenge durchgehen und tauschen
		for(int j = left; j < right; j++)
		{
			// Alle kleiner als x auf der linken Seite
			if (arr[j] <= x)
			{
				i++;
				swap(arr[i], arr[j]);
			}
		}
		swap(arr[i+1], arr[right]);
		return i + 1;
	}

	//************
	// MergeSort *
	//************

	//***************************
	// implement mergesort here *
	//***************************


	void Merge(vector<int> &a, vector<int> &b, int low, int pivot, int high) {
		int leftEnd = pivot - 1;
		int tmpPos = low;
		int n = high - low + 1;

		while (low <= leftEnd && pivot <= high) // Mische 2 Teilmengen
		{
			if (a[low] <= a[pivot])
			{
				b[tmpPos] = a[low];
				tmpPos++;
				low++;
			}
			else
			{
				b[tmpPos] = a[pivot];
				tmpPos++;
				pivot++;
			}
		}

		// Kopiere den Rest der 1. Teilmenge
		while (low <= leftEnd)
		{
			b[tmpPos] = a[low];
			tmpPos++;
			low++;
		}

		// Kopiere den Rest der 2. Teilmenge
		while (pivot <= high)
		{
			b[tmpPos] = a[pivot];
			tmpPos++;
			pivot++;
		}

		// Kopiere temp. Feld b in a,
		// ausgehend von der letzten Position der Teilmenge
		for (int i = 0; i < n; i++)
		{
			a[high] = b[high];
			high--;
		}
	}

	void MergeSort(vector<int> &a, vector<int> &b, int low, int high) {
		if (low < high)
		{
			// Bekomme die Mitte - Divide
			int pivot = (low + high) / 2;
			// Conquer
			// Linke Teilmenge
			MergeSort(a, b, low, pivot);
			// Rechte Teilmenge
			MergeSort(a, b, pivot + 1, high);
			// Verschmelze die Teilmengen zueinander - Combine
			Merge(a, b, low, pivot + 1, high);
		}
	}



	//************
	// Heapsort  *
	//************

	void HeapSort(vector<int> &a, int n) {


		//***************************
		// implement heapsort here *
		//***************************

		// Baue Heap auf
		for (int i = n / 2; i >= 0; i--)
		{
			PercDown(a, i, n);
		}
		
		// Sortieren
		for (int j = n - 1; j > 0; j--)
		{
			swap(a[0], a[j]);
			PercDown(a, 0, j);
		}
	}

	void PercDown(vector<int>& a, int p, int n)
	{
		
		while (leftChild(p) < n)
		{
			int child = leftChild(p);

			if (child < (n - 1) && (a[child] < a[child + 1]))
			{
				child++;
			}
			if (!(a[p] < a[child])) break;
			
			swap(a[p], a[child]);	
			p = child;
		}
		
	}

	int leftChild(int i)
	{
		return i * 2 + 1;
	}


	//************
	// Shellsort *
	//************
	void ShellSort(vector<int>& a, int n)
	{
		//***************************
		// implement shellsort here *
		//***************************

		int h = 1;
		while (h < n)
		{
			h = 2 * h + 1;
		}

		while (h >= 1)
		{
			for (int i = h; i < n; i++)
			{
				for (int j = i; j >= h && a[j] < a[j - h]; j -= h)
				{
					swap(a[j], a[j - h]);
				}
			}
			h = h / 2;
		}
	}


  void randomizeVector(vector<int> &array, int n) {
    array.resize(n);

    for(unsigned int i=0;i<array.size();i++)
      array[i]=rand() % 1000000;
  }


}





