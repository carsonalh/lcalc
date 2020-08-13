cmake_minimum_required (VERSION 3.8)
project (lambda_calculus VERSION 0.1.0 LANGUAGES C)

find_package ("rigid" REQUIRED)

add_library ("${PROJECT_NAME}"
        STATIC
            "lambda_calculus.h"
            "lambda_calculus_internal.h"
            "src/token.c"
            "src/tree.c"
)
target_include_directories ("${PROJECT_NAME}"
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
            $<INSTALL_INTERFACE:include>
)
target_link_libraries ("${PROJECT_NAME}" PRIVATE "rigid")

install (TARGETS "${PROJECT_NAME}" EXPORT "${PROJECT_NAME}Config"
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
)
install (FILES "lambda_calculus.h" DESTINATION include)
install (EXPORT "${PROJECT_NAME}Config"
        DESTINATION "lib/${PROJECT_NAME}_${${PROJECT_NAME}_VERSION}"
)

find_package ("pest" REQUIRED)

enable_testing ()

add_executable("${PROJECT_NAME}_token_test" "tests/token_test.c")
target_link_libraries ("${PROJECT_NAME}_token_test"
        PRIVATE
            "${PROJECT_NAME}"
            "rigid"
            "pest"
)
add_test (NAME "${PROJECT_NAME}_token_test" COMMAND "${PROJECT_NAME}_token_test")

add_executable ("${PROJECT_NAME}_tree_test" "tests/tree_test.c")
target_link_libraries ("${PROJECT_NAME}_tree_test" 
        PRIVATE
            "${PROJECT_NAME}"
            "pest"
)
add_test (NAME "${PROJECT_NAME}_tree_test" COMMAND "${PROJECT_NAME}_tree_test")

