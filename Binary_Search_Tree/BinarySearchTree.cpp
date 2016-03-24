#include <iostream>

#include "BinarySearchTree.h"
#include "BinarySearchTreeNode.h"
#include "BinarySearchTreeNodeExists.h"
#include "BinarySearchTreeNodeNotFound.h"

namespace cs20a
{	
	template<class T>
	BinarySearchTree<T>::BinarySearchTree() : root(NULL), size(0)
	{}

	template<class T>
	BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree &original) : root(NULL), size(0)
	{
		deepCopy(original.root);
	}

	template<class T>
	const BinarySearchTree<T> & BinarySearchTree<T>::operator=(const BinarySearchTree &original)
	{
		if (this == &original)
			return *this;

		makeEmpty();
		deepCopy(original.root);

		return *this;
	}

	template<class T>
	BinarySearchTree<T>::~BinarySearchTree()
	{
		makeEmpty();
	}

	template<class T>
	inline void BinarySearchTree<T>::deepCopy(const BinarySearchTreeNode<T>* node)
	{
		if (node != NULL)
			insert(node->value);

		if (node->left != NULL)
			deepCopy(node->left);

		if (node->right != NULL)
			deepCopy(node->right);
	}

	template<class T>
	void BinarySearchTree<T>::makeEmpty()
	{
		makeEmpty(root);
		root = NULL;
	}

	template<class T>
	void BinarySearchTree<T>::makeEmpty(BinarySearchTreeNode<T>* node)
	{
		if (node != NULL) 
		{
			if (node->left != NULL)
				makeEmpty(node->left);

			if (node->right != NULL)
				makeEmpty(node->right);

			delete node;
			node = NULL;

			size--;
		}
	}

	template<class T>
	void BinarySearchTree<T>::insert(const T &value) // Insert a value 
	{
		if (root == NULL)
		{
			root = new BinarySearchTreeNode<T>(value, NULL, NULL);
			size++;
		}
		else
		{
			insert(value, root);
		}
	}

	template<class T>
	void BinarySearchTree<T>::insert(const T &value, BinarySearchTreeNode<T>* node) 
	{
		if (value < node->value)
		{
			if (node->left == NULL)
			{
				node->left = new BinarySearchTreeNode<T>(value, NULL, NULL);
				size++;
			}
			else
			{
				insert(value, node->left);
			}
		}
		else
			if (value > node->value)
			{
				if (node->right == NULL)
				{
					node->right = new BinarySearchTreeNode<T>( value, NULL, NULL);
					size++;
				}
				else
				{
					insert(value, node->right);
				}
			}
			else
			{
				throw BinarySearchTreeNodeExists();
			}
	}

	template<class T>
	void BinarySearchTree<T>::remove(const T &value)
	{		
		remove(value, root);
	}

	template<class T>
	void BinarySearchTree<T>::remove(const T &value, BinarySearchTreeNode<T>* node)
	{
		// ALGORITHM:
		//	Find the node to be removed.
		//	? If it does not exist, throw a BinarySearchTreeNodeNotFound exception and stop.
		//	? If it does exist, determine how many children it has.There are three cases :
		//	1. No children : set its parent’s child pointer to NULL and then delete it.
		//	2. One child : set its parent’s child pointer to its one child and then delete it.
		//	3. Two children : Find the node with the largest element in its left subtree.Replace the
		//	element in the node to be deleted with the largest element in its left subtree.Delete the
		//	node containing the largest element in the left subtree.

		BinarySearchTreeNode<T> *find = node;
		BinarySearchTreeNode<T>* parent = NULL;
		while (find->value != value) // Find the node to be removed
		{
			parent = find; // Keep tabs on the parent for later use for deletion (stay one node before the node of interest)
			if (find->value > value) // If the node's value is greater than parameter value
				find = find->left;
			else  // find->value < value
				find = find->right;
		}
		if (find == NULL)
			throw BinarySearchTreeNodeNotFound();

		// Check to ensure find hold's our value of interest before we begin deletion
		if (find->value == value)
		{
			// Determine how many children it has [3 CASES]

			if (find->left == NULL && find->right == NULL) // CASE 1: No children
			{
				// Set it's parent's child pointer to NULL
				if (parent->right == find)
				{
					parent->right = NULL;
					delete find;
					find = NULL;
					size--;
				}
				if (parent->left == find)
				{
					parent->left = NULL;
					delete find;
					find = NULL;
					size--;
				}
			}

			else if ((find->left == NULL && find->right != NULL) || (find->right == NULL && find->left != NULL)) // CASE 2: 1 Child
			{
				if (find->left == NULL) // Subcase: Only a right child
				{
					if (parent->right == find)
						parent->right = find->right;
					else // parent->left == find (parent's left child pointer points to the same thing find points to)
						parent->left = find->right;
					delete find;
					find = NULL;
					size--;

				}
				else if (find->right == NULL) // Subcase: Only a left child
				{
					if (parent->left == find)
						parent->left = find->left;
					else // parent->right == find
						parent->right = find->left;
					delete find;
					find = NULL;
					size--;

				}
			}

			else if (find->left != NULL && find->right != NULL) // CASE 3: 2 Children
			{
				BinarySearchTreeNode<T> *findGreatest = find;
				BinarySearchTreeNode<T> *parent = findGreatest;
				// Subcase: Find the greatest element in the left subtree
				findGreatest = findGreatest->left; // Go to the root node of the left subtree
				// Follow the right pointers as far as we go until we find a NULL right pointers
				while (findGreatest->right != NULL)
				{
					parent = findGreatest; // keep tabs on parent of findGreatest
					findGreatest = findGreatest->right;
				} // findGreatest now holds the greatest element in the left subtree
				// Replace the element in the node we WANT to DELETE, with the greatest element in the left subtree
				find->value = findGreatest->value;

				// *****Remove that node****** //
				if (findGreatest->left != NULL) // If it happens to have a left child 
				{
					BinarySearchTreeNode<T>* leftNode = findGreatest->left;
					remove(findGreatest->left->value, leftNode);
				}
				else
				{
					if (parent->left == findGreatest)
						parent->left = NULL;
					else // parent->right == findGreatest
						parent->right = NULL;
					delete findGreatest;
					findGreatest = NULL;
					size--;
				}
				
			}
		}
	}

	template<class T>
	T & BinarySearchTree<T>::retrieve(T &value) const
	{
		return retrieve(value, root);
	}

	template<class T>
	T & BinarySearchTree<T>::retrieve(T &value, BinarySearchTreeNode<T>* node) const
	{
		if (node == NULL)
			throw BinarySearchTreeNodeNotFound();
		else if (value < node->value)
			return retrieve(value, node->left);
		else if (value > node->value)
			return retrieve(value, node->right);
		else
			return node->value;
	}

	template<class T>
	bool BinarySearchTree<T>::contains(const T &value) const
	{
		if (root == NULL)
			return false;
		else
			return contains(value, root);
	}

	template<class T>
	bool BinarySearchTree<T>::contains(const T &value, BinarySearchTreeNode<T> *node) const {
		if (node == NULL)
			return false;
		else if (value < node->value)
			return contains(value, node->left);
		else if (value > node->value)
			return contains(value, node->right);
		else // value == node->value
			return true;
	}

	template<class T>
	void BinarySearchTree<T>::inOrder(void(*func)(const T &)) const
	{
		inOrder(func, root);
	}

	template<class T>
	void BinarySearchTree<T>::inOrder(void(*func)(const T &), BinarySearchTreeNode<T>* node) const
	{
		if (node != NULL)
		{
			inOrder(func, node->left);
			if (func != NULL)
				func(node->value);
			inOrder(func, node->right);
		}
	}

	template<class T>
	bool BinarySearchTree<T>::isEmpty() const
	{
		return root == NULL;
	}

	template<class T>
	int BinarySearchTree<T>::getSize() const
	{
		return size;
	}

	template<class T>
	int BinarySearchTree<T>::numberOfLeafNodes()
	{
		return numberOfLeafNodes(root);
	}

	template<class T>
	int BinarySearchTree<T>::numberOfLeafNodes(BinarySearchTreeNode<T> *findLeaf)
	{
		if (findLeaf == NULL)
			return 0;
		if (findLeaf->right == NULL && findLeaf->left == NULL)
			return 1;
		else
			return numberOfLeafNodes(findLeaf->right) + numberOfLeafNodes(findLeaf->left);
	}

}