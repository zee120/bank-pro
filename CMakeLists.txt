cmake_minimum_required(VERSION 3.16)
project(bank-pro VERSION 1.0.0 LANGUAGES CXX)

add_executable(bank-pro src/Main.cpp)
set_target_properties(bank-pro PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

target_include_directories(bank-pro PRIVATE
    include
    src
    src/models
    src/screens
    src/screens/auth
    src/screens/clients
    src/screens/transactions
    src/screens/users
)

if(MSVC)
    # The date library uses standard C time functions.
    target_compile_definitions(bank-pro PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

# Run with the project directory as cwd so the app can find data/.
add_custom_target(run
    COMMAND $<TARGET_FILE:bank-pro>
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    DEPENDS bank-pro
    USES_TERMINAL
)
