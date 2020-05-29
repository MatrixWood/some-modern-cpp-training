project(test)
cmake_minimum_required(VERSION 3.0)

FIND_PACKAGE( Boost 1.65 COMPONENTS program_options REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

ADD_EXECUTABLE( test test.cpp )

#TARGET_LINK_LIBRARIES( test LINK_PUBLIC ${Boost_LIBRARIES} )
