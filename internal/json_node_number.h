#ifndef JSON_NODE_NUMBER_H
#define JSON_NODE_NUMBER_H

#include "json_node.h"

class json_node_number : public json_node {
 public:
  json_node_number(double val);

  json_node_number(int val);

  inline bool is_double() const { return m_is_double; }

  inline double get_double() const { return m_double; }

  inline int get_int() const { return m_int; }

 private:
  const bool m_is_double;
  const double m_double;
  const int m_int;
};

#endif  // JSON_NODE_NUMBER_H
