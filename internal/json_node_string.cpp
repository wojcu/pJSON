#include "json_node_string.h"

json_node_string::json_node_string(std::string value)
    : json_node(json_type_string), m_value(std::move(value)) {}
