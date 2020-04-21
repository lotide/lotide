add_executable(testClient testClient.cpp)
target_link_libraries(testClient LoTide)

add_executable(testServer testServer.cpp)
target_link_libraries(testServer LoTide)
