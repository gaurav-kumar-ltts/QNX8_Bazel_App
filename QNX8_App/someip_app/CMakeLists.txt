# SOME/IP Server / Client
set(SOMEIP_ARXML_FILE "${CMAKE_CURRENT_SOURCE_DIR}/input.arxml" CACHE FILEPATH "Input ARXML used to generate vsomeip.json")
set(SOMEIP_GENERATED_JSON "${CMAKE_BINARY_DIR}/bin/vsomeip.json")
set(SOMEIP_SOURCE_JSON "${CMAKE_CURRENT_SOURCE_DIR}/vsomeip.json")

add_executable(someip_vsomeip_generator arxml_to_vsomeip.cpp)

target_include_directories(someip_vsomeip_generator PRIVATE
    ${NLOHMANN_JSON_INCLUDE_DIR}
)

target_compile_definitions(someip_vsomeip_generator PRIVATE
    SOMEIP_ARXML_DEFAULT_PATH="${SOMEIP_ARXML_FILE}"
    SOMEIP_VSOMEIP_DEFAULT_OUTPUT="${SOMEIP_GENERATED_JSON}"
    SOMEIP_SERVICE_APP_NAME="example_service_app"
    SOMEIP_CONSUMER_APP_NAME="example_consumer_app"
)

add_executable(someip_server server.cpp)
add_executable(someip_client client.cpp)

target_include_directories(someip_server PRIVATE
    ${CMAKE_SOURCE_DIR}/common
    ${VSOMEIP_INCLUDE_DIR}
    ${DLT_INCLUDE_DIR}
)

target_include_directories(someip_client PRIVATE
    ${VSOMEIP_INCLUDE_DIR}
    ${DLT_INCLUDE_DIR}
)

target_link_libraries(someip_server
    vsomeip
    vsomeip_cfg
    vsomeip_sd
    dlt
    Threads::Threads
)

target_link_libraries(someip_client
    vsomeip
    vsomeip_cfg
    vsomeip_sd
    dlt
    Threads::Threads
)

if(EXISTS "${SOMEIP_ARXML_FILE}")
    add_custom_command(
        OUTPUT ${SOMEIP_GENERATED_JSON}
        COMMAND someip_vsomeip_generator
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SOMEIP_GENERATED_JSON} ${SOMEIP_SOURCE_JSON}
        BYPRODUCTS ${SOMEIP_SOURCE_JSON}
        DEPENDS someip_vsomeip_generator ${SOMEIP_ARXML_FILE}
        COMMENT "Generating vsomeip.json from ARXML and updating source vsomeip.json"
        VERBATIM
    )
else()
    add_custom_command(
        OUTPUT ${SOMEIP_GENERATED_JSON}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SOMEIP_SOURCE_JSON} ${SOMEIP_GENERATED_JSON}
        DEPENDS ${SOMEIP_SOURCE_JSON}
        COMMENT "Copying fallback vsomeip.json"
        VERBATIM
    )
endif()

add_custom_target(someip_vsomeip_json DEPENDS ${SOMEIP_GENERATED_JSON})
add_dependencies(someip_server someip_vsomeip_json)
add_dependencies(someip_client someip_vsomeip_json)
 