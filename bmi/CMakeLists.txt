cmake_minimum_required(VERSION 2.6)

project (bmi)

set (BMI_VERSION 0.1)

#add_subdirectory (tests)

include(FindPkgConfig)
pkg_check_modules(GMODULE2 gmodule-2.0)
pkg_check_modules(GMODULE2 glib-2.0)
include_directories(${GMODULE2_INCLUDE_DIRS} ${GLIB2_INCLUDE_DIRS})
link_directories(${GMODULE2_LIBRARY_DIRS} ${GLIB2_LIBRARY_DIRS})

configure_file (${CMAKE_CURRENT_SOURCE_DIR}/bmic.pc.cmake
                ${CMAKE_CURRENT_SOURCE_DIR}/bmic.pc)

set (BUILD_SHARED_LIBS ON)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/.. )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

set (bmi_lib_SRCS bmi.c register.c)
add_library (bmic ${bmi_lib_SRCS} )

target_link_libraries(bmic ${GMODULE2_LIBRARIES} ${GLIB2_LIBRARIES})

########### Heat main ###############

#set (testing_sources ${bmi_lib_SRCS})
#add_executable (test_bmi ${testing_sources})

#target_link_libraries(test_bmi ${GMODULE2_LIBRARIES} ${GLIB2_LIBRARIES})
set (bmi_test_sources tester.c tests/test_info_funcs.c tests/test_time_funcs.c)
add_executable (bmi_tester ${bmi_test_sources})

target_link_libraries(bmi_tester ${GMODULE2_LIBRARIES} ${GLIB2_LIBRARIES} bmic)

########### Install files ###############

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/bmi_tester DESTINATION bin)
install(TARGETS bmic DESTINATION lib COMPONENT bmi)
install(FILES bmi.h bmilib.h
        DESTINATION include/bmi
        COMPONENT bmi)
install(FILES bmic.pc DESTINATION lib/pkgconfig)

#message("----------------------------------------")
#message("gmodule libraries: ${GMODULE2_LIBRARIES}")
#message("gmodule library dirs: ${GMODULE2_LIBRARY_DIRS}")
#message("----------------------------------------")
