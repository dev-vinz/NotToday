###############################################################################
##########          MINIMUM REQUIREMENTS (some need to be BEFORE project command)
###############################################################################

###############################################################################
##########          REQUIREMENTS + GLOBAL DEFINITION
###############################################################################
set(TARGET_NAME LibTools)

set(${TARGET_NAME}_SOURCES
    priorityqueue.h priorityqueue.cpp
    recurrence.h
    task.h task.cpp
    taskstatus.h
    timespan.h timespan.cpp
    todolist.h todolist.cpp
    utils.h utils.cpp
)

set(${TARGET_NAME}_TESTS
${CMAKE_CURRENT_SOURCE_DIR}/tools_test.cpp

PARENT_SCOPE # must be reused from main testing program
)

###############################################################################
##########          PLATFORM SPECIFIC GLOBAL SETTINGS
###############################################################################

###############################################################################
##########          INTERNAL PROJECTS (OUR OWN)
###############################################################################

add_library(${TARGET_NAME} ${${TARGET_NAME}_SOURCES})
target_include_directories(${TARGET_NAME} PUBLIC ..)
target_link_libraries(${TARGET_NAME}
    Qt6::Core
)