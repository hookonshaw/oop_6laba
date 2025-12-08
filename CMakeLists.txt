cmake_minimum_required(VERSION 3.10)
project(NPC_Fight CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основные исходные файлы из src/
set(NPC_SOURCES
    src/main.cpp
    src/npc.cpp
    src/queen.cpp
    src/dragon.cpp
    src/knight_errant.cpp
    src/npc_factory.cpp
    src/fight_visitor.cpp
    src/observer.cpp
)

# Тестовые файлы из tests/
set(TEST_SOURCES
    tests/test_main.cpp
    tests/test_npc.cpp
    tests/test_factory.cpp
    tests/test_visitor.cpp
)

# Проверяем существование файлов
message(STATUS "Проверка файлов...")

foreach(file ${NPC_SOURCES})
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${file})
        message(STATUS "✓ Найден: ${file}")
    else()
        message(FATAL_ERROR "✗ НЕ найден: ${file}")
    endif()
endforeach()

foreach(file ${TEST_SOURCES})
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${file})
        message(STATUS "✓ Найден: ${file}")
    else()
        message(FATAL_ERROR "✗ НЕ найден: ${file}")
    endif()
endforeach()

# Основная программа
add_executable(npc_simulation ${NPC_SOURCES})
target_include_directories(npc_simulation PRIVATE include)

# Google Test
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

# Тестовая программа
add_executable(npc_tests
    ${TEST_SOURCES}
    # Нужно также включить основные исходники
    src/npc.cpp
    src/queen.cpp
    src/dragon.cpp
    src/knight_errant.cpp
    src/npc_factory.cpp
    src/fight_visitor.cpp
    src/observer.cpp
)

target_include_directories(npc_tests PRIVATE include)
target_link_libraries(npc_tests
    GTest::gtest
    GTest::gtest_main
    Threads::Threads
)

message(STATUS "Конфигурация завершена успешно!")