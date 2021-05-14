set(TARGET_NAME loopback_example_app)


#
# set cmake settings
#
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


#
# add source files to target
#
add_executable(${TARGET_NAME}
	main.cc
)


#
# link against libs
#
target_link_libraries(${TARGET_NAME}
	spidevpp
	bcm2835
)
