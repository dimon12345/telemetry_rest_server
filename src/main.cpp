#include <iostream>

#include "app/ArgParseConfig.h"
#include "rest/RestServer.h"


int main(int argc, char **argv) {
    try {
        ArgParseConfig config(argc, argv);
        RestServer server(config);
        return server.run();
    } catch(const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
