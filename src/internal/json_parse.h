#ifndef JSON_PARSE_H
#define JSON_PARSE_H

#include <iosfwd>
#include <memory>

class json_node;
using s_node = std::shared_ptr<const json_node>;
class json_node_object;
class json_node_array;
class json_node_number;
class json_node_bool;

class json_parse_context {
 public:
  json_parse_context(std::istream &stream);

  bool ok() const;

  char c() const;

  void next();

  void skipWS();

 private:
  std::istream &m_stream;
};

std::string encode_json_string(const std::string &value);

void dump_object(std::ostream &stream, const json_node_object &node);
void dump_array(std::ostream &stream, const json_node_array &node);
void dump_number(std::ostream &stream, const json_node_number &node);
void dump_bool(std::ostream &stream, const json_node_bool &node);
void dump_null(std::ostream &stream);
void dump_any(std::ostream &stream, const json_node &node);

s_node parse_object(json_parse_context &ctx);
s_node parse_array(json_parse_context &ctx);
s_node parse_string(json_parse_context &ctx);
s_node parse_number(json_parse_context &ctx);
s_node parse_bool(json_parse_context &ctx);
s_node parse_null(json_parse_context &ctx);
s_node parse_any(json_parse_context &ctx);

#endif  // JSON_PARSE_H
