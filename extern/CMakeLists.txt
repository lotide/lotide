add_subdirectory(TSAL)

set(SKIP_PORTABILITY_TEST ON CACHE INTERNAL "")
set(SKIP_PERFORMANCE_COMPARISON ON CACHE INTERNAL "")
set(JUST_INSTALL_CEREAL ON CACHE INTERNAL "")
add_subdirectory(cereal)

set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(json)
