#ifndef NORMALNODE_HPP
# define NORMALNODE_HPP

# include "BaseNode.hpp"
# include <vector>

class NormalNode : public BaseNode
{
private:
	static const size_t _sizeNormal;
public:
	NormalNode();
	virtual ~NormalNode();
private:
	NormalNode(const NormalNode &other);
	NormalNode& operator=(const NormalNode &other);
};

#endif