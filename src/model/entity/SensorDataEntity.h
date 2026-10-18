#pragma once

#include <string>


struct SensorDataEntity {
    int id;
    int sensor_id;
    double value;
    std::string timestamp;
};
