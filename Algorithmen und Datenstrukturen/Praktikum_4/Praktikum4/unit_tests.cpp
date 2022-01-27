#include <vector>
#include "catch.h"
#include "sorting.h"
#include "hashtable.h"

std::vector<int> V{98, 44, 30, 22, 64, 63, 11, 23, 8, 18};

TEST_CASE("Quicksort", "[QUICKSORT]") {

  SECTION("sorting 10 elements - simple") {
  
    std::vector<int> a(V);
	sorting::QuickSort(a,0,a.size()-1);
    
    REQUIRE(a.at(0) == 8);
    REQUIRE(a.at(1) == 11);
    REQUIRE(a.at(2) == 18);
    REQUIRE(a.at(3) == 22);
    REQUIRE(a.at(4) == 23);
    REQUIRE(a.at(5) == 30);
    REQUIRE(a.at(6) == 44);
    REQUIRE(a.at(7) == 63);
    REQUIRE(a.at(8) == 64);
    REQUIRE(a.at(9) == 98);
  }
}


TEST_CASE("ShellSort", "[SHELLSORT]") {


  SECTION("sorting 10 elements - simple") {

    std::vector<int> b(V);
	sorting::ShellSort(b,b.size());

    REQUIRE(b.at(0) == 8);
    REQUIRE(b.at(1) == 11);
    REQUIRE(b.at(2) == 18);
    REQUIRE(b.at(3) == 22);
    REQUIRE(b.at(4) == 23);
    REQUIRE(b.at(5) == 30);
    REQUIRE(b.at(6) == 44);
    REQUIRE(b.at(7) == 63);
    REQUIRE(b.at(8) == 64);
    REQUIRE(b.at(9) == 98);
  }
}


TEST_CASE("HeapSort", "[HEAPSORT]") {

  SECTION("sorting 10 elements - simple") {
    std::vector<int> c(V);
	sorting::HeapSort(c,c.size());

    REQUIRE(c.at(0) == 8);
    REQUIRE(c.at(1) == 11);
    REQUIRE(c.at(2) == 18);
    REQUIRE(c.at(3) == 22);
    REQUIRE(c.at(4) == 23);
    REQUIRE(c.at(5) == 30);
    REQUIRE(c.at(6) == 44);
    REQUIRE(c.at(7) == 63);
    REQUIRE(c.at(8) == 64);
    REQUIRE(c.at(9) == 98);
  }
}


TEST_CASE("MergeSort", "[MERGESORT]") {



  SECTION("sorting 10 elements - simple") {
  
    std::vector<int> d(V);
    std::vector<int> tmp;
    tmp.resize(d.size());

	sorting::MergeSort(d,tmp,0,d.size()-1);

	REQUIRE(d.at(0) == 8);
	REQUIRE(d.at(1) == 11);
	REQUIRE(d.at(2) == 18);
	REQUIRE(d.at(3) == 22);
	REQUIRE(d.at(4) == 23);
	REQUIRE(d.at(5) == 30);
	REQUIRE(d.at(6) == 44);
	REQUIRE(d.at(7) == 63);
	REQUIRE(d.at(8) == 64);
	REQUIRE(d.at(9) == 98);
  }

  
}


TEST_CASE("HashTable", "[HASHTABLE]") {

	SECTION("Hashing 10 elements - Size: 20") {

		HashTable H(20);

		for (unsigned int i = 0; i < V.size(); i++)
		{
			H.insert(V.at(i));
		}

		if (H.getSize() > 0) {
			REQUIRE(H.at(0) == -1);
			REQUIRE(H.at(1) == -1);
			REQUIRE(H.at(2) == 22);
			REQUIRE(H.at(3) == 63);
			REQUIRE(H.at(4) == 44);
			REQUIRE(H.at(5) == 64);
			REQUIRE(H.at(6) == -1);
			REQUIRE(H.at(7) == 23);
			REQUIRE(H.at(8) == 8);
			REQUIRE(H.at(9) == -1);
			REQUIRE(H.at(10) == 30);
			REQUIRE(H.at(11) == 11);
			REQUIRE(H.at(12) == -1);
			REQUIRE(H.at(13) == -1);
			REQUIRE(H.at(14) == -1);
			REQUIRE(H.at(15) == -1);
			REQUIRE(H.at(16) == -1);
			REQUIRE(H.at(17) == -1);
			REQUIRE(H.at(18) == 98);
			REQUIRE(H.at(19) == 18);
		}

		REQUIRE(H.getCollisionCount() == 4);
	}


	SECTION("Hashing 10 elements - Size: 50") {

		HashTable H(50);

		for (unsigned int i = 0; i < V.size(); i++)
		{
			H.insert(V.at(i));
		}

		for (int i = 0; i < H.getSize(); i++) {

			if (i == 8)
				REQUIRE(H.at(i) == 8);

			else if (i == 11)
				REQUIRE(H.at(i) == 11);
			
			else if (i == 13)
				REQUIRE(H.at(i) == 63);

			else if (i == 14)
				REQUIRE(H.at(i) == 64);

			else if (i == 18)
				REQUIRE(H.at(i) == 18);

			else if (i == 22)
				REQUIRE(H.at(i) == 22);

			else if (i == 23)
				REQUIRE(H.at(i) == 23);

			else if (i == 30)
				REQUIRE(H.at(i) == 30);

			else if (i == 44)
				REQUIRE(H.at(i) == 44);

			else if (i == 48)
				REQUIRE(H.at(i) == 98);

			else
				REQUIRE(H.at(i) == -1);
		}

		REQUIRE(H.getCollisionCount() == 0);
	}

}
