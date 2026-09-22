#pragma once

#include <string>


struct SensorEntity {
    int name_id;
    std::string name;
    double last_value;
    std::string timestamp;
};
