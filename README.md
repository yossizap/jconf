# JConf

JConf library provides a way to manage Property Tree that has a schema to
validate against. The property can be serialized and deserialized to JSON and
some of its binary derivatives, such as BSON, CBOR, MessagePack, and UBJSON.

It is very similar in concept and usage to Boost's `PropertyTree`, but the main
difference is that JConf has JSON Schema support for data validation.

## Usage
```cpp
jconf::Config config("config.json", "schema.json");
config.load();

std::cout << config.at("some_key");         // Retrieve a key
std::cout << config.at("/parent/child");    // Even works with JSON pointer

config.at("some_integer") = 1337;           // An integer
config.validate();

config.at("some_integer") = "hello world";  // A string??
config.validate();                          // Will raise an exception
```