add_executable(
  benchmarkPOC
  benchmarkPOC.cpp
)

target_link_libraries(
    benchmarkPOC
    PRIVATE 
        benchmark::benchmark
)
