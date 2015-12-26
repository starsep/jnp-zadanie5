cmake_minimum_required(VERSION 2.8)
project(jnp_zadanie5)

add_custom_target(ptest COMMAND make -C ${jnp_zadanie5_SOURCE_DIR}
        CLION_EXE_DIR=${PROJECT_BINARY_DIR})
