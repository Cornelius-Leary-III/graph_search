#include "BaseNode.h"

BaseNode::BaseNode() : mName()
{
}

BaseNode::BaseNode(const std::string& name) : mName(name)
{
}

BaseNode::BaseNode(const BaseNode& node_to_copy)
{
   if (this != &node_to_copy)
   {
      this->mName = node_to_copy.mName;
   }
}

BaseNode::~BaseNode()
{
}

BaseNode& BaseNode::operator=(const BaseNode& node_to_copy)
{
   if (this != &node_to_copy)
   {
      this->mName = node_to_copy.mName;
   }

   return *this;
}

bool operator==(const BaseNode& lhs, const BaseNode& rhs)
{
   return (lhs.mName == rhs.mName);
}

bool operator!=(const BaseNode& lhs, const BaseNode& rhs)
{
   return !(lhs.mName == rhs.mName);
}

bool operator==(BaseNode& lhs, BaseNode& rhs)
{
   return (lhs.mName == rhs.mName);
}

bool operator!=(BaseNode& lhs, BaseNode& rhs)
{
   return !(lhs.mName == rhs.mName);
}
