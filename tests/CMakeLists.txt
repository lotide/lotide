add_executable (testClient testClient.cpp)

# Make LoTide a library
target_link_libraries(testClient LoTide)
