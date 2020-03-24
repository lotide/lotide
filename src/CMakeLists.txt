set(SOURCES
  LoTide.cpp
  Sequencer.cpp
  Note.cpp
  Song.cpp
  Phrase.cpp
  Group.cpp
  main.cpp
  LTSynth.cpp
  )

# set(PROTOS
#     ${PROJECT_SOURCE_DIR}/protos/lotiderpc.proto
# )

# set(PROTO_SRC_DIR ${PROJECT_BINARY_DIR}/proto-src)
# file(MAKE_DIRECTORY ${PROTO_SRC_DIR})

# protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_SRC_DIR} ${PROTOS})
# grpc_generate_cpp(GRPC_SRCS GRPC_HDRS ${PROTO_SRC_DIR} ${PROTOS})

# add_executable(lotide ${SOURCES} ${PROTO_SRCS} ${GRPC_SRCS})

add_executable(lotide ${SOURCES})

target_include_directories(lotide
  # PUBLIC
    # ${PROTO_SRC_DIR}
  PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

# TODO: Try without ssl/bz2/z/zip
target_link_libraries(lotide
  tsal::tsal
  # gRPC::grpc++_reflection
  # protobuf::libprotobuf
  )
