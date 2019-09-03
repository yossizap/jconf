#include <iomanip>
#include <iostream>

#include "jconf/jconf.hpp"

using namespace std;

int main(int argc, char **argv)
{
    jconf::Config c("./config.json", "./schema.json");
    cout << "Loading configuration and schema..." << endl;
    c.load();
    cout << "Configuration:" << endl;
    cout << setw(4) << c << endl;

    cout << "Enabled? " << c.get("enable") << endl;
    if (!c.get("enable"))
    {
        cout << "Apparently not. Enabling now..." << endl;
        c.set(R"(
               {"enable": true}
             )"_json);
    }

    cout << "Logging level is currently " << c.get("/logging/level") << endl;
    cout << "Setting logging.level to 'notice' using JSON objects..." << endl;
    try
    {
        c.set(R"({
                "logging" :
                {"level":  "notice"}
             })"_json);
    }
    catch (const std::exception &e)
    {
        cout << e.what();
        cout << "Oops. 'notice is invalid. Setting to 'info'" << endl;
        c.set({{"logging", {{"level", "info"}}}});
        cout << "The new logging level is: " << c.get("/logging/level") << endl;
    }

    cout << "Setting queues.rx to '5000'..." << endl;
    c.set("/queues/rx", 5000);
    cout << "RX is now set to " << c.get("/queues/rx") << " TX is still "
         << c.get("/queues/tx") << endl;

    return 0;
}
