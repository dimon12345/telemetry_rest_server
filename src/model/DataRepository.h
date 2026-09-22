#pragma once

#include <vector>

#include "entity/SensorEntity.h"
#include "entity/SensorDataEntity.h"

class DataRepository {
public:
    virtual ~DataRepository() = default;
    virtual std::vector<SensorEntity> getSensors() = 0;
    virtual std::vector<SensorDataEntity> getSensorsData(int seconds) = 0;
};
