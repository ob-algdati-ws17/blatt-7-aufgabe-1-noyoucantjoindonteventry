file(GLOB SRCS *.cpp)

add_executable(testAVL ${SRCS} ../library/library.cpp ../library/library.h)

target_link_libraries(testAVL
        gtest
        gmock
        )

include_directories("..")

install(TARGETS testAVL DESTINATION bin)