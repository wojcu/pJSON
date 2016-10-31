#ifndef JSON_H
#define JSON_H

#include <memory>
#include <string>

class json_node;
using s_node = std::shared_ptr<const json_node>;

namespace persistent {
class json {
 public:
  json() = default;
  json(std::string value);
  json(const char *cstr);
  json(bool value);
  json(double value);
  json(int value);

  static json make_array();
  static json make_object();
  static json make_null();

  inline bool empty() const { return !m_node; }

  bool is_object() const;
  bool is_string() const;
  bool is_number() const;
  bool is_array() const;
  bool is_bool() const;
  bool is_null() const;

  void to_object();
  void to_array();
  void to_null();

  void clear();

  json &operator=(std::string value);
  json &operator=(int value);
  json &operator=(double value);
  json &operator=(bool value);
  json &operator=(const char *cstr);

  void insert(std::string key, json value);
  void erase(const std::string &key);
  json at(const std::string &key) const;
  json at(size_t index) const;
  bool contains(const std::string &key) const;
  size_t size() const;
  void push_back(json value);
  void pop_back();
  bool is_real() const;
  double real() const;
  int integer() const;
  bool boolean() const;
  const std::string &string() const;

 private:
  friend std::ostream &operator<<(std::ostream &stream, const json &obj);
  friend std::istream &operator>>(std::istream &stream, json &obj);

  s_node m_node;
};

}  // persistent
#endif  // JSON_H
