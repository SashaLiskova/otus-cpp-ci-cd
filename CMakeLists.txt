cmake_minimum_required(VERSION 3.22.1) # current version on my ubuntu

# with cmake ..-DDPATCH_VERSION I can change  patch version locally, guthub actions does the same but adds build number

# set(PATCH_VERSION "1") - set value of PATCH_VERSION, it cannot be changed with  -DDPATCH_VERSION ( value from console stored in cache, but set(..) stores  in this run(locally?),
# and locall overwrites chache value)

# CACHE stores  PATCH_VERSION in cache, and we can ovewrride it from console with flag 
# INTERNAL - make value internal, so we can't wee it from GUI(never used gui..), prbably better to leave it internal

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version") 

#updates only patch version, I wonder how with ci/cd to handle minor and major verion
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

#verison.h.in uses it, project(..) automatically generates PROJECT_VERSION_MAJOR PROJECT_VERSION_MINOR PROJECT_VERSION_PATCH PROJECT_VERSION
project(helloworld VERSION ${PROJECT_VESRION}) 

#boost looks slightly confuing for me , for now and other projects I will switch to gtest due to familarity (and good for work )
option(WITH_GTEST_TEST "Whether to build GTest test" ON)

#configure the verion.h.in file 
# format configure_file(<input> <output> [COPYONLY] [ESCAPE_QUOTES] [@ONLY])
#so input and output file can be whater i want 
configure_file(version.h.in version.h)

add_executable(helloworld_cli main.cpp)
add_library(helloworld lib.cpp)

#will be used for other homeworks
set_target_properties(helloworld_cli helloworld PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

#inlcudes fiels from BINARY_DIR in helloworld, where our version.h will be generated
target_include_directories(helloworld
    PRIVATE "${CMAKE_BINARY_DIR}"
)

#links helloworld_cli wth lib  helloworld
target_link_libraries(helloworld_cli PRIVATE
    helloworld
)


#I guess it's adding compile flags to our target helloworld_cli (form microsoft and linux)
if (MSVC)
    target_compile_options(helloworld_cli PRIVATE
        /W4
    )
    target_compile_options(helloworld PRIVATE
        /W4
    )
else ()
    target_compile_options(helloworld_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(helloworld PRIVATE
        -Wall -Wextra -pedantic -Werror
    )

endif()

if(WITH_GTEST_TEST)
    add_subdirectory(tests)
endif()
           

#locally inslall just copied helloworld_cli target to other folder , was nnot allowed to bin, so I added helloworld_cli
#-DCMAKE_INSTALL_PREFIX that added prefix path and bin dir was created there
#everething that will be included in the package needs to be included here
install(TARGETS helloworld_cli RUNTIME DESTINATION bin)
#creste debian package
set(CPACK_GENERATOR DEB)
#sets the veriosn of package
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT alexandrabrsk7ls@gmail.com)
include(CPack)
#command make --build . --target package will create .deb package 


