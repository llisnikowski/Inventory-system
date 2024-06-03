find_program(PRECOMMIT pre-commit)

if(NOT PRECOMMIT)
    message(AUTHOR_WARNING "pre-commit was not found")
else()
    message(STATUS "pre-commit was found")
endif()