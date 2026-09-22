#pragma once

class RestServer {
public:
    RestServer(const class Config &config) : config_(config) {}

    int run();

private:
    const class Config &config_;
};
