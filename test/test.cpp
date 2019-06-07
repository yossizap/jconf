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

  cout << "Enabled? " << c.at("enable") << endl;
  if (!c.at("enable")) {
    cout << "Apparently not. Enabling now..." << endl;
    c.at("enable") = true;
  }

  cout << "Logging level is currently " << c.at("/logging/level") << endl;
  cout << "Setting logging.level to 'notice'..." << endl;

  c.at("/logging/level") = "notice";
  try {
    c.validate();
  } catch (const std::exception &e) {
    cout << e.what();
    cout << "Oops. 'notice is invalid. Setting to 'warning'" << endl;
    c.at("/logging/level") = "warning";
  }

  return 0;
}
