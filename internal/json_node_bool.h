#ifndef JSON_NODE_BOOL_H
#define JSON_NODE_BOOL_H

#include "json_node.h"

class json_node_bool : public json_node {
 public:
  json_node_bool(bool b = false);

  inline bool value() const { return m_value; }

 private:
  bool m_value;
};

#endif  // JSON_NODE_BOOL_H
