if(JCONF_USE_EXTERNAL_JSON)
  find_package(nlohmann_json 3.6.1 REQUIRED)
else()
  set(JSON_BuildTests OFF CACHE INTERNAL "")
  add_subdirectory(json)
endif()

# For some stupid reason, json-schema-validator invents its own interface
# target for nlohmann_json. I basically tricking it to use the original one.
add_library(json-hpp ALIAS nlohmann_json)
add_subdirectory(json-schema-validator)