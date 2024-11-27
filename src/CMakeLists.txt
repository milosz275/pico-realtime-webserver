set(MAKE_FS_DATA_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/external/makefsdata)

if (NOT EXISTS ${MAKE_FS_DATA_SCRIPT})
    file(DOWNLOAD
        https://raw.githubusercontent.com/lwip-tcpip/lwip/e799c266facc3c70190676eccad49d6c2db2caac/src/apps/http/makefsdata/makefsdata
        ${MAKE_FS_DATA_SCRIPT}
        )
endif()
message("Running makefsdata script")
execute_process(COMMAND
    perl ${MAKE_FS_DATA_SCRIPT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    ECHO_OUTPUT_VARIABLE
    ECHO_ERROR_VARIABLE
    )
file(RENAME fsdata.c generated_fsdata.c)

add_executable(${PROGRAM_NAME}
    main.c
    realtime_webserver.c
    ssi.c
    cgi.c
    common.c
    state.c
    auth.c
)

target_link_libraries(${PROGRAM_NAME}
    pico_stdlib
    pico_cyw43_arch_lwip_threadsafe_background
    pico_lwip_http
    pico_multicore
    hardware_adc
    FreeRTOS-Kernel-Heap4
)

target_include_directories(${PROGRAM_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/../include
)

suppress_pico_sdk_warnings()
pico_enable_stdio_usb(${PROGRAM_NAME} 1)
pico_enable_stdio_uart(${PROGRAM_NAME} 0)
pico_add_extra_outputs(${PROGRAM_NAME})
