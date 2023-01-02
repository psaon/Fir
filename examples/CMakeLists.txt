project(FirTest)

include_directories(../include)
add_executable(FirTest Test.cpp)

target_link_libraries(FirTest PUBLIC FirCore)