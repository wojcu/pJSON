#ifndef JSON_NODE_H
#define JSON_NODE_H

#include <memory>
#include "json_type.h"

class json_node {
 public:
  inline json_type type() const { return m_type; }

 protected:
  using s_node = std::shared_ptr<const json_node>;

  json_node(json_type type);

 private:
  const json_type m_type;
};

#endif  // JSON_NODE_H
