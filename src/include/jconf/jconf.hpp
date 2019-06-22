#ifndef JCONF_H
#define JCONF_H

#include <ostream>
#include <string>

#include "nlohmann/json.hpp"
#include <json-schema.hpp>

namespace jconf {

using json_validator = nlohmann::json_schema::json_validator;
using json = nlohmann::json;
using json_pointer = nlohmann::json_pointer<json>;

class Config {

public:
  Config(std::string storage_path, std::string schema_path);
  void load(std::string ext_schema_path="");
  void save();
  void set(const json &property);
  json get(const std::string &key);

  template <typename T>
  void set(const std::string &key, const T &value) {
    json j;

    if (key.rfind('/', 0) == 0) {
      // If the key starts with "/", then it is a path, like "logging/level"
      j[json_pointer(key)] = value;
    } else {
      j[key] = value;
    }

    set(j);
  }

  friend std::ostream &operator<<(std::ostream &os, const Config &c);

private:
  std::string m_storage_path;
  std::string m_schema_path;
  json m_data;
  json m_schema;
  json_validator m_validator;
};
} // namespace jconf

#endif // JCONF_H
