#ifndef JSON_NODE_OBJECT_H
#define JSON_NODE_OBJECT_H

#include "json_node.h"
#include "map.h"

class json_node_object : public json_node {
 public:
  using map_t = persistent::map<std::string, const s_node>;

  json_node_object(map_t values = map_t());

  inline const map_t &values() const { return m_values; }

 private:
  const map_t m_values;
};

#endif  // JSON_NODE_OBJECT_H
