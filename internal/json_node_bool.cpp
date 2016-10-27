#include "json_node_bool.h"

json_node_bool::json_node_bool(bool b)
    : json_node(json_type_bool), m_value(b) {}
