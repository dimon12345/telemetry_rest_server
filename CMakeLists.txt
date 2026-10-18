cmake_minimum_required(VERSION 3.14)

project(rest_server CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)

pkg_check_modules(PQXX REQUIRED IMPORTED_TARGET libpqxx)

add_executable(rest_server
    src/main.cpp
    src/app/ArgParseConfig.cpp
    src/data/PostgresqlDataRepository.cpp
    src/rest/JsonMapper.cpp
    src/rest/RestServer.cpp
    src/model/use_cases/GetSensorsUseCase.cpp
    src/model/use_cases/GetDataForIntervalUseCase.cpp
)

target_include_directories(rest_server PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/include
    src
)

target_link_libraries(rest_server PRIVATE pqxx pq)
