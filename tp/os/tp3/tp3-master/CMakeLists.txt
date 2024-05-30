cmake_minimum_required(VERSION 3.25.1)

# Our project can compile both C and C++
project(imageconvert C CXX)

# Create an executable target
add_executable(imageconvert
# Source file. You can add any here
    src/main.c
# List headers for IDEs
    include/stb_image_write.h
    include/stb_image.h
)
target_include_directories(imageconvert PRIVATE include/)

# On linux, we need to link the math library explicitely...
find_library(MATH_LIBRARY m)
if(MATH_LIBRARY)
    target_link_libraries(imageconvert PUBLIC ${MATH_LIBRARY})
endif()

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(imageconvert PRIVATE Threads::Threads)

target_compile_features(imageconvert PUBLIC c_std_11)

# Expose tests through the test target
enable_testing()

# We will execute tests directly in our target dir
set(TESTS_WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/workingdir)
# Create the output directory if it doesn't exist
file(MAKE_DIRECTORY ${TESTS_WORKING_DIRECTORY}/out)

add_test(NAME IC.furet
    COMMAND imageconvert images/furet.jpg
    WORKING_DIRECTORY ${TESTS_WORKING_DIRECTORY}
)
add_test(NAME IC.pandaroux
    COMMAND imageconvert images/pandaroux.jpg
    WORKING_DIRECTORY ${TESTS_WORKING_DIRECTORY}
)
add_test(NAME IC.lionsrock
    COMMAND imageconvert images/lionsrock.jpg
    WORKING_DIRECTORY ${TESTS_WORKING_DIRECTORY}
)
add_test(NAME IC.chat_et_chien
    COMMAND imageconvert images/chat.jpg images/chien.jpg
    WORKING_DIRECTORY ${TESTS_WORKING_DIRECTORY}
)
