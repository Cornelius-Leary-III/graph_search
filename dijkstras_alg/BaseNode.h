#ifndef DIJKSTRAS_ALG__BASE_NODE_H
#define DIJKSTRAS_ALG__BASE_NODE_H

#include <string>

struct BaseNode
{
   std::string mName;

   BaseNode();
   explicit BaseNode(const std::string& name);
   explicit BaseNode(const BaseNode& node_to_copy);
   virtual ~BaseNode();

   BaseNode& operator=(const BaseNode& node_to_copy);
};

bool operator==(const BaseNode& lhs, const BaseNode& rhs);
bool operator!=(const BaseNode& lhs, const BaseNode& rhs);

bool operator==(BaseNode& lhs, BaseNode& rhs);
bool operator!=(BaseNode& lhs, BaseNode& rhs);

#endif // DIJKSTRAS_ALG__BASE_NODE_H
