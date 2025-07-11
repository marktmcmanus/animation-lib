
#
# animation-lib
#

set(_library_src_root_path "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}")
file(
    GLOB_RECURSE _library_source_list 
    LIST_DIRECTORIES false
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${_library_src_root_path}/*.c*"
    "${_library_src_root_path}/*.h*"
)
add_library( "${PROJECT_NAME}" ${_library_source_list} )
target_include_directories("${PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/include" )
target_compile_definitions("${PROJECT_NAME}" PUBLIC WIN32_LEAN_AND_MEAN)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${_library_source_list})

#
# animation-lib.test
#

if(ANIM_BUILD_TESTS)
    include(FetchContent)

    set(wxBUILD_SHARED OFF)
    set(wxUSE_WEBVIEW OFF)

    message(STATUS "Fetching wxWidgets...")

    FetchContent_Declare(
       wxWidgets
       GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
       GIT_SHALLOW ON
    )
    FetchContent_MakeAvailable(wxWidgets)

    set(SRCS 
        "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.test/main.cpp" 
        "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.test/MainWindow.cpp" 
        "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.test/MainWindow.h"
	    "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.test/WindowAnimationEventHandler.cpp"
	    "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.test/WindowAnimationEventHandler.h"
	    "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.test/MainWindowVariableChangeHandler.cpp"
	    "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.test/MainWindowVariableChangeHandler.h"
	    "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.test/LogStoryboardEventHandler.h"
	    "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.test/LogStoryboardEventHandler.cpp"
	    "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.test/main.exe.manifest" )

    add_executable("${PROJECT_NAME}.test" WIN32 ${SRCS} )
    target_compile_definitions("${PROJECT_NAME}.test" PUBLIC WIN32_LEAN_AND_MEAN)
    target_link_libraries("${PROJECT_NAME}.test" PRIVATE "${PROJECT_NAME}" wxcore wxnet )
endif()
