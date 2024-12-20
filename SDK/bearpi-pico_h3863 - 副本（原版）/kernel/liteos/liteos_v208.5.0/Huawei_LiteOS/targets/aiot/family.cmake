# C include
string(REPLACE "\${ROOT_DIR}" "${ROOT_DIR}" CONFIG_LWIP_COMPILE_PATH "${CONFIG_LWIP_COMPILE_PATH}")

if(${LOSCFG_PLATFORM} STREQUAL "ws63")
    list(APPEND MODULE_INCLUDE_PUB ${CMAKE_CURRENT_SOURCE_DIR}/ws63/include)
    if (EXISTS ${CONFIG_LWIP_COMPILE_PATH}/src/include)
        list(APPEND MODULE_INCLUDE_PUB ${CONFIG_LWIP_COMPILE_PATH}/src/include)
    else()
        list(APPEND MODULE_INCLUDE_PUB ${ROOT_DIR}/open_source/lwip/lwip_v2.1.3/src/include)
    endif()
    if (EXISTS ${CONFIG_LWIP_COMPILE_PATH}/src/include/lwip/nettool)
        list(APPEND MODULE_INCLUDE_PUB ${CONFIG_LWIP_COMPILE_PATH}/src/include/lwip/nettool)
    else()
        list(APPEND MODULE_INCLUDE_PUB ${ROOT_DIR}/open_source/lwip/lwip_v2.1.3/src/include/lwip/nettool)
    endif()
    if (EXISTS ${CONFIG_LWIP_COMPILE_PATH}/../lwip_adapter/liteos_207/src/include/)
        list(APPEND MODULE_INCLUDE_PUB ${CONFIG_LWIP_COMPILE_PATH}/../lwip_adapter/liteos_207/src/include/)
    else()
        list(APPEND MODULE_INCLUDE_PUB ${ROOT_DIR}/open_source/lwip/lwip_adapter/liteos_207/src/include/)
    endif()
    list(APPEND MODULE_INCLUDE_PUB ${ROOT_DIR}/kernel/osal/include/lock/)
    list(APPEND MODULE_INCLUDE_PUB ${ROOT_DIR}/kernel/osal/include/schedule/)
    list(APPEND MODULE_CMACRO_PUB LWIP_CONFIG_FILE=\"lwip/lwipopts_default.h\")
elseif(${LOSCFG_PLATFORM} STREQUAL "ws53")
    list(APPEND MODULE_INCLUDE_PUB ${CMAKE_CURRENT_SOURCE_DIR}/ws53/include)
    list(APPEND MODULE_INCLUDE_PUB ${ROOT_DIR}/open_source/lwip/lwip_v2.1.3/src/include)
    list(APPEND MODULE_INCLUDE_PUB ${ROOT_DIR}/open_source/lwip/lwip_v2.1.3/src/include/lwip/nettool)
    list(APPEND MODULE_INCLUDE_PUB ${ROOT_DIR}/open_source/lwip/lwip_adapter/liteos_207/src/include/)
    list(APPEND MODULE_INCLUDE_PUB ${ROOT_DIR}/kernel/osal/include/lock/)
    list(APPEND MODULE_INCLUDE_PUB ${ROOT_DIR}/kernel/osal/include/schedule/)
    list(APPEND MODULE_CMACRO_PUB LWIP_CONFIG_FILE=\"lwip/lwipopts_default.h\")
endif()


