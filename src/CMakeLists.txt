set(HEADER_LIST "${PROJECT_SOURCE_DIR}/include/LoTide.hpp")

SET(BUILD_SHARED_LIBS ON)

set(SOURCES
  LoTide.cpp
  Sequencer.cpp
  Note.cpp
  Song.cpp
  Phrase.cpp
  Group.cpp
  main.cpp
  LTSynth.cpp
  Server.cpp
  )

add_library(LoTide STATIC ${SOURCES} ${HEADER_LIST})
add_library(${LOCAL_PROJECT_NAMESPACE}::${LOCAL_PROJECT_NAME} ALIAS LoTide)

target_include_directories(LoTide
  PUBLIC
  ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(LoTide
  tsal::tsal
  cereal
  )

if(WIN32)
  target_link_libraries(LoTide wsock32 ws2_32)
endif()

add_executable(lotide-bin ${SOURCES})

target_include_directories(lotide-bin
  PUBLIC
  ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(lotide-bin
  tsal::tsal
  cereal
  )

if(WIN32)
  target_link_libraries(lotide-bin wsock32 ws2_32)
endif()

set_target_properties(lotide-bin
  PROPERTIES
  OUTPUT_NAME lotide
  )