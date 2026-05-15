set(srcs src/status_json.cc src/callbacks.cc src/cli_out.cc  src/so_out.cc
    src/uout_writer_raw.cc src/uout_writer_file.cc src/uout_writer_console.cc)  

set(platform_srcs "") 
include("${CMAKE_CURRENT_LIST_DIR}/../../source_filter.cmake" OPTIONAL)

if(COMMAND idf_component_register)
idf_component_register(SRCS ${srcs} 
    INCLUDE_DIRS "./include" 
    PRIV_INCLUDE_DIRS "./include/uout" 
    REQUIRES  utils_debug utils_misc 
)
component_compile_options(${comp_compile_opts})
component_compile_features(${comp_compile_feats})
else()

add_library(uout STATIC ${srcs})
target_include_directories(uout PUBLIC ./include)
target_link_libraries(uout PUBLIC utils_debug utils_misc)

endif()
