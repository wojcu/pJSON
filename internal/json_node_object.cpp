#include "json_node_object.h"

json_node_object::json_node_object(json_node_object::map_t values)
    : json_node(json_type_object), m_values(std::move(values)) {}
