#ifndef JSON_NODE_STRING_H
#define JSON_NODE_STRING_H

#include <string>
#include "json_node.h"

class json_node_string : public json_node {
 public:
  json_node_string(std::string value = "");

  inline const std::string &value() const { return m_value; }

 private:
  const std::string m_value;
};

#endif  // JSON_NODE_STRING_H
