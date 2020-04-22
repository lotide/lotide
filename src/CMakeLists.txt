set(HEADER_LIST "${PROJECT_SOURCE_DIR}/include/LoTide.hpp")

SET(BUILD_SHARED_LIBS ON)

set(SOURCES
  Server.cpp
  LoTide.cpp
  Sequencer.cpp
  Note.cpp
  Song.cpp
  Phrase.cpp
  Group.cpp
  main.cpp
  LTSynth.cpp
  )

find_library(WSOCK32_LIBRARY wsock32)
find_library(WS2_32_LIBRARY ws2_32)

add_library(LoTide STATIC ${SOURCES} ${HEADER_LIST})
add_library(${LOCAL_PROJECT_NAMESPACE}::${LOCAL_PROJECT_NAME} ALIAS LoTide)

target_include_directories(LoTide
  PUBLIC
  ${PROJECT_SOURCE_DIR}/include
)

if(WIN32)
  target_link_libraries(LoTide wsock32 ws2_32)
endif()

target_link_libraries(LoTide
  tsal::tsal
  cereal
  nlohmann_json::nlohmann_json
  )

add_executable(lotide-bin ${SOURCES})

target_include_directories(lotide-bin
  PUBLIC
  ${PROJECT_SOURCE_DIR}/include
)

if(WIN32)
  target_link_libraries(lotide-bin wsock32 ws2_32)
endif()

target_link_libraries(lotide-bin
  tsal::tsal
  cereal
  nlohmann_json::nlohmann_json
  )

set_target_properties(lotide-bin
  PROPERTIES
  OUTPUT_NAME lotide
  )
