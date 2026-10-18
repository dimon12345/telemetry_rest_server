#include <unordered_map>

#include "ConfigOld.h"
#include "PostgresqlDataRepository.h"


PostgresqlDataRepository::PostgresqlDataRepository(const class ConfigOld &config_old) {
    std::string connection_string =
            "host=" + config_old.pg_host +
            " dbname=telemetry" +
            " user=" + config_old.pg_user +
            " password=" + config_old.pg_password;

    connection_ = std::make_unique<pqxx::connection>(connection_string);
}

std::vector<SensorEntity> PostgresqlDataRepository::getSensors() {
    std::unordered_map<int, std::string> sensors;
    std::vector<SensorEntity> result;

    pqxx::work txn(*connection_);
    pqxx::result res = txn.exec("SELECT * FROM names;");
    for (auto const &row : res) {
        int name_id = row["name_id"].as<int>();
        sensors[name_id] = row["name"].as<std::string>();
    }

    for (auto &sensor: sensors ) {
        pqxx::result res = txn.exec_params("SELECT value,to_char(timestamp AT TIME ZONE 'UTC', 'YYYY-MM-DD\"T\"HH24:MI:SS\"Z\"') as formatted_timestamp FROM telemetry WHERE name_id = $1 ORDER BY timestamp DESC LIMIT 1;", sensor.first);
        if (!res.empty()) {
            double last_result = res[0]["value"].as<double>();
            std::string timestamp = res[0]["formatted_timestamp"].as<std::string>();
            result.emplace_back(SensorEntity{sensor.first, sensor.second, last_result, timestamp});
        }
    }

    return result;
}

std::vector<SensorDataEntity> PostgresqlDataRepository::getSensorsData(int seconds) {
    pqxx::work txn(*connection_);
    pqxx::result res = txn.exec_params(
        "SELECT id,sensor_id,value,to_char(timestamp AT TIME ZONE 'UTC', "
        "'YYYY-MM-DD\"T\"HH24:MI:SS\"Z\"') as formatted_timestamp from "
        "telemetry where timestamp >= NOW() - ($1 * INTERVAL '1 second');",
        seconds);

    std::vector<SensorDataEntity> result;
    result.reserve(res.size());

    for (auto const &row: res) {
        int id = row["id"].as<int>();
        int sensor_id = row["sensor_id"].as<int>();
        double value = row["value"].as<double>();
        std::string timestamp = row["formatted_timestamp"].as<std::string>();
        result.emplace_back(SensorDataEntity{id, sensor_id, value, timestamp});
    }

    return result;
}
