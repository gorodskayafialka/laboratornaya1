using namespace std;
#include <iostream>
#include <iomanip>
#include "Map.h"

int main()
{
	map<int, float> m;
	m.insert(7, 0.312);
	m.insert(6, 10);
	m.insert(5, 4);
	m.insert(4, 23);
	m.insert(3, 11);
	m.insert(2, 11);
	m.insert(1, 18);
	m.insert(0, 18);
	m.remove(1);
	m.get_keys();
	m.get_values();
	m.print();
}

