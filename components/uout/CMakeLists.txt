set(srcs src/status_json.cc src/callbacks.cc src/cli_out.cc  src/so_out.cc src/so_target_desc.cc)  

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
