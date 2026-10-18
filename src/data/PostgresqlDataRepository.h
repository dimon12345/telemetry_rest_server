#pragma once

#include <pqxx/pqxx>

#include "model/DataRepository.h"


class PostgresqlDataRepository : public DataRepository {
public:
    PostgresqlDataRepository(const class ConfigOld &config_old);
    std::vector<SensorEntity> getSensors() override;
    std::vector<SensorDataEntity> getSensorsData(int seconds) override;

private:
    std::unique_ptr<pqxx::connection> connection_;
};
