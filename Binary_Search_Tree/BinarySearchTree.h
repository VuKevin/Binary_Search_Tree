#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "BinarySearchTreeNode.h"

namespace cs20a 
{
	template<class T>
	class BinarySearchTree
	{
	public:
		BinarySearchTree(); // Constructor [Set Root to NULL and Size of 0]
		BinarySearchTree(const BinarySearchTree &original); // Copy Constructor [Perform a deep copy]
		~BinarySearchTree(); // Destructor 

		const BinarySearchTree & operator=(const BinarySearchTree &original); // Destructor + Copy Constructor

		void insert(const T & value);
		void remove(const T & value);

		bool contains(const T & value) const;
		T & retrieve(T & value) const;

		void makeEmpty();
		bool isEmpty() const;

		void inOrder(void(*func)(const T &)) const;

		int getSize() const;

		int numberOfLeafNodes();
		int numberOfLeafNodes(BinarySearchTreeNode<T> *findLeaf);


	private:
		BinarySearchTreeNode<T> *root;
		int size;

		void insert(const T &  value, BinarySearchTreeNode<T>* node);
		void remove(const T &  value, BinarySearchTreeNode<T>* node);

		bool contains(const T&  value, BinarySearchTreeNode<T>* node) const;
		T & retrieve(T & value, BinarySearchTreeNode<T>* node) const;

		void makeEmpty(BinarySearchTreeNode<T>* node);
		inline void deepCopy(const BinarySearchTreeNode<T>* node);

		void inOrder(void(*func)(const T &), BinarySearchTreeNode<T>* node) const;
	};
}
#endif


