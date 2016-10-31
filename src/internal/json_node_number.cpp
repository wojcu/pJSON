#include "json_node_number.h"

json_node_number::json_node_number(double val)
    : json_node(json_type_number), m_is_double(true), m_double(val), m_int(0) {}

json_node_number::json_node_number(int val)
    : json_node(json_type_number),
      m_is_double(false),
      m_double(0.0),
      m_int(val) {}
