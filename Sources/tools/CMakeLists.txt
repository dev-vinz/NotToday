###############################################################################
##########          MINIMUM REQUIREMENTS (some need to be BEFORE project command)
###############################################################################

###############################################################################
##########          REQUIREMENTS + GLOBAL DEFINITION
###############################################################################
set(TARGET_NAME tools)


set(${TARGET_NAME}_SOURCES
priorityqueue.cpp
priorityqueue.h
recurrence.h
task.cpp
task.h
taskstatus.h
timespan.h
timespan.cpp
todolist.cpp
todolist.h
utils.cpp
utils.h
)

set(${TARGET_NAME}_TESTS
${CMAKE_CURRENT_SOURCE_DIR}/tools_tests.cpp

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
