#include "json_node_array.h"

json_node_array::json_node_array(json_node_array::map_t values)
    : json_node(json_type_array), m_values(std::move(values)) {}
