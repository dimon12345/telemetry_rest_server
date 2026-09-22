#pragma once

#include "model/DataRepository.h"

class GetDataForIntervalUseCase {
public:
    GetDataForIntervalUseCase(DataRepository &data_repository)
        : data_repository_(data_repository) {}
    std::vector<SensorDataEntity> operator()(int seconds);

private:
    DataRepository &data_repository_;
};
