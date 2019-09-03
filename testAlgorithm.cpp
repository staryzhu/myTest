#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int print_vector(int value)
{
	cout << value << " ";
	return 0;
}

#define MAX_LENGTH 10

int maindebug(int argc, char argv[])
{
	vector<int> vc;
	for (int i = 0; i < MAX_LENGTH; i++)
	{
		vc.push_back(rand() % (10 * MAX_LENGTH));
	}
	for_each(vc.begin(), vc.end(), print_vector);
	cout << endl;

	make_heap(vc.begin(), vc.end());
	for_each(vc.begin(), vc.end(), print_vector);
	cout << endl;

	sort_heap(vc.begin(), vc.end());
	for_each(vc.begin(), vc.end(), print_vector);
	cout << endl;

	return 0;
}