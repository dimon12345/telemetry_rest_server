#include "GetSensorsUseCase.h"

std::vector<SensorEntity> GetSensorsUseCase::operator() () const {
    return data_repository_.getSensors();
}
