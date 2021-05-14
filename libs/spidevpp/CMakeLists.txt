set(TARGET_NAME spidevpp)

#
# set cmake settings
#
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#
# add source files to target
#
add_library(${TARGET_NAME}
	spi.cc
	spi.h
	gpio.cc
	gpio.h
)

#
# link against libs
#
target_link_libraries(${TARGET_NAME}
)

#
# add parent folder to targets include directories
#
target_include_directories(${TARGET_NAME}
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..
)
