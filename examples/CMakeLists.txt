project(FirTest)

include_directories(../)
add_executable(FirTest Test.cpp)

target_link_libraries(FirTest PUBLIC Fir)