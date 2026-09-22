#include "JsonMapper.h"

using json = nlohmann::json;


json JsonMapper::mapSensors(const std::vector<SensorEntity> &sensors) {
    json results = json::array();

    for (auto &sensor : sensors) {
        json sensor_result;
        sensor_result["name"] = sensor.name;
        sensor_result["nameId"] = sensor.name_id;
        sensor_result["lastValue"] = sensor.last_value;
        sensor_result["lastTimestamp"] = sensor.timestamp;
        results.push_back(std::move(sensor_result));
    }

    return results;
}

json JsonMapper::mapSensorsData(const std::vector<SensorDataEntity> &sensors_data) {
    json results = json::array();

    for (auto &data : sensors_data) {
        json data_result;
        data_result["valueId"] = data.value_id;
        data_result["nameId"] = data.name_id;
        data_result["value"] = data.value;
        data_result["timestamp"] = data.timestamp;
        results.push_back(std::move(data_result));
    }

    return results;
}
