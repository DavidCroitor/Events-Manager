cmake_minimum_required(VERSION 3.28)
project(EventsManager)

set(CMAKE_CXX_STANDARD 14)

include_directories("Source Files")
include_directories("Header Files")


add_executable(${PROJECT_NAME}
        "Source Files/main.cpp"
        "Source Files/compareDates.cpp"
        "Source Files/mergeSort.cpp"
        "Source Files/Writer.cpp"
        "Source Files/Service.cpp"
        "Source Files/Validator.cpp"
        "Source Files/Repository.cpp"
        "Source Files/Event.cpp"
        "Source Files/FileRepository.cpp"
        "Source Files/Utils.cpp"
        "Header Files/compareDates.h"
        "Header Files/Writer.h"
        "Header Files/Repository.h"
        "Header Files/mergeSort.h"
        "Header Files/Utils.h"
        "Header Files/Service.h"
        "Header Files/Validator.h"
        "Header Files/FileRepository.h"
        "Header Files/ADMIN_GUI.h"
        "Source Files/ADMIN_GUI.cpp"
        "Header Files/RepositoryException.h"
        "Source Files/RepositoryException.cpp"
        "Header Files/MainWindow.h"
        "Source Files/MainWindow.cpp"
        "Header Files/USER_GUI.h"
        "Source Files/USER_GUI.cpp"
        "Source Files/Command.cpp"
        "Header Files/Command.h"
        "Header Files/EventTableModel.h"
        "Source Files/EventTableModel.cpp"
        "Source Files/test.h"
        "Source Files/test.cpp"
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_EXECUTABLE "D:\\Qt\\6.9.0\\mingw_64\\bin")
set(CMAKE_PREFIX_PATH "D:\\Qt\\6.9.0\\mingw_64\\lib\\cmake")

find_package(Qt6Widgets REQUIRED)
find_package(QT6 REQUIRED COMPONENTS Widgets)
target_link_libraries(${PROJECT_NAME} Qt6::Widgets)