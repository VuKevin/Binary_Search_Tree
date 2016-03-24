#ifndef BINARYSEARCHTREENODEEXISTS_H
#define BINARYSEARCHTREENODEEXISTS_H

#include <stdexcept>

namespace cs20a 
{
	class BinarySearchTreeNodeExists : public std::logic_error {
	public:
		BinarySearchTreeNodeExists();
	};
}
#endif