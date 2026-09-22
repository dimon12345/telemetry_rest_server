#include "GetDataForIntervalUseCase.h"


std::vector<SensorDataEntity> GetDataForIntervalUseCase::operator()(int seconds) {
    return data_repository_.getSensorsData(seconds);
}
