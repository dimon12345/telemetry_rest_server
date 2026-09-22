#include <fstream>

#include <argparse.hpp>
#include <nlohmann/json.hpp>

#include "ArgParseConfig.h"


namespace {
    const std::string AppName = "Telemetry REST server";
    const std::string DefaultConfigFilename = "config.json";

    void parse_arguments(argparse::ArgumentParser &program,
                                int argc, char **argv) {
        program
            .add_argument("-c", "--config_filename")
            .help("config filename")
            .default_value("");
        program.parse_args(argc, argv);
    }
}

ArgParseConfig::ArgParseConfig(int argc, char **argv) {
    argparse::ArgumentParser program(AppName);
    ::parse_arguments(program, argc, argv);

    std::string config_filename = program.get<std::string>("config_filename");
    if (config_filename.empty()) {
        config_filename = DefaultConfigFilename;
    }

    if (!std::filesystem::exists(config_filename)) {
        throw std::runtime_error("Bad filename: " + config_filename);
    }

    std::ifstream file(config_filename);
    nlohmann::json config = nlohmann::json::parse(file);

    pg_host = config["pg"]["host"];
    pg_user = config["pg"]["user"];
    pg_password = config["pg"]["password"];

    validate();
}


void ArgParseConfig::validate() {
    if (pg_host.empty()) {
        throw std::runtime_error("PostgreSQL host is empty");
    }
    if (pg_user.empty()) {
        throw std::runtime_error("PostgreSQL user is empty");
    }
    if (pg_host.empty()) {
        throw std::runtime_error("PostgreSQL password is empty");
    }
}
