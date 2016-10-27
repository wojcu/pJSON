#ifndef JSON_NODE_ARRAY_H
#define JSON_NODE_ARRAY_H

#include "json_node.h"
#include "map.h"

class json_node_array : public json_node {
 public:
  using map_t = persistent::map<size_t, const s_node>;

  json_node_array(map_t values = map_t());

  inline const map_t &values() const { return m_values; }

 private:
  const map_t m_values;
};

#endif  // JSON_NODE_ARRAY_H
