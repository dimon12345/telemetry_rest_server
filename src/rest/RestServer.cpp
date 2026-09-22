#include "crow.h"

#include "Config.h"
#include "RestServer.h"
#include "JsonMapper.h"
#include "data/PostgresqlDataRepository.h"
#include "model/use_cases/GetSensorsUseCase.h"
#include "model/use_cases/GetDataForIntervalUseCase.h"

namespace {
    constexpr int seconds_per_minute = 60;
    constexpr int minutes_per_hour = 60;
    constexpr int seconds_per_hour = minutes_per_hour * seconds_per_minute;
}


int RestServer::run() {
    crow::SimpleApp app;
    JsonMapper jsonMapper;

    PostgresqlDataRepository postgresqlDataRepository(config_);
    GetSensorsUseCase getSensorsUseCase(postgresqlDataRepository);
    GetDataForIntervalUseCase getDataForIntervalUseCase(postgresqlDataRepository);

    CROW_ROUTE(app, "/")([](){
        return "Telemetry REST server.";
    });

    CROW_ROUTE(app, "/sensors")([&](){
        nlohmann::json sensors_json =
            jsonMapper.mapSensors(getSensorsUseCase());

        crow::response res(sensors_json.dump());
        res.set_header("Content-Type", "application/json");
        return res;
    });

    CROW_ROUTE(app, "/data/hour")([&](){
        nlohmann::json data_json =
            jsonMapper.mapSensorsData(getDataForIntervalUseCase(seconds_per_hour));

        crow::response res(data_json.dump());
        res.set_header("Content-Type", "application/json");
        return res;
    });

    CROW_ROUTE(app, "/data/sixHours")([&](){
        nlohmann::json data_json =
            jsonMapper.mapSensorsData(getDataForIntervalUseCase(6 * seconds_per_hour));

        crow::response res(data_json.dump());
        res.set_header("Content-Type", "application/json");
        return res;
    });

    CROW_ROUTE(app, "/data/day")([&](){
        nlohmann::json data_json =
            jsonMapper.mapSensorsData(getDataForIntervalUseCase(24 * seconds_per_hour));

        crow::response res(data_json.dump());
        res.set_header("Content-Type", "application/json");
        return res;
    });

    app.port(18080).multithreaded().run();
    return 0;
}
