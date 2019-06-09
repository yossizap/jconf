#include <iomanip>
#include <iostream>

#include "jconf/jconf.hpp"

using namespace std;

int main(int argc, char **argv) {
  jconf::Config c("./config.json", "./schema.json");
  cout << "Loading configuration and schema..." << endl;
  c.load();
  cout << "Configuration:" << endl;
  cout << setw(4) << c << endl;

  cout << "Enabled? " << c.get_property("enable") << endl;
  if (!c.get_property("enable")) {
    cout << "Apparently not. Enabling now..." << endl;
    c.set_property(R"(
                     {"enable": true}
                   )"_json);
  }

  cout << "Logging level is currently " << c.get_property("/logging/level") << endl;
  cout << "Setting logging.level to 'notice' using JSON objects..." << endl;
  try {
    c.set_property(R"({
                     "logging" :
                     {"level":  "notice"}
                   })"_json);
  } catch (const std::exception &e) {
    cout << e.what();
    cout << "Oops. 'notice is invalid. Setting to 'info'" << endl;
    c.set_property({{"logging", 
                     {{"level", "info"}}
                   }});
    cout << "The new logging level is: " << c.get_property("/logging/level") << endl;
  }

  return 0;
}
