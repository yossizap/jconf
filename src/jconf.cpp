#include <fstream>
#include <iomanip>
#include <iostream>
#include <utility>

#include "jconf/jconf.hpp"

namespace jconf {

using json_pointer = nlohmann::json_pointer<json>;
using invalid_iterator = nlohmann::json::invalid_iterator;

Config::Config(std::string storage_path, std::string schema_path)
    : m_storage_path(std::move(storage_path)),
      m_schema_path(std::move(schema_path)) {}

void Config::load() {
    std::ifstream(m_storage_path) >> m_data;
    std::ifstream(m_schema_path) >> m_schema;

    // Fully validate the schema with a temporary validator object
    json_validator init_validator;
    init_validator.set_root_schema(m_schema);
    init_validator.validate(m_data);

    // Remove the 'required' field to avoid insertion runtime issues
    remove(m_schema, "required");

    m_validator.set_root_schema(m_schema);
}

void Config::save() {
    std::ofstream o(m_storage_path);
    o << std::setw(4) << m_data << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Config& c) {
    return os << c.m_data;
}

void Config::set(const json& property) {
    m_validator.validate(property);
    m_data.merge_patch(property);
}

void Config::set(const std::string& key, const json& property) {
    if (key.rfind('/', 0) == 0) {
        // If the key starts with "/", then it is a path, like "logging/level"
        json_pointer jp(key);
        m_data.at(jp) = property;
    } else {
        m_data.at(key) = property;
    }
}

json Config::get(const std::string& key) {
    if (key.compare("/") == 0) {
        return m_data;
    } else if (key.rfind('/', 0) == 0) {
        // If the key starts with "/", then it is a path, like "logging/level"
        json_pointer jp(key);
        return m_data.at(jp);
    } else {
        return m_data.at(key);
    }
}

void Config::remove(json& j, const std::string& key) {
    for (auto it = j.begin(); it != j.end(); ++it) {
        // Keep recursing if the iterator is an array/object to remove nested
        // keys
        if (it->is_structured()) {
            remove(*it, key);
        }

        try {
            if (0 == it.key().compare(key)) {
                j.erase(it);
            }
            // Only json objects have keys, items without values or items with
            // multiple values will throw an exception so we ignore them
        } catch (const invalid_iterator& e) {
        }
    }
}

}  // namespace jconf
