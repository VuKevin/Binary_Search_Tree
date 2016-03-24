#include <iostream>
#include <stdlib.h>
#include <string>
#include "BinarySearchTree.h"
#include "BinarySearchTree.cpp"

using namespace std;
using namespace cs20a;

void printWordLocation(const int & i);

int main()
{
	srand(77);	// Initialize random seed

	int first = 0;

	BinarySearchTree<int> bt;
	for (int i=0; i < 100; i++)
	{
		int num = rand() % 100 + 1;

		if (i==0) first = num;

		if (!bt.contains(num))
			bt.insert(num);
	}

	if (bt.contains(first))
	{			
		cout << "Before Delete" << endl;
		bt.inOrder(printWordLocation);

		cout << "remove " << first << endl;
		bt.remove(first);

		cout << "After Delete" << endl;
		bt.inOrder(printWordLocation);

		cout << endl << endl;
	}

	for (int i=0; i < 20; i++)
	{
		int num = rand() % 100 + 1;

		if (bt.contains(num))
		{			
			cout << "Before Delete" << endl;
			bt.inOrder(printWordLocation);

			cout << "remove " << num << endl;
			int loc = bt.retrieve(num);
			bt.remove(num);

			cout << "After Delete" << endl;
			bt.inOrder(printWordLocation);

			cout << endl << endl;
		}
	}

	cerr << "Done." << endl;

	int numberOfLeaves = bt.numberOfLeafNodes();
	cout << numberOfLeaves;
	return 0;
}

void printWordLocation(const int & i)
{
	cout << i << " ";
}
