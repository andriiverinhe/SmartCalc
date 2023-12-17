cmake_minimum_required(VERSION 3.5)

project(Smart_calc VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets PrintSupport REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets PrintSupport REQUIRED)

# Добавим пути к заголовочным файлам
include_directories(SmartCalc)
include_directories(SmartCalc/function/calculator)
include_directories(SmartCalc/function/stack)

# Добавим исходные файлы
set(PROJECT_SOURCES
    source/main.cpp
    source/mainwindow.cpp
    source/mainwindow.h
    source/mainwindow.ui
    qcustomplot.cpp
    qcustomplot.h
    source/creditcalc.cpp
    source/creditcalc.h
    source/creditcalc.ui
    source/depositcalc.cpp
    source/depositcalc.h
    source/depositcalc.ui
    SmartCalc/s21_smartCalc.h
    SmartCalc/function/calculator/calculator.c
    SmartCalc/function/calculator/calculator.h
    SmartCalc/function/calculator/help.c
    SmartCalc/function/calculator/parser.c
    SmartCalc/function/calculator/bonusCalc.c
    SmartCalc/function/struct.h
    SmartCalc/function/stack/help.c
    SmartCalc/function/stack/stack.c
    SmartCalc/function/stack/stack.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Smart_calc
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(Smart_calc SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Smart_calc
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Link against Widgets and PrintSupport
target_link_libraries(Smart_calc PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::PrintSupport)

# # Для си файлов нужно использовать флаг -lm
# if (NOT WIN32)
#     target_link_libraries(Smart_calc PRIVATE m)
# endif()

# # Добавим линковку с библиотекой libsmartcalc.a
# target_link_libraries(Smart_calc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/SmartCalc/libsmartcalc.a)

# # Выведем информацию о сборке
# message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
# message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")

# # Проверим, содержится ли функция s21_calc в библиотеке libsmartcalc.a
# execute_process(
#     COMMAND nm ${CMAKE_CURRENT_SOURCE_DIR}/SmartCalc/libsmartcalc.a
#     COMMAND grep s21_calc
#     RESULT_VARIABLE result
# )

# if (result EQUAL 0)
#     message(STATUS "Function s21_calc found in libsmartcalc.a")
# else()
#     message(FATAL_ERROR "Function s21_calc not found in libsmartcalc.a")
# endif()
