cmake_minimum_required(VERSION 3.10)
project(NPCGame VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

# Указываем пути к заголовочным файлам
include_directories(include)
include_directories(src)

# Основная программа
add_executable(npc_game
    src/main.cpp
    src/npc.cpp
    src/dragon.cpp
    src/queen.cpp
    src/knight_errant.cpp
    src/fight_visitor.cpp
    src/observer.cpp
    src/npc_factory.cpp
)

# Указываем пути для поиска заголовков
target_include_directories(npc_game PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Тесты
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/test_main.cpp")
    add_executable(npc_tests
        tests/test_main.cpp
        src/npc.cpp
        src/dragon.cpp
        src/queen.cpp
        src/knight_errant.cpp
        src/fight_visitor.cpp
        src/observer.cpp
        src/npc_factory.cpp
    )
    
    target_include_directories(npc_tests PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    )
    target_link_libraries(npc_tests GTest::gtest GTest::gtest_main)
    
    # Добавляем запуск тестов
    include(GoogleTest)
    gtest_discover_tests(npc_tests)
endif()

# Установка выходных файлов в bin директорию
set_target_properties(npc_game npc_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)