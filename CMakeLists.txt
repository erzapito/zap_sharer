cmake_minimum_required (VERSION 2.6)
project (ZapSharer)

find_package(Boost 1.32 REQUIRED COMPONENTS system)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

add_executable(ZapSharer src/ZapSharer.cpp)
target_compile_features(ZapSharer PRIVATE cxx_range_for)
target_link_libraries(ZapSharer
	${Boost_SYSTEM_LIBRARY}
)

