#include <iostream>

#include "app/ArgParseConfigOld.h"
#include "rest/RestServer.h"


int main(int argc, char **argv) {
    try {
        ArgParseConfigOld config(argc, argv);
        RestServer server(config);
        return server.run();
    } catch(const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
