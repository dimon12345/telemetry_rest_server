#pragma once

class RestServer {
public:
    RestServer(const class ConfigOld &config_old) : config_old_(config_old) {}

    int run();

private:
    const class ConfigOld &config_old_;
};
