# JConf

[![Build Status](https://api.travis-ci.org/yossizap/jconf.svg?branch=master)](https://api.travis-ci.org/yossizap/jconf)

JConf library provides a way to manage Property Tree that has a schema to
validate against. The property can be serialized and deserialized to JSON and
some of its binary derivatives, such as BSON, CBOR, MessagePack, and UBJSON.

It is very similar in concept and usage to Boost's `PropertyTree`, but the main
difference is that JConf has JSON Schema support for data validation.

## Usage
```cpp
jconf::Config config("config.json", "schema.json");
config.load();

// Retrieve a key
std::cout << config.get("some_key");
// Even works with nested properties(converted to a JSON pointer)
std::cout << config.get("/parent/child");

// Set an integer using nlohmann's json object
config.set({{"some_integer", 1337}});
config.set({{"some_integer", "string"}}); // Will raise an exception

// Set nested properties
// NOTE: Refer to the documentation of the `JSON framework` in `See also`
// for syntax documentation
config.set(R"({
                "multiple_values": {
                  "some_integer": 100,
                  "some_boolean": true
                }
              })"_json);

// Set parameters using a path
config.set("logging/level", "info");
config.set("queue/tx", 5000);
```

## See also
JSON framework:
https://github.com/nlohmann/json

Validation framework:
https://github.com/pboettch/json-schema-validator/

JSON Schema reference:
https://json-schema.org/understanding-json-schema/index.html
