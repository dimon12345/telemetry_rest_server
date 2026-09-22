#pragma once

#include <vector>

#include <nlohmann/json.hpp>

#include "model/entity/SensorEntity.h"
#include "model/entity/SensorDataEntity.h"

class JsonMapper {
public:
    nlohmann::json mapSensors(const std::vector<SensorEntity> &sensors);
    nlohmann::json mapSensorsData(const std::vector<SensorDataEntity> &sensors_data);
};
