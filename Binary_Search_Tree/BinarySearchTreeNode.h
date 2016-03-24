#ifndef BINARYSEARCHTREENODE_H
#define BINARYSEARCHTREENODE_H
#include <iostream>

namespace cs20a 
{
	template<class T>
	struct BinarySearchTreeNode
	{
		BinarySearchTreeNode() : value(), left(NULL), right(NULL)
		{}

		BinarySearchTreeNode(const T &t, BinarySearchTreeNode<T> *l = NULL, 
			BinarySearchTreeNode<T> *r = NULL)
			: value(t), left(l), right(r)
		{}

		T value;
		BinarySearchTreeNode<T> *left, *right;
	};
}
#endif