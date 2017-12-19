file(GLOB SRCS *.cpp)

add_executable(testAVLTree ${SRCS} ../AVLTree/library.h ../AVLTree/library.cpp)

target_link_libraries(testAVLTree
        gtest
        gmock
        )

include_directories("..")

install(TARGETS testAVLTree DESTINATION bin)