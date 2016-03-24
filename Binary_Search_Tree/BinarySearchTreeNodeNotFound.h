#ifndef BINARYSEARCHTREENODENOTFOUND_H
#define BINARYSEARCHTREENODENOTFOUND_H

#include <stdexcept>

namespace cs20a 
{
	class BinarySearchTreeNodeNotFound : public std::logic_error 
	{
	public:
		BinarySearchTreeNodeNotFound();
	};
}
#endif