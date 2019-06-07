#ifndef JCONF_H
#define JCONF_H

#include <ostream>
#include <string>

#include "nlohmann/json.hpp"

namespace jconf {

using json = nlohmann::json;

class Config {

public:
  Config(std::string storage_path, std::string schema_path);
  void load();
  void save();
  void validate();
  json & at(const std::string& key = "");
  friend std::ostream &operator<<(std::ostream &os, const Config &c);

private:
  std::string m_storage_path;
  std::string m_schema_path;
  json m_data;
  json m_schema;
};
} // namespace jconf

#endif // JCONF_H