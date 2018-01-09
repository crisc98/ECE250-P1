#include <iostream>
//using namespace std;

#include "Double_sentinel_list.h"

int amain() {
	Double_sentinel_list<int> list;

	std::cout << "Size:  " << list.size() << " ( = 0 )" << std::endl;
	std::cout << "Empty:  " << list.empty() << " ( = 1 )" << std::endl;

	for (int i=0; i<5; i++) {
		list.push_front(i);
	}
	// start with 1, then try 2, and then 3, etc.

    std::cout << list << std::endl;


	return 0;
}
