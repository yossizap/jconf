#include <fstream>
#include <iomanip>
#include <utility>

#include "jconf/jconf.hpp"

namespace jconf {

using json_pointer = nlohmann::json_pointer<json>;

Config::Config(std::string storage_path, std::string schema_path)
    : m_storage_path(std::move(storage_path)),
      m_schema_path(std::move(schema_path)) {}

void Config::load() {
  std::ifstream i(m_storage_path);
  i >> m_data;

  std::ifstream j(m_schema_path);
  j >> m_schema;

  m_validator.set_root_schema(m_schema);
  m_validator.validate(m_data);
}

void Config::save() {
  std::ofstream o(m_storage_path);
  o << std::setw(4) << m_data << std::endl;
}

std::ostream &operator<<(std::ostream &os, const Config &c) {
  return os << c.m_data;
}

void Config::set_property(const json &property) {
  m_validator.validate(property); 
  m_data.merge_patch(property);
}

json Config::get_property(const std::string &key) {
  if (key.rfind('/', 0) == 0) {
    // If the key starts with "/", then it is a path, like "logging/level"
    json_pointer jp(key);
    return m_data.at(jp);
  } else {
    return m_data.at(key);
  }
}
} // namespace jconf
