#include "json.h"

#include <istream>
#include <ostream>

#include "json_node.h"
#include "json_node_array.h"
#include "json_node_bool.h"
#include "json_node_null.h"
#include "json_node_number.h"
#include "json_node_object.h"
#include "json_node_string.h"
#include "json_parse.h"

namespace persistent {

json::json(std::string value) { *this = value; }

json::json(const char *cstr) : json(std::string(cstr)) {}

json::json(bool value) { *this = value; }

json::json(double value) { *this = value; }

json::json(int value) { *this = value; }

json json::make_array() {
  json j;
  j.to_array();
  return j;
}

json json::make_object() {
  json j;
  j.to_object();
  return j;
}

json json::make_null() {
  json j;
  j.to_null();
  return j;
}

bool json::is_object() const {
  return !empty() && m_node->type() == json_type_object;
}

bool json::is_string() const {
  return !empty() && m_node->type() == json_type_string;
}

bool json::is_number() const {
  return !empty() && m_node->type() == json_type_number;
}

bool json::is_array() const {
  return !empty() && m_node->type() == json_type_array;
}

bool json::is_bool() const {
  return !empty() && m_node->type() == json_type_bool;
}

bool json::is_null() const {
  return !empty() && m_node->type() == json_type_null;
}

void json::to_object() { m_node = s_node(new json_node_object); }

void json::to_array() { m_node = s_node(new json_node_array); }

void json::to_null() { m_node = s_node(new json_node_null); }

void json::clear() { m_node = nullptr; }

json &json::operator=(const char *cstr) {
  *this = std::string(cstr);
  return *this;
}

void json::insert(std::string key, json value) {
  json_node_object::map_t values;
  if (is_object()) {
    values = std::static_pointer_cast<const json_node_object>(m_node)->values();
  }
  values.insert(std::move(key), std::move(value.m_node));
  m_node = s_node(new json_node_object(std::move(values)));
}

json json::at(const std::string &key) const {
  if (!is_object()) {
    return json();
  }
  const json_node_object::map_t &m =
      std::static_pointer_cast<const json_node_object>(m_node)->values();
  if (!m.contains(key)) {
    return json();
  }
  json result;
  result.m_node = m.at(key).second;
  return result;
}

bool json::contains(const std::string &key) const {
  if (!is_object()) {
    return false;
  }
  return std::static_pointer_cast<const json_node_object>(m_node)
      ->values()
      .contains(key);
}

void json::erase(const std::string &key) {
  json_node_object::map_t values;
  if (is_object()) {
    values = std::static_pointer_cast<const json_node_object>(m_node)->values();
  }
  values.erase(key);
  m_node = s_node(new json_node_object(std::move(values)));
}

const std::string &json::string() const {
  return std::static_pointer_cast<const json_node_string>(m_node)->value();
}

bool json::is_real() const {
  return is_number() &&
         std::static_pointer_cast<const json_node_number>(m_node)->is_double();
}

double json::real() const {
  return std::static_pointer_cast<const json_node_number>(m_node)->get_double();
}

int json::integer() const {
  return std::static_pointer_cast<const json_node_number>(m_node)->get_int();
}

void json::push_back(json value) {
  json_node_array::map_t values;
  if (is_array()) {
    values = std::static_pointer_cast<const json_node_array>(m_node)->values();
  }
  values.insert(values.size(), std::move(value.m_node));
  m_node = s_node(new json_node_array(std::move(values)));
}

size_t json::size() const {
  if (is_array()) {
    return std::static_pointer_cast<const json_node_array>(m_node)
        ->values()
        .size();
  }
  if (is_object()) {
    return std::static_pointer_cast<const json_node_object>(m_node)
        ->values()
        .size();
  }
  return 0;
}

json json::at(size_t index) const {
  if (is_array()) {
    const json_node_array::map_t &m =
        std::static_pointer_cast<const json_node_array>(m_node)->values();
    if (!m.contains(index)) {
      return json();
    }
    json result;
    result.m_node = m.at(index).second;
    return result;
  }
  if (is_object()) {
    const json_node_object::map_t &m =
        std::static_pointer_cast<const json_node_object>(m_node)->values();
    if (m.size() <= index) {
      return json();
    }
    json result;
    result.m_node = m.nth(index).second;
    return result;
  }
  return nullptr;
}

void json::pop_back() {
  json_node_array::map_t values;
  if (is_array()) {
    values = std::static_pointer_cast<const json_node_array>(m_node)->values();
  }
  if (values.size() != 0) {
    values.erase(values.size() - 1);
  }
  m_node = s_node(new json_node_array(std::move(values)));
}

bool json::boolean() const {
  return std::static_pointer_cast<const json_node_bool>(m_node)->value();
}

std::istream &operator>>(std::istream &stream, json &obj) {
  json_parse_context ctx(stream);
  obj.m_node = parse_any(ctx);
  return stream;
}

std::ostream &operator<<(std::ostream &stream, const json &obj) {
  if (!obj.empty()) {
    dump_any(stream, *obj.m_node);
  }
  return stream;
}

json &json::operator=(bool value) {
  m_node = s_node(new json_node_bool(value));
  return *this;
}

json &json::operator=(double value) {
  m_node = s_node(new json_node_number(value));
  return *this;
}

json &json::operator=(int value) {
  m_node = s_node(new json_node_number(value));
  return *this;
}

json &json::operator=(std::string value) {
  m_node = s_node(new json_node_string(std::move(value)));
  return *this;
}

}  // namespace persistent
