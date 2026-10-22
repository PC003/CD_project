cmake_minimum_required(VERSION 3.10)
project(NLOpt CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

# Check for LLVM (Optional)
find_package(LLVM CONFIG)
if(LLVM_FOUND)
    message(STATUS "LLVM found. Building with LLVM backend support.")
    add_definitions(${LLVM_DEFINITIONS})
    include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})
    llvm_map_components_to_libnames(llvm_libs core irreader support)
    set(NLOPT_HAS_LLVM 1)
else()
    message(STATUS "LLVM not found. Building with demo backend only.")
    set(NLOPT_HAS_LLVM 0)
    set(llvm_libs "")
endif()

add_definitions(-DNLOPT_HAS_LLVM=${NLOPT_HAS_LLVM})

include_directories(src src/parser src/ast src/semantic src/rule_ir src/optimizer src/backend src/validation)

# Generate Lexer and Parser
BISON_TARGET(Parser src/parser/parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.cpp COMPILE_FLAGS "-d")
FLEX_TARGET(Lexer src/lexer/lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.cpp)
ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Source files
set(SOURCES
    src/main.cpp
    src/ast/ast_printer.cpp
    src/semantic/checker.cpp
    src/rule_ir/rule_ir.cpp
    src/optimizer/matcher.cpp
    src/optimizer/rewriter.cpp
    src/backend/demo_backend.cpp
    src/validation/validator.cpp
    ${BISON_Parser_OUTPUTS}
    ${FLEX_Lexer_OUTPUTS}
)

if(LLVM_FOUND)
    list(APPEND SOURCES src/backend/llvm_backend.cpp)
endif()

add_executable(nlopt ${SOURCES})
if(LLVM_FOUND)
    target_link_libraries(nlopt PRIVATE ${llvm_libs})
endif()
