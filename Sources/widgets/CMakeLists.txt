###############################################################################
##########          MINIMUM REQUIREMENTS (some need to be BEFORE project command)
###############################################################################

###############################################################################
##########          REQUIREMENTS + GLOBAL DEFINITION
###############################################################################
set(TARGET_NAME widgets)


set(${TARGET_NAME}_SOURCES
dashboard.cpp
dashboard.h
mainwindow.cpp
mainwindow.h
tabmodel.cpp
tabmodel.h
tabwidget.cpp
tabwidget.h
taskdialog.cpp
taskdialog.h
taskmanagement.cpp
taskmanagement.h
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
    Qt6::Widgets
)