cmake_minimum_required(VERSION 3.14)
project(code)

set(CMAKE_CXX_STANDARD 14)

add_executable(code Basic/basic.cpp
        Basic/evalstate.cpp Basic/evalstate.h
        Basic/exp.cpp Basic/exp.h
        Basic/parser.h Basic/parser.cpp
        Basic/program.cpp Basic/program.h
        Basic/statement.cpp Basic/statement.h
        StanfordCPPLib/error.cpp StanfordCPPLib/error.h
        StanfordCPPLib/simpio.cpp StanfordCPPLib/simpio.h
        StanfordCPPLib/tokenscanner.cpp StanfordCPPLib/tokenscanner.h
        StanfordCPPLib/strlib.cpp StanfordCPPLib/strlib.h
        )