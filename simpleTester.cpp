#include <iostream>
//using namespace std;

#include "Double_sentinel_list.h"
void factory() {
	Double_sentinel_list<int> list;
	list.push_back(3);
	list.push_back(4);
	list.push_back(12);
	std::cout << list;
    Double_sentinel_list<int> list2(std::move(list));
    std::cout << list2;

}

int main() {
	factory();


	return 0;
}
