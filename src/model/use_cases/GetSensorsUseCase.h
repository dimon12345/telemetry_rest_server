#pragma once

#include "model/DataRepository.h"

class GetSensorsUseCase {
public:
    GetSensorsUseCase(DataRepository &data_repository)
        : data_repository_(data_repository) {}
    std::vector<SensorEntity> operator()() const;

private:
    DataRepository &data_repository_;
};
